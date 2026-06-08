template <typename T>
void foo(const T &t);

// Specialization #1: doesn't specialize the primary template.  The
// deduction fails, because the primary template accepts its argument
// by a const reference, and this specialization accepts by value.

// template <>
// void foo(bool);

// Specialization #2: doesn't specialize the primary template.  The
// deduction fails, because the primary template accepts its arugment
// by a const reference, and this specialization accepts by a
// non-const reference.  T of the primary template can't be deduced
// such that it gobbles the const of the primary template.

// template <>
// void foo(int &);
