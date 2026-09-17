#include "Utils.h"
#include <iostream>
#include <ctime>
#include <cstdio>

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[X] Invalid input. Please enter a whole number.\n";
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[X] Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(buf);
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%I:%M %p", ltm);
    return string(buffer);
}
