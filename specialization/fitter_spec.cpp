template <typename T>
void foo(T t);

template <typename T>
void foo(T *t);

// Specialization #1: only the first primary template is candidate.
template <>
void foo(int);

// Specialization #2: both primary templates are candidate.
template <>
void foo(int *);
