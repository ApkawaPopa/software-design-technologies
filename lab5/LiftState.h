#ifndef SOFTWARE_DESIGN_TECHNOLOGIES_LIFTSTATE_H
#define SOFTWARE_DESIGN_TECHNOLOGIES_LIFTSTATE_H


#include <iostream>
#include <queue>

class Lift;

class LiftState {
protected:
    Lift *lift;

public:
    explicit LiftState(Lift *lift) : lift(lift) {}

    virtual void handleCall() {};

    virtual void handleVisit() {};

    virtual void handleLoad() {};

    virtual void handleUnload() {};

    virtual void handlePowerOn() {};

    virtual void handlePowerOff() {};
};

class Rest : public LiftState {
public:
    explicit Rest(Lift *lift);

    void handleCall() override;

    void handleLoad() override;

    void handlePowerOff() override;
};

class Moving : public LiftState {
public:
    explicit Moving(Lift *lift);

    void handleVisit() override;

    void handleLoad() override;

    void handlePowerOff() override;
};

class Overloaded : public LiftState {
public:
    explicit Overloaded(Lift *lift);

    void handleLoad() override;

    void handleUnload() override;

    void handlePowerOff() override;
};

class Powerless : public LiftState {
public:
    explicit Powerless(Lift *lift);

    void handlePowerOn() override;
};

class Crashed : public LiftState {
public:
    explicit Crashed(Lift *lift);
};

class Lift {
private:
    int currentFloor;
    std::queue<int> targetFloors;
    int currentWeight;
    int maxWeight;
    LiftState *state;

public:
    Lift();

    void call(int floor);

    void visitNextTarget();

    void load(int weight);

    void unload(int weight);

    void turnPowerOn();

    void turnPowerOff();

    void setState(LiftState *state);

    int getCurrentWeight();

    int getMaxWeight();

    bool hasTargetFloor();
};


#endif //SOFTWARE_DESIGN_TECHNOLOGIES_LIFTSTATE_H
