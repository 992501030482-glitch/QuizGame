int main() {
  MYSQL *conn;
  const char *server = "localhost";
  const char *user = "root";
  char password[20];
  const char *database = NULL;

  conn = mysql_init(NULL);

  printf("Enter the password : ");
  scanf("%19s", password);

  printf("Enter the no of players participating : ");
  int n;
  scanf("%d", &n);
  getchar();

  user_Entry(conn, server, user, password, database, n);
  user_Quiz(conn, server, user, password, database, n);
  leaderboard(conn);

  mysql_close(conn);
  return EXIT_SUCCESS;
}