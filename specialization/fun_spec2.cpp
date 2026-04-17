template <typename T>
void foo(const T &t);

// The one below doesn't specialize the one above.  T can't be deduced
// such that it gobbles the const.

// template <>
// void foo(int &);
