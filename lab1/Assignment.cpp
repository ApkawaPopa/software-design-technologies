#include <utility>
#include "Assignment.h"

Assignment::Assignment(int id, AssignmentType type, std::wstring description) :
        id(id), type(type), description(std::move(description)), isDone(false) {}

int Assignment::getId() const {
    return id;
}

void Assignment::setDone() {
    isDone = true;
}

std::wstring Assignment::getType() const {
    switch (type) {
        case AssignmentType::PROCEDURE:
            return L"'Процедура'";
        case AssignmentType::MEDICINE:
            return L"'Лекарство'";
        case AssignmentType::OPERATION:
            return L"'Операция'";
    }
}

const std::wstring &Assignment::getDescription() {
    return description;
}
