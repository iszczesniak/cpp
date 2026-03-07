int main()
{
  int x = 1;
  // Expression 1 doesn't have identity.
  // &1 ; // Error.

  // Default-initialize y.
  int y = {};
  // Expression {} doesn't have identity.
  // &{} ; // Error.
}
