#ifndef LAB1_NURSE_H
#define LAB1_NURSE_H


#include "Medic.h"

class Nurse : public Medic {
public:
    explicit Nurse(const std::wstring &name);
};


#endif //LAB1_NURSE_H
