#include <filesystem>
#include <memory>
#include <stdexcept>
#include "pipeline.h"

namespace Quant
{
    struct BatchProcessor
    {
        BatchProcessor() = delete;
        BatchProcessor(std::unique_ptr<Pipeline>);
        virtual ~BatchProcessor() = default;

        virtual void batch_process(const std::filesystem::path &input, const std::filesystem::path &output) const = 0;
        const Pipeline &get_pipeline() const;

    protected:
        std::unique_ptr<Pipeline> m_pipeline;
    };

    // TODO
    struct ParallelProcessor : BatchProcessor
    {
        void batch_process(const std::filesystem::path &input, const std::filesystem::path &output) const override
        {
            throw std::logic_error("Not implemented");
        }
    };

}