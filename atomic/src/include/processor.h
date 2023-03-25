#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include "variant_helper.h"
#include <unordered_map>
#include "data_types.h"
#include "data_type_checker.h"
#include "task_parameters.h"
namespace Quant
{
  // main interface for the pipeline and tasks
  struct IProcessor
  {
    virtual data_t process(data_t) const = 0;
    virtual ~IProcessor() = default;
  };

  struct IParametrized
  {
    virtual ~IParametrized() = default;
    virtual void set_parameters(TaskParameters params){/* no parameters by default*/};
  };

  // parametrize by input and output types
  struct TaskProcessor : IProcessor, IParametrized
  {
    virtual ~TaskProcessor() = default;
  };

  // parametrize by input and output types
  struct DataTypeInfo
  {
    DataTypeInfo(const std::type_info &input_type, const std::type_info &output_type);
    std::type_index get_in_type_index() const;
    std::type_index get_out_type_index() const;
    const std::type_info &get_in_type() const;
    const std::type_info &get_out_type() const;

  private:
    const std::type_info &m_input_type_info;
    const std::type_info &m_output_type_info;
    const std::type_index m_input_type;
    const std::type_index m_output_type;
  };
}
