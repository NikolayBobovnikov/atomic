#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

/*
• добавить сотрудника;
• запросить список сотрудников;
• запросить должность и руководителя сотрудника;
• задать для сотрудника должность;
• задать для сотрудника руководителя;
• удалить сотрудника.
*/

namespace DB {
static const std::string create_employees =
    "CREATE TABLE employees(id INTEGER PRIMARY KEY, name TEXT NOT NULL, "
    "position TEXT NOT NULL, manager_id INTEGER);";

static const std::string create_managers =
    "CREATE TABLE managers(id INTEGER PRIMARY KEY, name TEXT NOT NULL, "
    "position TEXT NOT NULL);";

struct Employee {
  size_t id;
  std::optional<size_t> manager_id;
  std::string name;
  std::string position;
};

struct TestEmployee : Employee {
  TestEmployee() {
    id = 0;
    name = "Test employee name";
    position = "Test position";
  }
};

struct Manager {
  size_t id;
};

auto initDatabase(const std::string &database) {
  using namespace sqlite_orm;
  using namespace DB;
  return make_storage(
      database,
      make_table(
          "employees",
          make_column("id", &Employee::id, primary_key().autoincrement()),
          make_column("manager_id", &Employee::manager_id),
          make_column("name", &Employee::name),
          make_column("position", &Employee::position),
          make_table("managers", make_column("id", &Manager::id,
                                             primary_key().autoincrement()))));
}

using Storage = decltype(initDatabase());

struct IEmployeesDb {
  virtual ~IEmployeesDb() = default;

  virtual void insert_employee(const Employee &e) const = 0;
  virtual TestEmployee get_employee(size_t emp_id) const = 0;
  virtual std::vector<Employee> get_employees(size_t emp_id) const = 0;
  virtual std::string get_employee_position(size_t emp_id) const = 0;
  virtual std::string get_employee_manager(size_t emp_id) const = 0;
  virtual void set_employee_position(size_t emp_id) const = 0;
  virtual void set_employee_manager(size_t emp_id) const = 0;
  virtual void delete_employee(size_t emp_id) const = 0;
};

struct SQLiteDb : IEmployeesDb {
  void insert_employee(const Employee &e) const override;
  TestEmployee get_employee(size_t emp_id) const override;
  std::vector<Employee> get_employees(size_t emp_id) const override;
  std::string get_employee_position(size_t emp_id) const override;
  std::string get_employee_manager(size_t emp_id) const override;
  void set_employee_position(size_t emp_id) const override;
  void set_employee_manager(size_t emp_id) const override;
  void delete_employee(size_t emp_id) const override;
};
} // namespace DB
