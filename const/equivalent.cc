// Top-level qualifiers do not go to the function signature.

void foo(int);

// Redeclaration of the above.
void foo(const int);

void foo(int)
{
}

// Redefinition: error.

// void foo(const int)
// {
// }

void foo(int *)
