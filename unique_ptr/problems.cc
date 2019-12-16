// Who should destroy the allocated data?  Should the data be
// destroyed by the foo function?

void
foo(int *p)
{
  // By mistake the array delete is used.
  delete [] p;
}

int *
factory()
{
  int *p;

  try
    {
      p = new int;

      // Work on the new data.  An exception could be thrown here.
      throw true;

      return p;
    }
  catch(bool)
    {
      // It's easy to forget this delete:
      delete p;      
    }

  return nullptr;
}

int
main()
{
  // The problem is brewing: we use a pointer to integer to point to
  // the begining of an array of integers.
  int *p = factory();

  // I'm thinking that foo will use, but not destroy the data.
  foo(p);

  // This is the second delete.
  delete p;
}
