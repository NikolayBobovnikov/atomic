#pragma once

#include <variant>
#include "variant_helper.h"

namespace Quant
{
    // supported data types; string for logging error messages in the output inplace
    using data_t = std::variant<int, size_t, float, double>;

    using data_out_t = variant_append<data_t, std::string>;
    // using data_out_t = std::variant<int, size_t, float, double, std::string>;
}