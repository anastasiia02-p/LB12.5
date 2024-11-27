#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

const int MAX_FLIGHTS = 100;

struct Flight {
    char direction[50];
    int flightNumber;
    int daysOfWeek; // Кількість днів на тиждень
    char aircraftType[50];
    int seatCount;
    double ticketPrice;
};

// Функції для роботи з файлами
void writeToFile(const char* filename, Flight flights[], int count);
void readFromFile(const char* filename, Flight flights[], int& count);
void appendToFile(const char* filename, Flight flight);
void replaceInFile(const char* filename, int flightNumber, Flight newFlight);
void deleteFromFile(const char* filename, int flightNumber);
void findMinPriceFlights(const char* filename, const char* direction);
void summarizeAircrafts(const char* filename, const char* direction);
void removeFlightsWithLessThanTwo(const char* filename);

int main() {
   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Flight flights[MAX_FLIGHTS];
    int count = 0;
    char filename[100];

    cout << "Введіть ім'я файлу: ";
    cin >> filename;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Записати масив у файл\n";
        cout << "2. Зчитати масив з файлу\n";
        cout << "3. Доповнити файл\n";
        cout << "4. Замінити дані в файлі\n";
        cout << "5. Видалити дані з файлу\n";
        cout << "6. Знайти рейси з мінімальною вартістю\n";
        cout << "7. Підсумувати типи літаків\n";
        cout << "8. Видалити рейси з менш ніж двома польотами на тиждень\n";
        cout << "0. Вихід\n";
        cout << "Оберіть дію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeToFile(filename, flights, count);
            break;
        case 2:
            readFromFile(filename, flights, count);
            break;
        case 3: {
            Flight flight;
            cout << "Введіть напрямок: ";
            cin >> flight.direction;
            cout << "Введіть номер рейсу: ";
            cin >> flight.flightNumber;
            cout << "Введіть кількість днів на тиждень: ";
            cin >> flight.daysOfWeek;
            cout << "Введіть тип літака: ";
            cin >> flight.aircraftType;
            cout << "Введіть кількість посадкових місць: ";
            cin >> flight.seatCount;
            cout << "Введіть вартість квитка: ";
            cin >> flight.ticketPrice;
            appendToFile(filename, flight);
            break;
        }
        case 4: {
            int flightNumber;
            Flight newFlight;
            cout << "Введіть номер рейсу для заміни: ";
            cin >> flightNumber;
            cout << "Введіть новий напрямок: ";
            cin >> newFlight.direction;
            cout << "Введіть новий номер рейсу: ";
            cin >> newFlight.flightNumber;
            cout << "Введіть нову кількість днів на тиждень: ";
            cin >> newFlight.daysOfWeek;
            cout << "Введіть новий тип літака: ";
            cin >> newFlight.aircraftType;
            cout << "Введіть нову кількість посадкових місць: ";
            cin >> newFlight.seatCount;
            cout << "Введіть нову вартість квитка: ";
            cin >> newFlight.ticketPrice;
            replaceInFile(filename, flightNumber, newFlight);
            break;
        }
        case 5: {
            int flightNumber;
            cout << "Введіть номер рейсу для видалення: ";
            cin >> flightNumber;
            deleteFromFile(filename, flightNumber);
            break;
        }
        case 6: {
            char direction[50];
            cout << "Введіть напрямок для пошуку: ";
            cin >> direction;
            findMinPriceFlights(filename, direction);
            break;
        }
        case 7: {
            char direction[50];
            cout << "Введіть напрямок для підсумування: ";
            cin >> direction;
            summarizeAircrafts(filename, direction);
            break;
        }
        case 8:
            removeFlightsWithLessThanTwo(filename);
            break;
        case 0:
            cout << "Вихід з програми.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}

void writeToFile(const char* filename, Flight flights[], int count) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Не вдалося відкрити файл для запису.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(flights), sizeof(Flight) * count);
    outFile.close();
    cout << "Дані успішно записані у файл.\n";
}

void readFromFile(const char* filename, Flight flights[], int& count) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Не вдалося відкрити файл для читання.\n";
        return;
    }
    inFile.read(reinterpret_cast<char*>(flights), sizeof(Flight) * MAX_FLIGHTS);
    count = inFile.gcount() / sizeof(Flight);
    inFile.close();
    cout << "Дані успішно зчитані з файлу. Кількість рейсів: " << count << "\n";
}

void appendToFile(const char* filename, Flight flight) {
    ofstream outFile(filename, ios::binary | ios::app);
    if (!outFile) {
        cout << "Не вдалося відкрити файл для доповнення.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&flight), sizeof(Flight));
    outFile.close();
    cout << "Дані успішно доповнені у файл.\n";
}

void replaceInFile(const char* filename, int flightNumber, Flight newFlight) {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    readFromFile(filename, flights, count);
    for (int i = 0; i < count; i++) {
        if (flights[i].flightNumber == flightNumber) {
            flights[i] = newFlight;
            break;
        }
    }
    writeToFile(filename, flights, count);
    cout << "Дані успішно замінені у файлі.\n";
}

void deleteFromFile(const char* filename, int flightNumber) {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    readFromFile(filename, flights, count);
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (flights[i].flightNumber != flightNumber) {
            flights[newCount++] = flights[i];
        }
    }
    writeToFile(filename, flights, newCount);
    cout << "Дані успішно видалені з файлу.\n";
}

void findMinPriceFlights(const char* filename, const char* direction) {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    readFromFile(filename, flights, count);
    double minPrice = DBL_MAX;
    for (int i = 0; i < count; i++) {
        if (strcmp(flights[i].direction, direction) == 0 && flights[i].ticketPrice < minPrice) {
            minPrice = flights[i].ticketPrice;
        }
    }
    cout << "Мінімальна вартість квитків для напрямку " << direction << ": " << minPrice << "\n";
}

void summarizeAircrafts(const char* filename, const char* direction) {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    readFromFile(filename, flights, count);
    int totalSeats = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(flights[i].direction, direction) == 0) {
            totalSeats += flights[i].seatCount;
        }
    }
    cout << "Сумарна кількість посадкових місць для напрямку " << direction << ": " << totalSeats << "\n";
}

void removeFlightsWithLessThanTwo(const char* filename) {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    readFromFile(filename, flights, count);
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (flights[i].daysOfWeek >= 2) {
            flights[newCount++] = flights[i];
        }
    }
    writeToFile(filename, flights, newCount);
    cout 
       << "Дані успішно видалені з файлу для рейсів з менш ніж двома польотами на тиждень.\n";
}