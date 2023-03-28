#pragma once

#include "employee.h"
#include "sqlite_orm/sqlite_orm.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace DB
{
struct TestEmployee : Employee
{
  TestEmployee() : Employee("Test employee name", "Test position") {}
};

static auto
initDatabase(const std::string &database)
{
  using namespace sqlite_orm;
  auto storage = make_storage(
      database, make_table("employees", make_column("id", &Employee::id, primary_key().autoincrement()),
                           make_column("manager_id", &Employee::manager_id), make_column("name", &Employee::name),
                           make_column("position", &Employee::position),
                           foreign_key(&Employee::manager_id).references(&Employee::id)));
  storage.sync_schema();
  return storage;
}

using Storage = decltype(initDatabase(""));

struct IEmployeeRepository
{
  virtual ~IEmployeeRepository() = default;

  virtual size_t insert_employee(const Employee &e) = 0;
  virtual Employee get_employee(size_t emp_id) = 0;
  virtual std::vector<Employee> get_employees() = 0;
  virtual std::string get_employee_position(size_t emp_id) = 0;
  virtual std::optional<size_t> get_employee_manager_id(size_t emp_id) = 0;
  virtual void set_employee_position(size_t emp_id, const std::string &position) = 0;
  virtual void set_employee_manager(size_t emp_id, size_t manager_id) = 0;
  virtual void delete_employee(size_t emp_id) = 0;
};

struct SQLiteDb : IEmployeeRepository
{
  SQLiteDb(const std::string &db_path);
  size_t insert_employee(const Employee &e) override;
  Employee get_employee(size_t emp_id) override;
  std::vector<Employee> get_employees() override;
  std::string get_employee_position(size_t emp_id) override;
  std::optional<size_t> get_employee_manager_id(size_t emp_id) override;
  void set_employee_position(size_t emp_id, const std::string &position) override;
  void set_employee_manager(size_t emp_id, size_t manager_id) override;
  void delete_employee(size_t emp_id) override;

  Storage m_storage;
};
}   // namespace DB
