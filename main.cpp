#include <iostream>
#include <fstream>
using namespace std;
struct Student {
    string name;
    int exams = 0;
    int* ball = new int[exams];
};
class file_open_error{
public:
    file_open_error() = default;
    static int file_close(bool a){
        try {
            if (a) {
                throw "file is not open";
            }
        }
        catch (const char* exc) {
            cerr << exc << endl;
            return 1;
        }
        return 0;
    }
};
class file_write_error{
public:
    file_write_error() = default;
    static int file_write(bool a){
        try {
            if (a) {
                    throw "file is empty";
                }
        }
        catch (const char* exc) {
            cerr << exc << endl;
            return 1;
        }
        return 0;
    }
};
class file_read_error{
public:
    file_read_error() = default;
    static int file_read(bool a){
        try {
            if (a) {
                    throw "mistake read of file";
                }
        }
        catch (const char* exc) {
            cerr << exc << endl;
            return 1;
        }
        return 0;
    }
};

int main() {
    int n;
    string name;
    int exams;
    cout << "Number of students: "; cin >> n;
    fstream f1((R"(C:\Users\Xiaomi\CLionProjects\exceptions\Students.txt)"),ios::out);
    file_open_error::file_close(f1.fail());
    if (f1) {
        cout << "Data about students: " << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Name of student: "; cin >> name; cout << "Number of exams: "; cin >> exams;
            int* ball = new int[exams];
            cout << "Ball: ";
            for (int j = 0; j < exams; ++j) {
                cin >> ball[j];
            }
            f1 << name << " " << exams;
            file_write_error::file_write(f1.fail());
            for (int j = 0; j < exams; ++j) {
                f1 << " " << ball[j];
                file_write_error::file_write(f1.fail());
            }
            f1 << endl;
            file_write_error::file_write(f1.fail());
            delete[]ball;
        }
    }
    f1.close();
    fstream f2((R"(C:\Users\Xiaomi\CLionProjects\exceptions\Student.txt)"),ios::in);
    Student* a = new Student[n];
    file_open_error::file_close(f2.fail());
    if (f2.is_open()) {
            for (int i = 0; i < n; ++i) {
                f2 >> a[i].name >> a[i].exams;
                file_read_error::file_read(f2.fail());
                for (int j = 0; j < a[i].exams; ++j) {
                    f2 >> a[i].ball[j];
                    file_read_error::file_read(f2.fail());
                }
            }
        }
    f2.close();
    double avgG = 0;
    double * avgS = new double [n]{};
    for (int i = 0; i < n; ++i) {
        int k = 0;
        for (int j = 0; j < a[i].exams; ++j) {
            if (a[i].ball[j] > 2) {
                k++;
                avgS[i] += a[i].ball[j];
            }
        }
        avgS[i] /= k;
    }
    for (int i = 0; i < n; ++i) {
        avgG += avgS[i];
    }
    avgG /= n;
    f1.open((R"(C:\Users\Xiaomi\CLionProjects\exceptions\Student.txt)"),ios::out);
    int b = 0;
    file_open_error::file_close(f1.fail());
    if (f1) {
        for (int i = 0; i < n; ++i) {
            if (avgS[i] > avgG) {
                f1 << a[i].name << " " << a[i].exams;
                file_write_error::file_write(f1.fail());
                for (int j = 0; j < a[i].exams; ++j) {
                    f1  << " " << a[i].ball[j];
                    file_write_error::file_write(f1.fail());
                }
                b++;
            }
        }
    }
    f1.close();
    f2.open((R"(C:\Users\Xiaomi\CLionProjects\exceptions\Student.txt)"),ios::in);
    file_open_error::file_close(f2.fail());
    if (f2.is_open()) {
            for (int i = 0; i < b; ++i) {
                f2 >> a[i].name >> a[i].exams;
                file_read_error::file_read(f2.fail());
                for (int j = 0; j < a[i].exams; ++j) {
                    f2 >> a[i].ball[j];
                    file_read_error::file_read(f2.fail());
                }
            }
        }
    for (int i = 0; i < b; ++i) {
        cout << a[i].name << " " << a[i].exams << " ";
        for (int j = 0; j < exams; ++j) {
            cout << a[i].ball[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
