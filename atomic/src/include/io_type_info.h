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
        IOTypeInfo(std::type_index input_type, std::type_index output_type);
        ~IOTypeInfo() = default;

        // is overridden in Task because of deducing input type later if not defined
        // TODO: code smell
        virtual void set_in_type(std::type_index index);
        void set_in_type(const std::type_info &type);
        void set_out_type(const std::type_info &type);
        void set_out_type(std::type_index index);
        const std::type_index &get_in_type() const;
        const std::type_index &get_out_type() const;

        bool is_input_type_defined() const;
        bool is_output_type_defined() const;

    private:
        std::type_index m_input_type_index;
        std::type_index m_output_type_index;
    };
}
