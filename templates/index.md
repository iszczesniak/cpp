---
title: Templates
---

# Introduction

Generic programming in C++ is supported by templates.  There can be
templates of:

* functions,
* classes,
* members (of classes),
* types (aliases),
* variables.

A template declaration or definition begins with the `template`
keyword, and it has this syntax:

```
template <parameter list>
```

We say a template is *parametrized*, because it has a list of
parameters.

## Parameter list

The list has to have at least one parameter.  The parameters in a list
are seprated by a comma.  Each paramter in the list is declared with
its type and name.  The types can be: type, value, and template.  For
instance:

```
template <typename T, int N, template<typename> typename C>
```

### Type parameter

We declare a type parameter with \code{typename T}, where
\code{typename} says it's a type parameter, and T is the name of the
parameter.  We can also declare equivalently a type parameter with
\code{class T}, but \code{typename T} is preferred in modern C++.  T
represents a type, and during compilation T is replaced with the
required types, like \code{int} or the user class \code{myclass}.

Type T doesn't have to be a class type (it can be a built-in type) or
meet some requirements (like inherit from an interface class).  The
requirements on type T follow from how we use it in the template.  For
instance:

\begin{itemize}
\item Do we default-construct values of type T?
\item Do we add, using \code{+}, the values of type T?
\item Do we dereference, using \code{&}, the values of type T?
\item Do we call some special function, e.g., \code{push_back} for the values of type T?
\item Do we output values of type T to std::ostream using \code{<<}?
\end{itemize}

This is an example of a function template with a type parameter T:

\lstinputlisting{print1.cc}

\subsubsection{Value parameter}

A parameter can also be a value parameter.  Such a parameter is also
called a non-type parameter.  Value parameters can be of different
types.  A typical example is "int", but other types are possible,
though not very common.

\begin{lstlisting}
template <int N>
\end{lstlisting}

This is an example of a function template with a value parameter N:

\lstinputlisting{print2.cc}

This is an example of a function template with a value parameter N,
where N has to be given explicitely, and T is deduced:

\lstinputlisting{print3.cc}

This is an example of a recursive function template.  The recursion is
terminated by the function specialization for N = 0.  There is no
partial specialization of function templates, only the full
specialization, which means that we also have to specialize the
terminating function for the type, i.e., int.

\lstinputlisting{print4.cc}

\subsubsection{Template parameter}

A template-type template parameter accepts a template as an argument.
In the definition of the parameter, we specify the list of parameters
of a template that can be an argument of this parameter.

\code{__PRETTY_FUNCTION__} is replaced by GCC with the function name,
and the template parameters, so that we can learn what the paremeters
really are.

\lstinputlisting{template_type.cc}

This is a modified example from above.  This time the template-type
template argument C can accept template types which accept two
arguments: the first being the type, the second being the value.

\lstinputlisting{template_type2.cc}

\end{document}


<!-- LocalWords: lvalue lvalues rvalue -->
