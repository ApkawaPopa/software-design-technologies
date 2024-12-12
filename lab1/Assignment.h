#ifndef LAB1_ASSIGNMENT_H
#define LAB1_ASSIGNMENT_H


#include <string>
#include "log.h"

enum AssignmentType {
    PROCEDURE,
    MEDICINE,
    OPERATION
};

class Assignment {
    int id;
    AssignmentType type;
    std::wstring description;
    bool isDone;

public:
    explicit Assignment(int id, AssignmentType type, std::wstring description);

    int getId() const;

    void setDone();

    std::wstring getType() const;

    const std::wstring &getDescription();
};


#endif //LAB1_ASSIGNMENT_H
