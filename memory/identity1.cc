int main()
{
  // Uninitialized.
  int x;

  // Default-initialized.
  int y = {};
  // Expression {} doesn't have identity.
  // &{}; // Error.

  // Initialized with 1.
  int x = 1;
  // Expression 1 doesn't have identity.
  // &1; // Error.
}
