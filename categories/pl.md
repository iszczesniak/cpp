---
title: Kategorie wartości wyrażeń
---

# Wprowadzenie

Kategorie wartości wyrażeń to podstawa, ale trudno je zrozumieć.
Chodzi o szczegóły dotyczące **l-wartości** i **r-wartości**, które w
codziennym programowaniu uchodzą naszej uwadze.

Żeby łatwiej zrozumieć znaczenie terminów l-wartości i r-wartości
proponuję szczegółowo przyswoić ten materiał, bez poszukiwania
głębszego sensu na tym etapie.  Podobną radę otrzymała Alicja od
Humpty Dumpty w powieści "Po drugiej strony lustra" autorstwa Lewisa
Carrolla:

> “Must a name mean something?” Alice asks Humpty Dumpty, only to get
> this answer: “When I use a word... it means just what I choose it to
> mean – neither more nor less.”

## Wartość wyrażenia

Wyrażenie może być:

* literałem: `3.14`,
* zmienną: `x`,
* operatorem z operandami: `x + y`,
* wywołaniem funkcji: `foo(x)`.

**Wartość wyrażenia** jest wynikiem opracowania wyrażenia.

Wartość wyrażenia ma:

* typ (np. `int`, `bool`, `class A`) znany w czasie kompilacji,

* wartość typu (np. `5`, `false`, `A()`) znaną w czasie uruchomienia,

* kategorię (np. l-wartość, r-wartość) znaną w czasie kompilacji.

Możemy mówić o **kategorii wartości wyrażenia**, albo w skrócie o
**kategorii wyrażenia**.

## Historia: CPL, C, C++98

Język CPL (około pół wieku temu) wprowadził dwie kategorie wartości
wyrażenia:

* **l-wartość**: kategoria ``na lewo od operatora przypisania'', czyli
  wyrażenie, które **może** znaleźć się po lewej stronie operatora
  przypisania: *można mu przypisać inne wyrażenie*,

* **r-wartość**: kategoria ``na prawo od operatora przypisania'',
  czyli wyrażenie, które *nie może* znaleźć sie po lewej stronie
  operatora przypisania: *nie można mu przypisać innego wyrażenia*.

Zarówno wyrażenie kategorii l-wartość, jak i r-wartość, może być
przypisane innemu wyrażeniu.

Język CPL zdefiniował kategorie wyrażeń w odniesieniu do operatora
przypisania.  Te definicje mają jedynie znaczenie historyczne i nie są
stosowane w C++.

W języku C, wyrażenie jest albo l-wartością, gdzie "l" pochodzi od
"locator", czyli czegoś, co lokalizuje (wskazuje) miejsce wartości
wyrażenia.  W języku C, **non-lvalue** jest wyrażeniem, które nie jest
kategorii l-wartość.  W języku C nie ma pojęcia r-wartości!

C++98 przyjął termin i definicję l-wartości z języka C, a wyrażenie,
które nie jest l-wartością, nazwał **r-wartością**.

# Szczegóły

## Kategorie wyrażeń

W C++, dwiema podstawowymi kategoriami wyrażeń są l-wartość i
r-wartość.  Wyrażenie, które jest:

* kategorii l-wartość nazywamy w skrócie l-wartością,

* kategorii r-wartość nazywamy w skrócie r-wartością.

Kategoria wyrażenia określa, co możemy zrobić z wyrażeniem.  Pewne
operacje możemy wykonać wyłącznie na l-wartości (np. `&x`, czyli
pobranie adresu zmiennej `x`), inne operacje wyłącznie na r-wartości.

Przykładowe operacje na wyrażeniu `<expr>`:

* przypisanie: `<expr> = 1`
* inicjalizacja referencji: `<reference type> y = <expr>`
* pobranie adresu: `&<expr>`
* wyłuskanie: `*<expr>`
* inkrementacja: `++<expr>`, `<expr>++`

## Definicje l-wartości i r-wartości

Na próżno szukać w standarcie C++ zwięzłej i poprawnej definicji
l-wartości i r-wartości.  Standard C++, który ma około 1500 stron,
definiuje po trochu te kategorie w różnych miejscach, według potrzeby.

Na domiar tych trudności, w C++17 wprowadzono kolejne kategorie:
pr-wartość, gl-wartość i x-wartość.  Jednak dwiema podstawowymi
kategoriami są l-wartość i r-wartość i tylko nimi będziemy się
zajmować.

Trzeba poznać szczegóły l-wartości i r-wartości, żeby zrozumieć i
wydajnie używać nowoczesny C++ (chociaż też bez nich można jakoś się
obejść po omacku).  Na przykład, nie sposób zrozumieć poniższego
zdania pochodzącego z <http://cppreference.com> bez szczegółowej
wiedzy na temat kategorii wyrażeń:

> Nawet jeżeli typem zmiennej jest referencja typu r-wartość
> (r-referencja), to wyrażenie składające się z nazwy tej zmiennej
> jest l-wartością.

## L-wartość

Standard C++ nie podaje zwięzłej definicji, ale poniższa obserwacja
(nie definicja) wydaje się sprawdzać.

**Obserwacja**: Jeżeli `&<expr>` kompiluje się, to `<expr>` jest
l-wartością.  Czyli wyrażenie jest l-wartością, jeżeli możemy pobrać
jego adres.

Najważniejszym przypadkiem tej obserwacji jest `&x`, gdzie `x` jest
nazwą zmiennej.  **Wyrażenie z nazwą zmiennej jest l-wartością.**

Przykłady l-wartości:

* nazwa zmiennej: `x`
* nazwa funkcji: `foo`
* ciąg znaków: `"Hello World!"`
* wynik prefiksowego operatora inkrementacji: `++i`

Definicja l-wartości jako wyrażenia, które może znaleźć się po lewej
stronie operatora przypisania nie ma zastosowania w C++.  W poniższym
przykładzie nie możemy użyć l-wartości po lewej stronie operatora
przypisania (a niby powinniśmy móc zgodnie z definicją), bo jest ona
stała:

{% highlight c++ %}
{% include_relative wrong-lvalue.cc %}
{% endhighlight %}

## R-wartość.

Wyrażenie jest r-wartością, jeżeli nie jest l-wartością.  Nie możemy
pobrać adresu r-wartości.

Przykładami r-wartości są:

* literał numeryczny: `1`
* obiekt tymczasowy: `std::string("Hello World!")`
* wynik sufiksowego operatora inkrementacji: `i++`
* wywołanie funkcji: `foo()`, jeżeli `int foo();`

Definicja r-wartości jako wyrażenia, które nie może znaleźć się po
lewej stronie operatora przypisania (czyli musi być po prawej
stronie), nie ma zastosowania w C++.  R-wartości możemy coś przypisać,
jak pokazuje poniższy przykład. `A()` jest wartością (bo tworzy obiekt
tymczasowy) i możemy mu przypisać `1`, bo zdefiniowaliśmy taki
operator przypisania w strukturze `A`:

{% highlight c++ %}
{% include_relative left-rvalue.cc %}
{% endhighlight %}

## From lvalue to rvalue

The C++ standard defines this *standard conversion*, which is applied
without the programmer explicitly requesting it:

> An lvalue of a non-function, non-array type T can be converted to an
> rvalue.

For instance, the `+` operator for an integer type (e.g., `int`)
requires rvalues as its operands.  In the following example the `+`
operator expects rvalues, and so the lvalues `x` and `y` are converted
to rvalues.

{% highlight c++ %}
{% include_relative conversion1.cc %}
{% endhighlight %}

For instance, the unary `*` operator (i.e., the dereference operator)
requires a value of a memory address, which is an rvalue.  However, we
can use the dereference operator with an lvalue too, because that
lvalue will be converted to an rvalue.

{% highlight c++ %}
{% include_relative conversion2.cc %}
{% endhighlight %}

There is no standard or implicit conversion from an rvalue to an
lvalue.  For example, the reference operator (i.e., the unary `&`
operator, a.k.a. the take-the-address-of operator) expects an lvalue.
The rvalue that you try to pass will not be converted to an lvalue.

{% highlight c++ %}
{% include_relative conversion3.cc %}
{% endhighlight %}

## Example of the increment operator

The increment operator (i.e., the `++` operator) requires an lvalue as
its operand.  This requirement applies to both the prefix and the
suffix versions of the operator.

{% highlight c++ %}
{% include_relative increment1.cc %}
{% endhighlight %}

The expression of the increment operator is:

* an **lvalue** for the **prefix** version of the operator, i.e., the
  `++<expr>` is an lvalue, because the prefix increment operator
  returns a reference to the just-incremented object it got as an
  operand,

* an **rvalue** for the **suffix** version of the operator, i.e., the
  `<expr>++` is an rvalue, because the suffix increment operator
  returns a temporary copy (which is an rvalue) of the object is got
  as an operand.

Therefore `++++x` compiles, and `x++++` doesn't.

{% highlight c++ %}
{% include_relative increment2.cc %}
{% endhighlight %}

As a side note, the prefix increment operator has the right-to-left
associativity, while the suffix increment operator has the
left-to-right associativity.

The same applies to the decrement operator.

## Temporary objects

A temporary object (or just a temporary) is an object that is created
when an expression is evaluated.  A temporary is automatically
destroyed (i.e., you don't need to explicitly destroy it) when it is
not needed anymore.

A temporary is needed when:

* evaluating an operation: `1 + 2`, `string("T") + "4"`

* when passing an argument to a function: `foo(A())`

* when returning an object from a function: `string x = foo();`

* throwing an exception: `throw A();`

A temporary is an object, not an expression, and so a temporary is
neither an lvalue nor an rvalue, because an object has no category of
expression.  An object is used in an expression that is either an
lvalue or an rvalue.  Usually a temporary is created in rvalue
expressions.

### A temporary as a function argument

An expression with a temporary can be an argument of a function call,
in which case that expression is an rvalue.  If a function takes an
argument by reference (i.e., the parameter of the function is of a
const reference type), the expression with that parameter name is an
lvalue even though the reference is bound to an rvalue.

That example follows.  The constructor outputs the address of the
object, so that we can make sure it's the same object in function
`foo`.

{% highlight c++ %}
{% include_relative tmp-fun.cc %}
{% endhighlight %}

### A temporary as an exception

An expression with a temporary can be an argument of the `throw`
instruction, in which case that expression is an rvalue.  If a catch
block catches the exception by a reference, the expression with that
reference name is an lvalue even though the reference is bound to an
rvalue.

That example follows.  The constructor outputs the address of the
object, so that we can make sure it's the same object in function
`foo`.

{% highlight c++ %}
{% include_relative tmp-except.cc %}
{% endhighlight %}

We should catch an exception by reference: if we catch it by value,
we're going to copy that exception.  Change the example so that an
exception is caught by value, and you'll see that we get a copy
(you'll see different addresses).

Interestingly, and as a side note: in the example above, that
non-const reference is bound to an rvalue.  C++98 states that only a
const reference can bind to an rvalue, which does not hold in the case
of catching an exception.  In the example above, I would expect
`catch(A &a)` to fail to compile, as it should be `catch(const A &a)`.
Wierd.

Interestingly, and as a side note, a statement block (i.e.,
`{<statements>}`), can be replaced with a single statement, e.g.,
`{++i;}` can be replaced with `++i;`.  However, the try and catch
blocks always have to be blocks, and you cannot remote `{}` even if it
has a single statement.  Wierd.

## Functions and categories of expressions

Function `foo`, (e.g., `void foo(<params>)`) can be used in an
expression in two ways:

* by name only:

  * the expression: `foo`,

  * that expression is an lvalue, 

  * we can take the address of that expression: `&foo`,

* by a function call:

  * the expression: `foo(<args>)`,

  * the category of that expression expression depends on the return
    type of the function called:

    * if the return type is *a reference* type, then that expression
      is an *lvalue*,

    * if the return type is *not a reference* type, then that
      expression is *an rvalue*.

This is an example of a function call that is an lvalue:

{% highlight c++ %}
{% include_relative lvalue-call.cc %}
{% endhighlight %}

This is an example of a function call that is an rvalue:

{% highlight c++ %}
{% include_relative rvalue-call.cc %}
{% endhighlight %}

## Incomplete types and categories of expressions

An incomplete type is the type that was either:

* declared, but not defined,

* or defined as an abstract class.

Expressions of the incomplete type can be only lvalues (and so rvalues
can be only of complete types).

{% highlight c++ %}
{% include_relative incomplete.cc %}
{% endhighlight %}

# Conclusion

An expression has a category.  A value of some type (e.g., of class
`A` or type `int`) has no category.

What we can do with an expression depends on its category.

Every expression is either an lvalue or an rvalue.

We covered only the basics, there is more: glvalue, prvalue, xvalue.

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->
