#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

const int MAX_FLIGHTS = 100;

struct Flight {
    char direction[50];
    int flightNumber;
    int daysOfWeek; // ʳ������ ��� �� �������
    char aircraftType[50];
    int seatCount;
    double ticketPrice;
};

// ������� ��� ������ � �������
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

    cout << "������ ��'� �����: ";
    cin >> filename;

    int choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� ����� � ����\n";
        cout << "2. ������� ����� � �����\n";
        cout << "3. ��������� ����\n";
        cout << "4. ������� ��� � ����\n";
        cout << "5. �������� ��� � �����\n";
        cout << "6. ������ ����� � ��������� �������\n";
        cout << "7. ϳ��������� ���� �����\n";
        cout << "8. �������� ����� � ���� �� ����� ��������� �� �������\n";
        cout << "0. �����\n";
        cout << "������ ��: ";
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
            cout << "������ ��������: ";
            cin >> flight.direction;
            cout << "������ ����� �����: ";
            cin >> flight.flightNumber;
            cout << "������ ������� ��� �� �������: ";
            cin >> flight.daysOfWeek;
            cout << "������ ��� �����: ";
            cin >> flight.aircraftType;
            cout << "������ ������� ���������� ����: ";
            cin >> flight.seatCount;
            cout << "������ ������� ������: ";
            cin >> flight.ticketPrice;
            appendToFile(filename, flight);
            break;
        }
        case 4: {
            int flightNumber;
            Flight newFlight;
            cout << "������ ����� ����� ��� �����: ";
            cin >> flightNumber;
            cout << "������ ����� ��������: ";
            cin >> newFlight.direction;
            cout << "������ ����� ����� �����: ";
            cin >> newFlight.flightNumber;
            cout << "������ ���� ������� ��� �� �������: ";
            cin >> newFlight.daysOfWeek;
            cout << "������ ����� ��� �����: ";
            cin >> newFlight.aircraftType;
            cout << "������ ���� ������� ���������� ����: ";
            cin >> newFlight.seatCount;
            cout << "������ ���� ������� ������: ";
            cin >> newFlight.ticketPrice;
            replaceInFile(filename, flightNumber, newFlight);
            break;
        }
        case 5: {
            int flightNumber;
            cout << "������ ����� ����� ��� ���������: ";
            cin >> flightNumber;
            deleteFromFile(filename, flightNumber);
            break;
        }
        case 6: {
            char direction[50];
            cout << "������ �������� ��� ������: ";
            cin >> direction;
            findMinPriceFlights(filename, direction);
            break;
        }
        case 7: {
            char direction[50];
            cout << "������ �������� ��� �����������: ";
            cin >> direction;
            summarizeAircrafts(filename, direction);
            break;
        }
        case 8:
            removeFlightsWithLessThanTwo(filename);
            break;
        case 0:
            cout << "����� � ��������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    } while (choice != 0);

    return 0;
}

void writeToFile(const char* filename, Flight flights[], int count) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "�� ������� ������� ���� ��� ������.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(flights), sizeof(Flight) * count);
    outFile.close();
    cout << "��� ������ ������� � ����.\n";
}

void readFromFile(const char* filename, Flight flights[], int& count) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "�� ������� ������� ���� ��� �������.\n";
        return;
    }
    inFile.read(reinterpret_cast<char*>(flights), sizeof(Flight) * MAX_FLIGHTS);
    count = inFile.gcount() / sizeof(Flight);
    inFile.close();
    cout << "��� ������ ������ � �����. ʳ������ �����: " << count << "\n";
}

void appendToFile(const char* filename, Flight flight) {
    ofstream outFile(filename, ios::binary | ios::app);
    if (!outFile) {
        cout << "�� ������� ������� ���� ��� ����������.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&flight), sizeof(Flight));
    outFile.close();
    cout << "��� ������ �������� � ����.\n";
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
    cout << "��� ������ ������ � ����.\n";
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
    cout << "��� ������ ������� � �����.\n";
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
    cout << "̳������� ������� ������ ��� �������� " << direction << ": " << minPrice << "\n";
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
    cout << "������� ������� ���������� ���� ��� �������� " << direction << ": " << totalSeats << "\n";
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
       << "��� ������ ������� � ����� ��� ����� � ���� �� ����� ��������� �� �������.\n";
}