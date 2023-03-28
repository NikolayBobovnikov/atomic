#pragma once

#include <optional>
#include <string>

namespace DB
{
static const std::string databaseFile{"Employees.db"};
struct EmployeeDTO
{
  EmployeeDTO() = default;
  EmployeeDTO(const std::string &_name, const std::string &_position) : name(_name), position(_position) {}

  size_t id;
  std::optional<size_t> manager_id;   // must map to id
  std::string name;
  std::string position;
};
}   // namespace DB
