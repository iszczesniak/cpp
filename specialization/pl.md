---
title: Specjalizacja szablonów
---
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
funkcji:

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

To samo zadanie rozwiązane z użyciem szablonów i ich
**specjalizacji**:

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

### Rodzaj parametru: typ

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

To jest przykład funkcji szablonowej z typowym parametrem, gdzie
kompilator jest w stanie **wywnioskować argument szablonu**:

{% highlight c++ %}
{% include_relative print1.cc %}
{% endhighlight %}

### Rodzaj parametru: wartość

Nazwijmy to prosto: **wartościowy parametr szablonu**.  Parametr tego
rodzaju deklarujemy pisząc `some_type I`, gdzie `some_type` jest
typem, np. `int`.  Typ `some_type` nie jest dowolny, tylko nieduży
zbiór typów jest dozwolony, a najczęściej używane są typy całkowite.
Podczas kompilacji za `I` podstawiana jest wartość tego typu, np. 1
dla parametru szablonu zadeklarowanego jako `int I`.

Przykład deklaracji wartościowego parametru szablonu:

```
template <int N>
```

To jest przykład szablonu funkcji z wartościowym parametrem szablonu
`N`, którego *argument* musi być jawnie podany, bo kompilator nie jest
w stanie go wywnioskować:

{% highlight c++ %}
{% include_relative print2.cc %}
{% endhighlight %}

W przykładzie niżej też mamy wartościowy parametr szablonu `N`,
którego argument musi być jawnie podany.  Ale mamy też wartościowy
parametr szablonu `T`, którego *argument* może być wywnioskowany:

{% highlight c++ %}
{% include_relative print3.cc %}
{% endhighlight %}

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu dla `N = 0`.
Nie ma *częściowej specjalizacji* szablonu funkcji, jest tylko *pełna
specjalizacja*, więc musimy jawnie podać także argument szablonu dla
parametru `T`, czyli `int`.

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

Innym rozwiązaniem jest użycie statycznej instrukcji warunkowej `if
constexpr`, żeby przerwać rekurencję:

{% highlight c++ %}
{% include_relative print5.cc %}
{% endhighlight %}

### Rodzaj parametru: szablon

Nazwijmy to tak: **szablonowy parametr szablonu**.  Parametr tego
rodzaju ma podstawiony typ szablonowy w czasie kompilacji, a w liście
parametrów szablonu deklarujemy go tak:

```
template <lista parametrów parametru> typename T
```

A to przykład początku deklaracji lub definicji szablonu z szablonowym
parametrem:

```
template <template <param-type-list> typename T>
```

Przykładowy program:

{% highlight c++ %}
{% include_relative template_type.cc %}
{% endhighlight %}

Za `__PRETTY_FUNCTION__` kompilator GCC podstawia nazwę funkcji i
argumenty szablonu, więc możemy przekonać się w jaki sposób funkcja
została skonkretyzowana.

W przykładzie niżej, za szablonowy parametr `C` może być podstawiony
dowolny typ szablonowy, którego pierwszy parametr jest typowy, a drugi
wartościowy.

{% highlight c++ %}
{% include_relative template_type2.cc %}
{% endhighlight %}

## Parametr a argument szablonu

Parametrem jest nazwa, np. `T`, którą używamy w deklaracji i definicji
szablonu.  Argumentem jest typ, wartość, albo szablon, który jest
podstawiany za parametr.  Argument możemy podać jawnie,
np. `print<100>()`, albo może być wnioskowany na podstawie argumentu
wywołania funkcji.

Ta terminologia jest analogiczna do terminologii **parametru funkcji**
i **argumentu wywołania funkcji**, ale ta analogia jest jedynie
powierzchowna.  Inicjalizacja parametru funkcji z użyciem argumentu
wywołania ma dużo szczegółów (jak na przykład konwersje między typami,
czy zasady inicjalizowania referencji), których podstawienie nie ma.
Podstawienie to skopiowanie tekstu argumentu do parametru ze
sprawdzeniem rodzaju argumentu (czy jest typem, wartością, czy typem
szablonowym).  Wniosek: **podstawienie to nie inicjalizacja**.

# Podsumowanie

* Szablony są podstawą programowania uogólnionego w C++.

* Parametry szablonów są typowe, wartościowa albo szablonowe.

* Programowanie uogólnione jest powszechnie stosowane w bibliotece
  standardowej C++.

# Quiz

* Czy programowanie uogólnione wprowadza narzut czasowy i pamięciowy
  do programu?

* Co to jest typowy parametr szablonu?

* Polimorfizm statyczny a dynamiczny.

<!-- LocalWords: lvalue lvalues rvalue -->
