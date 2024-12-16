#include <string>
#include <iostream>
#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
protected:
    std::vector<Observer *> observers;
public:
    void addObserver(Observer *observer) {
        observers.push_back(observer);
    }

    void notifyUpdate() {
        int size = observers.size();
        for (int i = 0; i < size; i++) {
            observers[i]->update();
        }
    }
};

namespace Model {
    class GasTank : public Observable {
    private:
        const double R = 8.31;

    public:
        double volume;

        double mass;

        double molar;

        GasTank(double volume, double mass, double molar) : volume(volume), mass(mass), molar(molar) {}

        double getPressure(int t) {
            // p V = v R T => p = v R T / V
            return amountOfMatter() * R * t / volume;
        }

        double amountOfMatter() {
            // p V = v R T = m R T / M => v = m / M
            return mass / molar;
        }

        std::wstring toString() {
            return L"Баллон с газом {\n"
                    "  Объем сосуда: " + std::to_wstring(volume) + L" м^3\n"
                    "  Масса газа: " + std::to_wstring(mass) + L" кг\n"
                    "  Молярная масса газа: " + std::to_wstring(molar) + L" кг/моль\n}";
        }
    };

    class GasTankAdapter : public Observable {
    private:
        GasTank *gasTank;

    public:
        GasTankAdapter(GasTank *gasTank) : gasTank(gasTank) {}

        double calculateDp(int t0, int dt) {
            // dp(t0, dt) = p - p0 = p(t0 + dt) - p(t0)
            return gasTank->getPressure(t0 + dt) - gasTank->getPressure(t0);
        }

        void modifMass(double dm) {
            gasTank->mass += dm;
            gasTank->notifyUpdate();
            notifyUpdate();
        }

        std::wstring getData() {
            return L"Adapter {\n" + gasTank->toString() + L"\n}";
        }
    };
}

namespace View {
    class GasTankView : public Observer {
    private:
        Model::GasTank *model;

    public:
        explicit GasTankView(Model::GasTank *model) : model(model) {
            model->addObserver(this);
            update();
        }

        void update() override {
            std::wcout << L"--------(GasTankView update begin)--------" << std::endl;
            std::wcout << model->toString() << std::endl;
            std::wcout << L"* Количество вещества в этом баллоне: " << model->amountOfMatter() << L" моль" << std::endl;
            std::wcout << L"--------(GasTankView update end)--------" << std::endl;
        }
    };

    class GasTankAdapterView : public Observer {
    private:
        Model::GasTankAdapter *model;

    public:
        explicit GasTankAdapterView(Model::GasTankAdapter *model) : model(model) {
            model->addObserver(this);
            update();
        }

        void update() override {
            std::wcout << L"--------(GasTankAdapterView update begin)--------" << std::endl;
            std::wcout << model->getData() << std::endl;
            std::wcout << L"--------(GasTankAdapterView update end)--------" << std::endl;
        }
    };
}

namespace Controller {
    class GasTankAdapterController {
    private:
        Model::GasTankAdapter *model;
        View::GasTankAdapterView *view;
    public:
        GasTankAdapterController(Model::GasTankAdapter *model, View::GasTankAdapterView *view) :
            model(model), view(view) {}

        void modifyGasTankMass(double massDifference) {
            model->modifMass(massDifference);
        }
    };
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::wcout << L"Модели отображения созданы:" << std::endl << std::endl;

    Model::GasTank gasTank(3.12, 50, 0.002016);

    View::GasTankView gasTankView(&gasTank);

    Model::GasTankAdapter gasTankAdapter(&gasTank);

    View::GasTankAdapterView gasTankAdapterView(&gasTankAdapter);

    std::wcout << std::endl << std::endl << L"Создаем контроллер и меняем через него массу газа в баллоне" << std::endl << std::endl;

    Controller::GasTankAdapterController gasTankAdapterController(&gasTankAdapter, &gasTankAdapterView);

    gasTankAdapterController.modifyGasTankMass(40);

    return 0;
}
