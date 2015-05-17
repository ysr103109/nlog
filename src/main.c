/*************************************************************************
	> File Name: parseAccess.c
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 五  4/10 10:00:23 2015
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <hiredis.h>
#include "parseAccess.h"
#include "queue.h"
#include "config.h"
#define THREAD_LENGTH 1

int check_redis_connection(redisContext *conn){
    if(NULL != conn && conn->err){
        return 0;
    }   
    return 1;
}

redisContext *get_redis_connection(char *host, int port){
    redisContext *conn = redisConnect(host, port);
    return conn;
}

long redis_rpush(redisContext *conn, char *list, char *data){
    if(0 == check_redis_connection(conn)){
        return 0;
    }   
    char *cmd = (char*)malloc(512*sizeof(char));
    sprintf(cmd, "rpush %s %s", list, data);
    redisReply *reply = (redisReply*)redisCommand(conn, cmd);
    cmd = '\0';
    if(3 != reply->type){
        return 0;
    }   
	return reply->integer;
}

void *thread_task(void *pqueue){
	nlog_config config = get_nlog_config();
	if(-1 == config.code){
		return 0;
	}
	redisContext *conn = get_redis_connection(config.redis_server_host, config.redis_server_port);
	char *data;
	while(1){
		data = lpopQueue(pqueue);
		if(NULL != data){
			printf("%s\n",data);
			redis_rpush(conn, config.redis_queue_name, data);
		}
	}
}

int main(int argc, char *argv[]){
	/*get some argvs in config file*/
	nlog_config config = get_nlog_config();
	//printf("%s,%s,%d,%d,%s", config.access_log_path, config.redis_server_host, config.redis_server_port, config.redis_db, config.redis_queue_name);
	if(-1 == config.code){
		return 0;
	}

	/*create a queue for log message*/
	Queue *pq = InitQueue();

	/*create some threads for mq writing*/
	pthread_t thread[THREAD_LENGTH];
	int i;
	for(i=0;i<THREAD_LENGTH;i++){
		pthread_create(&thread[i],NULL, thread_task, (void *)pq);
	}

	char *filepath = "a.txt";
	FILE *fp;
	long len,lastlen = 0;
	/*listen the target file*/
	while(1){
		fp = fopen(config.access_log_path,"r");
		if(NULL == fp){
			printf("file access.log not found in \"%s\"\n", config.access_log_path);
			return 0;
		}
		len = get_file_size(fp);
		if(len <= lastlen){
			fclose(fp);
			continue;
		}
		char *buf;
		buf = (char*)malloc((len-lastlen+1)*sizeof(char));
		fseek(fp, lastlen, SEEK_SET);
		fread(buf,1,len-lastlen+1,fp);
		if(0 != lastlen){
			ngx_log_message nlog;
			nlog = parse_ngx_log(buf);
			//printf("%s,%s,%d,%d,%s,%d,%s,%s,%s,%s\n", nlog.remote_addr, nlog.remote_user, nlog.status, nlog.body_byte_sent, nlog.request_time, nlog.msec, nlog.request_method, nlog.request_host, nlog.request_uri, nlog.http_referer);
			char *jstr = json_encode(nlog);
			EnQueue(pq, jstr);
		}
		lastlen = len;
		free(buf);
		fclose(fp);
	}
	return 0;
}


