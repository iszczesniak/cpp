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

* **wyciek pamięci** (ang. a memory leak), kiedy dynamicznie
    zaalokowane dane nie są nigdy zniszczone, mimo że nie są już
    potrzebne,

* **dyndającym wskaźnikiem** (ang. a dangling pointer), kiedy
    odwołujemy się do zwolnionego miejsca w pamięci, do danych, które
    zostały już zniszczone,

* **podwójnym usunięciem** (ang. a double deletion), kiedy próbujemy
    zniszczyć dane, które już zostały zniszczone.

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
musi dziedziczyć z jakiegoś typu bazowego (interfejsu) i implementować
go.

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

Inteligentne wskaźniki używają surowych wskaźników w swojej
implementacji, więc można powiedzieć, że obudowują je.  Na przykład,
semantyka przeniesienia jest elementem tej obudowy, która jest
niezbęda do wygodnej i poprawnej implementacji, ale nie wprowadza
żadnego narzutu czasowego w czasie uruchomienia.  Inteligentne
wskaźniki są tak szybkie i używają tak mało pamięci, jak to jest tylko
możliwe, czyli tak, jakbyśmy ręcznie (ale ciągle poprawnie) wyrzeźbili
ten kod.

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

## Funkcja `std::make_unique`

Szablon funkcji `std::make_unique` został wprowadzony dla wygody
(dalibyśmy radę bez niego): funkcja tworzy dane zarządzane i
zarządzający obiekt.

Możemy sami stworzyć dane i przekazać ich surowy wskaźnik obiektowi
zarządzającemu w ten sposób:

`unique_ptr<A> up(new A("A1"));`

Zamiast tego możemy napisać równoważny kod bez dwukrotnego pisania
`A`:

`auto up = make_unique<A>("A1");`

Funkcja `std::make_unique` nie wprowadza narzutu wydajnościowego:
konstruktor przenoszący będzie pominięty, zostanie zastosowana
optymalizacja wartości powrotu, więc obiekt zarządzający będzie
stworzony bezpośrednio w miejscu zmiennej `up`.

Używający specyfikatora typu `auto` prosimy kompilator o
wywnioskowanie typu dla zmiennej `up` na podstawie wyrażenia
inicjalizującego, czyli wyrażenia wywołania funkcji
`make_unique<A>("A1")`, której zwracana wartość jest typu
`std::unique_ptr<A>`.  Moglibyśmy równoważnie napisać:

`unique_ptr<A> up = make_unique<A>("A1");`

Szablonowi funkcji `std::make_unique` przekazujemy jako jego argument
typ danych do stworzenia i zarządzania.  Argumenty (w dowolnej
liczbie, także zero) wywołania funkcji są przekazywane do konstruktora
zarządzanych danych.  W przykładzie wyżej, `"A1"` jest argumentem
przekazywanym do konstruktora typu `A`.

## Bez narzutu wydajnościowego

Poniższy przykład pokazuje, że inteligentne wskaźniki nie wprowadzają
narzutu wydajnościowego.  W bardziej skomplikowanych przykładach być
może będzie drobny narzut, ale można oczekiwać, że wraz z kolejnymi
standardami C++ i nowszymi kompilatorami, ten narzut będzie mniejszy.

Przykład używa `std::unique_ptr` i `std::make_unique`.  Plik
`test1.cc`:

{% highlight c++ %}
{% include_relative test1.cc %}
{% endhighlight %}

Poniższy przykład implementuje tą samą funkcjonalność z surowymi
wskaźnikami.  Plik `test2.cc`:

{% highlight c++ %}
{% include_relative test2.cc %}
{% endhighlight %}

Kompilujemy do asemblera:

`g++ -S -O3 test1.cc test2.cc`

Otrzymaliśmy dwa pliki w asemblerze: `test1.s` i `test2.s`.  Spójrzymy
na jeden z nich:

`c++filt < test1.s | less`

Porównajmy te pliki, żeby się przekonać, że są takie same.  Porównanie
pokazuje, że `std::unique_ptr` i `std::make_unique` nie wprowadzają
narzutu:

`diff test1.s test2.s`

## Jak używać `std::unique_ptr`

Przykład niżej pokazuje, jak używać `std::unique_ptr`.

{% highlight c++ %}
{% include_relative usage.cc %}
{% endhighlight %}

# Rozwiązanie problemów

## Problem typu

Problem typu, czyli niespasowania wersji pojedynczej i tablicowej
operatorów `new` and `delete`, jest rozwiązany przez dwie wersje
inteligentnych wskaźników:

* dla pojedynczej danej: `std::unique_ptr<A>` zniszczy zarządzane dane
  z użyciem pojedynczej wersji operatora `delete`,

* dla tablicy danych: `std::unique_ptr<A[]>` zniszczy zarządzane dane
  z użyciem tablicowej wersji operatora `delete`.

Używając odpowiedniej wersji inteligentnego wskaźnika nie musimy
pamiętać o niszczeniu zarządzanych danych z użyciem odpowiedniego
operatora `delete`.

### Czychające problemy i jak sobie z nimi radzić.

Ciągle jednak możemy popełnić błędy, jak w przykładzie niżej, gdzie:

* używamy inteligentnego wskaźnika do zarządzania jedną daną, a
  alokujemy tablicę danych,

* używamy inteligentnego wskaźnika do zarządzania tablicą danych, a
  alokujemy jedną daną.

Szablon funkcji `std::make_unique` pozwala nam bezpieczne osiągnąć
poprawną implementację:

{% highlight c++ %}
{% include_relative solved_type.cc %}
{% endhighlight %}

### Lepiej użyć `std::array`!

Jeżeli potrzebujemy tablicy statycznego rozmiaru (czyli rozmiaru,
który nie zmienia się w czasie uruchomienia), to lepiej użyć
`std::array` zamiast tablicy języka C.  Możemy jej użyc z
inteligentnymi wskaźnikami w ten sposób:

{% highlight c++ %}
{% include_relative array.cc %}
{% endhighlight %}

## Problem własności

Problem własności jest rozwiązany: po prostu przenosimy własność przez
przenoszenie wartości inteligentnego wskaźnika, np. do funkcji czy
jakiejś struktury danych.  Możemy także przenieść własność przekazując
obiekt inteligentnego wskaźnika przez wartość, np. przekazując
argument do funkcji, albo zwracając wynik z funkcji.  Oto przykład:

{% highlight c++ %}
{% include_relative solved_ownership.cc %}
{% endhighlight %}

## Problem obsługi wyjątków

Kiedy rzucany jest wyjątek, to dane (albo jakikolwiek inny zasób),
które wcześniej były stworzone, ale nie są już potrzebne, powinny być
zniszczone (albo zasób zwolniony).  Programując z użyciem surowych
wskaźników możemy zwolnić pamięć w bloku obsługi wyjątku (ang. a catch
block), jak pokazano w przykładzie niżej.  Musimy zadeklarować
wskaźnik `p` przed blokiem przechwytywania wyjątku (ang. a try block),
żeby był dostępny w bloku obsługi wyjątku, a to komplikuje kod.

{% highlight c++ %}
{% include_relative except_raw1.cc %}
{% endhighlight %}

To samo, ale bezpieczniej, możemy osiągnąć z użyciem inteligentnych
wskaźników:

{% highlight c++ %}
{% include_relative except_smart1.cc %}
{% endhighlight %}

### Surowe wskaźniki nie takie łatwe

W poniższym przykładzie mamy wyciek pamięci, ponieważ standard nie
gwarantuje, że argumenty wywołania funkcji będą opracowane w
kolejności ich podania.  Wyciek da się zaobserwować (brak wywołania
destruktora) kompilując program z GCC.  Jeżeli używamy innego
kompilatora i nie widzimy wycieku, to powinien się on pojawić po
zamianie miejscami parametrów funkcji `foo`.

Obiekt klasy `A`:

* jest tworzony, ponieważ drugi argument wywołania funkcji `foo` jest
  opracowywany jako pierwszy, przed wywołaniem funkcji `index`,

* nie jest niszczony, ponieważ funkcja `index` rzuca wyjątek, więc
  funkcja `foo` nie jest wywołana.

{% highlight c++ %}
{% include_relative except_raw2.cc %}
{% endhighlight %}

To samo, ale bezpieczniej, możemy osiągnąć z użyciem inteligentnych
wskaźników.  Ten kod działa poprawnie z wyjątkami.

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
