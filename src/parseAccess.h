/*************************************************************************
	> File Name: parseAccess.h
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 五  4/10 14:47:47 2015
 ************************************************************************/

#ifndef PARSE_ACCESS_H

#define NLOG_ACCESS_PATH "/usr/local/homebrew/Cellar/nginx/1.6.3/logs/access.log"
#define SERVER_INFO_LENGTH 128
#define REQUEST_INFO_LENGTH 128
#define REMOTE_ADDR_LENGTH 32
#define REMOTE_USER_LENGTH 32
#define REQUEST_HOST_LENGTH 64
#define REQUEST_URI_LENGTH 64
#define HTTP_REFERER_LENGTH 128
#define HTTP_USER_AGENT_LENGTH 64

typedef struct ngx_log_message{
	char remote_addr[REMOTE_ADDR_LENGTH];
	char remote_user[REMOTE_USER_LENGTH];
	int msec;
	char request_method[16];
	char request_host[REQUEST_HOST_LENGTH];
	char request_uri[REQUEST_URI_LENGTH];
	int status;
	int body_byte_sent;
	char http_referer[HTTP_REFERER_LENGTH];
	char http_user_agent[HTTP_USER_AGENT_LENGTH];
	char request_time[16];
}ngx_log_message;

/*get the file length*/
long get_file_size(FILE *stream);

/*remove extra space in string */
void string_trim(char *pstr);

/*remove tab and enter in string */
void string_trim_nt(char *pstr);

/*get a string from another string */
char *substring(char *dst, char *src, int start, int len);

/*split ngx server info from a log */
char *get_ngx_server_info(char *log_info);

/*parse an ngx log into needed fomat */
ngx_log_message parse_ngx_log(char *log_info);

/*translate string into json string */
char *json_encode(ngx_log_message nlog);

#endif


