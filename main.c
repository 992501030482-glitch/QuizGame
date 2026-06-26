#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <ctype.h>

int user_Entry(MYSQL *conn, const char *server, const char *user, const char *password, const char *database, int n);
int user_Quiz(MYSQL *conn, const char *server, const char *user, const char *password, const char *database, int len);
void about(const char *name);
void leaderboard(MYSQL *conn);
int questions();

