#include "io_type_info.h"

namespace Quant
{
    using std::type_index;
    using std::type_info;

    IOTypeInfo::IOTypeInfo()
        : m_input_type_index(typeid(void)), m_output_type_index(typeid(void))
    {
    }

    IOTypeInfo::IOTypeInfo(const type_info &input_type, const type_info &output_type)
        : m_input_type_index(input_type), m_output_type_index(output_type)
    {
    }
    IOTypeInfo::IOTypeInfo(std::type_index input_type, std::type_index output_type)
        : m_input_type_index(input_type), m_output_type_index(output_type)
    {
    }

    void IOTypeInfo::set_in_type(const type_info &type)
    {
        m_input_type_index = std::type_index(type);
    }
    void IOTypeInfo::set_out_type(const type_info &type)
    {
        m_output_type_index = std::type_index(type);
    }
    void IOTypeInfo::set_in_type(std::type_index index)
    {
        m_input_type_index = index;
    }
    void IOTypeInfo::set_out_type(std::type_index index)
    {
        m_output_type_index = index;
    }

    const type_index &IOTypeInfo::get_in_type() const
    {
        return m_input_type_index;
    }
    const type_index &IOTypeInfo::get_out_type() const
    {
        return m_output_type_index;
    }

}
