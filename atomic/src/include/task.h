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
  struct ICheckType
  {
    virtual void check(data_t data) const = 0;
  };

  template <class T>
  struct CheckType : ICheckType
  {
    using type = T;

    // throw if data_t doesn't contain T
    void check(data_t data) const override
    {
      std::get<T>(data);
    }
  };

  struct IInOut
  {
    IInOut(std::unique_ptr<ICheckType> in, std::unique_ptr<ICheckType> out)
        : m_in(std::move(in)), m_out(std::move(out))
    {
    }

    virtual ~IInOut() = default;

    void check_input(data_t data) const
    {
      return m_in->check(data);
    }

    void check_output(data_t data) const
    {
      return m_out->check(data);
    }

  private:
    std::unique_ptr<ICheckType> m_in;
    std::unique_ptr<ICheckType> m_out;
  };

  struct Task : ProcessorBase
  {
    Task(const std::type_info &input_type,
         const std::type_info &output_type,
         std::string name);

    // static std::unique_ptr<Task> Create(const std::type_info& input_type,
    //                                     const std::type_info& output_type,
    //                                     std::string name,
    //                                     std::unique_ptr<IProcessor> processor);

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
