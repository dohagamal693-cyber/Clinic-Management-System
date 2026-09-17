#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;

const int MAX_PATIENTS = 100;
const int MAX_DOCTORS  = 50;
const int MAX_WAITING  = 50;

enum CaseType { EMERGENCY = 0, NORMAL = 1 };

int readInt(const string& prompt);
double readDouble(const string& prompt);
string readLine(const string& prompt);
string getCurrentDate();
string getCurrentTime();

#endif
