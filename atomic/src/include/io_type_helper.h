#include <typeindex>
#include <string>

namespace Quant
{
    struct IOTypeHelper
    {
        static std::type_index parse_type_index(std::string s);
    };
}