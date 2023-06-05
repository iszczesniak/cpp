template <typename Edge, typename... Props>
struct vertex: Props...
{
  vertex(Props &&... props): Props(std::forward<Props>(props))...
  {
  }

  // constexpr auto operator <=> (const weight &) const = default;
};

template <typename Weight>
struct weight
{
  using weight_type = Weight;
  weight_type m_weight;

  weight(const weight_type &weight): m_weight(weight)
  {
  }

  constexpr auto operator <=> (const weight &) const = default;
};

// The non-const getter.
template <typename Weight>
constexpr auto &
get_weight(weight<Weight> &a)
{
  return a.m_weight;
}

// The const getter.
template <typename Weight>
constexpr const auto &
get_weight(const weight<Weight> &a)
{
  return a.m_weight;
}

template <typename Weight>
std::ostream &
operator << (std::ostream &os, const weight<Weight> &w)
{
  os << "weight = " << w.m_weight;

  return os;
}

int
main()
{
}
