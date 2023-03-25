#pragma once

#include <typeinfo>
#include <typeindex>

namespace Quant
{
    // parametrize by input and output types
    struct IOTypeInfo
    {
        IOTypeInfo(const std::type_info &input_type, const std::type_info &output_type);
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
