#include <string>
#include <iostream>
#include <cassert>

class GasTank {
private:
    const double R = 8.31;

public:
    double volume;

    double mass;

    double molar;

    GasTank(double volume, double mass, double molar) : volume(volume), mass(mass), molar(molar) {
        std::wcout << L"Создан новый баллон с газом" << std::endl;
    }

    double getPressure(int t) {
        // p V = v R T => p = v R T / V
        return amountOfMatter() * R * t / volume;
    }

    double amountOfMatter() {
        // p V = v R T = m R T / M => v = m / M
        return mass / molar;
    }

    std::wstring toString() {
        return L"Баллон с газом {"
               "Объем сосуда - " + std::to_wstring(volume) + L", "
               "Масса газа - " + std::to_wstring(mass) + L", "
               "Молярная масса газа - " + std::to_wstring(molar) + L"}";
    }
};

class GasTankAdapter {
private:
    GasTank gasTank;

public:
    GasTankAdapter(GasTank gasTank) : gasTank(gasTank) {
        std::wcout << L"Создан новый адаптер для газового баллона" << std::endl;
    }

    double calculateDp(int t0, int dt) {
        // dp(t0, dt) = p - p0 = p(t0 + dt) - p(t0)
        return gasTank.getPressure(t0 + dt) - gasTank.getPressure(t0);
    }

    void modifMass(double dm) {
        gasTank.mass += dm;
    }

    std::wstring getData() {
        return gasTank.toString();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    GasTank gasTank(3.12, 50, 0.002016);

    std::wcout << gasTank.toString() << std::endl;
    std::wcout << L"Количество вещества в баллоне: " << gasTank.amountOfMatter() << std::endl;

    GasTankAdapter gasTankAdapter(gasTank);

    std::wcout << L"Изменение давления при t0 = 0 и dt = 1: " << gasTankAdapter.calculateDp(0, 1) << std::endl;

    gasTankAdapter.modifMass(40);

    std::wcout << L"Баллон изменен: " << gasTankAdapter.getData() << std::endl;
    std::wcout << L"Изменение давления при t0 = 0 и dt = 1: " << gasTankAdapter.calculateDp(0, 1) << std::endl;
    std::wcout << L"Изменение давления при t0 = 10 и dt = 2: " << gasTankAdapter.calculateDp(10, 2) << std::endl;

    return 0;
}
