#pragma once

#include <functional>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <string>
#include "task.h"
#include "processor.h"

namespace Quant
{
    struct Task : ProcessorBase
    {
    public:
        Task(
            const std::type_info &input_type,
            const std::type_info &output_type,
            std::function<std::any(std::any)> processor,
            const std::string &name);

        Task(const Task &) = delete;
        Task &operator=(const Task &) = delete;
        Task(Task &&) = default;
        Task &operator=(Task &&) = default;

        virtual std::any process(std::any data) const override;
        const std::string &name() const;

    private:
        std::function<std::any(std::any)> m_processor;
        std::string m_name;
    };
}
