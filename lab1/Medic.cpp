#include <iostream>
#include <utility>
#include "Medic.h"

Medic::Medic(std::wstring name) : name(std::move(name)) {}

void Medic::doAssignment(Patient *patient, int assignmentId) {
    log(L"Медицинский работник " + name + L" выполняет назначение с id=" + std::to_wstring(assignmentId));
    patient->setAssignmentDone(assignmentId);
}

std::wstring Medic::getName() const {
    return name;
}
