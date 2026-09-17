#ifndef CLINIC_H
#define CLINIC_H

#include "Utils.h"
#include "Person.h"
#include "WaitingRoom.h"
#include <string>
using namespace std;

class Clinic {
private:
    Patient* patients[MAX_PATIENTS];
    int patientCount;
    Doctor* doctors[MAX_DOCTORS];
    int doctorCount;
    WaitingRoom waitingRoom;

    int binarySearch(int id, int& comparisons);
    int findPatientIndex(int id);
    Doctor* findDoctorById(int id);
    Doctor* findDoctorByName(string name);

public:
    Clinic();
    ~Clinic();

    void addPatient();
    void viewAllPatients();
    void searchPatientById();
    void deletePatient();
    void viewPatientHistoryMenu();
    void sortPatients();

    void addDoctor();
    void viewAllDoctors();

    void addToWaitingRoom();
    void viewWaitingRoom();
    void callNextPatient();

    void patientMenu();
    void doctorMenu();
    void waitingRoomMenu();
    void mainMenu();
};

#endif
