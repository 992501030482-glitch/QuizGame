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
  int questions() {
  int score = 0;
  char question[][100]={">>>   1. Who is the founder of Microsoft? ",
                        ">>>   2. Who is considered the father of the World Wide Web? ",
                        ">>>   3. What programming language was developed by James Gosling at Sun Microsystems? "};

  char Options[][100]={"          A. Steve Jobs","          B. Bill Gates" , "          C. Mark Zuckerberg", "          D. Larry Page",
                       "          A. Bill Gates", "          B. Tim Berners-Lee", "          C. Steve Jobs", "          D. Larry Page",
                       "          A. Java", "          B. Python", "          C. Ruby", "          D. C#"};

  char answer[3]={'B','B','A'};
  char guess;

  for(int i = 0; i < 3; i++){
    printf("%s\n\n", question[i]);

    for(int j=(i*4); j < (i*4)+4; j++){
      printf("%s\n\n", Options[j]);
    }

    printf("Enter your answer: ");
    scanf(" %c", &guess);
    printf("\n");

    guess = toupper((unsigned char)guess);

    if (guess == answer[i]){
      printf(">> Correct!\n\n");
      score++;
    } else {
      printf("\033[22;31m>> Wrong!\033[0m\n\n");
    }
  }
  printf("****************************************************\n");
  printf("Your score is %d out of 3.\n", score);
  printf("****************************************************\n\n");
  return score;
}


  return EXIT_SUCCESS;
}