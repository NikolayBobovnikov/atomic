#include "database.h"
#include "sqlite_orm/sqlite_orm.h"
#include <array>
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

template <typename T, size_t N> auto constexpr make_array(T const (&input)[N])
{
  array<T, N> arr;
  for (size_t i = 0; i < N; ++i)
    arr[i] = input[i];

  return arr;
}

}   // namespace

// Main class
namespace DB
{

SQLiteDb::SQLiteDb(const string &db_path) : m_storage(initDatabase(db_path)) {}

size_t
SQLiteDb::insert_employee(const EmployeeDTO &e)
{
  return m_storage.insert(e);
}

EmployeeDTO
SQLiteDb::get_employee(size_t id)
{
  return m_storage.get<EmployeeDTO>(id);
}

std::vector<EmployeeDTO>
SQLiteDb::get_employees()
{
  return m_storage.get_all<EmployeeDTO>();
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
  m_storage.insert(into<EmployeeDTO>(), columns(&EmployeeDTO::id, &EmployeeDTO::position), values(id, position));
}

void
SQLiteDb::set_employee_manager(size_t emp_id, size_t manager_id)
{
  m_storage.insert(into<EmployeeDTO>(), columns(&EmployeeDTO::id, &EmployeeDTO::manager_id),
                   values(emp_id, manager_id));
}

void
SQLiteDb::delete_employee(size_t id)
{
  m_storage.remove<EmployeeDTO>(id);
}

void
SQLiteDb::fill_with_test_data()
{
  static const auto names = make_array({"Nikolay", "Sergey", "Pavel", "Olga", "Marina", "Alexander", "Irina"});
  static const auto positions = make_array({"Developer", "Accountant", "Assistent", "Anykey man", "Auditor"});
  static const size_t employee_count = 100;
  static const size_t managers_count = 10;

  clear();

  // fill managers
  size_t name_pos{};
  for (size_t i = 0; i < managers_count; ++i)
  {
    EmployeeDTO e;
    name_pos = name_pos < names.size() - 1 ? name_pos + 1 : 0;
    e.name = names[name_pos];
    e.position = "Manager";
    insert_employee(e);
  }

  // fill employees
  size_t position_pos{};
  size_t manager_pos{};
  for (size_t i = 0; i < employee_count; ++i)
  {
    EmployeeDTO e;
    name_pos = name_pos < names.size() - 1 ? name_pos + 1 : 0;
    position_pos = position_pos < positions.size() - 1 ? position_pos + 1 : 0;
    manager_pos = manager_pos < managers_count - 1 ? manager_pos + 1 : 0;

    e.name = names[name_pos];
    e.position = positions[position_pos];
    e.manager_id = manager_pos;

    insert_employee(e);
  }

  // SELECT COUNT(*)
  auto db_size = m_storage.select(count<EmployeeDTO>());
}

void
SQLiteDb::clear()
{
  m_storage.remove_all<EmployeeDTO>();
}
}   // namespace DB