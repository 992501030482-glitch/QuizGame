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
int main() {
  MYSQL *conn;
  const char *server = "localhost";
  const char *user = "root";
  char password[20];
  const char *database = NULL; // FIXED: Must be NULL, not uninitialized garbage

  conn = mysql_init(NULL);

  printf("Enter the password : ");
  scanf("%19s", password);

  printf("Enter the no of players participating : ");
  int n;
  scanf("%d", &n);
  getchar(); // Clears trailing newline

  user_Entry(conn, server, user, password, database, n);
  user_Quiz(conn, server, user, password, database, n);
  leaderboard(conn);

  mysql_close(conn);
  return EXIT_SUCCESS;
}