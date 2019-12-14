// Who should destroy the allocated data?  Should the data be
// destroyed by the foo function?

void
foo(int *p)
{
  // Do sth with p.
  try
    {
      // An exception could be thrown here.
      throw true;

      // We should have destroyed the data with the array version of
      // delete (i.e., delete [] p), because it was allocated with the
      // array version of new.
      delete p;
    }
  catch(bool)
    {
      // It's easy to forget this delete:
      delete p;      
    }
}

int
main()
{
  // The problem is brewing: we use a pointer to integer to point to
  // the begining of an array of integers.
  int *p = new int[5];
  foo(p);

  // This is the second delete.
  delete [] p;
}
