#include "sqlite_orm/sqlite_orm.h"
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

struct SQLiteDb {
  SQLiteDb() noexcept;
  void insert_employee(const Employee &e) const;
  TestEmployee get_employee(size_t emp_id) const;
  std::vector<Employee> get_employees(size_t emp_id) const;
  std::string get_employee_position(size_t emp_id) const;
  std::string get_employee_manager(size_t emp_id) const;
  void set_employee_position(size_t emp_id) const;
  void set_employee_manager(size_t emp_id) const;
  void delete_employee(size_t emp_id) const;

private:
};
} // namespace DB
