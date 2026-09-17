#include "Visit.h"

Visit::Visit(string date, string doctorName, string diagnosis)
    : date(date), doctorName(doctorName), diagnosis(diagnosis), fee(0.0) {}

Visit::~Visit() {}

string Visit::getDate() const { return date; }
string Visit::getDoctorName() const { return doctorName; }
string Visit::getDiagnosis() const { return diagnosis; }
double Visit::getFee() const { return fee; }

EmergencyVisit::EmergencyVisit(string date, string doctorName, string diagnosis)
    : Visit(date, doctorName, diagnosis) {
    fee = calculateFee();
}

double EmergencyVisit::calculateFee() const { return 400.0; }

NormalVisit::NormalVisit(string date, string doctorName, string diagnosis)
    : Visit(date, doctorName, diagnosis) {
    fee = calculateFee();
}

double NormalVisit::calculateFee() const { return 200.0; }
