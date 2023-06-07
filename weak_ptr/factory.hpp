#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <map>
#include <memory>

template <typename V, typename K>
auto
factory(const K &k)
{
  static std::map<K, std::weak_ptr<V>> cache;

  std::shared_ptr<V> sp;

  auto i = cache.find(k);

  if (i != cache.end())
    sp = i->second.lock();

  if (sp == nullptr)
    {
      sp = std::make_shared<V>(k);
      cache.insert(i, make_pair(k, sp));
    }

  return sp;
}

#endif // FACTORY_HPP
