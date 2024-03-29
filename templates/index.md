---
title: Templates
---

# Templates

There can be templates of:

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

We declare a type parameter with `typename T`, where `typename` says
it's a *type parameter*, and `T` is the name of the parameter.  We can
also declare equivalently a type parameter with `class T`, but
`typename T` is preferred in modern C++.  `T` represents a type, and
during compilation `T` is replaced with a type, e.g., `int` or the
user class `myclass`.

`T` can become any type: a built-in type, user-defined type, even
`void`. `T` doesn't have to meet some requirements, e.g., inheriting
from an interface class.  The requirements on type `T` follow from how
we use the type in the template definition, i.e., whether we:

* default-construct a value of type `T`,

* add, using `operator+`, the values of type `T`,

* dereference, using `operator&`, a value of type `T`,

* pass to some function, e.g., `push_back`, a value of type `T`,

* output to `std::ostream` a value of type `T` using `operator<<`.

This is an example of a function template with a type parameter `T`:

{% highlight c++ %}
{% include_relative print1.cc %}
{% endhighlight %}

### Value parameter

A parameter can also be a *value parameter*.  A value parameter is
asigned a value of some type, typically of `int`, but other types are
possible, though not very common:

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
