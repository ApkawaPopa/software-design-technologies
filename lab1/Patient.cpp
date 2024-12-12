#include <iostream>
#include "Patient.h"

Patient::Patient(const std::wstring &name) : name(name), assignments(), isDischarged(false) {
    log(L"Добавлен пациент " + name);
}

void Patient::discharge(const std::wstring &cause) {
    log(L"Пациент " + name + L" выписан по причине: " + cause);
    isDischarged = true;
}

void Patient::setAssignmentDone(int assignmentId) {
    for (auto &assignment: assignments) {
        if (assignment->getId() == assignmentId) {
            assignment->setDone();
            return;
        }
    }
}

void Patient::putNewAssignment(Assignment *assignment) {
    assignments.push_back(assignment);
}

const std::wstring &Patient::getName() const {
    return name;
}
