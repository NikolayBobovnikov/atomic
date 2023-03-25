#include <memory>
#include "settings.h"

namespace Quant
{
    struct Pipeline;
    struct PipelineFactory
    {
        static std::unique_ptr<Pipeline> Create(PipelineSettings);

        ~PipelineFactory(); // define where pipml type is complete
    };
}