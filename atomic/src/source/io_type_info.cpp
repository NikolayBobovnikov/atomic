#include "io_type_info.h"

namespace Quant
{
    IOTypeInfo::IOTypeInfo(const std::type_info &input_type, const std::type_info &output_type)
        : m_input_type_info(input_type), m_output_type_info(output_type)
    {
    }
    void IOTypeInfo::set_in_type(const std::type_info &type)
    {
    }
    void IOTypeInfo::set_out_type(const std::type_info &type)
    {
    }

    const std::type_info &IOTypeInfo::get_in_type() const
    {
        return m_input_type_info;
    }
    const std::type_info &IOTypeInfo::get_out_type() const
    {
        return m_output_type_info;
    }

}
