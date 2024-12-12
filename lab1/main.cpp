#include "Doctor.h"
#include "Nurse.h"

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
