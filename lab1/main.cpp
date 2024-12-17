#include <iostream>
#include <vector>

void log(const std::wstring &&message) {
    std::wcout << message << std::endl;
}

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
    explicit Assignment(int id, AssignmentType type, const std::wstring &description) :
            id(id), type(type), description(description), isDone(false) {}

    int getId() {
        return id;
    }

    void setDone() {
        isDone = true;
    }

    std::wstring getType() {
        switch (type) {
            case AssignmentType::PROCEDURE:
                return L"'Процедура'";
            case AssignmentType::MEDICINE:
                return L"'Лекарство'";
            case AssignmentType::OPERATION:
                return L"'Операция'";
        }
    }

    std::wstring getDescription() {
        return description;
    }
};

class Patient {
    std::wstring name;
    std::vector<Assignment *> assignments;
    bool isDischarged;

public:
    explicit Patient(const std::wstring &name) : name(name), assignments(), isDischarged(false) {
        log(L"Добавлен пациент " + name);
    }

    void discharge(const std::wstring &cause) {
        log(L"Пациент " + name + L" выписан по причине: " + cause);
        isDischarged = true;
    }

    void setAssignmentDone(int assignmentId) {
        for (auto &assignment: assignments) {
            if (assignment->getId() == assignmentId) {
                assignment->setDone();
                return;
            }
        }
    }

    void putNewAssignment(Assignment *assignment) {
        assignments.push_back(assignment);
    }

    std::wstring getName() {
        return name;
    }
};

class Medic {
protected:
    std::wstring name;

public:
    explicit Medic(const std::wstring &name) : name(name) {}

    void doAssignment(Patient *patient, int assignmentId) {
        log(L"Медицинский работник " + name + L" выполняет назначение с id=" + std::to_wstring(assignmentId));
        patient->setAssignmentDone(assignmentId);
    }

    std::wstring getName() {
        return name;
    }
};

class Doctor : public Medic {
public:
    explicit Doctor(const std::wstring &name) : Medic(name) {
        log(L"Добавлен доктор " + name);
    }

    void addAssignment(Patient *patient, Assignment *assignment) {
        log(L"Доктор " + name + L" назначает пациенту " + patient->getName() + L" процедуру с типом "
            + assignment->getType() + L": " + assignment->getDescription());
        patient->putNewAssignment(assignment);
    }
};

class Nurse : public Medic {
public:
    explicit Nurse(const std::wstring &name) : Medic(name) {
        log(L"Добавлена медсестра " + name);
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Doctor doctor1(L"Доктор №1");
    Doctor doctor2(L"Доктор №2");

    Nurse nurse(L"Медсестра №1");

    Patient patient1(L"Пациент №1");
    Patient patient2(L"Пациент №2");
    Patient patient3(L"Пациент №3");

    doctor1.addAssignment(&patient1, new Assignment(1, AssignmentType::PROCEDURE, L"Прогулка на свежем воздухе"));
    doctor2.addAssignment(&patient2, new Assignment(2, AssignmentType::MEDICINE, L"Парацетамол, 2 таблетки"));
    doctor1.addAssignment(&patient3, new Assignment(3, AssignmentType::OPERATION, L"Пересадка почки"));
    doctor2.addAssignment(&patient3, new Assignment(4, AssignmentType::PROCEDURE, L"Подтягивания, 15 раз"));

    nurse.doAssignment(&patient1, 1);
    doctor1.doAssignment(&patient2, 2);
    nurse.doAssignment(&patient3, 4);
    doctor2.doAssignment(&patient3, 3);

    patient1.discharge(L"Выздоровел");
    patient2.discharge(L"Нарушение режима");

    return 0;
}
