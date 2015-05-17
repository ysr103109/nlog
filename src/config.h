/*************************************************************************
	> File Name: config.h
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 五  4/17 15:25:44 2015
 ************************************************************************/

#define NLOG_CONFIG_FILE_PATH "config/nlog.conf"
#define CONF_SPLIT_FLAG "="
#define ACCESS_LOG_PATH_LENGTH 128
#define REDIS_SERVER_HOST_LENGTH 64
#define REDIS_QUEUE_NAME_LENGTH 32
#define LINE_LENGTH 1024 

typedef struct nlog_config{
	char access_log_path[ACCESS_LOG_PATH_LENGTH];
	char redis_server_host[REDIS_SERVER_HOST_LENGTH];
	char redis_queue_name[REDIS_QUEUE_NAME_LENGTH];
	int redis_server_port;
	int redis_db;
	int code;
}nlog_config;

typedef struct hash_array{
	char hash_key[32];
	char hash_value[64];
}hash_array;

/*parse each line in config file*/
hash_array get_key_value(char *line, char *flag);

/*parse config file and translate into needed format*/
nlog_config get_nlog_config();
