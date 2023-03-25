#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <variant>
#include <typeinfo>
#include <typeindex>
#include <exception>
#include <string>
#include "task.h"
#include "processor.h"
namespace Quant
{
  struct Pipeline : IProcessor, DataTypeInfo
  {
    Pipeline(const std::type_info &input_type, const std::type_info &output_type);
    ~Pipeline() = default;

    void validate() const;
    data_t process(data_t data) const override;
    data_out_t process_ext(data_t data) const noexcept;

    void add_task(std::unique_ptr<Task> task);
    void add_task(const std::type_info &input_type,
                  const std::type_info &output_type,
                  std::string task_name,
                  TaskParameters task_params);

  private:
    std::vector<std::unique_ptr<Task>> tasks;
  };

}
