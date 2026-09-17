#include "Clinic.h"
#include "Visit.h"
#include "VisitHistory.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

Clinic::Clinic() : patientCount(0), doctorCount(0) {}

Clinic::~Clinic() {
    for (int i = 0; i < patientCount; i++) delete patients[i];
    for (int i = 0; i < doctorCount; i++) delete doctors[i];
}

int Clinic::binarySearch(int id, int& comparisons) {
    comparisons = 0;
    int low = 0, high = patientCount - 1;
    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;
        if (patients[mid]->getId() == id) return mid;
        else if (patients[mid]->getId() < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int Clinic::findPatientIndex(int id) {
    int dummy;
    return binarySearch(id, dummy);
}

Doctor* Clinic::findDoctorById(int id) {
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i]->getId() == id) return doctors[i];
    }
    return nullptr;
}

Doctor* Clinic::findDoctorByName(string name) {
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i]->getName() == name) return doctors[i];
    }
    return nullptr;
}

void Clinic::addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        cout << "[X] Patient list is full.\n";
        return;
    }
    int id = readInt("ID    : ");
    if (findPatientIndex(id) != -1) {
        cout << "[X] Patient ID already exists.\n";
        return;
    }
    string name = readLine("Name  : ");
    int age = readInt("Age   : ");
    string phone = readLine("Phone : ");

    Patient* p = new Patient(id, name, age, phone);

    int pos = patientCount;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i]->getId() > id) { pos = i; break; }
    }
    for (int j = patientCount; j > pos; j--) {
        patients[j] = patients[j - 1];
    }
    patients[pos] = p;
    patientCount++;

    cout << "\n[OK] Patient " << id << " added.\n";
}

void Clinic::viewAllPatients() {
    if (patientCount == 0) {
        cout << "No patients.\n";
        return;
    }
    cout << "ID\tNAME\tAGE\tPHONE\n";
    for (int i = 0; i < patientCount; i++) {
        cout << *patients[i] << "\n";
    }
    cout << "\n" << patientCount << " patients.\n";
}

void Clinic::searchPatientById() {
    int id = readInt("Patient ID: ");
    int comparisons;
    int idx = binarySearch(id, comparisons);
    if (idx == -1) {
        cout << "[X] No patient with ID " << id << ".\n";
        return;
    }
    cout << "Found in " << comparisons << " comparisons [binary search]\n";
    patients[idx]->displayInfo();
    cout << "Visits : " << patients[idx]->getVisitCount() << "\n";
}

void Clinic::deletePatient() {
    int id = readInt("Patient ID: ");
    int idx = findPatientIndex(id);
    if (idx == -1) {
        cout << "[X] No patient with ID " << id << ".\n";
        return;
    }
    waitingRoom.removePatient(patients[idx]);
    delete patients[idx];
    for (int i = idx; i < patientCount - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patientCount--;
    cout << "[OK] Patient " << id << " deleted.\n";
}

void Clinic::viewPatientHistoryMenu() {
    int id = readInt("Patient ID: ");
    int idx = findPatientIndex(id);
    if (idx == -1) {
        cout << "[X] No patient with ID " << id << ".\n";
        return;
    }
    patients[idx]->printVisitHistory();
    cout << "Total paid: " << patients[idx]->getTotalPaid() << " EGP [recursive sum]\n";
}

void Clinic::sortPatients() {
    if (patientCount == 0) {
        cout << "No patients.\n";
        return;
    }
    int choice = readInt("Sort by (1) name  (2) age: ");

    Patient* temp[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) temp[i] = patients[i];

    int comparisons = 0;
    for (int i = 0; i < patientCount - 1; i++) {
        int best = i;
        for (int j = i + 1; j < patientCount; j++) {
            comparisons++;
            bool shouldSwap;
            if (choice == 1) shouldSwap = temp[j]->getName() < temp[best]->getName();
            else              shouldSwap = temp[j]->getAge() < temp[best]->getAge();
            if (shouldSwap) best = j;
        }
        if (best != i) {
            Patient* t = temp[i];
            temp[i] = temp[best];
            temp[best] = t;
        }
    }

    cout << "ID\tNAME\tAGE\n";
    for (int i = 0; i < patientCount; i++) {
        cout << temp[i]->getId() << "\t" << temp[i]->getName() << "\t" << temp[i]->getAge() << "\n";
    }
    cout << "\nSorted in " << comparisons << " comparisons [selection sort]\n";
}

void Clinic::addDoctor() {
    if (doctorCount >= MAX_DOCTORS) {
        cout << "[X] Doctor list is full.\n";
        return;
    }
    int id = readInt("ID             : ");
    if (findDoctorById(id) != nullptr) {
        cout << "[X] Doctor ID already exists.\n";
        return;
    }
    string name = readLine("Name           : ");
    string spec = readLine("Specialization : ");
    double fee = readDouble("Consult. Fee   : ");

    doctors[doctorCount] = new Doctor(id, name, spec, fee);
    doctorCount++;
    cout << "\n[OK] Doctor " << id << " added.\n";
}

void Clinic::viewAllDoctors() {
    if (doctorCount == 0) {
        cout << "No doctors.\n";
        return;
    }
    for (int i = 0; i < doctorCount; i++) {
        doctors[i]->displayInfo();
        cout << "-----\n";
    }
}

void Clinic::addToWaitingRoom() {
    int id = readInt("Patient ID : ");
    int idx = findPatientIndex(id);
    if (idx == -1) {
        cout << "[X] No patient with ID " << id << ".\n";
        return;
    }
    int choice = readInt("Case type   : (1) Emergency  (2) Normal\nChoose      : ");
    CaseType type = (choice == 1) ? EMERGENCY : NORMAL;

    bool ok = waitingRoom.addPatient(patients[idx], type);
    if (!ok) {
        cout << "[X] Waiting room is full.\n";
        return;
    }
    cout << "[OK] " << patients[idx]->getName() << " added as "
         << (type == EMERGENCY ? "EMERGENCY" : "NORMAL")
         << " at " << getCurrentTime() << ".\n";
}

void Clinic::viewWaitingRoom() {
    waitingRoom.view();
}

void Clinic::callNextPatient() {
    Patient* p;
    CaseType type;
    if (!waitingRoom.callNext(p, type)) {
        cout << "[X] No patients waiting.\n";
        return;
    }
    cout << ">>> NOW CALLING: " << p->getName()
         << " (" << (type == EMERGENCY ? "EMERGENCY" : "NORMAL") << ")\n";

    string docInput = readLine("Doctor (ID or Name) : ");
    Doctor* d = nullptr;

    bool isNum = !docInput.empty();
    for (size_t i = 0; i < docInput.size(); i++) {
        if (!isdigit(docInput[i])) { isNum = false; break; }
    }

    if (isNum) d = findDoctorById(atoi(docInput.c_str()));
    else       d = findDoctorByName(docInput);

    while (d == nullptr) {
        cout << "[X] No doctor found with that info.\n";
        docInput = readLine("Doctor (ID or Name) : ");
        isNum = !docInput.empty();
        for (size_t i = 0; i < docInput.size(); i++) {
            if (!isdigit(docInput[i])) { isNum = false; break; }
        }
        if (isNum) d = findDoctorById(atoi(docInput.c_str()));
        else       d = findDoctorByName(docInput);
    }

    string diagnosis = readLine("Diagnosis : ");

    Visit* v;
    if (type == EMERGENCY) v = new EmergencyVisit(getCurrentDate(), d->getName(), diagnosis);
    else                   v = new NormalVisit(getCurrentDate(), d->getName(), diagnosis);

    p->recordVisit(v);

    cout << "Fee: " << v->getFee() << " EGP ["
         << (type == EMERGENCY ? "EmergencyVisit::calculateFee" : "NormalVisit::calculateFee")
         << "]\n";
    cout << "[OK] Visit added to history. ";
    if (waitingRoom.isEmpty()) cout << "Waiting room is empty.\n";
    else cout << "Patients still waiting.\n";
}

void Clinic::patientMenu() {
    int choice;
    do {
        cout << "\n------------- PATIENTS ------------------\n"
             << "1. Add patient\n"
             << "2. View all patients\n"
             << "3. Search by ID\n"
             << "4. Delete patient\n"
             << "5. View patient history\n"
             << "6. Sort patients\n"
             << "0. Back\n"
             << "-----------------------------------------\n";
        choice = readInt("Choose: ");
        cout << "\n";
        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewAllPatients(); break;
            case 3: searchPatientById(); break;
            case 4: deletePatient(); break;
            case 5: viewPatientHistoryMenu(); break;
            case 6: sortPatients(); break;
            case 0: break;
            default: cout << "[X] Invalid choice.\n";
        }
    } while (choice != 0);
}

void Clinic::doctorMenu() {
    int choice;
    do {
        cout << "\n------------- DOCTORS -------------------\n"
             << "1. Add doctor\n"
             << "2. View all doctors\n"
             << "0. Back\n"
             << "-----------------------------------------\n";
        choice = readInt("Choose: ");
        cout << "\n";
        switch (choice) {
            case 1: addDoctor(); break;
            case 2: viewAllDoctors(); break;
            case 0: break;
            default: cout << "[X] Invalid choice.\n";
        }
    } while (choice != 0);
}

void Clinic::waitingRoomMenu() {
    int choice;
    do {
        cout << "\n---------- WAITING ROOM -----------------\n"
             << "1. Add to waiting room\n"
             << "2. View who is waiting\n"
             << "3. Call next patient\n"
             << "0. Back\n"
             << "-----------------------------------------\n";
        choice = readInt("Choose: ");
        cout << "\n";
        switch (choice) {
            case 1: addToWaitingRoom(); break;
            case 2: viewWaitingRoom(); break;
            case 3: callNextPatient(); break;
            case 0: break;
            default: cout << "[X] Invalid choice.\n";
        }
    } while (choice != 0);
}

void Clinic::mainMenu() {
    int choice;
    do {
        cout << "\n=========================================\n"
             << "        CLINIC MANAGEMENT SYSTEM\n"
             << "=========================================\n"
             << "1. Patients\n"
             << "2. Doctors\n"
             << "3. Waiting Room\n"
             << "0. Exit\n"
             << "-----------------------------------------\n";
        choice = readInt("Choose: ");
        switch (choice) {
            case 1: patientMenu(); break;
            case 2: doctorMenu(); break;
            case 3: waitingRoomMenu(); break;
            case 0: cout << "\nGoodbye.\n"; break;
            default: cout << "[X] Invalid choice.\n";
        }
    } while (choice != 0);
}
