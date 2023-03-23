#pragma once

#include <any>
#include <typeinfo>
#include <typeindex>

namespace Quant
{
    struct IProcessor
    {
        IProcessor(const std::type_info &input_type, const std::type_info &output_type);
        virtual ~IProcessor() = default;
        virtual std::any process(std::any) const = 0;
        virtual std::type_index input_type() const;
        virtual std::type_index output_type() const;

    protected:
        const std::type_index m_input_type;
        const std::type_index m_output_type;
    };
}
