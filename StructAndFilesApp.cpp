// StructAndFilesApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    string name;
    int age;
};

struct Employees {
    Employee* data = nullptr;
    int numEmployees = 0;
    int maxEmployees = 0;
};

void loadDataFromFile(Employees& employees, string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string name;
        int age;
        while (file >> name >> age) {
            if (employees.numEmployees == employees.maxEmployees) {
                employees.maxEmployees = employees.maxEmployees == 0 ? 1 : employees.maxEmployees * 2;
                Employee* newEmployees = new Employee[employees.maxEmployees];
                for (int i = 0; i < employees.numEmployees; i++) {
                    newEmployees[i] = employees.data[i];
                }
                delete[] employees.data;
                employees.data = newEmployees;
            }
            employees.data[employees.numEmployees].name = name;
            employees.data[employees.numEmployees].age = age;
            employees.numEmployees++;
        }
        file.close();
    }
}

void saveDataToFile(Employees& employees, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < employees.numEmployees; i++) {
            file << employees.data[i].name << " " << employees.data[i].age << endl;
        }
        file.close();
    }
}

void addEmployee(Employees& employees, string name, int age) {
    if (employees.numEmployees == employees.maxEmployees) {
        employees.maxEmployees = employees.maxEmployees == 0 ? 1 : employees.maxEmployees * 2;
        Employee* newEmployees = new Employee[employees.maxEmployees];
        for (int i = 0; i < employees.numEmployees; i++) {
            newEmployees[i] = employees.data[i];
        }
        delete[] employees.data;
        employees.data = newEmployees;
    }
    employees.data[employees.numEmployees].name = name;
    employees.data[employees.numEmployees].age = age;
    employees.numEmployees++;
}

void editEmployee(Employees& employees, int index, string name, int age) {
    if (index >= 0 && index < employees.numEmployees) {
        employees.data[index].name = name;
        employees.data[index].age = age;
    }
}

void deleteEmployee(Employees& employees, int index) {
    if (index >= 0 && index < employees.numEmployees) {
        for (int i = index; i < employees.numEmployees - 1; i++) {
            employees.data[i] = employees.data[i + 1];
        }
        employees.numEmployees--;
    }
}

int findEmployeeByName(Employees& employees, string name) {
    for (int i = 0; i < employees.numEmployees; i++) {
        if (employees.data[i].name == name) {
            return i;
        }
    }
    return -1;
}

void printEmployee(Employees& employees, int index) {
    if (index >= 0 && index < employees.numEmployees) {
        cout << "Name: " << employees.data[index].name << endl;
        cout << "Age: " << employees.data[index].age << endl;
    }
}

void printAllEmployees(Employees& employees) {
    for (int i = 0; i < employees.numEmployees; i++) {
        printEmployee(employees, i);
    }
}

void printAllEmployeesByAge(Employees& employees, int age) {
    for (int i = 0; i < employees.numEmployees; i++) {
        if (employees.data[i].age == age) {
            printEmployee(employees, i);
        }
    }
}

void printAllEmployeesByName(Employees& employees, char letter) {
    for (int i = 0; i < employees.numEmployees; i++) {
        if (!employees.data[i].name.empty() && employees.data[i].name[0] == letter) {
            printEmployee(employees, i);
        }
    }
}

int main() {
    Employees employees;

    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    loadDataFromFile(employees, filename);

    string command;
    while (true) {
        cout << "Enter a command (add, edit, delete, search, print, printall, printage, printname, save, quit): ";
        cin >> command;
        if (command == "add") {
            string name;
            int age;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter the age: ";
            cin >> age;
            addEmployee(employees, name, age);
        }
        else if (command == "edit") {
            int index;
            string name;
            int age;
            cout << "Enter the index: ";
            cin >> index;
            cout << "Enter the new name: ";
            cin >> name;
            cout << "Enter the new age: ";
            cin >> age;
            editEmployee(employees, index, name, age);
        }
        else if (command == "delete") {
            int index;
            cout << "Enter the index: ";
            cin >> index;
            deleteEmployee(employees, index);
        }
        else if (command == "search") {
            string name;
            cout << "Enter the name: ";
            cin >> name;
            int index = findEmployeeByName(employees, name);
            if (index >= 0) {
                cout << "Employee found at index " << index << endl;
                printEmployee(employees, index);
            }
            else {
                cout << "Employee not found" << endl;
            }
        }
        else if (command == "print") {
            int index;
            cout << "Enter the index: ";
            cin >> index;
            printEmployee(employees, index);
        }       
          else if (command == "printall") {
            printAllEmployees(employees);
        } else if (command == "printage") {
            int age;
            cout << "Enter the age: ";
            cin >> age;
            printAllEmployeesByAge(employees, age);
        } else if (command == "printname") {
            char letter;
            cout << "Enter the letter: ";
            cin >> letter;
            printAllEmployeesByName(employees, letter);
        } else if (command == "save") {
            saveDataToFile(employees, filename);
        } else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    saveDataToFile(employees, filename);

    delete[] employees.data;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
