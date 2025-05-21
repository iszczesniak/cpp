void foo(int &);
void foo(const int &);

int main()
{
  // Literal 1 is an rvalue of nonconst integer type.  Nonconst
  // reference is preferred because:
  //
  // [over.ics.rank#3.2.6]: S1 and S2 bind “reference to T1” and
  // “reference to T2”, respectively ([dcl.init.ref]), where T1 and T2
  // are not the same type, and T2 is reference-compatible with T1
  //
  // [dcl.init.ref#4]: “cv1 T1” is reference-compatible with “cv2 T2”
  // if a prvalue of type “pointer to cv2 T2” can be converted to the
  // type “pointer to cv1 T1” via a standard conversion sequence.
  foo(1);
}
