#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <exception>
#include <string>
#include "task.h"
#include "processor.h"
namespace Quant
{
  struct Pipeline : ProcessorBase
  {
    Pipeline(const std::type_info &input_type, const std::type_info &output_type);
    ~Pipeline() = default;

    std::any process(std::any data) const override;

    void add(std::unique_ptr<Task> task);

  private:
    std::vector<std::unique_ptr<Task>> tasks;
  };

}
