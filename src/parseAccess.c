/*************************************************************************
	> File Name: parseAccess.c
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 五  4/10 14:47:47 2015
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseAccess.h"
#include "cjson.h"

long get_file_size(FILE *stream){
	long curpos, length;
	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}

void string_trim(char *pstr){
	char *ptmp;
	ptmp = pstr;
	while('\0' != *pstr){
		if(' ' != *pstr || ' ' != *(pstr+1)){
			*ptmp++ = *pstr;
		}
		++pstr;
	}
	ptmp = '\0';
}

void string_trim_nt(char *pstr){
	char *ptmp;
	ptmp = pstr;
	while('\0' != *pstr){
		if('\t' != *pstr && '\n' != *pstr){
			*ptmp++ = *pstr;
		}
		++pstr;
	}
	ptmp = '\0';
}

char *substring(char *dst, char *src, int start, int len){
	char *p=dst;
	char *q=src;
	int length = strlen(src);
	if(start >= length || 0 > start) return NULL;
	if(len > length) len = length - start;
	q += start;
	while(len--)
	{
		*(p++) = *(q++);
	}
	*(p++) = '\0';
	return dst;
}

char *get_ngx_server_info(char *log_info){
	char *server_info = (char*)malloc(SERVER_INFO_LENGTH*sizeof(char));
	int i = 0;
	while('\0' != log_info){
		if('[' == *log_info){
			break;
		}
		else{
			i++;
		}
		++log_info;
	}
	log_info -= i;
	if(SERVER_INFO_LENGTH < i) i = SERVER_INFO_LENGTH;
	substring(server_info, log_info, 0, i);
	return server_info;
}

ngx_log_message parse_ngx_log(char *log_info){
	ngx_log_message nlog; 
	char *server_info = (char*)malloc(SERVER_INFO_LENGTH*sizeof(char));
	server_info = get_ngx_server_info(log_info);
	
	char *p;
	int i = 0;
	p = strtok(server_info, " ");
	strcpy(nlog.remote_addr, p);
	while(p){
		p = strtok(NULL," ");
		switch(i){
			case 0:
				strcpy(nlog.remote_user, p);
				break;
			case 1:
				nlog.status = atoi(p);
				break;
			case 2:
				nlog.body_byte_sent = atoi(p);
				break;
			case 3:
				//nlog.request_time = atof(p);
				strcpy(nlog.request_time, p);
				break;
			case 4:
				nlog.msec = (int)(atof(p));
				break;
			default:
				break;
		}
		i++;
	}

	i = 0;
	char *request_info =(char*)malloc(REQUEST_INFO_LENGTH*sizeof(char));
	p = strtok(log_info, "\"");
	while(p){
		p = strtok(NULL, "\"");
		if(0 == i){
			request_info = p;
		}
		else if(2 == i){
			strcpy(nlog.http_referer, p);
		}
		else if(3 == i){
			//strcpy(nlog.http_user_agent, p);
		}
		i++;
	}

	p = strtok(request_info, " ");
	strcpy(nlog.request_host, p);
	p = strtok(NULL, " ");
	strcpy(nlog.request_method, p);
	p = strtok(NULL, " ");
	strcpy(nlog.request_uri, p);
	return nlog;
}

char *json_encode(ngx_log_message nlog){
	char *pstr;
	char jstr[1024];
	pstr = jstr;
	/*
	cJSON *root,*fmt;
	root=cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type", "rect");
	cJSON_AddNumberToObject(fmt,"width", 1920);
	cJSON_AddNumberToObject(fmt,"height", 1080);
	cJSON_AddNumberToObject(fmt,"frame rate", 24);                                   
	jstr=cJSON_Print(root);                                                                                           
	printf("%s\n",jstr);
	*/
	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "remote_addr", nlog.remote_addr);
	cJSON_AddStringToObject(root, "remote_user", nlog.remote_user);
	cJSON_AddNumberToObject(root, "status", nlog.status);
	cJSON_AddNumberToObject(root, "body_byte_sent", nlog.body_byte_sent);
	cJSON_AddStringToObject(root, "request_time", nlog.request_time);
	cJSON_AddNumberToObject(root, "msec", nlog.msec);
	cJSON_AddStringToObject(root, "request_method", nlog.request_method);
	cJSON_AddStringToObject(root, "request_host", nlog.request_host);
	cJSON_AddStringToObject(root, "request_uri", nlog.request_uri);
	cJSON_AddStringToObject(root, "http_referer", nlog.http_referer);
	//strcpy(jstr, cJSON_Print(root));
	strcpy(jstr, cJSON_PrintUnformatted(root));
	//string_trim_nt(pstr);
	//printf("%s\n", pstr);
	return pstr;
}

/*
int main(){
	char str[] = "127.0.0.1 - 304 0 0.000 1428820478.224 [12/Apr/2015:14:34:38 +0800] \"GET / HTTP/1.1\" \"-\" \"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.122 Safari/537.36\" \"-\"";
	char *pstr = str;
	ngx_log_message nlog;
	nlog = parse_ngx_log(pstr);
	printf("%s,%s,%d,%d,%f,%d,%s,%s,%s\n", nlog.remote_addr, nlog.remote_user, nlog.status, nlog.body_byte_sent, nlog.request_time, nlog.msec, nlog.request_method, nlog.request_uri, nlog.http_referer);
	char *jstr = json_encode(nlog);
	return 0;
}
*/
