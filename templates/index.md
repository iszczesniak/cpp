---
title: Templates
---

# Templates

A template can be of a:

* function,

* class, struct, union,

* member (a member function, a member field),

* type alias,

* variable.

A template declaration or definition begins with the `template`
keyword, and it has this syntax:

```
template <parameter list>
```

We say a template is *parametrized*, because it has a list of
parameters that we call **template parameters**.

When we call a function defined with a template, then after the
function name we can provide **template arguments** in `<>`.
Instantiation **substitutes** a template argument for a template
parameter in a template, i.e., puts an argument where a parameter is.

# Template parameters

Template parameters are defined in a parameter list, where they are
comma-separated.  A parameter is defined by a kind and an optional
name.  There are three kinds: type, value, and template.  An example
with three parameters: T of the type kind, N of the value kind, and
C of the template kind.

```
template <typename T, int N, template<typename> typename C>
```

## Parameter kind: type

It's the most common kind.  We declare a type parameter with `typename
T`, where `typename` says it's a *type parameter*, and `T` is the name
of the parameter.  We can also declare equivalently a type parameter
with `class T`, but `typename T` is preferred in modern C++.

Instantiation can substitute `T` with any type: a built-in type,
user-defined type, even `void`. `T` doesn't have to meet any
requirements, e.g., inheriting from an interface class.  The
requirements on type `T` follow from how we use the type in the
template definition, i.e., whether we, e.g.,:

* default-construct a value of type `T`,

* add, using `operator+`, the values of type `T`,

* dereference, using `operator&`, a value of type `T`,

* pass to some function, e.g., `push_back`, a value of type `T`,

* output to `std::ostream` a value of type `T` using `operator<<`.

This is an example of a function template with a type parameter, where
the compiler is able to **deduce the template argument**, so that we
do not have to provide it explictly when calling the function:

{% highlight c++ %}
{% include_relative print1.cc %}
{% endhighlight %}

### Value parameter

A parameter of this kind we define with `some_type I`, where
`some_type` is a type, e.g., `int`.  Type `some_type` cannot be any,
only some types allowed, with integer types being the most popular.
Instantiation substitutes the parameter name with a value of that
type, e.g., `1` for an template parameter declared as `int I`.

An example of a template parameter declaration of the value kind:

```
template <int N>
```

This is an example of a function template with a value parameter `N`:

{% highlight c++ %}
{% include_relative print2.cc %}
{% endhighlight %}

This is an example of a function template with a value parameter `N`,
where `N` has to be *given explicitely* by a programmer, and `T` is
*deduced* by a compiler:

{% highlight c++ %}
{% include_relative print3.cc %}
{% endhighlight %}

This is an example of a recursive function template.  The recursion is
terminated by the compile-time conditional statement `if constexpr`

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

### Template parameter

A template parameter `T` can be of a template type, i.e., at compile
time the parameter is replaced with a template.  We declare a template
paramater `T` as a template type like this, where `param-type-list` is
a list of parameter types of template `T`:

```
template <param-type-list> typename T
```

This is an example of how a template with a template parameter begins:

```
template <template <param-type-list> typename T>
```

Here's an example:

{% highlight c++ %}
{% include_relative template1.cc %}
{% endhighlight %}

`__PRETTY_FUNCTION__` is replaced by GCC with the function name, and
the template parameters, so that we can learn what the paremeters
really are.

This is a modified example from above.  This time the template-type
template argument C can accept template types which accept two
arguments: the first being the type, the second being the value.

{% highlight c++ %}
{% include_relative template2.cc %}
{% endhighlight %}

<!-- LocalWords: lvalue lvalues rvalue -->
