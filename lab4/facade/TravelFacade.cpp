#include "TravelFacade.h"

Travel::Tour::Tour(
    std::unordered_map<std::wstring, double> countryMultiplier,
    const int ticketCost,
    const double durationMultiplier,
    const double hotelMultiplier,
    const double foodTypeMultiplier
) : countryMultiplier(countryMultiplier),
    ticketCost(ticketCost),
    durationMultiplier(durationMultiplier),
    hotelMultiplier(hotelMultiplier),
    foodTypeMultiplier(foodTypeMultiplier) {}

int Travel::Tour::calculateCost(std::wstring country, int duration, int hotelStars, int foodType) {
    if (!countryMultiplier.contains(country)) {
        return -1;
    }
    return countryMultiplier[country] * (
        ticketCost + durationMultiplier * duration *
                     (0.5 + hotelMultiplier * hotelStars) *
                     (0.7 + foodTypeMultiplier * foodType)
    );
}

Travel::BeachTour::BeachTour() : Tour({{L"Турция", 1.0}, {L"Индонезия", 1.3}, {L"ОАЭ", 2}}, 40000, 5050, 0.1, 0.05) {}

Travel::ExcursionTour::ExcursionTour() : Tour({{L"Непал", 0.9}, {L"Америка", 1.3}, {L"Африка", 0.6}}, 30000, 3500, 0.08, 0.03) {}

Travel::SkiTour::SkiTour() : Tour({{L"Швейцария", 1.0}, {L"Россия", 0.7}, {L"Австрия", 0.9}}, 50000, 8000, 0.11, 0.1) {}

TravelFacade::TravelFacade() : tours({Travel::BeachTour(), Travel::ExcursionTour(), Travel::SkiTour()}) {}

bool TravelFacade::isCountryAvailable(std::wstring country) {
    for (auto &tour : tours) {
        if (tour.countryMultiplier.contains(country)) {
            return true;
        }
    }
    return false;
}

double TravelFacade::calculateCost(
    std::wstring country,
    int duration,
    TravelFacade::HotelStars hotelStars,
    TravelFacade::FoodType foodType
) {
    for (auto &tour : tours) {
        if (tour.countryMultiplier.contains(country)) {
            return tour.calculateCost(country, duration, hotelStars, foodType);
        }
    }

    throw CountryNotAvailableException{L"Страна из путевки недоступна для поездки."};
}
