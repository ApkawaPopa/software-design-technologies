#ifndef LAB1_PATIENT_H
#define LAB1_PATIENT_H


#include <string>
#include <vector>
#include "Assignment.h"

class Patient {
    std::wstring name;
    std::vector<Assignment *> assignments;
    bool isDischarged;

public:
    explicit Patient(const std::wstring &name);

    void discharge(const std::wstring &cause);

    void setAssignmentDone(int assignmentId);

    void putNewAssignment(Assignment *assignment);

    [[nodiscard]] const std::wstring &getName() const;
};


#endif //LAB1_PATIENT_H
