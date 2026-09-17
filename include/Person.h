#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

class VisitHistory;
class Visit;

class Person {
protected:
    int id;
    string name;
public:
    Person(int id, string name);
    virtual ~Person();

    int getId() const;
    string getName() const;
    void setName(string n);

    virtual void displayInfo() const = 0;
};

class Patient : public Person {
private:
    int age;
    string phone;
    VisitHistory* history;

public:
    Patient(int id, string name, int age, string phone);
    ~Patient();

    int getAge() const;
    string getPhone() const;
    void setAge(int a);
    void setPhone(string p);

    void displayInfo() const override;

    void recordVisit(Visit* v);
    void printVisitHistory() const;
    double getTotalPaid() const;
    int getVisitCount() const;

    friend ostream& operator<<(ostream& out, const Patient& p);
};

class Doctor : public Person {
private:
    string specialization;
    double consultationFee;
public:
    Doctor(int id, string name, string specialization, double fee);
    ~Doctor();

    string getSpecialization() const;
    double getConsultationFee() const;
    void setSpecialization(string s);
    void setConsultationFee(double f);

    void displayInfo() const override;
};

#endif
