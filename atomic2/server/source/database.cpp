#include "database.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sqlite_orm;
namespace {
using namespace DB;
static const string database = "employees_db";
static const string employees = "employees";
static const string managers = "managers";
static const string database_full_name = database + ".db3";

static const std::string insert_query =
    "INSERT INTO Employees VALUES(1, 'John', 'Software Developer', 2);"
    "INSERT INTO Employees VALUES(2, 'Jill', 'Manager', Null);"
    "INSERT INTO Employees VALUES(3, 'Bob', 'Software Developer', 2);"
    "INSERT INTO Employees VALUES(4, 'Alice', 'Software Developer', 2);"
    "INSERT INTO Employees VALUES(5, 'Dave', 'Manager', Null);"
    "INSERT INTO Employees VALUES(6, 'Sarah', 'Software Developer', 5);"
    "INSERT INTO Managers VALUES(2);"
    "INSERT INTO Managers VALUES(5);";
static const string create_employees =
    "CREATE TABLE Employees(id INTEGER PRIMARY KEY, name TEXT NOT NULL,"
    "position TEXT NOT NULL, manager_id INTEGER);";

static const string create_managers =
    "CREATE TABLE Managers(manager_id INTEGER PRIMARY KEY,"
    "FOREIGN KEY(manager_id) REFERENCES Employees(id));";
} // namespace

// Main class
namespace DB {
static auto storage = initDatabase("employees.db");

void SQLiteDb::insert_employee(const Employee &e) const {}
TestEmployee SQLiteDb::get_employee(size_t emp_id) const {
  return TestEmployee();
}
std::vector<Employee> SQLiteDb::get_employees(size_t emp_id) const {
  return {TestEmployee()};
}

std::string SQLiteDb::get_employee_position(size_t emp_id) const {
  TestEmployee e;
  return e.position;
}
std::string SQLiteDb::get_employee_manager(size_t emp_id) const {
  return "test manager";
}
void SQLiteDb::set_employee_position(size_t emp_id) const {}
void SQLiteDb::set_employee_manager(size_t emp_id) const {}
void SQLiteDb::delete_employee(size_t emp_id) const {}

} // namespace DB
