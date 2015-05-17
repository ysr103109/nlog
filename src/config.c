/*************************************************************************
	> File Name: config.c
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 五  4/17 14:24:30 2015
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

hash_array get_key_value(char *line, char *flag){
	hash_array arr;
	char *p;
	//p = strtok(line, flag);
	p = strstr(line, flag);
	if(NULL != p){
		p = strtok(line, flag);
		strcpy(arr.hash_key, p);
		p = strtok(NULL, flag);
		arr.hash_value[strlen(arr.hash_key)-1] = '\0';
		strcpy(arr.hash_value, p);
		arr.hash_value[strlen(arr.hash_value)-1] = '\0';
	}
	else{
		arr.hash_key[0] = '\0';
		arr.hash_value[0] = '\0';
	}
	p = '\0';
	return arr;
}

nlog_config get_nlog_config(){
	nlog_config config;
	hash_array artmp;
	FILE *fp;
	char *p;
	if(NULL == (fp = fopen(NLOG_CONFIG_FILE_PATH, "r"))){
		printf("config file nlog.conf not found in \"%s\"!!\n", NLOG_CONFIG_FILE_PATH);
		config.code = -1;
		return config;
	}
	config.code = 0;
	char *keytmp;
	char *buf = (char*)malloc(LINE_LENGTH*sizeof(char));
	while(1){
		p = fgets(buf, LINE_LENGTH, fp);
		if(!p)
			break;
		artmp = get_key_value(buf, CONF_SPLIT_FLAG);
		if('\0' != artmp.hash_key[0]){
			//printf("%s\n",artmp.hash_key);
			keytmp = artmp.hash_key;
			if(0 == strcmp(keytmp, "access_log_path"))
				strcpy(config.access_log_path, artmp.hash_value);
			else if(0 == strcmp(keytmp, "redis_server_host"))
				strcpy(config.redis_server_host,artmp.hash_value);
			else if(0 == strcmp(keytmp, "redis_server_port"))
				config.redis_server_port = atoi(artmp.hash_value);
			else if(0 == strcmp(keytmp, "redis_db"))
				config.redis_db = atoi(artmp.hash_value);
			else if(0 == strcmp(keytmp, "redis_queue_name"))
				strcpy(config.redis_queue_name, artmp.hash_value);
		}
	}
	free(buf);
	buf = '\0';
	//printf("%s,%s,%d,%d,%s",config.access_log_path, config.redis_server_host, config.redis_server_port, config.redis_db, config.redis_queue_name);
	return config;
}
