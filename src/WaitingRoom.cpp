#include "WaitingRoom.h"
#include <iostream>

WaitingRoom::WaitingRoom() : size(0) {}

bool WaitingRoom::isFull() const { return size >= MAX_WAITING; }
bool WaitingRoom::isEmpty() const { return size == 0; }

void WaitingRoom::removePatient(Patient* p) {
    for (int i = 0; i < size; i++) {
        if (entries[i].patient == p) {
            for (int j = i; j < size - 1; j++) {
                entries[j] = entries[j + 1];
            }
            size--;
            i--;
        }
    }
}

bool WaitingRoom::addPatient(Patient* p, CaseType type) {
    if (isFull()) return false;

    int pos = size;
    for (int i = 0; i < size; i++) {
        if (entries[i].caseType > type) {
            pos = i;
            break;
        }
    }
    for (int j = size; j > pos; j--) {
        entries[j] = entries[j - 1];
    }
    entries[pos].patient = p;
    entries[pos].caseType = type;
    entries[pos].arrivalTime = getCurrentTime();
    size++;
    return true;
}

void WaitingRoom::view() const {
    if (isEmpty()) {
        cout << "No patients waiting.\n";
        return;
    }
    cout << "#\tPATIENT\t\tCASE\t\tARRIVED\n";
    for (int i = 0; i < size; i++) {
        cout << (i + 1) << "\t"
             << entries[i].patient->getName() << "\t\t"
             << (entries[i].caseType == EMERGENCY ? "EMERGENCY" : "NORMAL") << "\t"
             << entries[i].arrivalTime << "\n";
    }
}

bool WaitingRoom::callNext(Patient*& outPatient, CaseType& outType) {
    if (isEmpty()) return false;
    outPatient = entries[0].patient;
    outType = entries[0].caseType;
    for (int i = 0; i < size - 1; i++) {
        entries[i] = entries[i + 1];
    }
    size--;
    return true;
}
