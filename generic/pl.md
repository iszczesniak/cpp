---
title: Programowanie uogólnione
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
Podczas kompilacji funkcja `sort` jest *konkretyzowana* (kompilowana
"na miarę") dla użytej struktury danych i typów elementów struktury.

**Programowanie uogólnione** może też działać na strukturach danych,
które **nie są obiektowe**, na przykład na tablicach z języka C, przez
co jest bardziej ogólne niż programowanie obiektowe, które działa
wyłącznie na typach obiektowych.  Możemy przerobić przykład wyżej,
żeby działał nie tylko na kontenerach (które są obiektowe), ale też na
tablicy z języka C: zamieniamy wywołania funkcji składowych `begin` i
`end`, na wywołania funkcji szablonowych `std::begin` i `std::end`:

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

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

Kompilujemy oba przykłady do asemblera (możemy też użyć Code Explorer)
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
szablonowym typem klasowym, więc ma konstruktor i destruktor, jednak
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
funkcji znajduje się niżej.  Te przeciążenia mają kod wspólny
(`std::cout << "Function foo:";` i `std::cout << std::endl`) i kod
zależny od typu parametru.

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

Niżej znajduje się rozwiązanie z użyciem szablonu, gdzie wspólny kod
pojawia się tylko raz.  Funkcja szablonowa korzysta z operatora `<<`,
który jest przeciążony dla różnych typów.  Ciągle korzystamy z
przeciążania, jak w poprzednim przykładzie, ale już dla bardziej
okrojonej funkcjonalności, czyli tylko operatora `<<`, który możemy
użyć także gdzie indziej.  Możemy powiedzieć, że uogólniliśmy kod
funkcji `foo`.

{% highlight c++ %}
{% include_relative generic2.cc %}
{% endhighlight %}

## Przykład polimorfizmu dynamicznego

To samo zadanie możemy zaimplementować z użyciem polimorfizmu
dynamicznego.  Kod wynikowy funkcji `main` jest jednak znacznie
bardziej skomplikowany.

{% highlight c++ %}
{% include_relative object.cc %}
{% endhighlight %}

# Podsumowanie

* Programowanie uogólnione jest powszechnie stosowane w bibliotece
  standardowej C++.

*

*

# Quiz

* Czy programowanie uogólnione wprowadza narzut czasowy i pamięciowy
  do programu?

* Polimorfizm statyczny a dynamiczny.

* 

<!-- LocalWords: lvalue lvalues rvalue -->
