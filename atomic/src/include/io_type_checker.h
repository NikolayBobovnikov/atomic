#pragma once

#include <memory>
#include <typeindex>
#include "io_types.h"

namespace Quant
{
    struct IDataTypeChecker
    {
        virtual void check(data_t data) const = 0;
        virtual ~IDataTypeChecker() = default;
    };

    template <class T>
    struct DataTypeChecker : IDataTypeChecker
    {
        // throw if data_t doesn't contain T
        void check(data_t data) const override
        {
            std::get<T>(data);
        }
    };

    struct DefaultDataTypeChecker : IDataTypeChecker
    {
        void check(data_t data) const override {}
    };

    // TODO
    template <class T>
    struct OutputTypeConverter
    {
        // throw if data_t doesn't contain T
        T convert(data_t data) const override
        {
            return std::visit(overload{
                                  [](auto value) -> T
                                  { return static_cast<T>(value); },
                              },
                              data);
        }
    };

    struct IOTypeChecker
    {
        virtual ~IOTypeChecker() = default;

        void set_input_checker(std::type_index);

        void set_output_checker(std::type_index);

        void check_input(data_t data) const;

        void check_output(data_t data) const;

    protected:
        IOTypeChecker() = default;

    private:
        std::unique_ptr<IDataTypeChecker> m_in;
        std::unique_ptr<IDataTypeChecker> m_out;
    };

}