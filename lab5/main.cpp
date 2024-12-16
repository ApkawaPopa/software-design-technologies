#include "LiftState.h"

int main() {
    setlocale(LC_ALL, "Russian");


    std::wcout << L"Сценарий использования 'Поездка с 10 этажа на 1'" << std::endl << std::endl;

    Lift lift;
    lift.call(10);
    lift.visitNextTarget();
    lift.load(60);
    lift.call(1);
    lift.visitNextTarget();
    lift.unload(60);

    std::wcout << std::endl << std::endl << L"Сценарий использования 'Аварийная перегрузка'" << std::endl << std::endl;

    lift = Lift();
    lift.load(1000);
    lift.load(500);
    lift.call(5);
    lift.call(7);
    lift.unload(500);
    lift.visitNextTarget();
    lift.visitNextTarget();
    lift.unload(1000);
    lift.load(1001);
    lift.load(1);

    return 0;
}
