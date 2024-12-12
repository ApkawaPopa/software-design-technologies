#ifndef LAB1_DOCTOR_H
#define LAB1_DOCTOR_H


#include "Medic.h"

class Doctor : public Medic {
public:
    explicit Doctor(const std::wstring &name);

    void addAssignment(Patient *patient, Assignment *assignment);
};


#endif //LAB1_DOCTOR_H
