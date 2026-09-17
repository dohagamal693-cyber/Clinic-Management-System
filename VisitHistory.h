#ifndef VISITHISTORY_H
#define VISITHISTORY_H

#include "Visit.h"

class VisitHistory {
private:
    struct Node {
        Visit* visit;
        Node* next;
        Node(Visit* v);
    };

    Node* head;
    Node* tail;
    int count;

    double sumFeesRecursive(Node* node) const;
    void destroyRecursive(Node* node);

public:
    VisitHistory();
    ~VisitHistory();

    void addVisit(Visit* v);
    void printHistory() const;
    double getTotalPaid() const;
    int getVisitCount() const;
};

#endif
