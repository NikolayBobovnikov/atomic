#pragma once

#include <typeinfo>
#include <typeindex>

namespace Quant
{

    // parametrize by input and output types
    struct IOTypeInfo
    {
        IOTypeInfo();
        IOTypeInfo(const std::type_info &input_type, const std::type_info &output_type);

        void set_in_type(const std::type_info &type);
        void set_out_type(const std::type_info &type);
        void set_in_type(std::type_index index);
        void set_out_type(std::type_index index);
        const std::type_index &get_in_type() const;
        const std::type_index &get_out_type() const;

    private:
        std::type_index m_input_type_index;
        std::type_index m_output_type_index;
    };
}
