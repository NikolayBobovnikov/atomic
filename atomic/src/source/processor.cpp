#include "processor.h"

namespace Quant
{
    IProcessor::IProcessor(const std::type_info &input_type, const std::type_info &output_type)
        : m_input_type(std::type_index(input_type)), m_output_type(std::type_index(output_type))
    {
    }

    std::type_index IProcessor::input_type() const
    {
        return m_input_type;
    }
    std::type_index IProcessor::output_type() const
    {
        return m_output_type;
    }

}
