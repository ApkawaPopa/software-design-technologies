#include <iostream>
#include "Nurse.h"

Nurse::Nurse(const std::wstring &name) : Medic(name) {
    log(L"Добавлена медсестра " + name);
}
