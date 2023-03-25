#pragma once

#include <string>
#include <memory>
#include "processor.h"
#include "io_type_info.h"
#include "io_type_checker.h"

namespace Quant
{
  struct TaskProcessor;
  struct Task : IOTypeInfo, IProcessor, IOTypeChecker
  {
    Task(const std::type_info &input_type,
         const std::type_info &output_type,
         std::string name);

    Task(const Task &) = delete;
    Task &operator=(const Task &) = delete;
    Task(Task &&) = default;
    Task &operator=(Task &&) = default;
    ~Task(); // define where pipml type is complete

    virtual data_t process(data_t) const override;
    const std::string &name() const;
    void set_processor(std::unique_ptr<TaskProcessor> processor);

  private:
    const std::string m_name;
    std::unique_ptr<TaskProcessor> m_processor;
  };
}
