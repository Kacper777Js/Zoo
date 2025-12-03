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
            break;  // <-- bardzo wa¿ne, ¿eby wyjœæ z case 1
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
