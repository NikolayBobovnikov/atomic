#pragma once

#include <functional>
#include <variant>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <memory>
#include "task.h"
#include "processor.h"
#include "variant_helper.h"

namespace Quant
{
    struct Task : ProcessorBase
    {
      Task(const std::type_info& input_type,
        const std::type_info& output_type,
        std::string name);

      //static std::unique_ptr<Task> Create(const std::type_info& input_type,
      //                                    const std::type_info& output_type,
      //                                    std::string name,
      //                                    std::unique_ptr<IProcessor> processor);

        Task(const Task &) = delete;
        Task &operator=(const Task &) = delete;
        Task(Task &&) = default;
        Task &operator=(Task &&) = default;

        virtual data_t process(data_t) const override;
        const std::string &name() const;
        void set_processor(std::unique_ptr<IProcessor> processor);
        
    private:
        const std::string m_name;
        std::unique_ptr<IProcessor> m_processor;
    };
}
