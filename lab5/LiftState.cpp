#include "LiftState.h"

void Lift::call(int floor) {
    std::wcout << L"Лифт вызвали на этаж " << floor << std::endl;
    if (floor == currentFloor) {
        return;
    }
    targetFloors.push(floor);
    state->handleCall();
}

void Lift::visitNextTarget() {
    if (!targetFloors.empty()) {
        std::wcout << L"Лифт посетил следующий этаж из очереди: " << targetFloors.front() << std::endl;
        targetFloors.pop();
    }
    std::wcout << L"Нет этажа, который лифт мог бы посетить" << std::endl;
    state->handleVisit();
}

void Lift::load(int weight) {
    currentWeight += weight;
    std::wcout << L"В лифт загрузили " << weight << L" кг, текущий вес: " << currentWeight << L" кг" << std::endl;
    state->handleLoad();
}

void Lift::unload(int weight) {
    currentWeight -= weight;
    std::wcout << L"Из лифта выгрузили " << weight << L" кг, текущий вес: " << currentWeight << L" кг" << std::endl;
    state->handleUnload();
}

void Lift::turnPowerOn() {
    std::wcout << L"Питание лифта выключено" << std::endl;
    state->handlePowerOn();
}

void Lift::turnPowerOff() {
    std::wcout << L"Питание лифта включено" << std::endl;
    state->handlePowerOff();
}

void Lift::setState(LiftState *state) {
    this->state = state;
}

int Lift::getCurrentWeight() {
    return currentWeight;
}

int Lift::getMaxWeight() {
    return maxWeight;
}

bool Lift::hasTargetFloor() {
    return !targetFloors.empty();
}

Lift::Lift() :
    currentFloor(1),
    targetFloors(),
    currentWeight(0),
    maxWeight(1000),
    state(new Rest(this)) {}

void Rest::handleCall() {
    lift->setState(new Moving(lift));
    delete this;
}

void Rest::handleLoad() {
    if (lift->getCurrentWeight() > lift->getMaxWeight()) {
        lift->setState(new Overloaded(lift));
        delete this;
    }
}

void Rest::handlePowerOff() {
    lift->setState(new Powerless(lift));
    delete this;
}

Rest::Rest(Lift *lift) : LiftState(lift) {
    std::wcout << L"Лифт в состоянии 'Покой'" << std::endl;
}

void Moving::handleLoad() {
    if (lift->getCurrentWeight() > lift->getMaxWeight()) {
        lift->setState(new Crashed(lift));
        delete this;
    }
}

void Moving::handlePowerOff() {
    lift->setState(new Powerless(lift));
    delete this;
}

Moving::Moving(Lift *lift) : LiftState(lift) {
    std::wcout << L"Лифт в состоянии 'Движение'" << std::endl;
}

void Moving::handleVisit() {
    if (!lift->hasTargetFloor()) {
        lift->setState(new Rest(lift));
        delete this;
    }
}

void Overloaded::handleLoad() {
    lift->setState(new Crashed(lift));
    delete this;
}

void Overloaded::handleUnload() {
    if (lift->getCurrentWeight() <= lift->getMaxWeight()) {
        if (lift->hasTargetFloor()) {
            lift->setState(new Moving(lift));
        } else {
            lift->setState(new Rest(lift));
        }
        delete this;
    }
}

void Overloaded::handlePowerOff() {
    lift->setState(new Powerless(lift));
}

Overloaded::Overloaded(Lift *lift) : LiftState(lift) {
    std::wcout << L"Лифт в состоянии 'Перегружен'" << std::endl;
}

void Powerless::handlePowerOn() {
    if (lift->getCurrentWeight() > lift->getMaxWeight()) {
        lift->setState(new Overloaded(lift));
    } else {
        if (lift->hasTargetFloor()) {
            lift->setState(new Moving(lift));
        } else {
            lift->setState(new Rest(lift));
        }
    }
    delete this;
}

Powerless::Powerless(Lift *lift) : LiftState(lift) {
    std::wcout << L"Лифт в состоянии 'Нет питания'" << std::endl;
}

Crashed::Crashed(Lift *lift) : LiftState(lift) {
    std::wcout << L"Лифт в состоянии 'Авария'" << std::endl;
}
