template <typename T>
void foo(const T &t);

// The two below don't specialize the one above.

// template <>
// void foo(int &);

// template <>
// void foo(bool);
