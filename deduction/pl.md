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

Kiedy korzystamy z kontenerów bilbioteki standardowej (a każdy robił
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
  parametru szablonu jednoparametrowego, którego argument komilator
  wnioskuje,

* obiekt klasy szablonowej na podstawie argumentów wywołania
  konstruktora (np. `pair p{1, .1};`).

Kiedy kompilator kompiluje wywołanie jakiejś funkcji szablonowej, to
musi skonkretyzować szablon funkcji, czyli wygenerować kod funkcji
szablonowej na podstawie szablonu funkcji i jego argumentów.  Jeżeli
argumenty szablonu nie są jawnie podane, to kompilator musi je
wywnioskować, a jeżeli nie jest w stanie tego zrobić, to korzysta z
domyślnych argumentów, jeżeli są.

Kompilator wnioskuje argumenty szablonu funkcji na podstawie:

* **typów** parametrów szablonu funkcji,

* **typów** argumentów funkcji szablonowej, czyli wyrażeń, które są
  argumentami wywołania funkcji szablonowej.

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
list`) szablonu funkcji `foo` na podstawie typu `ParameterType` i typu
wyrażenia `expr`.  Parametr `t` funkcji `foo` jest typu
`ParameterType`.  Typ `ParameterType` zależy od co najmniej jednego
parametru szablonu.  Sposobów zdefiniowania typu `TypParametru` w
zależności od parametrów szablonu jest wiele, a my omówimy
najważniejsze.

Ponieważ parametr funkcji jest inicjalizowany na podstawie argumentu
wywołania funkcji, to wnioskowanie sprowadza się do znalezienia typu
`T` w deklaracji i inicjalizacji na podstawie typu wyrażenia `expr`:

```cpp
lista_kwalifikatorów T deklarator nazwa_zmiennej = expr;
```

`lista_kwalifikatorów` może być pusta, `const`, `volatile`, albo
`const volatile`.  `deklarator` może być pusty, `*` lub `&`.

Na przykład, `T = int` żeby ten kod się skompilował (bo `1` jest
r-wartością, a tę można wskazać referencją stałą):

```cpp
const T &r = 1;
```

Dla każdego **rodzaju** parametru szablonu, kompilator może wnioskować
argument.  Najczęściej chcemy, żeby kompilator wnioskował typowe
argumenty, ale czasem też argumenty wartościowe czy szablonowe.

## Typowy argument

Typowego parametru używamy w definicji typu parametru funkcji, który
może być typem:

* referencyjnym lub wskaźnikowym,

* zwykłym (niereferencyjnym, niewskaźnikowym).

W zależności od zdefiniowanego typu parametru funkcji, kompilator
stosuje różne zasady wnioskowania typowego argumentu.

### Referencyjny lub wskażnikowy typ parametru funkcji

*Zasada: wnioskowany argument jest typem argumentu wywołania z
 pominięciem kwalifikatorów `const` czy `volatile` jeżeli te
 kwalifikatory zostały podane w definicji typu parametru funkcji.*

Oto przykład dla typów referencyjnych:

{% highlight c++ %}
{% include_relative arg_type_ref.cc %}
{% endhighlight %}

Oto przykład dla typów wskaźnikowych:

{% highlight c++ %}
{% include_relative arg_type_ptr.cc %}
{% endhighlight %}

### Wskaźnikowy typ parametru funkcji

### Zwykły typ parametru funkcji

## Wartościowy argument

## Szablonowy argument

## Więcej parametrów funkcji
