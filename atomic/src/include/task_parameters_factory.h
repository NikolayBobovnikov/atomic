#include "settings.h"
#include "parameters.h"

namespace Quant
{
    struct TaskParametersFactory
    {
        static TaskParameters Create(Settings::Task);
    };
}