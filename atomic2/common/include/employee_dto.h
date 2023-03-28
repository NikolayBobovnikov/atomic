#pragma once

#include <optional>
#include <string>

namespace DB
{
struct EmployeeDTO
{
  EmployeeDTO() = default;
  EmployeeDTO(const std::string &_name, const std::string &_position) : name(_name), position(_position) {}

  size_t id;
  std::optional<size_t> manager_id;   // must map to id
  std::string name;
  std::string position;
};

struct TestEmployee : EmployeeDTO
{
  TestEmployee() : EmployeeDTO("Test employee name", "Test position") {}
};

}   // namespace DB
