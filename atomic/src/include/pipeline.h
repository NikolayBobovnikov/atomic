#pragma once

#include <memory>
#include <vector>
#include <string>
#include "parameters.h"
#include "processor.h"
#include "io_type_info.h"

namespace Quant
{
  struct Task;
  struct Pipeline : IProcessor, IOTypeInfo
  {
    Pipeline(const std::type_info &input_type, const std::type_info &output_type);
    ~Pipeline(); // define where pipml type is complete

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
