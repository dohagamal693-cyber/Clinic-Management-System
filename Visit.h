#ifndef VISIT_H
#define VISIT_H

#include <string>
using namespace std;

class Visit {
protected:
    string date;
    string doctorName;
    string diagnosis;
    double fee;
public:
    Visit(string date, string doctorName, string diagnosis);
    virtual ~Visit();

    virtual double calculateFee() const = 0;

    string getDate() const;
    string getDoctorName() const;
    string getDiagnosis() const;
    double getFee() const;
};

class EmergencyVisit : public Visit {
public:
    EmergencyVisit(string date, string doctorName, string diagnosis);
    double calculateFee() const override;
};

class NormalVisit : public Visit {
public:
    NormalVisit(string date, string doctorName, string diagnosis);
    double calculateFee() const override;
};

#endif
