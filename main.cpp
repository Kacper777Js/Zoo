#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    double weight;

public:
    Animal(const string& n, int a, double w) : name(n), age(a), weight(w) {}

    virtual void makeSound() const {
        cout << "Jestem zwierzêciem\n";
    }

    virtual void printInfo() const {
        cout << "Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }

    virtual ~Animal() {}
};

class Lion : public Animal {
public:
    Lion(const string& n, int a, double w)
        : Animal(n, a, w) {
    }

    void makeSound() const override {
        cout << "Rraaah!\n";
    }

    void printInfo() const override {
        cout << "[LEW] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
};

class Elephant : public Animal {
public:
    Elephant(const string& n, int a, double w)
        : Animal(n, a, w) {
    }

    void makeSound() const override {
        cout << "TRUUU!\n";
    }

    void printInfo() const override {
        cout << "[S£OÑ] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
};

class Monkey : public Animal {
public:
    Monkey(const string& n, int a, double w)
        : Animal(n, a, w) {
    }

    void makeSound() const override {
        cout << "Ooo-oo-oo!\n";
    }

    void printInfo() const override {
        cout << "[MA£PA] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
};

class Zoo {
private:
    vector<unique_ptr<Animal>> animals;

public:
    void addAnimal(unique_ptr<Animal> a) {
        animals.push_back(std::move(a));
    }

    void showAll() const {
        for (const auto& a : animals) {
            a->printInfo();
        }
    }

    void playSounds() const {
        for (const auto& a : animals) {
            a->makeSound();
        }
    }
};

int main() {
    Zoo zoo;
    int option;

    do {
        cout << "===== ZOO =====\n";
        cout << "1. Dodaj zwierzaka.\n";
        cout << "2. Poka¿ zwierzêta.\n";
        cout << "3. Us³ysz dŸwiêki\n";
        cout << "4. Wyjœcie\n";
        cout << "Wybierz opcjê: ";
        cin >> option;

        switch (option) {
        case 1: {
            cout << "==== Dodawanie zwierzaka ====\n";
            cout << "1. Lew\n";
            cout << "2. S³oñ\n";
            cout << "3. Ma³pa\n";
            cout << "Twój wybór: ";

            int type;
            cin >> type;

            string name;
            int age;
            double weight;

            cout << "Podaj imiê: ";
            cin >> name;

            cout << "Podaj wiek: ";
            cin >> age;

            cout << "Podaj wagê: ";
            cin >> weight;

            switch (type) {
            case 1:
                zoo.addAnimal(make_unique<Lion>(name, age, weight));
                break;
            case 2:
                zoo.addAnimal(make_unique<Elephant>(name, age, weight));
                break;
            case 3:
                zoo.addAnimal(make_unique<Monkey>(name, age, weight));
                break;
            default:
                cout << "Nie ma takiego zwierzêcia!\n";
            }
            break;
        }
        case 2:
            cout << "==== Zwierzêta w ZOO ====\n";
            zoo.showAll();
            break;
        case 3:
            cout << "==== DŸwiêki zwierz¹t w ZOO ====\n";
            zoo.playSounds();
            break;
        case 4:
            cout << "Wychodzê z programu...\n";
            break;
        default:
            cout << "Nie ma takiej opcji\n";
        }

    } while (option != 4);

    return 0;
}
