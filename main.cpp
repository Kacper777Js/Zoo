#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>

using namespace std;

// -------------------- KLASA BAZOWA --------------------
class Animal {
protected:
    string name;
    int age;
    double weight;

public:
    Animal(const string& n, int a, double w) : name(n), age(a), weight(w) {}
    virtual ~Animal() {}

    virtual void makeSound() const = 0;
    virtual void printInfo() const = 0;
    virtual string serialize() const = 0;

    static unique_ptr<Animal> deserialize(const string& line);
};

// -------------------- KLASY POCHODNE --------------------
class Lion : public Animal {
public:
    Lion(const string& n, int a, double w) : Animal(n, a, w) {}
    void makeSound() const override { cout << "Rraaah!\n"; }
    void printInfo() const override {
        cout << "[LEW] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
    string serialize() const override {
        return "Lion;" + name + ";" + to_string(age) + ";" + to_string(weight);
    }
};

class Elephant : public Animal {
public:
    Elephant(const string& n, int a, double w) : Animal(n, a, w) {}
    void makeSound() const override { cout << "TRUUU!\n"; }
    void printInfo() const override {
        cout << "[S£OÑ] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
    string serialize() const override {
        return "Elephant;" + name + ";" + to_string(age) + ";" + to_string(weight);
    }
};

class Monkey : public Animal {
public:
    Monkey(const string& n, int a, double w) : Animal(n, a, w) {}
    void makeSound() const override { cout << "Ooo-oo-oo!\n"; }
    void printInfo() const override {
        cout << "[MA£PA] Nazywam siê " << name
            << ". Mam " << age << " lat."
            << " Wa¿ê " << weight << " kg.\n";
    }
    string serialize() const override {
        return "Monkey;" + name + ";" + to_string(age) + ";" + to_string(weight);
    }
};

// -------------------- FUNKCJA DESERIALIZACJI --------------------
unique_ptr<Animal> Animal::deserialize(const string& line) {
    string type, name;
    int age;
    double weight;

    size_t pos1 = line.find(';');
    size_t pos2 = line.find(';', pos1 + 1);
    size_t pos3 = line.find(';', pos2 + 1);

    type = line.substr(0, pos1);
    name = line.substr(pos1 + 1, pos2 - pos1 - 1);
    age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
    weight = stod(line.substr(pos3 + 1));

    if (type == "Lion") return make_unique<Lion>(name, age, weight);
    if (type == "Elephant") return make_unique<Elephant>(name, age, weight);
    if (type == "Monkey") return make_unique<Monkey>(name, age, weight);

    return nullptr;
}

// -------------------- KLASA ZOO --------------------
class Zoo {
private:
    vector<unique_ptr<Animal>> animals;

public:
    void addAnimal(unique_ptr<Animal> a) { animals.push_back(move(a)); }

    void showAll() const {
        if (animals.empty()) {
            cout << "Brak zwierz¹t w ZOO!\n";
            return;
        }
        for (const auto& a : animals) a->printInfo();
    }

    void playSounds() const {
        if (animals.empty()) {
            cout << "Brak zwierz¹t w ZOO!\n";
            return;
        }
        for (const auto& a : animals) a->makeSound();
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& a : animals)
            file << a->serialize() << "\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            auto animal = Animal::deserialize(line);
            if (animal) addAnimal(move(animal));
        }
    }
};

// -------------------- FUNKCJA MAIN --------------------
int main() {
    Zoo zoo;
    zoo.loadFromFile("zoo.txt");

    int option;
    do {
        cout << "\n===== ZOO =====\n";
        cout << "1. Dodaj zwierzaka.\n";
        cout << "2. Poka¿ zwierzêta.\n";
        cout << "3. Us³ysz dŸwiêki\n";
        cout << "4. Wyjœcie\n";
        cout << "Wybierz opcjê: ";
        cin >> option;

        switch (option) {
        case 1: {
            cout << "==== Dodawanie zwierzaka ====\n";
            cout << "1. Lew\n2. S³oñ\n3. Ma³pa\nTwój wybór: ";
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
            case 1: zoo.addAnimal(make_unique<Lion>(name, age, weight)); break;
            case 2: zoo.addAnimal(make_unique<Elephant>(name, age, weight)); break;
            case 3: zoo.addAnimal(make_unique<Monkey>(name, age, weight)); break;
            default: cout << "Nie ma takiego zwierzêcia!\n"; break;
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
            zoo.saveToFile("zoo.txt");
            break;
        default:
            cout << "Nie ma takiej opcji!\n";
        }

    } while (option != 4);

    return 0;
}
