#include <iostream>
#include <iomanip>

#include "TravelFacade.h"

int main() {
    setlocale(LC_ALL, "Russian");

    TravelFacade facade;

    if (facade.isCountryAvailable(L"ОАЭ")) {
        std::wcout
                << L"Путевка на пляжный курорт в ОАЭ на 7 дней в 5-звездочный отель с двухразовым питанием стоит: "
                << std::setprecision(2) << std::fixed
                << facade.calculateCost(L"ОАЭ", 7, TravelFacade::FIVE, TravelFacade::TWO_TIMES) << std::endl;
    }

    if (facade.isCountryAvailable(L"Непал")) {
        std::wcout
                << L"Путевка на экскурсию в Непал на 5 дней в 3-звездочный отель с трехразовым питанием стоит: "
                << std::setprecision(2) << std::fixed
                << facade.calculateCost(L"Непал", 5, TravelFacade::THREE, TravelFacade::THREE_TIMES) << std::endl;
    }

    if (facade.isCountryAvailable(L"Россия")) {
        std::wcout
                << L"Путевка на горнолыжный курорт в Россию на 14 дней в 4-звездочный отель с питанием типа все "
                   "включено стоит: " << std::setprecision(2) << std::fixed
                << facade.calculateCost(L"Россия", 14, TravelFacade::FOUR, TravelFacade::ALL_INCLUSIVE) << std::endl;
    }
    
    std::wcout << L"Доступность страны 'Люксембург': " << (facade.isCountryAvailable(L"Люксембург") ? "true" : "false") << std::endl;
    std::wcout << L"Попытка посчитать стоимость путевки в Люксембург: " << std::endl;
    try {
        facade.calculateCost(L"Люксембург", 0, TravelFacade::ONE, TravelFacade::TWO_TIMES);
    } catch (CountryNotAvailableException &e) {
        std::wcout << e.message << std::endl;
    }

    return 0;
}
