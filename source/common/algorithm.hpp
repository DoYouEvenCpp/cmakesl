#pragma once

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <utility>

namespace cmsl {
namespace details {
template <size_t N>
struct contains_helper;

template <size_t N>
struct contains_helper : contains_helper<N - 1>
{
};

template <>
struct contains_helper<0>
{
};

template <typename Container, typename Value>
auto contains_impl(Container&& container, Value&& value, contains_helper<1>)
  -> decltype(std::declval<Container>().find(value) !=
              std::declval<Container>().end())
{
  return container.find(value) != container.cend();
}

template <typename Container, typename Value>
bool contains_impl(Container&& container, Value&& value, contains_helper<0>)
{
  return std::find(std::cbegin(container), std::cend(container), value) !=
    std::cend(container);
}
}

template <typename Container, typename Value>
bool contains(Container&& container, Value&& value)
{
  return details::contains_impl(std::forward<Container>(container),
                                std::forward<Value>(value),
                                details::contains_helper<1>{});
}

template <typename Container, typename Predicate>
bool contains_if(Container&& container, Predicate&& pred)
{
  return std::find_if(std::cbegin(container), std::cend(container), pred) !=
    std::cend(container);
}

inline bool starts_with(cmsl::string_view str, cmsl::string_view pattern)
{
  return str.size() >= pattern.size() &&
    cmsl::string_view{ str.data(), pattern.size() } == pattern;
}

template <typename K, typename T, typename H, typename KE, typename A,
          typename Pred>
void remove_if(std::unordered_multimap<K, T, H, KE, A>& map, Pred&& predicate)
{
  for (auto it = begin(map); it != end(map);) {
    if (predicate(*it)) {
      it = map.erase(it);
    } else {
      ++it;
    }
  }
}
}
