#include "VisitHistory.h"
#include <iostream>

VisitHistory::Node::Node(Visit* v) : visit(v), next(nullptr) {}

VisitHistory::VisitHistory() : head(nullptr), tail(nullptr), count(0) {}

VisitHistory::~VisitHistory() {
    destroyRecursive(head);
}

double VisitHistory::sumFeesRecursive(Node* node) const {
    if (node == nullptr) return 0.0;
    return node->visit->getFee() + sumFeesRecursive(node->next);
}

void VisitHistory::destroyRecursive(Node* node) {
    if (node == nullptr) return;
    destroyRecursive(node->next);
    delete node->visit;
    delete node;
}

void VisitHistory::addVisit(Visit* v) {
    Node* node = new Node(v);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    count++;
}

void VisitHistory::printHistory() const {
    if (head == nullptr) {
        cout << "No visits recorded.\n";
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->visit->getDate() << "\t"
             << current->visit->getDoctorName() << "\t"
             << current->visit->getDiagnosis() << "\t"
             << current->visit->getFee() << " EGP\n";
        current = current->next;
    }
}

double VisitHistory::getTotalPaid() const {
    return sumFeesRecursive(head);
}

int VisitHistory::getVisitCount() const {
    return count;
}
