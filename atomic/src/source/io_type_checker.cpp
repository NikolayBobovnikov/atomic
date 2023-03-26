#include <string>
#include <stdexcept>
#include "io_type_checker.h"

using namespace std;

namespace
{
    using namespace Quant;

    unique_ptr<IDataTypeChecker> make_data_checker(type_index ti)
    {
        static const string type_not_supported_prfix = "Type is not supported: ";

        if (ti == type_index(typeid(void)))
        {
            // if not defined
            return make_unique<DefaultDataTypeChecker>();
        }
        if (ti == type_index(typeid(int)))
        {
            return make_unique<DataTypeChecker<int>>();
        }
        if (ti == type_index(typeid(size_t)))
        {
            return make_unique<DataTypeChecker<size_t>>();
        }
        if (ti == type_index(typeid(float)))
        {
            return make_unique<DataTypeChecker<float>>();
        }
        if (ti == type_index(typeid(double)))
        {
            return make_unique<DataTypeChecker<double>>();
        }

        throw invalid_argument(type_not_supported_prfix + ti.name());
    }
}

namespace Quant
{
    void IOTypeChecker::set_input_checker(type_index type)
    {
        m_in = make_data_checker(type);
    }

    void IOTypeChecker::set_output_checker(type_index type)
    {
        m_out = make_data_checker(type);
    }

    void IOTypeChecker::check_input(data_t data) const
    {
        return m_in->check(data);
    }

    void IOTypeChecker::check_output(data_t data) const
    {
        return m_out->check(data);
    }

}