#pragma once

#include <optional>
#include <string>

namespace DB
{
struct EmployeeDTO
{
  EmployeeDTO() = default;
  EmployeeDTO(size_t _id, std::optional<size_t> _manager_id, const std::string &_name, const std::string &_position)
      : id(_id), manager_id(_manager_id), name(_name), position(_position)
  {
  }

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
