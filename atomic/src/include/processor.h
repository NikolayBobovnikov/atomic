#pragma once

#include <string>
#include <variant>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <unordered_map>

namespace Quant
{
    // supported data types; string for logging error messages in the output inplace
    using data_t = std::variant<int, size_t, float, double, std::string>; 

    // main interface for the pipeline and tasks
    struct IProcessor
    {
      virtual data_t process(data_t) const = 0;
      virtual ~IProcessor() = default;
    };

    struct TaskParameters {
      std::vector<data_t> args;
      std::unordered_map<std::string, data_t> kwargs;
    };

    struct IParametrized {
      virtual ~IParametrized() = default;
      virtual void set_parameters(TaskParameters params) = 0;
    };

    // parametrize by input and output types
    struct ProcessorBase : IProcessor
    {
      ProcessorBase(const std::type_info& input_type, const std::type_info& output_type);
      std::type_index input_type() const;
      std::type_index output_type() const;

    private:
      const std::type_index m_input_type;
      const std::type_index m_output_type;
    };
}
