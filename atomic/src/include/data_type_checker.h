#pragma once

#include <memory>
#include "data_types.h"

namespace Quant
{
    struct IDataTypeChecker
    {
        virtual void check(data_t data) const = 0;
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

    struct IODataTypeChecker
    {
        virtual ~IODataTypeChecker() = default;

        void set_input_checker(std::unique_ptr<IDataTypeChecker>);

        void set_output_checker(std::unique_ptr<IDataTypeChecker>);

        void check_input(data_t data) const;

        void check_output(data_t data) const;

    protected:
        IODataTypeChecker() = default;

    private:
        std::unique_ptr<IDataTypeChecker> m_in;
        std::unique_ptr<IDataTypeChecker> m_out;
    };

}