/*************************************************************************
	> File Name: redis.c
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 日  4/19 14:36:30 2015
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hiredis.h>
#include "myRedis.h"

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

void redis_set(redisContext *conn, char *rkey, char *rvalue){
	if(0 == check_redis_connection(conn)){
		return;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "set %s %s", rkey, rvalue);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	freeReplyObject(reply);
	cmd = '\0';
}

char *redis_get(redisContext *conn, char *rkey){
	if(0 == check_redis_connection(conn)){
		return NULL;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "get %s", rkey);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(1 != reply->type){
		return NULL;
	}
	return reply->str;
}

long redis_lpush(redisContext *conn, char*list, char *data){
	if(0 == check_redis_connection(conn)){
		return 0;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "lpush %s %s", list, data);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(3 != reply->type){
		return 0;
	}
	return reply->integer;
}

long redis_rpush(redisContext *conn, char *list, char *data){
	if(0 == check_redis_connection(conn)){
		return 0;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "rpush %s %s", list, data);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(3 != reply->type){
		return 0;
	}
	return reply->integer;
}

char *redis_lpop(redisContext *conn, char *list){
	if(0 == check_redis_connection(conn)){
		return NULL;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "lpop %s", list);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(1 != reply->type){
		return NULL;
	}
	return reply->str;
}

char *redis_rpop(redisContext *conn, char *list){
	if(0 == check_redis_connection(conn)){
		return NULL;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "rpop %s", list);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(1 != reply->type){
		return NULL;
	}
	return reply->str;
}

char *redis_blpop(redisContext *conn, char *list, int timeout){
	if(0 == check_redis_connection(conn)){
		return NULL;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "blpop %s %d", list, timeout);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(2 != reply->type){
		return NULL;
	}
	return reply->element[1]->str;
}

char *redis_brpop(redisContext *conn, char *list, int timeout){
	if(0 == check_redis_connection(conn)){
		return NULL;
	}
	char *cmd = (char*)malloc(512*sizeof(char));
	sprintf(cmd, "brpop %s %d", list, timeout);
	redisReply *reply = (redisReply*)redisCommand(conn, cmd);
	free(cmd);
	cmd = '\0';
	if(2 != reply->type){
		return NULL;
	}
	return reply->element[1]->str;
}
/*
int main(){
	redisContext *conn = get_redis_connection("127.0.0.1", 6379);
	printf("%ld\n", redis_rpush(conn, "storm_message", "etet"));
	printf("%s", redis_blpop(conn, "storm_message", 1));
	char *head = "set ";
	char *mid = "foo ";
	char *rear = "1234333";
	char *str = (char*)malloc(512*sizeof(char));
	sprintf(str, "%s%s%s", head, mid, rear);
	printf("%s\n", str);

	if(NULL != conn && conn->err){
		printf("connection error");
		return 0;
	}
	redisReply *reply = (redisReply*)redisCommand(conn, str);
	freeReplyObject(reply);
	redisContext *conn  = redisConnect("127.0.0.1",6379);
	if(conn != NULL && conn->err){   
		printf("connection error: %s\n",conn->errstr); 
		return 0; 
	}   
	redisReply *reply = (redisReply*)redisCommand(conn,"set foo 1234"); 
	freeReplyObject(reply); 

	reply = redisCommand(conn,"get foo"); 
	printf("%s\n",reply->str); 
	freeReplyObject(reply);
	redisFree(conn); 
	return 0;
}
*/
