#include "Person.h"
#include "VisitHistory.h"
#include "Visit.h"

Person::Person(int id, string name) : id(id), name(name) {}
Person::~Person() {}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
void Person::setName(string n) { name = n; }

Patient::Patient(int id, string name, int age, string phone)
    : Person(id, name), age(age), phone(phone), history(nullptr) {}

Patient::~Patient() {
    delete history;
}

int Patient::getAge() const { return age; }
string Patient::getPhone() const { return phone; }
void Patient::setAge(int a) { if (a >= 0 && a <= 130) age = a; }
void Patient::setPhone(string p) { phone = p; }

void Patient::displayInfo() const {
    cout << "ID    : " << id << "\n"
         << "Name  : " << name << "\n"
         << "Age   : " << age << "\n"
         << "Phone : " << phone << "\n";
}

void Patient::recordVisit(Visit* v) {
    if (history == nullptr) {
        history = new VisitHistory();
    }
    history->addVisit(v);
}

void Patient::printVisitHistory() const {
    cout << "VISIT HISTORY - " << name << "\n";
    if (history == nullptr) {
        cout << "No visits recorded.\n";
        return;
    }
    history->printHistory();
}

double Patient::getTotalPaid() const {
    if (history == nullptr) return 0.0;
    return history->getTotalPaid();
}

int Patient::getVisitCount() const {
    if (history == nullptr) return 0;
    return history->getVisitCount();
}

ostream& operator<<(ostream& out, const Patient& p) {
    out << p.id << "\t" << p.name << "\t" << p.age << "\t" << p.phone;
    return out;
}

Doctor::Doctor(int id, string name, string specialization, double fee)
    : Person(id, name), specialization(specialization), consultationFee(fee) {}
Doctor::~Doctor() {}

string Doctor::getSpecialization() const { return specialization; }
double Doctor::getConsultationFee() const { return consultationFee; }
void Doctor::setSpecialization(string s) { specialization = s; }
void Doctor::setConsultationFee(double f) { if (f >= 0) consultationFee = f; }

void Doctor::displayInfo() const {
    cout << "ID             : " << id << "\n"
         << "Name           : " << name << "\n"
         << "Specialization : " << specialization << "\n"
         << "Consult. Fee   : " << consultationFee << " EGP\n";
}
