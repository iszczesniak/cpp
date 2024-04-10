---
title: Kategorie wyrażeń
---

# Wprowadzenie

Kategorie wyrażeń to podstawa, ale trudno je zrozumieć, bo chodzi o
wiele szczegółów **l-wartości** i **r-wartości**, które w codziennym
programowaniu uchodzą naszej uwadze.

Żeby łatwiej zrozumieć l-wartości i r-wartości, proponuję szczegółowo
przyswoić ten materiał, bez poszukiwania głębszego sensu na tym
etapie.  Podobną radę otrzymała Alicja od Humpty Dumpty w powieści "Po
drugiej stronie lustra" autorstwa Lewisa Carrolla:

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

Wyrażenie ma:

* typ (np. `int`, `bool`, `class A`) znany w czasie kompilacji,

* wartość typu (np. `5`, `false`, `A()`) znaną w czasie kompilacji lub
  uruchomienia,

* kategorię (np. l-wartość, r-wartość) znaną w czasie kompilacji.

Możemy mówić o **kategorii wartości wyrażenia**, albo w skrócie o
**kategorii wyrażenia**.

## Historia: CPL, C, C++98

Język CPL (około pół wieku temu) zdefiniował dwie kategorie wyrażeń w
odniesieniu do operatora przypisania:

* **l-wartość**: kategoria ``na lewo od operatora przypisania'', czyli
  wyrażenie, które **może** znaleźć się po lewej stronie operatora
  przypisania: **można mu przypisać inne wyrażenie**,

* **r-wartość**: kategoria ``na prawo od operatora przypisania'',
  czyli wyrażenie, które **nie może** znaleźć sie po lewej stronie
  operatora przypisania: **nie można mu przypisać innego wyrażenia**.

Te definicje mają jedynie znaczenie historyczne i nie są stosowane w
C++.

W języku C, wyrażenie jest albo l-wartością, gdzie "l" pochodzi od
"locator", czyli czegoś, co lokalizuje (wskazuje) miejsce wartości
wyrażenia.  W języku C, **non-lvalue** jest wyrażeniem, które nie jest
kategorii l-wartość.  W języku C nie ma pojęcia r-wartości!

C++98 przyjął termin i znaczenie l-wartości z języka C, a wyrażenie,
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
definiuje po trochu te kategorie w różnych miejscach, według potrzeby,
co utrudnia zrozumienie kategorii wartości.

Na domiar tych trudności, w C++11 wprowadzono kolejne kategorie:
pr-wartość, gl-wartość i x-wartość, które w C++17 uszczegółowiono.
Jednak dwiema podstawowymi kategoriami są l-wartość i r-wartość i
tylko nimi będziemy się zajmować.

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
stronie operatora przypisania (czyli może też po prawej) nie ma
zastosowania w C++.  W poniższym przykładzie nie możemy użyć
l-wartości po lewej stronie operatora przypisania (a niby powinniśmy
móc zgodnie z definicją), bo jest ona stała:

{% highlight c++ %}
{% include_relative wrong-lvalue.cc %}
{% endhighlight %}

Operator przypisania dla typów całkowitych wymaga l-wartości po lewej
stronie, więc nie możemy napisać `1 = 1`.  Oto bardziej rozbudowany
przykład:

{% highlight c++ %}
{% include_relative assignment.cc %}
{% endhighlight %}

## R-wartość

Wyrażenie jest r-wartością, jeżeli nie jest l-wartością.  Nie możemy
pobrać adresu r-wartości.

Przykładami r-wartości są:

* literał numeryczny: `1`
* wyrażenie tworzące obiekt tymczasowy: `std::string("Hello World!")`
* wynik sufiksowego operatora inkrementacji: `i++`
* wywołanie funkcji: `foo()`, jeżeli `int foo();`

Definicja r-wartości jako wyrażenia, które nie może znaleźć się po
lewej stronie operatora przypisania (czyli musi po prawej), nie ma
zastosowania w C++.  R-wartości możemy coś przypisać, jak pokazuje
poniższy przykład. `A()` jest r-wartością (bo tworzy obiekt
tymczasowy) i możemy mu przypisać `1`, bo zdefiniowaliśmy taki
operator przypisania w strukturze `A`:

{% highlight c++ %}
{% include_relative left-rvalue.cc %}
{% endhighlight %}

## Konwersja standardowa z l-wartości na r-wartość

Standard C++ definiuje taką *konwersję standardową*: l-wartość może
zostać niejawnie poddana konwersji do r-wartości.  Niejawnie, czyli
programista nie musi rzutować.

Na przykład, operator `+` dla typów całkowitych (np. `int`) wymaga
r-wartości jako operandów.  W poniższym przykładzie operator `+`
wymaga r-wartości, więc l-wartości `x` i `y` są konwertowane niejawnie
do r-wartości.

{% highlight c++ %}
{% include_relative conversion1.cc %}
{% endhighlight %}

Kolejny przykład dotyczy jednoargumentowego operatora `*` (czyli
operatora wyłuskania), który wymaga r-wartości: adresu pamięci.  Ale
wyłuskać możemy też l-wartość, bo zostanie ona poddana konwersji
standardowej:

{% highlight c++ %}
{% include_relative conversion2.cc %}
{% endhighlight %}

Nie ma niejawnej konwersji z r-wartości na l-wartość.  Na przykład,
operator pobrania adresu (czyli jednoargumentowy operator `&`) wymaga
l-wartości.  Jeżeli przekażemy mu r-wartość, to nie będzie ona poddana
niejawnej konwersji do l-wartości, jak pokazuje przykład niżej:

{% highlight c++ %}
{% include_relative conversion3.cc %}
{% endhighlight %}

## Przykład z operatorem inkrementacji

Operator inkrementacji (czyli `++`) dla typów całkowitych wymaga
l-wartości jako operandu.  Wymóg ten dotyczy wersji prefiksowej i
sufiksowej operatora.  To samo dotyczy operatora dekrementacji.

{% highlight c++ %}
{% include_relative increment1.cc %}
{% endhighlight %}

Wyrażenie operatora inkrementacji dla typów wbudowanych jest:

* **l-wartością** w przypadku wersji prefiksowej, czyli wyrażenie
  `++<expr>` jest l-wartością, bo zwracana jest referencja na daną,
  która została przekazana operatorowi, i która właśnie została
  zinkrementowana,

* **r-wartością** w przypadku wersji sufiksowej, czyli wyrażenie
  `<expr>++` jest r-wartością, bo operator sufiksowy zwraca daną
  tymczasową (a ta jest r-wartością), która jest zdekrementowaną kopią
  danej przekazanej operatorowi.

Dlatego `++++x` kompiluje się, a `x++++` nie.

{% highlight c++ %}
{% include_relative increment2.cc %}
{% endhighlight %}

Tak przy okazji:

* wersja prefiksowa ma priorytet niższy od sufiksowej,

* wersja prefiksowa ma wiązanie od prawej do lewej,

* wersja sufiksowa ma wiązanie od lewej do prawej.

Przykład poniżej pokazuje implementację sufiksowego operatora
inkrementacji dla `std::string`.  Pętla z prefiksowym operatorem
byłaby bardziej skomplikowana.

{% highlight c++ %}
{% include_relative string.cc %}
{% endhighlight %}

## Dana tymczasowa

Podczas opracowywania wyrażenia może być tworzona dana tymczasowa
(ang. a temporary), która jest później niszczona automatycznie (czyli
nie musimy jej jawnie niszczyć), kiedy nie jest już potrzebna.  Data
tymczasowa to wartość typu podstawowego (np. `int`), lub obiekt.

Dana tymczasowa jest potrzebna, kiedy:

* używamy operatora: `1 + 2`, `string("T") + "4"`

* przekazujemy argument do funkcji: `foo(A())`

* zwracamy wynik z funkcji: `string x = foo();`

* rzucamy wyjątek: `throw A();`

**Wyrażenie tworzące daną tymczasową jest r-wartością.** Na przykład,
jeżeli `A` jest typem klasowym, to `A()` tworzy obiekt tymczasowy, a
wyrażenie to jest r-wartością.

Dana tymczasowa czasem jest **błędnie** określana r-wartością, a
przecież dana tymczasowa nie jest wyrażeniem, więc nie ma kategorii i
nie możemy mówić o niej jako o l-wartości czy r-wartości.

Ta sama dana tymczasowa może być użyta w l-wartości, albo r-wartości,
kiedy, na przykład:

* przekazujemy daną przez referencję do funkcji,

* rzucamy daną jako wyjątek.

### Dana tymczasowa jako argument funkcji

Dana tymczasowa może być argumentem wywołania funkcji.  Jeżeli funkcja
przyjmuje argument przez referencję stałą (czyli parametr funkcji jest
typu referencyjnego na daną stałą), to parametr będzie aliasem danej
tymczasowej.

I tu zwrot akcji: dana tymczasowa została stworzona w r-wartości, a
wyrażenie odwołujące się do niej przez nazwę (referencję) to już
l-wartość.  L-wartość i r-wartość odnoszą się do wyrażeń, a dana
tymczasowa była i jest bez kategorii.

Omówiony wyżej przypadek prezentuje poniższy przykład.  Konstruktor
wypisuje adres tworzonego obiektu, żebyśmy mogli się upewnić, że to
ten sam obiekt w funkcji `foo`.

{% highlight c++ %}
{% include_relative tmp-fun.cc %}
{% endhighlight %}

### Dana tymczasowa jako wyjątek

Wyrażenie z daną tymczasową (czyli r-wartość) może być argumentem
rzucania wyjątku.  Jeżeli blok obsługi wyjątku przechwyci wyjątek
przez referencję stałą, to parametr bloku będzie aliasem danej
tymczasowej.

Podobny zwrot akcji: dana tymczasowa została stworzona w r-wartości, a
wyrażenie odwołujące się do niej przez nazwę (referencję) to już
l-wartość.

Omówiony wyżej przypadek prezentuje poniższy przykład.  Konstruktor
wypisuje adres tworzonego obiektu, żebyśmy mogli się upewnić, że to
ten sam obiekt w bloku obsługi wyjątku.

{% highlight c++ %}
{% include_relative tmp-except.cc %}
{% endhighlight %}

Powinniśmy obsługiwać wyjątki przez referencję, bo jeżeli będziemy
obsługiwać przez wartość, to wyjątek będzie kopiowany.  Proszę zmienić
przykład wyżej, żeby obsługiwać wyjątek przez wartość: wyjątek będzie
kopiowany i zobaczymy różne adresy.

Co ciekawe, w powyższym przykładzie obsłużyliśmy wyjątek przez
**niestałą referencję**!  C++98 mówi, że tylko **stałą referencję**
można zainicjalizować r-wartością, czyli niestałej referencji już nie.
Ale jakoś ta zasada nie dotyczy obsługi wyjątków.  Spodziewałbym się,
że w przykładzie wyżej `catch(A &a)` nie będzie się kompilowało, i że
będzie trzeba napisać `catch(const A &a)`.  A jednak.

Blok instrukcji (czyli `{<instrukcje>}`) z jedną instrukcją możemy
zamienić na tę jedną instrukcję, co jest wygodne w pisaniu pętli.  Na
przykład, możemy zamienić `{++i;}` na `++i;`.  Jednak bloki
przechwytywania wyjątku (`try`) i obsługi wyjątku (`catch`) ciągle
muszą być blokami i nie można usunąć `{}`, nawet jeżeli zawierają
jedną instrukcję.  Taka nieścisłość.

## Przeciążanie funkcji składowych

Funkcja składowa może być wywołana dla l-wartości lub r-wartości.
Możemy jednak zadeklarować funkcję z kwalifikatorem referencji `&`
albo `&&`, żeby można ją było wywołać albo dla l-wartości, albo
r-wartości.  Na przykład:

{% highlight c++ %}
{% include_relative overloading.cc %}
{% endhighlight %}

## Funkcje a kategorie wyrażeń

Funkcja `foo` (np. `void foo();`) może być użyta w wyrażeniu na dwa
sposoby:

* tylko przez nazwę:

  * wyrażenie: `foo`,

  * to wyrażenie jest l-wartością,
  
  * możemy pobrać adres: `&foo`,

* wywołanie funkcji:

  * wyrażenie: `foo(<argumenty>)`,

  * kategoria tego wyrażenia zależy od typu wartości zwracanej przez
    funkcję: jeżeli zwracana wartość:

    * jest typu referencyjnego (typ zdefiniowany z użyciem deklaratora
      `&`), to wyrażenie jest l-wartością,

    * nie jest typu referencyjnego, to wyrażenie jest r-wartością.

To jest przykład wyrażenia wywołania funkcji, które jest l-wartością,
bo zwracana wartość jest typu referencyjnego:

{% highlight c++ %}
{% include_relative lvalue-call.cc %}
{% endhighlight %}

To jest przykład wyrażenia wywołania funkcji, które jest r-wartością,
bo zwracana wartość nie jest typu referencyjnego:

{% highlight c++ %}
{% include_relative rvalue-call.cc %}
{% endhighlight %}

## Typy niekompletne a kategorie wyrażeń

Typ niekompletny to taki, którego obiektów nie jesteśmy w stanie
stworzyć, bo:

* został zadeklarowany, ale nie został zdefiniowany, lub

* został zdefiniowany jako klasa abstrakcyjna (czyli ma funkcję czysto
  wirtualną).

Wyrażenia typów niekompletnych mogą być tylko l-wartością (czyli nie
mogą być r-wartością).

W przykładzie niżej używamy typu, który nie został zdefiniowany:

{% highlight c++ %}
{% include_relative incomplete.cc %}
{% endhighlight %}

# Podsumowanie

* Wyrażenie ma kategorię.  Dana nie ma kategorii.

* Od kategorii zależy, co możemy zrobić z wyrażeniem.

* Wyrażenie jest l-wartością, albo r-wartością.

* To tylko początek.  Jest więcej: gl-wartość, pr-wartość i x-wartość.

# Quiz

* Dlaczego `int i; ++i++;` się nie kompiluje?

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->
