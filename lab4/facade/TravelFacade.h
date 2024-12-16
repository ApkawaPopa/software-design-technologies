#ifndef SOFTWARE_DESIGN_TECHNOLOGIES_TRAVELFACADE_H
#define SOFTWARE_DESIGN_TECHNOLOGIES_TRAVELFACADE_H


#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

namespace Travel {
    class Tour {
    public:
        std::unordered_map<std::wstring, double> countryMultiplier;
        const int ticketCost;
        const double durationMultiplier;
        const double hotelMultiplier;
        const double foodTypeMultiplier;

        Tour(
            std::unordered_map<std::wstring, double> countryMultiplier,
            const int ticketCost,
            const double durationMultiplier,
            const double hotelMultiplier,
            const double foodTypeMultiplier
        );

        int calculateCost(std::wstring country, int duration, int hotelStars, int foodType);
    };

    class BeachTour : public Tour {
    public:
        BeachTour();
    };

    class ExcursionTour : public Tour {
    public:
        ExcursionTour();
    };

    class SkiTour : public Tour {
    public:
        SkiTour();
    };
}

struct CountryNotAvailableException {
    const wchar_t *message;
};

class TravelFacade {
private:
    std::array<Travel::Tour, 3> tours;
public:
    TravelFacade();

    enum HotelStars {
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5
    };

    enum FoodType {
        TWO_TIMES = 1,
        THREE_TIMES = 2,
        ALL_INCLUSIVE = 3
    };

    bool isCountryAvailable(std::wstring country);

    double calculateCost(std::wstring country, int duration, HotelStars hotelStars, FoodType foodType);
};


#endif //SOFTWARE_DESIGN_TECHNOLOGIES_TRAVELFACADE_H
