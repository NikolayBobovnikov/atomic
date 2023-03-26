#include "batch_processor.h"

namespace Quant
{
    BatchProcessor::BatchProcessor(std::unique_ptr<Pipeline> pipeline)
        : m_pipeline(move(pipeline))
    {
    }

    const Pipeline &BatchProcessor::get_pipeline() const
    {
        return *m_pipeline;
    }
}