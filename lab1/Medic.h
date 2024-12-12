#ifndef LAB1_MEDIC_H
#define LAB1_MEDIC_H


#include <string>
#include "Patient.h"

class Medic {
protected:
    std::wstring name;

public:
    explicit Medic(std::wstring name);

    void doAssignment(Patient *patient, int assignmentId);

    std::wstring getName() const;
};


#endif //LAB1_MEDIC_H
