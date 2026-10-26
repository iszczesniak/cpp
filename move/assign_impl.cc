#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B() {}

  // The copy assignment operator ------------------------------------

  // The copy assignment operator has to copy the base and the member
  // objects of the source object.
  B & operator=(const B &source)
  {
    // Even though member function A::operator= expects two arguments,
    // we pass only one, because the member object (i.e., *this) is
    // implicitly passed as the first argument, just like for any
    // member function called from a member function.
    A::operator=(source);
    // We can assign (as above) to the base object this way too:
    // static_cast<A &>(*this) = source;
    m_s = source.m_s;
    return *this;
  }

  // Above is the default implementation which we can get with:
  // B &operator=(const B &) = default;

  // The move assignment operator ------------------------------------

  // The implementation of the move assignment operator has to use the
  // std::move function to move the base and the member objects of the
  // source object, otherwise they would be copied.
  B & operator=(B &&source)
  {
    A::operator=(std::move(source));
    // We can assign (as above) to the base object this way too:
    // static_cast<A &>(*this) = std::move(source);
    m_s = std::move(source.m_s);
    return *this;
  }

  // Above is the default implementation which we can get with:
  // B &operator=(B &&) = default;
};

int
main()
{
  B b1, b2;
  b1 = b2;
  b1 = std::move(b2);
  b1 = B();
}
