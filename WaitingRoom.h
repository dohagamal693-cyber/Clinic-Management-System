#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include "Utils.h"
#include "Person.h"
#include <string>
using namespace std;

struct WaitingEntry {
    Patient* patient;
    CaseType caseType;
    string arrivalTime;
};

class WaitingRoom {
private:
    WaitingEntry entries[MAX_WAITING];
    int size;
public:
    WaitingRoom();

    bool isFull() const;
    bool isEmpty() const;

    void removePatient(Patient* p);
    bool addPatient(Patient* p, CaseType type);
    void view() const;
    bool callNext(Patient*& outPatient, CaseType& outType);
};

#endif
