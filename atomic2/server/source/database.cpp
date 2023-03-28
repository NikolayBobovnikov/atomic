#include "database.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sqlite_orm;
namespace
{
using namespace DB;
static const string employees = "employees";
static const string managers = "managers";

static const std::string insert_query = "INSERT INTO Employees VALUES(1, 'John', 'Software Developer', 2);"
                                        "INSERT INTO Employees VALUES(2, 'Jill', 'Manager', Null);"
                                        "INSERT INTO Employees VALUES(3, 'Bob', 'Software Developer', 2);"
                                        "INSERT INTO Employees VALUES(4, 'Alice', 'Software Developer', 2);"
                                        "INSERT INTO Employees VALUES(5, 'Dave', 'Manager', Null);"
                                        "INSERT INTO Employees VALUES(6, 'Sarah', 'Software Developer', 5);"
                                        "INSERT INTO Managers VALUES(2);"
                                        "INSERT INTO Managers VALUES(5);";
static const string create_employees = "CREATE TABLE Employees(id INTEGER PRIMARY KEY, name TEXT NOT NULL,"
                                       "position TEXT NOT NULL, manager_id INTEGER);";

static const string create_managers = "CREATE TABLE Managers(manager_id INTEGER PRIMARY KEY,"
                                      "FOREIGN KEY(manager_id) REFERENCES Employees(id));";
}   // namespace

// Main class
namespace DB
{

SQLiteDb::SQLiteDb(const string &db_path) : m_storage(DB::initDatabase(db_path)) {}

size_t
SQLiteDb::insert_employee(const Employee &e)
{
  return m_storage.insert(e);
}

Employee
SQLiteDb::get_employee(size_t id)
{
  return m_storage.get<Employee>(id);
}

std::vector<Employee>
SQLiteDb::get_employees()
{
  return m_storage.get_all<Employee>();
}

std::string
SQLiteDb::get_employee_position(size_t id)
{
  return get_employee(id).position;
}

std::optional<size_t>
SQLiteDb::get_employee_manager_id(size_t id)
{
  return get_employee(id).manager_id;
}

void
SQLiteDb::set_employee_position(size_t id, const string &position)
{
  m_storage.insert(into<Employee>(), columns(&Employee::id, &Employee::position), values(id, position));
}

void
SQLiteDb::set_employee_manager(size_t emp_id, size_t manager_id)
{
  m_storage.insert(into<Employee>(), columns(&Employee::id, &Employee::manager_id), values(emp_id, manager_id));
}

void
SQLiteDb::delete_employee(size_t id)
{
  m_storage.remove<Employee>(id);
}
}   // namespace DB