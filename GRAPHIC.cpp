#include <graphics.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <conio.h> // for getch()
using namespace std;

// Abstract class
class Booth {
public:
    virtual void display() = 0;
};

class TrafficBooth : public Booth {
public:
    void display() override {
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        outtextxy(100, 50, "Welcome to Traffic Management System Booth");
    }
};

// Vehicle class
class Vehicle {
protected:
    string vehicleNumber, ownerName, vehicleType;
public:
    void setVehicleData(string number, string name, string type) {
        vehicleNumber = number;
        ownerName = name;
        vehicleType = type;
    }

    string getVehicleNumber() const { return vehicleNumber; }
    string getOwnerName() const { return ownerName; }
    string getVehicleType() const { return vehicleType; }

    virtual void displayInfo(int x, int y) {
        outtextxy(x, y, ("Vehicle Number: " + vehicleNumber).c_str());
        outtextxy(x, y + 20, ("Owner Name: " + ownerName).c_str());
        outtextxy(x, y + 40, ("Vehicle Type: " + vehicleType).c_str());
    }
};

class Challan : public Vehicle {
    int fineAmount;
public:
    void issueChallan(int amount) {
        fineAmount = amount;
    }

    void displayInfo(int x, int y) override {
        Vehicle::displayInfo(x, y);
        outtextxy(x, y + 60, ("Fine Amount: " + to_string(fineAmount)).c_str());
    }
};

// File Handling
void saveVehicleData(const Vehicle &v) {
    ofstream file("vehicles.txt", ios::app);
    file << v.getVehicleNumber() << "," << v.getOwnerName() << "," << v.getVehicleType() << "\n";
    file.close();
}

void saveChallanData(const Challan &c) {
    ofstream file("challans.txt", ios::app);
    file << c.getVehicleNumber() << "," << c.getOwnerName() << "," << c.getVehicleType() << "\n";
    file.close();
}

// Input function for GUI (simple)
string getInput(int x, int y) {
    string input = "";
    char ch;
    while ((ch = getch()) != 13) { // Enter key
        if (ch == 8 && !input.empty()) { // Backspace
            input.pop_back();
            setcolor(WHITE);
            bar(x, y, x + 300, y + 20);
        } else if (ch != 8) {
            input.push_back(ch);
        }
        outtextxy(x, y, input.c_str());
    }
    return input;
}

// Draw Menu Buttons
void drawMenu() {
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(100, 120, "1. Register Vehicle");
    outtextxy(100, 160, "2. Issue Challan");
    outtextxy(100, 200, "3. Display All Vehicles");
    outtextxy(100, 240, "4. Search Vehicle");
    outtextxy(100, 280, "5. Exit");
}

int main() {
    initwindow(800, 600);
    TrafficBooth booth;
    booth.display();

    map<string, Vehicle> vehicleRecords;

    int choice;
    string temp;
    while (true) {
        setcolor(WHITE);
        drawMenu();
        outtextxy(100, 320, "Enter choice (1-5): ");
        choice = stoi(getInput(350, 320));

        cleardevice();
        if (choice == 1) {
            Vehicle v;
            outtextxy(100, 100, "Enter Vehicle Number: ");
            string num = getInput(400, 100);

            outtextxy(100, 140, "Enter Owner Name: ");
            string name = getInput(400, 140);

            outtextxy(100, 180, "Enter Vehicle Type: ");
            string type = getInput(400, 180);

            v.setVehicleData(num, name, type);
            vehicleRecords[num] = v;
            saveVehicleData(v);
            outtextxy(100, 220, "Vehicle Registered Successfully!");
            getch();
        }

        else if (choice == 2) {
            Challan c;
            outtextxy(100, 100, "Enter Vehicle Number: ");
            string num = getInput(400, 100);

            outtextxy(100, 140, "Enter Owner Name: ");
            string name = getInput(400, 140);

            outtextxy(100, 180, "Enter Vehicle Type: ");
            string type = getInput(400, 180);

            outtextxy(100, 220, "Enter Fine Amount: ");
            int fine = stoi(getInput(400, 220));

            c.setVehicleData(num, name, type);
            c.issueChallan(fine);
            saveChallanData(c);
            outtextxy(100, 260, "Challan Issued Successfully!");
            getch();
        }

        else if (choice == 3) {
            int y = 100;
            for (auto &p : vehicleRecords) {
                outtextxy(100, y, ("Vehicle Number: " + p.first).c_str());
                p.second.displayInfo(100, y + 20);
                y += 100;
            }
            getch();
        }

        else if (choice == 4) {
            outtextxy(100, 100, "Enter vehicle number to search: ");
            string num = getInput(400, 100);

            if (vehicleRecords.find(num) != vehicleRecords.end()) {
                vehicleRecords[num].displayInfo(100, 140);
            } else {
                outtextxy(100, 140, "Vehicle not found.");
            }
            getch();
        }

        else if (choice == 5) {
            outtextxy(100, 100, "Exiting...");
            getch();
            break;
        }

        else {
            outtextxy(100, 100, "Invalid choice!");
            getch();
        }
        cleardevice();
    }

    closegraph();
    return 0;
}
