---
title: Wnioskowanie argumentów szablonu
---

# Wprowadzenie

Argumenty szablonu mogą być:

* wnioskowane przez kompilator (najczęściej stosowane),

* jawnie podane przez programistę (czasami niezbędne),

* domyślnie podane przez programistę (czasami wygodne).

Ten przykład pokazuje wyżej wymienione przypadki:

{% highlight c++ %}
{% include_relative intro.cc %}
{% endhighlight %}

Skoncentrujemy się na wnioskowaniu, ale pierwsze omówimy jawne
podawanie argumentów szablonów i domyślne argumenty szablonów.

## Jawnie podane argumenty szablonu

Kiedy korzystamy z kontenerów biblioteki standardowej (a każdy robił
to na pewno), jawnie podajemy argumenty szablonu jako część nazwy typu
używając `<>`, czyli składni `typ kontenera<lista argumentów>`:

{% highlight c++ %}
{% include_relative explicit.cc %}
{% endhighlight %}

Tej składni możemy też użyć przy wywołaniu funkcji szablonowej (a nie
tylko przy definiowaniu typu, np. kontenera), co jest przydatne w
dwóch przypadkach:

* chcemy innych argumentów niż te wnioskowane przez kompilator, co
  zrobiliśmy w przykładzie wyżej z funkcją `print`,

* musimy jawnie podać argumenty, bo kompilator nie jest ich w stanie
  wywnioskować.

Kompilator wnioskuje argumenty szablonu na podstawie typów wyrażeń,
które są przekazywane w wyrażeniu wywołania funkcji (kiedy wywołujemy
funkcję) czy konstruktora (kiedy tworzymy obiekt).  Jeżeli nie jest w
stanie wywnioskować argumentów, to musimy jawnie je podać.

Przykład niżej pokazuje implementację fabryki obiektów.  Argument
wywołania fabryki przekazujemy do konstruktora obiektu, którego typ
jest określony przez argument szablonu.  Kompilator nie jest w stanie
określić typu obiektu, więc musimy go jawnie podać.

{% highlight c++ %}
{% include_relative explicit2.cc %}
{% endhighlight %}

### Kolejność argumentów

Kolejność argumentów szablonu ma znaczenie (tak jak w przypadku
argumentów wywołania funkcji), bo argumenty są pozycyjne, czyli od
pozycji argumenty zależy to, o który argument nam chodzi.  Tak więc
jeżeli chcemy podać drugi argument, to musimy podać też pierwszy
argument.

Jeżeli w powyższym przykładzie z fabryką zmienimy kolejność
argumentów, to typ argumentu wywołania konstruktora będziemy musieli
także podać jawnie, chociaż mógłby być wywnioskowany.  A musimy jawnie
podać pierwszy argument, bo musimy podać drugi argument.

{% highlight c++ %}
{% include_relative explicit3.cc %}
{% endhighlight %}

## Domyślne argumenty szablonu

Parametr szablonu (każdego rodzaju: typowy, wartościowy i szablonowy)
może mieć zdefiniowany domyślny argument, które będzie użyty, jeżeli
kompilator nie jest w stanie wywnioskować argumentu.  Może mieć, więc
domyślny argument jest opcjonalny.

Domyślny argument podajemy po nazwie parametru z użyciem `=`.  Oto
przykład:

{% highlight c++ %}
{% include_relative default.cc %}
{% endhighlight %}

### Domyślne callable

Czasami trzeba przekazać callable jakiejś funkcji, ale nie zawsze to
callable jest wymagane.  Nie chcemy przekazywać wskaźnika i sprawdzać
w czasie uruchomienia, czy jest on `nullptr`, albowiem niewydajne i
nieciekawe.  Chcemy, żeby callable było wkompilowane, a w szczególnym
przypadku, żeby callable nie wprowadzało narzutu, jeżeli nie jest
wymagane.  Do tego właśnie przydaje się domyślny argument szablonu.

Rozwiązanie: typ callable jest parametrem szablonu z domyślnym
argumentem, którym jest pusty callable, czyli struktura z operatorem
wywołania o pustym ciele.  Musimy też podać domyślną wartość callable
(argumentu wywołania funkcji), czyli `{}` (będzie wywołany domyślny
konstruktor).  Oto super przykład:

{% highlight c++ %}
{% include_relative empty_callable.cc %}
{% endhighlight %}

# Wnioskowanie argumentów szablonu

Argumenty szablonu są wnioskowane dla naszej wygody, żeby nie trzeba
było ich jawnie podawać i nie pomylić się przy okazji.  Kompilator
wnioskuje argumenty szablonu kiedy kompiluje wywołanie funkcji
szablonowej -- to jest najczęstsze zastosowanie.  Ale te same zasady
wnioskowania są też wykorzystywane kiedy *inicjalizujemy*:

* zmienną typu `auto` na podstawie wyrażenia inicjalizującego
  (np. `auto i = m.find(key);`), gdzie `auto` pełni rolę typowego
  parametru szablonu, którego argument kompilator wnioskuje,

* obiekt klasy szablonowej na podstawie argumentów wywołania
  konstruktora (np. `pair p{1, .1};`).

Kiedy kompilator kompiluje wywołanie jakiejś **funkcji szablonowej**,
to musi skonkretyzować **szablon funkcji**, czyli wygenerować kod
funkcji szablonowej na podstawie szablonu funkcji i jego argumentów.
Jeżeli argumenty szablonu nie są jawnie podane, to kompilator musi je
wywnioskować, a jeżeli nie jest w stanie tego zrobić, to korzysta z
domyślnych argumentów, jeżeli są.

Kompilator wnioskuje argumenty szablonu funkcji na podstawie:

* **typów** parametrów szablonu funkcji,

* **typów** argumentów funkcji szablonowej, czyli wyrażeń, które są
  argumentami wywołania funkcji szablonowej.

## Najprostszy przypadek

W najprostszym przypadku kompilator kompiluje wywołanie funkcji z
jednym parametrem:

```cpp
template <parameter list>
void
foo(ParameterType t)
{
  // Body of a function template.
}

int
main()
{
  foo(expr);
}
```

Kompilator ma wywnioskować argumenty dla parametrów (tych z `parameter
list`) szablonu funkcji `foo` na podstawie typu wyrażenia `expr` i
typu `ParameterType` parametru `t` funkcji `foo`.  Żeby można mówić o
wnioskowaniu, typ `ParameterType` musi zależeć od (użyć w swojej
definicji) co najmniej jednego parametru szablonu.  Sposobów
zdefiniowania typu `ParameterType` w zależności od parametrów szablonu
jest wiele, a my omówimy najważniejsze.

## Inicjalizacja parametrów funkcji szablonowej: bez konwersji

Ponieważ parametr funkcji jest inicjalizowany na podstawie argumentu
wywołania funkcji, to wnioskowanie argumentów szablonu ma pozwolić na
tę inicjalizację.  Wnioskowanie wprowadza ważne ograniczenie:
**inicjalizacja ma się odbyć bez konwersji typu** (z typu argumentu
wywołania funkcji do typu parametru funkcji).  Tego warunku nie ma
przy wywołaniu zwykłej (nieszablonowej) funkcji, gdzie konwersje są
dozwolone.

Inicjalizacja parametru `t` w powyższym najprostszym przypadku wygląda
zatem tak:

```cpp
ParameterType t = expr;
```

Kompilator musi tak wywnioskować argumenty szablonu, których parametry
są użyte w definicji typu `ParameterType`, żeby inicjalizacja była
możliwa bez konwersji typu.  Może się to okazać niemożliwe, co
uniemożliwia użycie szablonu.

Na przykład, jeżeli `ParameterType` jest typem referencyjnym na obiekt
stały typu `T`, który jest parametrem szablonu, a argumentem wywołania
funkcji jest `1`, to inicjalizacja wygląda tak:

```cpp
const T & t = 1;
```

Wywnioskowanym argumentem będzie `int`, bo wtedy ta inicjalizacja jest
możliwa bez konwersji typu.

# Rodzaje argumentów

Dla każdego **rodzaju** parametru szablonu, kompilator może wnioskować
argument.  Najczęściej chcemy, żeby kompilator wnioskował typowe
argumenty, ale czasem też argumenty wartościowe czy szablonowe.

## Typowy argument

Typowego parametru używamy w definicji typu parametru funkcji, który
może być typem:

* referencyjnym lub wskaźnikowym,

* zwykłym (niereferencyjnym i niewskaźnikowym).

W zależności od zdefiniowanego typu parametru funkcji, kompilator
stosuje różne zasady wnioskowania typowego argumentu.

### Referencyjny lub wskaźnikowy typ parametru funkcji

*Zasada: wnioskowany argument szablonu jest typem argumentu wywołania
 z pominięciem kwalifikatorów typu (`const` czy `volatile`) jeżeli te
 kwalifikatory zostały podane w definicji typu parametru funkcji.*

Chodzi o to, żeby referencyjny (albo wskaźnikowy) typ parametru
funkcji rzeczywiście mógł być zainicjalizowany: jeżeli typ argumentu
wywołania jest stały (bądź ulotny), to referencja (albo wskaźnik) musi
być stała (bądź ulotna).

Oto przykład dla typów referencyjnych, gdzie funkcja `foo1` została
skonkretyzowana trzy razy, funkcje `foo2` i `foo3` po dwa razy, a
`foo4` raz:

{% highlight c++ %}
{% include_relative arg_type_ref.cc %}
{% endhighlight %}

Oto przykład dla typów wskaźnikowych:

{% highlight c++ %}
{% include_relative arg_type_ptr.cc %}
{% endhighlight %}

### Zwykły typ parametru funkcji

*Zasada: wnioskowany argument szablonu jest typem argumentu wywołania
 z pominięciem kwalifikatorów `const` i `volatile`.*

Chodzi o to, że inicjalizacja parametrów funkcji (przy przekazywaniu
argumentów wywołania przez wartość) kopiuje wartość argumentu
wywołania do parametru funkcji.  Wtedy nie trzeba już zadbać o
kwalifikatory typu, bo w ciele funkcji działamy na kopii.

Przykład:

{% highlight c++ %}
{% include_relative arg_type_val.cc %}
{% endhighlight %}

Każda z funkcji w powyższym przykładzie została skonkretyzowana tylko
raz - wydaje się, że kwalifikatory typu (`const` i `volatile`) podane
w definicji szablonu nie miały znaczenia.  Kwalifikatory typu dla
parametrów zwykłych typów (niereferencyjnych i niewskaźnikowych) mają
jedynie znaczenie na etapie kompilacji: kompilator ma nie pozwolić na
modyfikację parametru i nie optymalizować odwołań do parametru.  Typy
tych funkcji nie mają zachowanych kwalifikatorów typu, bo nie mają one
znaczenia dla kodu wywołującego te funkcje.

### Przekazywanie funkcji

Funkcję (czyli callable) możemy przekazać do funkcji szablonowej
przez:

* referencję,

* wskaźnik (jak w języku C).

Żeby funkcję przekazać przez referencję, to parametr funkcji
szablonowej ma mieć typ referencyjny, a dokładnie typ `F &`, gdzie `F`
jest typowym parametrem szablonu.  Wywnioskowanym argumentem szablonu
będzie typ przekazywanej funkcji.  Przykład:

{% highlight c++ %}
{% include_relative foo_ref.cc %}
{% endhighlight %}

Żeby funkcję przekazać przez wskaźnik, to parametr funkcji szablonowej
może mieć typ wskaźnikowy, a dokładnie typ `F *`, gdzie `F` jest
typowym parametrem szablonu.  Wywnioskowanym argumentem szablonu
będzie typ funkcji.  Przykład:

{% highlight c++ %}
{% include_relative foo_ptr.cc %}
{% endhighlight %}

Zamianę nazwy funkcji na wskaźnik do niej nazywamy **rozpadem funkcji
na wskaźnik** (ang. decay), który pochodzi z języka C.  Z rozpadu
skorzystaliśmy wyżej podając nazwę funkcji jako argument wywołania
funkcji szablonowej.

Możemy też zadeklarować zwykły (niereferencyjny i niewskaźnikowy) typ
parametru funkcji szablonowej, a i tak będziemy mogli przekazać
wskaźnik na funkcję, bo wtedy wywnioskowanym argumentem szablonu
będzie typ wskaźnikowy na funkcję.  Przykład:

{% highlight c++ %}
{% include_relative foo_val.cc %}
{% endhighlight %}

### Przekazywanie tablic języka C

Tablicę języka C możemy przekazać do funkcji szablonowej przez:

* referencję,

* wskaźnik.

Żeby tablicę przekazać przez referencję, to parametr funkcji
szablonowej ma mieć typ referencyjny, a dokładnie typ `A &`, gdzie `A`
jest typowym parametrem szablonu.  Wywnioskowanym argumentem będzie
typ tablicy.  Przykład:

{% highlight c++ %}
{% include_relative car_ref.cc %}
{% endhighlight %}

Żeby funkcję przekazać przez wskaźnik, to parametr funkcji szablonowej
ma mieć typ wskaźnikowy, a dokładnie typ `A *`, gdzie `A` jest typowym
parametrem szablonu.  Wywnioskowanym argumentem będzie typ funkcji.
Przykład:

{% highlight c++ %}
{% include_relative car_ptr.cc %}
{% endhighlight %}

Jeżeli typem argumentu funkcji szablonowej jest zwykły typ
(niereferencyjny i niewskaźnikowy), a argumentem wywołania funkcji
będzie nazwa tablicy, to:

* tablica rozpadnie (ang. decay) się na wskaźnik na pierwszy element
  tablicy,

* wywnioskowanym argumentem będzie typ wskaźnikowy na element tablicy.

Oto przykład z rozpadem:

{% highlight c++ %}
{% include_relative foo_val.cc %}
{% endhighlight %}
