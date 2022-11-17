---
title: Referencje
---

# Wprowadzenie

Najważniejsze fakty o referencjach:

* Referencja jest aliasem (nazwą) danej (zmiennej, obiektu, czy
  obiektu tymczasowego),

* Mając referencję do obiektu, możemy uzyskać dostęp do składowych pól
  i funkcji z użyciem operatora dostępu (czyli `object.member`, jak w
  przypadku nazwy zmiennej), a nie z użyciem operatora dostępu przez
  wskaźnik (czyli `pointer->member`, jak w przypadku wskaźnika).

* Referencja musi być zainicjalizowana, więc nie ma referencji
  pustych, które nie zostały zainicjalizowane.  Wskaźnik może być
  pusty (czyli `nullptr`).

* W przeciwieństwie do wskaźnika, referencji nie można zmienić, żeby
  była aliasem innej danej.

* Typ referencyjny nie może mieć kwalifikatorów typu.

* Istnieje referencja do wskaźnika, ale nie wskaźnik do referencji.

* Referencja może być przechowywana w `std::pair` i `std::tuple`, ale
  nie w kontenerze czy tablicy.

* Istnieje typ `void *`, ale nie `void &` (na szczęście).

Główne zastosowania referencji:

* przekazywanie argumentu do funkcji przez referencję,

* zwracanie wartości z funkcji przez referencję,

* użycie danych przez referencję w polach składowych obiektów,

* dostęp do danych tylko do odczytu (referencja stała).

**Referencja jest inicjalizowana na podstawie wyrażenia
inicjalizującego**.  Mając daną, która jest wartością wyrażenia
inicjalizującego, możemy równoważnie powiedzieć, że referencja:

* **odnosi się** (ang. refers to) do danej,

* **wiąże się** (ang. binds to) z daną,

* **nazywa** (ang. names) daną.

Referencja odnosi się do wartości wyrażenia kategorii l-wartość, albo
kategorii r-wartość, ale w skrócie możemy powiedzieć, że wiąże się z
l-wartością albo r-wartością (ang. a reference binds to an lvalue).

Referencje języka C++ nie mają odpowiednika w języku Java czy C#: w
C++ referencja może nie istnieć w czasie uruchomienia, bo została
**wyoptymalizowana** w czasie kompilacji.

W Javie czy C# referencja jest wskaźnikiem o semantyce współdzielonej
własności: referencje mogą być kopiowane, a dana będzie tak długo
istnieć, jak istnieje przynajmniej jeden taki wskaźnik.  W tych
językach wskaźnik (i to nie taki zwykły jak w C, tylko implementujący
współdzielenie obiektu) zawsze istnieje w czasie uruchomienia.

Poniższy przykład pokazuje wyoptymalizowanie referencji w czasie
kompilacji.  Poniższe dwa programy robią to samo, ale w drugim używamy
referencji, które są wyoptymalizowane.

Zapiszmy ten plik jako `test1.cc`:

{% highlight c++ %}
{% include_relative test1.cc %}
{% endhighlight %}

Zapiszmy ten plik jako `test2.cc`:

{% highlight c++ %}
{% include_relative test2.cc %}
{% endhighlight %}

Skompilujmy je do asemblera:

`g++ -S -O3 test1.cc test2.cc`

Mamy teraz dwa pliki `test1.s` i `test2.s`.  Spójrzmy na pierwszy z
nich:

`c++filt < test1.s | less`

Porównajmy je, żeby się przekonać, że są takie same (czyli że nie ma
śladu po referencji):

`diff test1.s test2.s`

# Typy referencyjne

Są trzy typy referencji:

* **l-referencja** typu `T &`: odnosi się do danej, którą możemy
  zmieniać, ale nie przenosić (ang. move), bo będzie może ta dana
  potem potrzebna w jej obecnym miejscu,

* **referencja stała** typu `const T &`: odnosi się do danej, której
  nie możemy zmieniać, ani przenosić,

* **r-referencja** typu `T &&`: odnosi się do danej, którą możemy
  zmieniać i przenosić, bo wkrótce będzie zniszczona.

L-referencja jest też nazywana referencją l-wartości, albo referencją
do l-wartości.  R-referencja jest też nazywana referencją r-wartości,
albo referencją do r-wartości.

Typy referencyjne używamy w definicji typu, np. typu zmiennej czy typu
zwracanego przez funkcję.  Wyrażenie nigdy nie jest typu
referencyjnego, ponieważ w miejsce referencji (np. zmiennej
referencyjnej) podstawiana jest dana, do której referencja się
odnosi. [expr.type]

## Terminy l-wartość i r-wartość w nazwach typów

Wyrażenia nazywamy l-wartością lub r-wartością, np.:

* `"1"` jest l-wartością,

* `1` jest r-wartością.

Te terminy także są używane w nazwach typów, co jest trochę mylące:

* `int &x = <expr>;` - wyrażenie `x` jest referencją l-wartości
  (ang. lvalue reference) i kategorii l-wartość.

* `int &&x = <expr>;` - wyrażenie `x` jest referencją r-wartości
  (ang. rvalue reference) i kategorii l-wartość.

Teraz rozumiem to zdanie z <http://cppreference.com>:

> Nawet jeżeli typem zmiennej jest referencja typu r-wartość
> (r-referencja), to wyrażenie składające się z nazwy tej zmiennej
> jest l-wartością.

## L-referencja

**L-referencja może być zainicjalizowana tylko l-wartością.**

Tak definiujemy l-referencję:

`T &name = <expr>;`

Referencja `name` odnosi się do danej typu `T`.  Wyrażeniem
inicjalizującym jest `<expr>`.  *Deklaratorem* l-referencji jest `&`.

Podstawowe przykłady:

{% highlight c++ %}
{% include_relative lref.cc %}
{% endhighlight %}

Przykłady dla kontenerów i tablic:

{% highlight c++ %}
{% include_relative containers.cc %}
{% endhighlight %}

Przykłady dla `std::pair` i `std::tuple`:

{% highlight c++ %}
{% include_relative quasi.cc %}
{% endhighlight %}

## Referencja stała

Tak definiujemy referencję stałą:

`const T &name = <expr>;`

Jest to l-referencja, która odwołuje się do danej typu `const T`,
czyli kwalifikator `const` doprecyzowuje typ danej, a nie typ
referencji.  Referencji i tak nie możemy zmienić, ale nazywamy ją
referencją stałą w skrócie (myślowym), żeby nie mówić o l-referencji
do stałej danej.

Referencja stała została wprowadzona, żeby dane można było używać
tylko do odczytu.  Na przykład, funkcja może przyjmować argument przez
referencję stałą, żeby zapewnić brak modyfikacji argumentu.  Co
więcej, aby funkcja mogła przyjąć daną tymczasową (czyli r-wartość), w
C++98 napisano:

**Referencja stała może być zainicjalizowana l-wartością lub
r-wartością.**

Przykłady:

{% highlight c++ %}
{% include_relative cref.cc %}
{% endhighlight %}

## R-referencja

**R-referencja może być zainicjalizowana tylko r-wartością.**

Tak definiujemy r-referencję z użyciem deklaratora `&&`:

`T &&name = <expr>;`

R-referencja została wprowadzona w C++11, żeby umożliwić:

* semantykę przeniesienia,

* doskonałe przekazywanie argumentów wywołania funkcji szablonowej.

Przykłady:

{% highlight c++ %}
{% include_relative rref.cc %}
{% endhighlight %}

## Referencji nie można zmienić

Referencja (każda, nie tylko stała) nie może być zmieniona, żeby
odwoływała się do innej danej.  Referencja może być tylko
zainicjalizowana.  Taka zmiana byłaby wymagana przez operator
przypisania typu klasowego, który ma referencyjne pole składowe, tak
jak w przykładzie niżej:

{% highlight c++ %}
{% include_relative members.cc %}
{% endhighlight %}

## Kwalifikatory

Typ wskaźnikowy może mieć kwalifikatory `const` lub `volatile`
(ang. cv-qualified), a typ referencyjny nie (ang. cv-unqualified).

Przykłady dla wskaźnika:

{% highlight c++ %}
{% include_relative qualifiers_ptr.cc %}
{% endhighlight %}

Przykłady dla referencji:

{% highlight c++ %}
{% include_relative qualifiers_ref.cc %}
{% endhighlight %}

W przykładzie wyżej użyliśmy kwalifikatorów w deklaracjach referencji,
ale nie na **najwyższym poziomie** (ang. top-level).  Kwalifikator
najwyższego poziomu dla typu referencyjnego byłby na prawo od
deklaratora `&`, ale tam jest zabroniony.

## Referencja do wskaźnika, ale nie na odwrót.

Referencja do wskaźnika istnieje, ale nie wskaźnik do referencji.

{% highlight c++ %}
{% include_relative r2p.cc %}
{% endhighlight %}

# Sztuczki referencyjne

## Typ referencji a wybór przeciążeń funkcji

Funkcja może być przeciążana w zależności od typów parametrów i to
także dotyczy typów referencyjnych.  Mamy zatem trzy możliwe
przeciążenia:

* `void foo(T &);` - przeciążenie #1,
* `void foo(const T &);` - przeciążenie #2,
* `void foo(T &&);` - przeciążenie #3.

Przy wywołaniu funkcji `foo(<expr>)` kompilator wybierze przeciążenie
(ang. overload resolution):

* #1, jeżeli `<expr>` jest l-wartością niestałego typu,

* #2, jeżeli `<expr>` jest l-wartością stałego typu,

* #3, jeżeli `<expr>` jest r-wartością.

Referencja stała (użyta w przeciążeniu #2) może być zainicjalizowana
l-wartością niestałego typu albo r-wartością, więc kiedy nie
zadeklarowano przeciążeń #1 i #3, kompilator wybierze przeciążenie #2.

Oto przykład:

{% highlight c++ %}
{% include_relative overloading.cc %}
{% endhighlight %}

## Konwersja l-wartości do r-wartości

Możemy jawnie konwertować l-wartość do r-wartości przez użycie
`static_cast<T &&>(<expr>)`, gdzie `<expr>` może być l-wartością albo
r-wartością.  Jawne podanie typu `T` jest jednak trochę uciążliwe.

Prościej jest otrzymać r-wartość z użyciem `std::move(<expr>)`, gdzie
`<expr>` może być l-wartością albo r-wartością.  Funkcja `std::move`
jest szablonowa, gdzie typ r-wartości będzie wywnioskowany na
podstawie typu wyrażenia `<expr>`.  Funkcja używa `static_cast<T
&&>(<expr>)`.

Przykład:

{% highlight c++ %}
{% include_relative move.cc %}
{% endhighlight %}

### Jeden przypadek użycia

Jawnej konwersji l-wartości do r-wartości używamy tylko po to, żeby
jawnie umożliwić przenoszenie obiektu `x`, który nie mógłby być
przeniesiony, bo wyrażenie `x` jest l-wartością.  Zmieniając kategorię
wyrażenia, wpływamy na wybór przeciążenia konstruktora obiektu,
operatora przypisania, czy dowolnej innej funkcji przeciążonej typami
referencyjnymi.

## Przedłużenie istnienia danej tymczasowej

Istnienie danej tymczasowej może być przedłużone referencją, która
odwołuje się do niej.  Dana tymczasowa będzie zniszczona, kiedy
referencja wyjdzie poza zakres.  Bez referencji, dana tymczasowa
byłaby niszczona po opracowaniu wyrażenia.

{% highlight c++ %}
{% include_relative tmp.cc %}
{% endhighlight %}

Referencyjne pole składowe może odwoływać się do danej tymczasowej.
Referencja musi być zainicjalizowana przez konstruktor.  Dana będzie
niszczona podczas niszczenia obiektu:

{% highlight c++ %}
{% include_relative tmp2.cc %}
{% endhighlight %}

# Podsumowanie

* Referencja daje możliwość odwołania się do danej przez nazwę.

* Referencja musi być zainicjalizowana i nie może być zmieniona.

* Są trzy typy referencji:

  * l-referencja,

  * stała referencja,

  * r-referencja.

* Referencja przedłuża istnienie danej tymczasowej.

<!-- LocalWords: expr -->
<!-- LocalWords: lvalue lvalues rvalue -->
<!-- LocalWords: rvalue -->

<!-- LocalWords: deklaratora -->
<!-- LocalWords: deklaratorem -->

<!-- LocalWords: inicjalizowana -->
<!-- LocalWords: inicjalizowaną -->
<!-- LocalWords: inicjalizowane -->
<!-- LocalWords: inicjalizującego -->
<!-- LocalWords: inicjalizującym -->

<!-- LocalWords: wyoptymalizowana -->
<!-- LocalWords: wyoptymalizowane -->
<!-- LocalWords: wyoptymalizowanie -->

<!-- LocalWords: zainicjalizowana -->
<!-- LocalWords: zainicjalizowaną -->
<!-- LocalWords: zainicjalizowane -->

<!-- LocalWords: binds -->
<!-- LocalWords: nullptr -->
<!-- LocalWords: object -->
<!-- LocalWords: overload -->
<!-- LocalWords: name names -->
<!-- LocalWords: member -->
<!-- LocalWords: move -->
<!-- LocalWords: reference references -->
<!-- LocalWords: refer refers -->
<!-- LocalWords: resolution -->
<!-- LocalWords: title -->
