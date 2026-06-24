#include<mysql/mysql.h>
#include<iostream>
using namespace std;

class Database {
  protected:
    MYSQL *conn;

  public:
    Database() {
      conn = mysql_init(NULL);
    }

    bool connect(const char *server, const char *user, const char *password, const char *db) {
      if (!mysql_real_connect(conn, server, user, password, db, 0, NULL, 0)) {
          cout << "Connection failed: " << mysql_error(conn) << endl;
          return false;
      }
      cout << "Connected successfully\n";
      return true;
    }

    MYSQL* getConn() {
      return conn;
    }

    ~Database() {
      mysql_close(conn);
    }
};

int main() {
  const char *server = "localhost";
  const char *user = "yourMySQLUsername";
  const char *password = "yourMySQLPassword";

  Database db;
  if(db.connect(server, user, password, NULL)) {
    cout << "Success" << endl;
  }
  return 0;
}
class QuizGame : public Database {
public:
    void setupDatabase() {
        mysql_query(conn, "CREATE DATABASE IF NOT EXISTS quiz");
        mysql_query(conn, "USE quiz");
        mysql_query(conn, "DROP TABLE IF EXISTS score");

        const char *query =
            "CREATE TABLE score ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(100), "
            "score INT, "
            "time DECIMAL(10,2))";

        mysql_query(conn, query);
    }

    void addPlayers(int n) {
        string name;
        char query[256];

        cin.ignore();

        for (int i = 0; i < n; i++) {
            cout << "Enter player " << i + 1 << ": ";
            getline(cin, name);

            sprintf(query, "INSERT INTO score(name) VALUES('%s')", name.c_str());
            mysql_query(conn, query);
        }
    }
}