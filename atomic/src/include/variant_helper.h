#pragma once

#include <variant>
namespace Quant
{
  // type mathing in std visit
  template <class... Ts>
  struct overload : Ts...
  {
    using Ts::operator()...;
  };
  template <class... Ts>
  overload(Ts...) -> overload<Ts...>;

  // append type to std variant
  template <class V, class T>
  struct variant_append_helper;

  template <class... A, class T>
  struct variant_append_helper<std::variant<A...>, T>
  {
    using type = std::variant<A..., T>;
  };

  template <class V, class T>
  using variant_append = typename variant_append_helper<V, T>::type;

  // variant cast
  template <class... Args>
  struct variant_cast_proxy
  {
    std::variant<Args...> v;

    template <class... ToArgs>
    operator std::variant<ToArgs...>() const
    {
      return std::visit([](auto &&arg) -> std::variant<ToArgs...>
                        { return arg; },
                        v);
    }
  };

  template <class... Args>
  auto variant_cast(const std::variant<Args...> &v) -> variant_cast_proxy<Args...>
  {
    return {v};
  }
}