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
  string getName() { return Name; }
  int getID() { return employeeID; }

  Employee() {
    employeeID = 0;
    Name = "";
    Age = 0;
    Department = "";
    basicSalary = 0.0;
  }

  // Input employee details with validation
  virtual void inputDetails() {
    cout << "Enter Employee Details:" << endl;

    // ID validation
    while (true) {
      cout << "Employee ID: ";
      cin >> employeeID;
      if (cin.fail() || employeeID <= 0) {
        cout << "Invalid ID. Please enter a positive number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else {
        break;
      }
    }

    cin.ignore();
    cout << "Name: ";
    getline(cin, Name);

    // Age validation
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

    // Salary validation
    while (true) {
      cout << "Basic Salary: ";
      cin >> basicSalary;
      if (cin.fail() || basicSalary < 0) {
        cout << "Invalid salary. Must be a non-negative number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else {
        break;
      }
    }
  }

  // Display employee details
  virtual void displayDetails() {
    cout << "Employee Information:" << endl;
    cout << "ID: " << employeeID << endl;
    cout << "Name: " << Name << endl;
    cout << "Age: " << Age << endl;
    cout << "Department: " << Department << endl;
    cout << "Basic Salary: " << basicSalary << endl;
  }

  // Save to file
  virtual void saveToFile(ofstream &ofs) {
    ofs << employeeID << endl;
    ofs << Name << endl;
    ofs << Age << endl;
    ofs << Department << endl;
    ofs << basicSalary << endl;
  }

  // Load from file
  virtual void loadFromFile(ifstream &ifs) {
    ifs >> employeeID;
    ifs.ignore();
    getline(ifs, Name);
    ifs >> Age;
    ifs.ignore();
    getline(ifs, Department);
    ifs >> basicSalary;
  }

  virtual ~Employee() {}
};

// Manager class
class Manager : public Employee {
private:
  double Bonus;
  int teamSize;

public:
  Manager() {
    Bonus = 0.0;
    teamSize = 0;
  }

  void inputDetails() override {
    Employee::inputDetails();

    while (true) {
      cout << "Bonus: ";
      cin >> Bonus;
      if (cin.fail() || Bonus < 0) {
        cout << "Invalid. Enter a non-negative number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else
        break;
    }

    while (true) {
      cout << "Team Size: ";
      cin >> teamSize;
      if (cin.fail() || teamSize < 0) {
        cout << "Invalid. Enter a non-negative number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else
        break;
    }
  }

  void displayDetails() override {
    Employee::displayDetails();
    cout << "Bonus: " << Bonus << endl;
    cout << "Team Size: " << teamSize << endl;
    cout << "Total Salary: " << basicSalary + Bonus << endl;
  }

  void saveToFile(ofstream &ofs) override {
    Employee::saveToFile(ofs);
    ofs << Bonus << endl;
    ofs << teamSize << endl;
  }

  void loadFromFile(ifstream &ifs) override {
    Employee::loadFromFile(ifs);
    ifs >> Bonus;
    ifs >> teamSize;
  }
};

// Engineer class
class Engineer : public Employee {
private:
  string Specialisation;
  double projectAllowance;

public:
  Engineer() {
    Specialisation = "";
    projectAllowance = 0.0;
  }

  void inputDetails() override {
    Employee::inputDetails();
    cin.ignore();
    cout << "Specialisation: ";
    getline(cin, Specialisation);

    while (true) {
      cout << "Project Allowance: ";
      cin >> projectAllowance;
      if (cin.fail() || projectAllowance < 0) {
        cout << "Invalid input. Enter non-negative number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else
        break;
    }
  }

  void displayDetails() override {
    Employee::displayDetails();
    cout << "Specialisation: " << Specialisation << endl;
    cout << "Project Allowance: " << projectAllowance << endl;
    cout << "Total Salary: " << basicSalary + projectAllowance << endl;
  }

  void saveToFile(ofstream &ofs) override {
    Employee::saveToFile(ofs);
    ofs << Specialisation << endl;
    ofs << projectAllowance << endl;
  }

  void loadFromFile(ifstream &ifs) override {
    Employee::loadFromFile(ifs);
    ifs.ignore();
    getline(ifs, Specialisation);
    ifs >> projectAllowance;
  }
};

// Intern class
class Intern : public Employee {
private:
  int Duration;
  double Stipend;

public:
  Intern() {
    Duration = 0;
    Stipend = 0.0;
  }

  void inputDetails() override {
    Employee::inputDetails();

    while (true) {
      cout << "Duration (months): ";
      cin >> Duration;
      if (cin.fail() || Duration <= 0) {
        cout << "Invalid. Enter a positive number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else
        break;
    }

    while (true) {
      cout << "Stipend: ";
      cin >> Stipend;
      if (cin.fail() || Stipend < 0) {
        cout << "Invalid. Enter non-negative number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
      } else
        break;
    }
  }

  void displayDetails() override {
    Employee::displayDetails();
    cout << "Duration: " << Duration << " months" << endl;
    cout << "Stipend: " << Stipend << endl;
  }

  void saveToFile(ofstream &ofs) override {
    Employee::saveToFile(ofs);
    ofs << Duration << endl;
    ofs << Stipend << endl;
  }

  void loadFromFile(ifstream &ifs) override {
    Employee::loadFromFile(ifs);
    ifs >> Duration;
    ifs >> Stipend;
  }
};

// Main System to manage employees
class EmployeeManagementSystem {
private:
  vector<Employee *> employees;

  // Load all records
  void loadAllData() {
    clearEmployees();
    loadFromFile("manager.txt", 1);
    loadFromFile("engineer.txt", 2);
    loadFromFile("intern.txt", 3);
  }

  void loadFromFile(const string &filename, int type) {
    ifstream ifs(filename);
    if (!ifs)
      return;

    while (true) {
      Employee *emp = nullptr;
      if (type == 1)
        emp = new Manager();
      else if (type == 2)
        emp = new Engineer();
      else if (type == 3)
        emp = new Intern();
      else
        return;

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

  void clearEmployees() {
    for (auto emp : employees)
      delete emp;
    employees.clear();
  }

public:
  // Add employee after checking ID uniqueness
  void addEmployee() {
    int choice;
    Employee *newEmployee = nullptr;

    cout << "Add Employee" << endl;
    cout << "1. Manager" << endl;
    cout << "2. Engineer" << endl;
    cout << "3. Intern" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      newEmployee = new Manager();
      break;
    case 2:
      newEmployee = new Engineer();
      break;
    case 3:
      newEmployee = new Intern();
      break;
    default:
      cout << "Invalid choice." << endl;
      return;
    }

    newEmployee->inputDetails();

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
    else if (choice == 3)
      ofs.open("intern.txt", ios::app);

    if (ofs.is_open()) {
      newEmployee->saveToFile(ofs);
      ofs.close();
    }

    cout << "Employee added successfully." << endl;
  }

  // View all employees
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

  // Search employee by ID or name
  void searchEmployee() {
    loadAllData();
    int searchChoice;
    cout << "Search Employee" << endl;
    cout << "1. By ID" << endl;
    cout << "2. By Name" << endl;
    cout << "Enter choice: ";
    cin >> searchChoice;

    if (searchChoice == 1) {
      int id;
      cout << "Enter Employee ID: ";
      cin >> id;
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

    } else if (searchChoice == 2) {
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
    } else {
      cout << "Invalid choice." << endl;
    }
  }

  // Delete employee by ID
  void deleteEmployee() {
    loadAllData();
    if (employees.empty()) {
      cout << "No employees found." << endl;
      return;
    }

    int delID;
    cout << "Enter Employee ID to delete: ";
    cin >> delID;

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
      for (auto m : updatedManagers)
        m->saveToFile(ofs);
      ofs.close();

      ofs.open("engineer.txt");
      for (auto e : updatedEngineers)
        e->saveToFile(ofs);
      ofs.close();

      ofs.open("intern.txt");
      for (auto i : updatedInterns)
        i->saveToFile(ofs);
      ofs.close();

      cout << "Employee deleted successfully." << endl;
    } else {
      cout << "Employee not found." << endl;
    }

    clearEmployees();
  }

  ~EmployeeManagementSystem() { clearEmployees(); }
};

// Entry point
int main() {
  EmployeeManagementSystem system;
  int choice;

  do {
    cout << "\nAdmin Menu:\n";
    cout << "1. Add Employee\n";
    cout << "2. View All Employees\n";
    cout << "3. Search Employee\n";
    cout << "4. Delete Employee\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      system.addEmployee();
      break;
    case 2:
      system.viewAllEmployee();
      break;
    case 3:
      system.searchEmployee();
      break;
    case 4:
      system.deleteEmployee();
      break;
    case 5:
      cout << "Exiting system.\n";
      break;
    default:
      cout << "Invalid option.\n";
    }
  } while (choice != 5);

  return 0;
}
