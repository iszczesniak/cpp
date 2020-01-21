#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct A
{
  string m_text;

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  ~A()
  {
    cout << "dtor:" << m_text << endl;
  }
};

int main (void)
{
  // sp takes the ownership.
  shared_ptr sp(new A("A1"));
  sp.reset(new A("A2"));
}

  \begin{itemize}
  \item Oddanie pod zarządzanie: \code{shared_ptr<A> sp(new A());}
  \item Oddanie pod zarządzanie: \code{sp.reset(new A());}
  \item Kopiowanie obiektów: \code{shared_ptr<A> sp2(sp);}
  \item Kopiowanie obiektów: \code{sp2 = sp;}
  \item Przenoszenie obiektów: \code{shared_ptr<A> sp2(move(sp));}
  \item Przenoszenie obiektów: \code{sp2 = move(sp);}
  \item Niszczenie: tego nie robimy, to odbywa się automatycznie.
  \end{itemize}
