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
        Task(const std::type_info &input_type,
             const std::type_info &output_type,
             const std::string &name);

        Task(const Task &) = delete;
        Task &operator=(const Task &) = delete;
        Task(Task &&) = default;
        Task &operator=(Task &&) = default;

        const std::string &name_str() const;
        virtual std::any process(std::any) const override;

    private:
        const std::function<std::any(std::any)> m_processor;
        const std::string m_name;
    };
}
