// This example is wierd, but it shows how to explicitely delete a
// special member function.
struct A
{
  ~A() = delete;
};

int
main()
{
  // This compiles, because we're not deleting the object.
  A *p = new A();
  // A a; // Error: a local variable has to have a destructor called.
}
