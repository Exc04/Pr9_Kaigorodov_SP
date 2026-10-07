// Pr9_Kaigorodov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void increaseHealth(double* data, int size) {
    for (int i = 0; i < size; ++i) {
        data[i] += 10.0;
    }
}

void decreaseHealth(double* data, int size) {
    for (int i = 0; i < size; ++i) {
        data[i] -= 10.0;
    }
}

void restoreHealth(double* data, int size) {
    for (int i = 0; i < size; ++i) {
        data[i] = 100.0;
    }
}

void clampHealth(double* data, int size) {
    for (int i = 0; i < size; ++i) {
        if (data[i] < 0.0) {
            data[i] = 0.0;
        }
        else if (data[i] > 100.0) {
            data[i] = 100.0;
        }
    }
}


void applyProcessing(double* data, int size, void (*processor)(double*, int)) {
    if (processor != nullptr) {
        processor(data, size);
    }
}


void print(const double* data, int size, const char* title) {
    cout << title << ":\n";
    for (int i = 0; i < size; ++i) {
        cout << setw(8) << fixed << setprecision(1) << data[i];
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    if (size % 10 != 0) cout << "\n";
    cout << "\n";
}

void copyArray(const double* src, double* dst, int size) {
    for (int i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));

    const int SIZE = 20;

    double original[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        original[i] = rand() % 151 - 25; 
    }

    double data[SIZE];
    copyArray(original, data, SIZE);

    void (*processors[])(double*, int) = {
        increaseHealth,
        decreaseHealth,
        restoreHealth,
        clampHealth
    };

    const int PROC_COUNT = sizeof(processors) / sizeof(processors[0]);

    int choice = 0;

    do {
        cout << "================ МЕНЮ ================\n";
        cout << "1. Показать текущие данные\n";
        cout << "2. Выбрать и выполнить обработку\n";
        cout << "3. Восстановить исходные данные\n";
        cout << "4. Выход\n";
        cout << "======================================\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            print(data, SIZE, "Текущие данные");
            break;
        }

        case 2: {
            cout << "\nДоступные обработки:\n";
            cout << "1. Увеличить здоровье\n";
            cout << "2. Уменьшить здоровье\n";
            cout << "3. Восстановить здоровье до 100\n";
            cout << "4. Ограничить значения диапазоном 0..100\n";
            cout << "Выберите номер обработки: ";

            int op;
            cin >> op;

            if (op >= 1 && op <= PROC_COUNT) {
                print(data, SIZE, "До обработки");

                void (*processor)(double*, int) = processors[op - 1];

                applyProcessing(data, SIZE, processor);

                print(data, SIZE, "После обработки");
            }
            else {
                cout << "Неверный номер обработки!\n";
            }
            break;
        }

        case 3: {
            copyArray(original, data, SIZE);
            cout << "Исходные данные восстановлены.\n";
            break;
        }

        case 4: {
            cout << "Выход из программы.\n";
            break;
        }

        default: {
            cout << "Неверный пункт меню!\n";
            break;
        }
        }

        cout << "\n";

    } while (choice != 4);

    return 0;
}