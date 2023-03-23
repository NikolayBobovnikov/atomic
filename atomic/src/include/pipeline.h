#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <exception>
#include <string>
namespace Quant
{
  struct Task
  {
    virtual std::any process(std::any) const = 0;
    virtual std::type_index input_type() const = 0;
    virtual std::type_index output_type() const = 0;
    virtual const std::string &name() const = 0;
  };

  struct AbstractTask : Task
  {
  public:
    virtual std::type_index input_type() const override
    {
      return m_input_type;
    }
    virtual std::type_index output_type() const override
    {
      return m_output_type;
    }

  protected:
    AbstractTask(const std::type_info &input_type, const std::type_info &output_type)
        : m_input_type(std::type_index(input_type)), m_output_type(std::type_index(output_type))
    {
    }

    const std::type_index m_input_type;
    const std::type_index m_output_type;
  };

  struct ConcreteTask : AbstractTask
  {
    ConcreteTask(
        const std::type_info &input_type,
        const std::type_info &output_type,
        std::function<std::any(std::any)> processor,
        const std::string &name)
        : AbstractTask(input_type, output_type), m_processor(processor), m_name(name)
    {
    }

    virtual std::any process(std::any data) const override
    {
      return m_processor(data);
    }

  private:
    std::function<std::any(std::any)> m_processor;
    std::string m_name;
  };

  struct Pipeline : AbstractTask
  {
    Pipeline(const std::type_info &input_type, const std::type_info &output_type)
        : AbstractTask(input_type, output_type)
    {
    }

    virtual const std::string &name() const override;

    std::any process(std::any data) const override;

    void add(std::unique_ptr<Task> task);

  private:
    std::vector<std::unique_ptr<Task>> tasks;
  };

}
