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

int user_Entry(MYSQL *conn, const char *server, const char *user, const char *password, const char *database, int n) {
  char na[100];

  if(mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
    printf("Error with input password: %s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
  } else {
    printf("Successful\n");
  }

  if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS quiz")) {
    printf("DATABASE check/creation failed\n");
  } else {
    printf("DATABASE active\n");
  }

  mysql_query(conn, "USE quiz");
  mysql_query(conn, "DROP TABLE IF EXISTS score");

  char *create_table_query =
        "CREATE TABLE IF NOT EXISTS score ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "name VARCHAR(100) NOT NULL, "
        "score INT DEFAULT 0, "
        "time DECIMAL(10,1) DEFAULT 0.0"
        ") ENGINE=InnoDB;";

  mysql_query(conn, create_table_query);

  char query[512];
  printf("Enter the names : \n");

  for (int i = 0; i < n; i++) {
    printf("Enter name of player %d: ", i + 1);
    fgets(na, sizeof(na), stdin);
    na[strcspn(na, "\n")] = '\0';

    sprintf(query, "INSERT INTO score(name) VALUES ('%s');", na);
    mysql_query(conn, query);
  }

  return EXIT_SUCCESS;
}