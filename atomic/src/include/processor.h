#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include "variant_helper.h"
#include <unordered_map>
#include "data_types.h"
#include "data_type_checker.h"
namespace Quant
{
  // main interface for the pipeline and tasks
  struct IProcessor
  {
    virtual data_t process(data_t) const = 0;
    virtual ~IProcessor() = default;
  };

  struct TaskParameters
  {
    std::vector<data_t> args;
    std::unordered_map<std::string, data_t> kwargs;
  };

  struct IParametrized
  {
    virtual ~IParametrized() = default;
    virtual void set_parameters(TaskParameters params){/* no parameters by default*/};
  };

  // parametrize by input and output types
  struct TaskProcessorBase : IProcessor, IODataTypeChecker, IParametrized
  {
  };

  // parametrize by input and output types
  struct DataTypeInfo
  {
    DataTypeInfo(const std::type_info &input_type, const std::type_info &output_type);
    std::type_index input_type() const;
    std::type_index output_type() const;

  private:
    const std::type_index m_input_type;
    const std::type_index m_output_type;
  };
}
