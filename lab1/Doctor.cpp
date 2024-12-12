#include <iostream>
#include "Doctor.h"

void Doctor::addAssignment(Patient *patient, Assignment *assignment) {
    log(L"Доктор " + name + L" назначает пациенту " + patient->getName() + L" процедуру с типом "
        + assignment->getType() + L": " + assignment->getDescription());
    patient->putNewAssignment(assignment);
}

Doctor::Doctor(const std::wstring &name) : Medic(name) {
    log(L"Добавлен доктор " + name);
}
