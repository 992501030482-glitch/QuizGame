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
};
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
    virtual int askQuestions() {
	    int score = 0;
	    char guess;

	    char question[][100] = {
		">>>   1. Who is the founder of Microsoft?",
		">>>   2. Who is considered the father of the World Wide Web?",
		">>>   3. What programming language was developed by James Gosling at Sun Microsystems?"
	    };

	    char Options[][100] = {
		"          A. Steve Jobs",
		"          B. Bill Gates",
		"          C. Mark Zuckerberg",
		"          D. Larry Page",

		"          A. Bill Gates",
		"          B. Tim Berners-Lee",
		"          C. Steve Jobs",
		"          D. Larry Page",

		"          A. Java",
		"          B. Python",
		"          C. Ruby",
		"          D. C#"
	    };

	    char answer[3] = {'B', 'B', 'A'};

	    for (int i = 0; i < 3; i++) {

		printf("\n%s\n\n", question[i]);

		for (int j = (i * 4); j < (i * 4) + 4; j++) {
		    printf("%s\n", Options[j]);
		}

		printf("\nEnter your answer: ");
		cin >> guess;

		guess = toupper((unsigned char)guess);

		if (guess == answer[i]) {
		    printf("\n>> Correct!\n");
		    score++;
		} else {
		    printf("\n>> Wrong!\n");
		}
	    }

	    printf("\n****************************************************\n");
	    printf("Your score is %d out of 3.\n", score);
	    printf("****************************************************\n\n");

	    return score;
	}
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
