#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> // for toupper()

using namespace std;

// Abstract Base Class
class User {
public:
    virtual void login() = 0; // pure virtual function
};

// Admin Class
class Admin : public User {
public:
    void login() override {
        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (username == "admin" && password == "admin123") {
            cout << "Admin logged in successfully."<<endl;
        } else {
            cout << "Invalid user name or pass"<<endl;
            exit(0); // Exit program if login fails
        }
    }
    void viewResults() {
        ifstream inFile("data/score.txt");
        if (!inFile) {
            cerr << "Error opening file for reading." << endl;
            return;
        }
        string line;
        cout << "Results:\n";
        while (getline(inFile, line, '.')) {
            cout << line << endl;
            cout<< "-------------------" << endl;
        }
    }
};

// Student Class
class Student : public User {
public:
    string name;
    Student(string n) : name(n) {}
    void login() override {
        cout << "Student " << name << " logged in.\n";
    }
};

// Abstract Base Question Class
class Question {
public:
    virtual void ask() = 0;
    virtual char getCorrectAnswer() = 0;
    virtual ~Question() {} // Virtual destructor
};

// MCQ Class, Derived from Question
class MCQ : public Question {
    string text;
    char correctOption;
public:
    MCQ(string t, char c) : text(t), correctOption(toupper(c)) {}//constructor
    void ask() override {
        cout << text << endl;
    }
    char getCorrectAnswer() override {
        return correctOption;
    }
};

// Answer Class with Operator Overloading
class Answer {
    char ans;
public:
    Answer(char a) : ans(toupper(a)) {}
    bool operator==(const Answer& other) {
        return ans == other.ans;
    }
};

int main() {
    Student s("unknown");
    int user;
    cout << "Welcome to Online Examination System" << endl;
    cout << "1. Admin Login\n2. Student Login\nEnter your choice: ";
    cin >> user;

    if (user == 1) {
        Admin admin;
        admin.login();
        cout << "Admin Menu:\n";
        cout << "1. View Results\n2. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            admin.viewResults();
        } else {
            cout << "Exiting...\n";
            return 0;
        }
        return 0;
    } else if (user == 2) {
        // Student Login
        string studentName;
        cout << "Enter your name (single word): ";
        cin >> studentName;
        s =  Student(studentName);
        s.login();
    } else {
        cout << "Invalid choice!" << endl;
    }
    // Creating the quiz (MCQs only)
    vector<Question*> quiz;
    quiz.push_back(new MCQ("Q1: What is 2 + 2?\nA) 3\nB) 4\nC) 5", 'B'));
    quiz.push_back(new MCQ("Q2: Capital of France?\nA) London\nB) Paris\nC) Rome", 'B'));
    quiz.push_back(new MCQ("Q3: Which one is a programming language?\nA) Snake\nB) Python\nC) Cobra", 'B'));

    // Start the quiz
    char userInput;
    int score = 0;

    for (auto q : quiz) {
        q->ask();
        cout << "Your answer: ";
        cin >> userInput;

        Answer userAns(userInput);
        Answer correctAns(q->getCorrectAnswer());

        if (userAns == correctAns) {
            cout << "Correct!\n\n";
            score++;
        } else {
            cout << "Wrong!\n\n";
        }
    }

    // Save result to file
    ofstream outFile("data/score.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }
    outFile << "Student: " << s.name << endl;
    outFile << "Score: " << score << " out of " << quiz.size() << "."<< endl;
    outFile.close();

    cout << "Your score has been saved to score.txt\n";

    // Free memory because we use new
    for (auto q : quiz) {
        delete q;
    }

    return 0;
}