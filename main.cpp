#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class: Employee
class Employee {
protected:
    int employeeID;
    string Name;
    int Age;
    string Department;
    double basicSalary;

public:
    // Getter method to return the employee's name
    string getName() { return Name; }

    // Getter method to return the employee's ID
    int getID() { return employeeID; }

    // Default constructor for the Employee class
    Employee() {
        employeeID = 0;
        Name = "";
        Age = 0;
        Department = "";
        basicSalary = 0.0;
    }

    // Collects general employee information with input validation
    virtual void inputDetails() {
        cout << "Enter Employee Details:" << endl;

        // Validate Employee ID (must be positive integer)
        while (true) {
            cout << "Employee ID: ";
            cin >> employeeID;
            if (cin.fail() || employeeID <= 0) {
                cout << "Invalid ID." << endl;
                cin.clear();                // clear input error flags
                cin.ignore(1000, '\n');     // discard invalid input
            } else {
                break;
            }
        }

        cin.ignore();
        cout << "Name: ";
        getline(cin, Name);

        // Validate Age (must be positive integer)
        while (true) {
            cout << "Age: ";
            cin >> Age;
            if (cin.fail() || Age <= 0) {
                cout << "Invalid Age. Enter a positive number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else {
                break;
            }
        }

        cin.ignore();
        cout << "Department: ";
        getline(cin, Department);

        // Validate Basic Salary (must be non-negative)
        while (true) {
            cout << "Basic Salary: ";
            cin >> basicSalary;
            if (cin.fail() || basicSalary < 0) {
                cout << "Invalid salary." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else {
                break;
            }
        }
    }

    // Displays employee information
    virtual void displayDetails() {
        cout << "Employee Information:" << endl;
        cout << "ID: " << employeeID << endl;
        cout << "Name: " << Name << endl;
        cout << "Age: " << Age << endl;
        cout << "Department: " << Department << endl;
        cout << "Basic Salary: " << basicSalary << endl;
    }

    // Saves employee information to file
    virtual void saveToFile(ofstream &ofs) {
        ofs << employeeID << endl;
        ofs << Name << endl;
        ofs << Age << endl;
        ofs << Department << endl;
        ofs << basicSalary << endl;
    }

    // Loads employee information from file
    virtual void loadFromFile(ifstream &ifs) {
        ifs >> employeeID;
        ifs.ignore();
        getline(ifs, Name);
        ifs >> Age;
        ifs.ignore();
        getline(ifs, Department);
        ifs >> basicSalary;
    }

    // Virtual destructor
    virtual ~Employee() {}
};

// Manager class inherits from Employee
class Manager : public Employee {
private:
    double Bonus;
    int teamSize;

public:
    // Constructor
    Manager() {
        Bonus = 0.0;
        teamSize = 0;
    }

    // Collects manager-specific input with validation
    void inputDetails() override {
        Employee::inputDetails();

        // Validate Bonus
        while (true) {
            cout << "Bonus: ";
            cin >> Bonus;
            if (cin.fail() || Bonus < 0) {
                cout << "Invalid. Enter a non-negative number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }

        // Validate Team Size
        while (true) {
            cout << "Team Size: ";
            cin >> teamSize;
            if (cin.fail() || teamSize < 0) {
                cout << "Invalid. Enter a non-negative number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }
    }

    // Displays manager-specific information
    void displayDetails() override {
        Employee::displayDetails();
        cout << "Bonus: " << Bonus << endl;
        cout << "Team Size: " << teamSize << endl;
        cout << "Total Salary: " << basicSalary + Bonus << endl;
    }

    // Saves manager data to file
    void saveToFile(ofstream &ofs) override {
        Employee::saveToFile(ofs);
        ofs << Bonus << endl;
        ofs << teamSize << endl;
    }

    // Loads manager data from file
    void loadFromFile(ifstream &ifs) override {
        Employee::loadFromFile(ifs);
        ifs >> Bonus;
        ifs >> teamSize;
    }
};

// Engineer class inherits from Employee
class Engineer : public Employee {
private:
    string Specialisation;
    double projectAllowance;

public:
    // Constructor
    Engineer() {
        Specialisation = "";
        projectAllowance = 0.0;
    }

    // Collects engineer-specific data with validation
    void inputDetails() override {
        Employee::inputDetails();
        cin.ignore();
        cout << "Specialisation: ";
        getline(cin, Specialisation);

        // Validate Project Allowance
        while (true) {
            cout << "Project Allowance: ";
            cin >> projectAllowance;
            if (cin.fail() || projectAllowance < 0) {
                cout << "Invalid input. Enter non-negative number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }
    }

    // Displays engineer-specific information
    void displayDetails() override {
        Employee::displayDetails();
        cout << "Specialisation: " << Specialisation << endl;
        cout << "Project Allowance: " << projectAllowance << endl;
        cout << "Total Salary: " << basicSalary + projectAllowance << endl;
    }

    // Saves engineer data to file
    void saveToFile(ofstream &ofs) override {
        Employee::saveToFile(ofs);
        ofs << Specialisation << endl;
        ofs << projectAllowance << endl;
    }

    // Loads engineer data from file
    void loadFromFile(ifstream &ifs) override {
        Employee::loadFromFile(ifs);
        ifs.ignore();
        getline(ifs, Specialisation);
        ifs >> projectAllowance;
    }
};

// Intern class inherits from Employee
class Intern : public Employee {
private:
    int Duration;
    double Stipend;

public:
    // Constructor
    Intern() {
        Duration = 0;
        Stipend = 0.0;
    }

    // Collects intern-specific input with validation
    void inputDetails() override {
        Employee::inputDetails();

        // Validate Duration
        while (true) {
            cout << "Duration (months): ";
            cin >> Duration;
            if (cin.fail() || Duration <= 0) {
                cout << "Invalid. Enter a positive number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }

        // Validate Stipend
        while (true) {
            cout << "Stipend: ";
            cin >> Stipend;
            if (cin.fail() || Stipend < 0) {
                cout << "Invalid. Enter non-negative number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }
    }

    // Displays intern specific information
    void displayDetails() override {
        Employee::displayDetails();
        cout << "Duration: " << Duration << " months" << endl;
        cout << "Stipend: " << Stipend << endl;
    }

    // Saves intern data to file
    void saveToFile(ofstream &ofs) override {
        Employee::saveToFile(ofs);
        ofs << Duration << endl;
        ofs << Stipend << endl;
    }

    // Loads intern data from file
    void loadFromFile(ifstream &ifs) override {
        Employee::loadFromFile(ifs);
        ifs >> Duration;
        ifs >> Stipend;
    }
};

// Main class to manage employee system
class EmployeeManagementSystem {
private:
    vector<Employee *> employees;

    // Loads all data from employee files
    void loadAllData() {
        clearEmployees();
        loadFromFile("manager.txt", 1);
        loadFromFile("engineer.txt", 2);
        loadFromFile("intern.txt", 3);
    }

    // Loads specific type of employee data from file
    void loadFromFile(const string &filename, int type) {
        ifstream ifs(filename);
        if (!ifs) return;

        while (true) {
            Employee *emp = nullptr;
            if (type == 1)
                emp = new Manager();
            else if (type == 2)
                emp = new Engineer();
            else if (type == 3)
                emp = new Intern();
            else return;

            emp->loadFromFile(ifs);
            if (ifs)
                employees.push_back(emp);
            else {
                delete emp;
                break;
            }
        }
        ifs.close();
    }

    // Frees memory and clears employee list
    void clearEmployees() {
        for (auto emp : employees)
            delete emp;
        employees.clear();
    }

public:
    // Adds a new employee with unique check
    void addEmployee() {
        int choice;
        Employee *newEmployee = nullptr;

        cout << "Add Employee" << endl;
        cout << "1. Manager" << endl;
        cout << "2. Engineer" << endl;
        cout << "3. Intern" << endl;
        cout << "Enter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input. Enter 1, 2 or 3: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (choice == 1)
            newEmployee = new Manager();
        else if (choice == 2)
            newEmployee = new Engineer();
        else
            newEmployee = new Intern();

        newEmployee->inputDetails();

        // Check for duplicate ID
        loadAllData();
        for (auto emp : employees) {
            if (emp->getID() == newEmployee->getID()) {
                cout << "Employee ID already exists. Try again." << endl;
                delete newEmployee;
                return;
            }
        }

        employees.push_back(newEmployee);
        ofstream ofs;
        if (choice == 1)
            ofs.open("manager.txt", ios::app);
        else if (choice == 2)
            ofs.open("engineer.txt", ios::app);
        else
            ofs.open("intern.txt", ios::app);

        if (ofs.is_open()) {
            newEmployee->saveToFile(ofs);
            ofs.close();
        }

        cout << "Employee added successfully." << endl;
    }

    // Displays all employee records
    void viewAllEmployee() {
        loadAllData();
        if (employees.empty()) {
            cout << "No employee records available." << endl;
            return;
        }

        cout << "=== All Employees ===" << endl;
        for (auto emp : employees) {
            emp->displayDetails();
            cout << "----------------------" << endl;
        }
    }

    // Searches for employee by ID or Name
    void searchEmployee() {
        loadAllData();
        int searchChoice;
        cout << "Search Employee" << endl;
        cout << "1. By ID" << endl;
        cout << "2. By Name" << endl;
        cout << "Enter choice: ";
        while (!(cin >> searchChoice) || (searchChoice != 1 && searchChoice != 2)) {
            cout << "Invalid input. Enter 1 or 2: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (searchChoice == 1) {
            int id;
            cout << "Enter Employee ID: ";
            while (!(cin >> id) || id <= 0) {
                cout << "Invalid ID. Enter a positive number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            bool found = false;
            for (auto emp : employees) {
                if (emp->getID() == id) {
                    emp->displayDetails();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Employee not found." << endl;

        } else {
            string name;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            bool found = false;
            for (auto emp : employees) {
                if (emp->getName() == name) {
                    emp->displayDetails();
                    found = true;
                }
            }
            if (!found)
                cout << "Employee not found." << endl;
        }
    }

    // Deletes an employee based on ID
    void deleteEmployee() {
        loadAllData();
        if (employees.empty()) {
            cout << "No employees found." << endl;
            return;
        }

        int delID;
        cout << "Enter Employee ID to delete: ";
        while (!(cin >> delID) || delID <= 0) {
            cout << "Invalid ID. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        bool found = false;
        vector<Employee *> updatedManagers, updatedEngineers, updatedInterns;

        for (auto emp : employees) {
            if (emp->getID() == delID) {
                found = true;
                delete emp;
            } else {
                if (dynamic_cast<Manager *>(emp))
                    updatedManagers.push_back(emp);
                else if (dynamic_cast<Engineer *>(emp))
                    updatedEngineers.push_back(emp);
                else if (dynamic_cast<Intern *>(emp))
                    updatedInterns.push_back(emp);
            }
        }

        if (found) {
            ofstream ofs("manager.txt");
            for (auto m : updatedManagers) m->saveToFile(ofs);
            ofs.close();

            ofs.open("engineer.txt");
            for (auto e : updatedEngineers) e->saveToFile(ofs);
            ofs.close();

            ofs.open("intern.txt");
            for (auto i : updatedInterns) i->saveToFile(ofs);
            ofs.close();

            cout << "Employee deleted successfully." << endl;
        } else {
            cout << "Employee not found." << endl;
        }

        clearEmployees();
    }

    // Destructor to clean up memory
    ~EmployeeManagementSystem() {
        clearEmployees();
    }
};

// Main function: Entry point for the application
int main() {
    EmployeeManagementSystem system;
    int choice;

    do {
        cout << "\nAdmin Menu:" << endl;
        cout << "==============" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View All Employees" << endl;
        cout << "3. Search Employee" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid input. Enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1: system.addEmployee(); break;
            case 2: system.viewAllEmployee(); break;
            case 3: system.searchEmployee(); break;
            case 4: system.deleteEmployee(); break;
            case 5: cout << "Exiting system.\n"; break;
        }
    } while (choice != 5);

    return 0;
}
