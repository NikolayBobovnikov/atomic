#include "data_type_checker.h"

namespace Quant
{
    using namespace std;

    void IOTypeChecker::set_input_checker(unique_ptr<IDataTypeChecker> in)
    {
        m_in = move(in);
    }

    void IOTypeChecker::set_output_checker(unique_ptr<IDataTypeChecker> out)
    {
        m_out = move(out);
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