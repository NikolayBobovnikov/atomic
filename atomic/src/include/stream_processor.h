#include "batch_processor.h"

namespace Quant
{
    struct StreamProcessor : BatchProcessor
    {
        StreamProcessor(std::unique_ptr<Pipeline>);
        void batch_process(const std::filesystem::path &input, const std::filesystem::path &output) const override;
    };
}