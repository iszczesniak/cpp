---
title: Szablony
---

# Wprowadzenie

*Alexander Stepanov*, jeden z twórców programowania uogólnionego,
napisał w swojej książce "From Mathematics to Generic Programming":

> Generic programming is an approach to programming that focuses on
> designing algorithms and data structures so that they work in the
> *most general setting without the loss of efficiency*.

Kluczowe są:

* **the most general setting**, czyli najbardziej ogólny przypadek:
  nie chodzi tylko o możliwość uogólnienia typu danych (czyli nasza
  funkcja może działać na `int` albo `double`), ale też struktury
  danych (czyli nasza funkcja może działać na `std::vector` albo
  `std::list`),

* **no loss of efficiency**, czyli bez utraty wydajności: nie chcemy,
  żeby nasz program działał wolniej, albo używał więcej pamięci, bo
  korzystał z programowania uogólnionego.  Chcemy, żeby program był
  tak wydajny, jak w przypadku, kiedy jest starannie dopracowany.

## Najbardziej ogólny przypadek

Programowanie uogólnione jest wspierane przez język C++ z użyciem
szablonów, przy użyciu których zaimplementowane są:

* uogólnione struktury danych, takie jak kontenery biblioteki
  standardowej, np. `std::vector`,

* uogólnione algorytmy, takie jak algorytmy biblioteki standardowej,
  np. `std::sort`.

Przykład niżej pokazuje w jaki sposób możemy używać kontenerów i
algorytmów biblioteki standardowej.  Przykład wymaga kompilatora
C++17.

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

W przykładzie wyżej możemy zmienić typ sortowanych liczb z `int` na
`double`: wystarczy zmienić strukturę `vector` na `vector<double>`.
Możemy też zmienić strukturę z `vector` na `array` (trzeba też dodać
`#include <array>`) czy `deque` (trzeba też dodać `#include <deque>`).
Podczas kompilacji funcja `sort` jest *konkretyzowana* (kompilowana
"na miarę") dla użytej struktury danych i typów elementów struktury.

Ale przykład nie działa ze strukturą `list`.  Kompilator zwraca masę
błędów, z których trudno się zorientować, gdzie jest problem.  A
problem w tym, że iterator struktury `list` nie jest *iteratorem
swobodnego dostępu* (ang. random access operator), czyli nie możemy
zmniejszyć albo zwiększyć iteratora o dowolną liczbę elementów,
np. `list{3, 2, 1}.end() - 2` nie kompiluje się.  Jeżeli struktura
posiada operator swobodnego dostępu `operator []`, to jej iterator
jest swobodnego dostępu.

Problemem przede wszystkim jest obecna słaba diagnostyka.  Powinniśmy
otrzymać komunikat, że funkcja `sort` wymaga iteratora swobodnego
dostępu.  C++20 wprowadza koncepty, które pozwolą na klarowną
diagnostykę błędów, ale to wymaga zmian (użycia konceptów) w
implementacji biblioteki standardowej.

## Bez utraty wydajności

Dla komitetu standaryzacyjnego C++, priorytetem jest wydajność kodu
wynikowego, a dopiero potem łatwość użycia języka.  Tak więc program
napisany z użyciem mechanizmów uogólnienia (np. szablonów) ma działać
szybko (tak szybko, jak to możliwe, czyli jak gdybyśmy "wyrzeźbili"
kod ręcznie), chociaż sam kod źródłowy może być trudny do napisania.

Z użyciem prostych przykładów niżej sprawdzimy, jaki narzut
wydajnościowy wprowadzają mechanizmy uogólnienia.  Każdy z tych
programów wypisuje na standardowe wyjście liczby 1 i 2.  Interesuje
nas kod wynikowy (asembler) programów.

To jest kod bazowy `test_baseline.cc`:

{% highlight c++ %}
{% include_relative test_baseline.cc %}
{% endhighlight %}

To jest kod z użyciem szablonu funkcji `test_template.cc`:

{% highlight c++ %}
{% include_relative test_template.cc %}
{% endhighlight %}

Kompilujem oba przykłady do asemblera (możemy też użyć Code Explorer)
i patrzymy na różnice (możemy też użyć `c++filt`):

```
g++ -O2 -std=c++17 -S test_baseline.cc test_template.cc
meld test_baseline.s test_template.s
```

Różnic nie ma.  Użycie funkcji szablonowej nie wprowadza żadnego
narzutu wydajnościowego, a kod jest tak szybki, jak bez wywołania
funkcji.

W tym przykładzie, jak pokazuje kod wynikowy, parametry funkcji
szablonowej nie są inicjalizowane (kopiowane) na podstawie argumentów
wywołania, mimo że są przekazywane przez wartość.  W języku C, funkcja
przyjmująca argumenty przez wartość (a nie przez wskaźnik, czy
referencję, bo referencji w C nie ma), zawsze ma parametry
inicjalizowane na podstawie argumentów wywołania, co wprowadza narzut
wydajnościowy.

Zwykła funkcja też może być wkompilowana, co można sprawdzić na tym
przykładzie:

{% highlight c++ %}
{% include_relative test_function.cc %}
{% endhighlight %}

Użycie krotki (`std::tuple`), też nie wprowadza narzutu.  Krotka jest
szablonowym typem klasowym, więc ma konstruktor i desktruktor, jednak
są one puste.  Oto przykład dla testów:

{% highlight c++ %}
{% include_relative test_tuple.cc %}
{% endhighlight %}

Nawet iterowanie po elementach tablicy `std::array` nie wprowadza
żadnego narzutu:

{% highlight c++ %}
{% include_relative test_foray.cc %}
{% endhighlight %}

# Programowanie uogólnione a obiektowe

Programowanie uogólnione i obiektowe są komplementarne, nie wykluczają
się.  Język C++ jest językiem wieloparadygmatowym, bo można w nim
programować obiektowo, strukturalnie, proceduralnie, funkcyjnie i w
sposób uogólniony.

Częstym problemem programowania jest potrzeba dostarczenia różnych
fragmentów kodu (operacji czy algorytmów) w zależności od typów
danych, na których działamy.  Programowanie uogólnione i obiektowe
rozwiązują problem z użyciem polimorfizmu, ale różnych rodzajów:

* W **programowaniu uogólnionym** używamy wywołania funkcji i
  mechanizmów ich uogólnienia: przeciążeń lub szablonów.  W *czasie
  kompilacji* dla danego wyrażenia wywołania funkcji wybierany jest
  szablon lub przeciążenie w zależności od typów przekazywanych
  argumentów.  Ten mechanizm nazywamy **polimorfizmem statycznym**
  (aka *polimorfizm czasu kompilacji*).  *Polimorfizm statyczny nie
  wprowadza narzutu czasowego w czasie uruchomienia.*

* W **programowaniu obiektowym** używamy interfejsu klasy bazowej i
  funkcji wirtualnych.  W *czasie uruchomienia* dla wywołania funkcji
  wirtualnej na rzecz danego obiektu wybierana jest implementacja
  funkcji wirtualnej w zależności od typu obiektu.  Ten mechanizm
  nazywamy **polimorfizmem dynamicznym** (aka *polimorfizm czasu
  uruchomienia*).  *Polimorfizm dynamiczny wprowadza narzut czasowy,
  bo wywołanie funkcji wirtualnej wymaga wywołania pośredniego z
  użyciem tablicy funkcji wirtualnych.*

Programowanie uogólnione może działać na danych dowolnego typu, a
programowanie obiektowe wyłącznie na typach klasowych (`1.foo()` nie
przejdzie).

## Przykład polimorfizmu statycznego

Przykład implementacji polimorfizmu statycznego z użyciem przeciążeń
funkcji:

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

To samo zadanie rozwiązane z użyciem szablonów i ich specjalizacji:

{% highlight c++ %}
{% include_relative generic2.cc %}
{% endhighlight %}

Dla obu przykładów wyżej uzyskujemy ten sam kod wynikowy dla funkcji
`main`, jak dla tego kodu źródłowego, czyli najprostszy możliwy kod
wynikowy:

{% highlight c++ %}
{% include_relative baseline.cc %}
{% endhighlight %}

## Przykład polimorfizmu dynamicznego

To samo zadanie możemy zaimplementować z użyciem polimorfizmu
dynamicznego.  Kod wynikowy funkcji `main` jest jednak znacznie
bardziej skomplikowany.

{% highlight c++ %}
{% include_relative object.cc %}
{% endhighlight %}

# Szablony

Szablonowe mogą być:

* funkcje, 

* klasy, struktury, unie,

* składowe klasy (czyli funkcje i pola składowe klasy),

* typy (czyli aliasy typów),

* zmienne.

Deklaracje i definicje szablonów rozpoczynają się słowem kluczowym
`template` z taką składnią:

```
template <lista parametrów>
```

Mówimy, że szablon jest sparametryzowany, bo ma listę parametrów.

## Lista parametrów

Lista musi mieć co najmniej jeden parametr.  Parametry w liście są
oddzielone przecinkami.  Deklaracja parametru składa się z rodzaju i
opcjonalnej nazwy parametru.  Rodzaje parametrów to: typ, wartość,
szablon.  Przykład listy parametrów:

```
template <typename T, int N, template<typename> typename C>
```

### Rodzaj parametru "typ"

Nazwijmy to prosto: **typowy parametr szablonu**.  I typowy on jest
też dlatego, że tego rodzaju parametr jest najczęstszy.  Typowy
parametr deklarujemy pisząc `typename T`: `typename` mówi, że chodzi o
typowy parametr, a `T` jest nazwą parametru.  Możemy również
równoważnie napisać `class T`, ale nowocześniej jest `typename T`.

Podczas kompilacji za `T` może być podstawiony dowolny typ: wbudowany
(np. `int`), użytkownika (np. `myclass`), a nawet `void`.  `T` nie
musi spełniać żadnych warunków, np. nie musi dziedziczyć z klasy
bazowej.  Wymagania dotyczące typu `T` wynikają z jego użycia w
definicji szablonu, czyli czy, na przykład:

* tworzymy domyślną wartość typu `T`, czyli `T{}`,

* dodajemy, używając `operator+`, wartości typu `T`,

* wyłuskujemy, używając `operator&`, wartość typu `T`,

* przekazujemy jakiejś funkcji, np. `push_back`, wartość typu `T`,

* piszemy do `std::ostream` wartość typu `T` z użyciem `operator<<`.

To jest przykład funkcji szablonowej z typowym parametrem:

{% highlight c++ %}
{% include_relative print1.cc %}
{% endhighlight %}

### Rodzaj parametru "wartość"

Nazwijmy to prosto: **wartościowy parametr szablonu**.  Parametr tego
rodzaju deklarujemy pisząc `some_type I`, gdzie `some_type` jest
typem, np. `int`.  Typ `some_type` nie jest dowolny, tylko nieduży
zbiór typów jest dozwolony, a najczęściej używane są typy całkowite.
Podczas kompilacji za `I` podstawiana jest wartość tego typu, np. 1
dla parametru szablonu zadeklarowanego jako `int I`.

Oto przykład deklaracji wartościowego parametru szablonu:

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
terminated by the function specialization for `N = 0`.  There is no
*partial specialization* of function templates, only the *full
specialization*, which means that we also have to specialize the
terminating function for the type, i.e., `int`.

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

We can also terminate the recursion with a compile-time conditional
statement `if constexpr`, and so we do not have to provide a full
specialization:

{% highlight c++ %}
{% include_relative print5.cc %}
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
{% include_relative template_type.cc %}
{% endhighlight %}

`__PRETTY_FUNCTION__` is replaced by GCC with the function name, and
the template parameters, so that we can learn what the paremeters
really are.

This is a modified example from above.  This time the template-type
template argument C can accept template types which accept two
arguments: the first being the type, the second being the value.

{% highlight c++ %}
{% include_relative template_type2.cc %}
{% endhighlight %}

<!-- LocalWords: lvalue lvalues rvalue -->
