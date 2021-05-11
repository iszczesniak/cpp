---
title: std::unique_ptr
---

# Wprowadzenie

Wskaźniki są nieodzowne.  Wskaźniki:

* wskazują miejsce w pamięci, zwykle zaalokowane dynamicznie,

* są używane w każdym języku programowania: C, C++, Java, C#,

* mogą być użyte w formie referencji, np. w Javie czy C#.

Wsparcie wskaźników może być:

* opakowane w referencję, np. w Javie czy C#,

* surowe albo zaawansowane, jak w C++,

* tylko surowe, jak w C.

W C++ najlepiej unikać surowych wskaźników i korzystać z
zaawansowanego wsparcia w postaci standardowych wskaźników
inteligentnych.

Referencja w Javie czy C# jest inteligentnym wskaźnikiem o semantyce
współdzielonej własności, gdzie dostęp do składowej uzyskujemy z
użyciem operatora `.` (czyli `object.member`), a nie `->` (czyli
`pointer->member`).  W C++ referencja jest aliasem, która w czasie
kompilacji będzie wyoptymalizowana albo zmieniona na surowy wskaźnik.

# Motywacja: problemy surowych wskaźników

Surowe wskaźniki łatwo używać, ale też łatwo popełniać błędy.

## Problemy

Kiedy mamy wskaźnik typu `T *`, który wskazuje na dynamicznie
stworzone dane, to mamy następujące problemy:

* **problem typu**: nie wiemy, czy wskaźnik wskazuje na jedną daną,
    czy może na tablicę danych,

* **problem własności**: nie wiemy, czy *my* czy może *ktoś inny*
    (czyli inny programista, który napisał inny fragment kodu)
    powinien zniszczyć dane,

* **problem obsługi wyjątków**: obsługa wyjątków ze surowymi
    wskaźnikami jest trudna, pracochłonna i podatna na błędy.

### Problem typu

Operatory `new` i `delete` mają wiele wersji, ale ważnymi są:

* wersja pojedyncza dla jednej danej,

* wersja tablicowa dla tablicy danych.

Jeżeli tworzymy dane z użyciem wersji pojedynczej albo tablicowej
operatora `new`, to powinniśmy zniszczyć dane tą samą wersją operatora
`delete`.  Pomieszanie dwóch wersji skutkuje niezdefiniowanym
działaniem.  Kompilator nie jest w stanie wychycić błędu, bo operatory
`new` i `delete` posługują się tym samym typem danych: `T *`.

### Problem własności

Problem własności może skutkować:

* **przeciekiem pamięci**, kiedy dynamicznie zaalokowane dane nie są
    nigdy zniszczone, mimo że nie są już potrzebne,

* **dyndającym wskaźnikiem**, kiedy odwołujemy się do miejsca w
    pamięci, ale dane, które tam się znajdowały, zostały już
    zniszczone,

* **podwójnym usunięciem**, kiedy próbujemy zniszczyć dane, które już
    zostały zniszczone.

### Problem obsługi wyjątków

Jeżeli zarządamy dynamicznie zaalokowanymi danymi z użyciem surowych
wskaźników, to obsługa wyjątków staje się nudnym i podatnym na błędy
programowaniem, szczególnie gdy dane są złożone.  Da się, ale kto chce
to robić?

## Przykład

Przykład niżej pokazuje jak łatwo możemy się natknąć na problemy typu,
własności i obsługi wyjątków.  Kompilator nie zgłasza błędów ani
ostrzeżeń przy kompilowaniu tego błędnego kodu.

{% highlight c++ %}
{% include_relative problems.cc %}
{% endhighlight %}

# Rozwiązanie: inteligentny wskaźnik

Inteligentny wskaźnik zarządza dynamicznie zaalokowanymi danymi, więc
objekt inteligentnego wskaźnika nazywamy **obiektem zarządzającym**, a
dynamicznie zaalokowane dane nazywamy **danymi zarządzanymi**.

Inteligentny wskaźnik nie kopiuje czy przenosi zarządzanych danych,
może je tylko zniszczyć.

Typ zarządzanych danych nie musi być przygotowany w jakiś specjalny
sposób, żeby można było użyć inteligentnych wskaźników, np. typ nie
musi dziedziczyć z jakiegoś typu bazowego (interfejsu) i go
implementować go.

Inteligentne wskaźniki rozwiązują:

* problem typu: inteligentny wskaźnik zna typ zarządzanych danych,
  więc niszczy je we właściwy sposób,

* problem własności: inteligentne wskaźniki implementują semantykę
  wyłącznej albo współdzielonej własności,

* problem obsługi wyjątków: obiekt inteligentnego wskaźnika jest
  automatycznie niszczony przy obsłudze wyjątków, więc jego dane też
  (a dane surowego wskaźnika nie).

Każdy wszechstronny język powinien wspierać surowe wskaźniki, ponieważ
ta niskopoziomowa funkcjonalność jest wymagana do implementacji
wysokopoziomowej funkcjonalności, takiej jak inteligentne wskaźniki.

Programista powinien mieć wybór pomiędzy surowymi wskaźnikami (na
przykład do implementacji jakiejś wyrafinowanej funkcjonalności) i
inteligentnymi wskaźnikami do codziennego użytku.

Za wyjątkiem specjalnych przypadków, obecnie programista C++ nie
powinien używać surowych wskaźników, nie mówiąc już o `void *` -- te
czasy już dawno minęły.

## Typy inteligentnych wskaźników

Są trzy typy inteligentnych wskaźników zdefiniowanych w pliku
nagłówkowym `memory`:

* `std::unique_ptr` - implementuje semantykę wyłącznej własności,

* `std::shared_ptr` - implementuje semantykę współdzielonej własności,

* `std::weak_ptr` - śledzi dane, ale nimi nie zarządza.

Inteligentne wskaźniki obudowują surowe wskaźniki, więc używają je w
implementacji.  Na przykład, semantyka przeniesienia jest elementem
tej obudowy, która jest niezbęda do wygodnej i poprawnej
implementacji, ale nie wprowadza żadnego narzutu czasowego w czasie
uruchomienia.  Inteligentne wskaźniki są tak szybkie i używają tak
mało pamięci, jak to jest tylko możliwe, czyli tak, jakbyśmy ręcznie
(ale ciągle poprawnie) wyrzeźbili ten kod.

Inteligentne wskaźniki są:

* *bezpieczne w użyciu z wyjątkami*: mogą być użyte bez problemów
   kiedy wyjątki są rzucane lub przechwytywane,

* *nie są bezpieczne w użyciu z wątkami*: mogą być używane w
   programowaniu wielowątkowym, ale z zachowaniem ostrożności.

Jest jeszcze przestarzały inteligentny wskaźnik `std::auto_ptr`, ale
nie należy już go stosować.

# `std::unique_ptr`

Typ `std::unique_ptr` implementuje semantykę wyłącznej własności:

* *wyłącznej*, ponieważ obiekt zarządzający jest jedynym właścicielem
  zarządzanych danych, czyli tylko jeden obiekt może zarządzać danymi,

* *własności*, ponieważ obiekt zarządzający jest odpowiedzialny za
   zniszczenie danych, którymi zarządza.

Wyłączność pociąga za sobą to, że `std::unique_ptr` jest typem tylko
do przenoszenia, więc:

* nie możemy inicjalizować ani przypisywać przez kopiowanie; te
  kopiujące składowe specjalne są usunięte,

* możemy inicjalizować i przypisywać przez przenoszenie.

Własność pociąga za sobą to, że zarządzane dane są niszczone, kiedy
obiekt zarządzający:

* jest niszczony, np. wychodzi poza zakres,

* ma przypisane nowe dane do zarządzania.

Kiedy nie chcemy już używać surowych wskaźników, to najczęściej
powinniśmy stosować ten typ inteligentnego wskaźnika.

## Przykład

Typ `std::unique_ptr` jest szablonowy: typ zarządzanych danych
przekazujemy jako argument szablonu.  Przekazujemy argumenty szablonu
w nawiasach kontowych `<>` w ten sposób:

```p
std::unique_ptr<typ> p;
```

W przykładzie niżej, obiekt zarządzający `p` zarządza daną typu `int`,
która będzie automatycznie zniszczona, kiedy `p` wyjdzie poza zakres.

{% highlight c++ %}
{% include_relative simple.cc %}
{% endhighlight %}

## Function `std::make_unique`

Function template `std::make_unique` was introduced for convenience
(we could do without it): it creates both the managing object, and the
managed data.

We can create the managed data yourself with the new operator, and
pass its raw pointer to the managing object like this:

`unique_ptr<A> up(new A("A1"));`

Instead, we can write the equivalent code like this, without typing
type `A` twice:

`auto up = make_unique<A>("A1");`

Function `std::make_unique` introduces no overhead: the move
constructor will be elided, the return value optimization will take
place, and so the managing object will be created directly in the
location of `up`.

By type `auto` above we ask the compiler to make the type of `up` the
same type as the type of the initializing expression
`make_unique<A>("A1")`, which is `std::unique_ptr<A>`.  We could have
equivallently written:

`unique_ptr<A> up = make_unique<A>("A1");`

To use function `std::make_unique`, you need to pass the template
argument, which is the type of the managed data to create, and manage.
The arguments (none, one or more) of the function are passed to the
constructor of the managed data (a feat accomplished with the variadic
templates).  In the example above `"A1"` is the argument passed to the
constructor of type `A`.

## No performance overhead

This example demonstrates that there is no performance overhead of
using smart pointers.  In more complicated examples there might be
some small overhead, which should go away as compilers get better at
optimization.

The following example uses both the `std::unique_ptr` and
`std::make_unique`.  Save this file as `test1.cc`:

{% highlight c++ %}
{% include_relative test1.cc %}
{% endhighlight %}

The following example of the same functionality uses raw pointers.
Save this file as `test2.cc`:

{% highlight c++ %}
{% include_relative test2.cc %}
{% endhighlight %}

Now compile them to the assembly code with:

`g++ -S -O3 test1.cc test2.cc`

Now there are two files with the assembly code: `test1.s`, and
`test2.s`.  Take a look at one of them:

`c++filt < test1.s | less`

Compare them to see that they are instruction-to-instruction the same
(almost, there is one small difference), which shows there is no
overhead of using `std::unique_ptr` and `std::make_unique`:

`diff test1.s test2.s`

## How to use `std::unique_ptr`

The example below demonstrates the basic usage of `std::unique_ptr`.

{% highlight c++ %}
{% include_relative usage.cc %}
{% endhighlight %}

# The solutions to the problems

## The type problem

The type problem, more specifically the problem of mismatching the
single and array versions of the new and delete operators, is solved
by two versions (two template overloads) of smart pointers:

* `std::unique_ptr<A>`: the managed data will be destroyed with the
  single version of the delete operator,

* `std::unique_ptr<A[]>`: the managed data will be destroyed with the
  array version of the delete operator.

By using the right version of the smart pointer, you don't have to
remember to destroy the managed data with the matching version of the
delete operator.

### Lurking problems, and how to deal with them.

However, we still can introduce bugs like in the example below, where
we:

* declare to allocate a single integer, but allocate an array of
  integers,

* declare to allocate an array of integers, but allocate a single
  integer.

Use `std::make_unique` to get the same done safer, as shown below.

{% highlight c++ %}
{% include_relative solved_type.cc %}
{% endhighlight %}

### Use `std::array` instead!

If you really have to have an array of static size (i.e., the size
doesn't change at run-time), it's better to use `std::array` instead
of the C-style array.  You can use it with smart pointers like this:

{% highlight c++ %}
{% include_relative array.cc %}
{% endhighlight %}

## The ownership problem

The ownership problem is solved: you just move the ownership where you
need to, e.g., a function or some structure.  You can move the
ownership when you pass or return a unique pointer by value in a
function call, as shown in the example below.

{% highlight c++ %}
{% include_relative solved_ownership.cc %}
{% endhighlight %}

## The exception handling problem

When an exception is thrown, the data previously allocated (or any
other resource acquired) and not required any longer because of the
exception, should be deleted (or released).  When programming with raw
pointers, we can release the memory in the catch block, as shown in
the example below.  We have to declare `p` before the try block, so
that it's accessible in the catch block, and that complicates the
code.

{% highlight c++ %}
{% include_relative except_raw1.cc %}
{% endhighlight %}

The same can be accomplished with smart pointers better:

{% highlight c++ %}
{% include_relative except_smart1.cc %}
{% endhighlight %}

### Raw pointers not so easy, rather error-prone.

Because function arguments are not guaranteed to be evalued in the
order they are listed, in the example below we've got a memory leak.
At least I've got it with GCC, and if you don't, try to swap the
arguments in the call to `foo`.  The object of class `A` is:

* created, because the second argument of the call to function `foo`
  is evaluated first, before function `index` is called,

* not destroyed, because function `foo` is not called, because a call
  to function `index` throws an exception.

{% highlight c++ %}
{% include_relative except_raw2.cc %}
{% endhighlight %}

The same can be accomplished the safe way with smart pointers.  This
code works correctly regardless of whether an exception is thrown or
not.

{% highlight c++ %}
{% include_relative except_smart2.cc %}
{% endhighlight %}

## The first example revisited

Below there is the first example fixed with raw pointers.  All
problems gone.

{% highlight c++ %}
{% include_relative problems_solved.cc %}
{% endhighlight %}

# Conclusion

* Don't use raw pointers, unless you really have to.

* Start using `std::unique_ptr`, the most useful smart pointer type.

* Smart pointers solve the type, ownership and exception handling
  problems.

* Smart pointers introduce no, or little, performance overhead.

* Go for the smart pointers!

# Quiz

* Why should we use smart pointers instead of raw pointers?

* What is the exclusive ownership?

* What do we need the `make_uniqe` function for?

<!-- LocalWords:  -->
