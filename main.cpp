#include<mysql/mysql.h>
#include<iostream>
#include <cstring>
#include <sys/time.h>
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
};

class TimedQuizGame : public QuizGame {
public:
    void startQuiz(int n) {
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[256];

        for (int i = 0; i < n; i++) {
            mysql_query(conn, "SELECT id,name FROM score");
            res = mysql_store_result(conn);

            cout << "\nPlayers:\n";
            while ((row = mysql_fetch_row(res))) {
                cout << row[0] << ". " << row[1] << endl;
            }
            mysql_free_result(res);

            int choice;
            cout << "Choose player number: ";
            cin >> choice;

            sprintf(query, "SELECT name FROM score LIMIT 1 OFFSET %d", choice - 1);
            mysql_query(conn, query);

            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            string name = row[0];
            mysql_free_result(res);

            cout << "\nReady " << name << "? (y/n): ";
            char ch;
            cin >> ch;

            struct timeval start, end;
            gettimeofday(&start, NULL);

            int score = 0;
            if (ch == 'y') {
                score = askQuestions(); // inherited method
            }

            gettimeofday(&end, NULL);

            double time_taken =
                (end.tv_sec - start.tv_sec) +
                (end.tv_usec - start.tv_usec) / 1000000.0;

            sprintf(query,
                "UPDATE score SET score=%d, time=%.2f WHERE name='%s'",
                score, time_taken, name.c_str());

            mysql_query(conn, query);
        }
    }

    void leaderboard() {
        MYSQL_RES *res;
        MYSQL_ROW row;

        mysql_query(conn,
            "SELECT name,score,time FROM score ORDER BY score DESC, time ASC");

        res = mysql_store_result(conn);

        cout << "\nLeaderboard:\n";
        int rank = 1;

        while ((row = mysql_fetch_row(res))) {
            cout << rank++ << ". "
                 << row[0] << " | Score: " << row[1]
                 << " | Time: " << row[2] << endl;
        }

        mysql_free_result(res);
    }
};

int main() {
    
  const char *server = "localhost";
  const char *user = "yourMySQLUsername";
  const char *password = "yourMySQLPassword";

  TimedQuizGame game;

    if (!game.connect(server, user, password, NULL)) {
        return 1;
    }

    int n;
    cout << "Enter number of players: ";
    cin >> n;

    game.setupDatabase();
    game.addPlayers(n);
    game.startQuiz(n);
    game.leaderboard();
    
  Database db;
  if(db.connect(server, user, password, NULL)) {
    cout << "Success" << endl;
  }

  return 0;
}
