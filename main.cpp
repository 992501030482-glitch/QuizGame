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
