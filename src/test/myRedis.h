/*************************************************************************
	> File Name: myRedis.h
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 四  5/14 13:31:00 2015
 ************************************************************************/

#include <hiredis.h>

#define REDIS_REPLY_STRING 1
#define REDIS_REPLY_ARRAY 2
#define REDIS_REPLY_INTEGER 3
#define REDIS_REPLY_NIL 4
#define REDIS_REPLY_STATUS 5
#define REDIS_REPLY_ERROR 6

/*check connection active*/
int check_redis_connection(redisContext *conn);

/*connection to redis server*/
redisContext *get_redis_connection(char *host, int port);

/*set*/
void redis_set(redisContext *conn, char *rkey, char *rvalue);

/*get*/
char *redis_get(redisContext *conn, char *rkey);

/*lpush*/
long redis_lpush(redisContext *conn, char*list, char *data);

/*rpush*/
long redis_rpush(redisContext *conn, char *list, char *data);

/*lpop*/
char *redis_lpop(redisContext *conn, char *list);

/*rpop*/
char *redis_rpop(redisContext *conn, char *list);

/*blpop*/
char *redis_blpop(redisContext *conn, char *list, int timeout);

/*brpop*/
char *redis_brpop(redisContext *conn, char *list, int timeout);
