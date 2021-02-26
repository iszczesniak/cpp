---
title: Organizacja pamięci
---

# Wprowadzenie

C++ przetwarza dane typów *wbudowanych* (np. `int`, `long double`)
albo *zdefiniowanych przez użytkownika* (np., `struct A`, `struct B`,
`enum C`, `union D`).  Standard C++ opisuje:

* kiedy dane są tworzone i niszczone,

* gdzie (w którym miejscu pamięci, w jakiej strukturze danych) dane
  się znajdują,

* jak dane są przekazywane do funkcji i jak są zwracane przez funkcję.

C++ musi spełniać podstawowe wymagania systemu operacyjnego dotyczące
organizacji pamięci, a reszta zależy do C++.

## Podstawowe wymagania systemu operacyjnego

Uruchomiony *program* jest *procesem* w systemie operacyjnym i
*zadaniem* wykonywanym przez procesor.  Proces zarządza swoją pamięcią
zgodnie z ograniczeniami systemu operacyjnego.  System operacyjny daje
procesowi do dyspozycji dwa rodzaje pamięci: *tylko do odczytu* oraz
*do zapisu i odczytu*.

Pamięć tylko do odczytu przechowuje kod programu (rozkazy procesora) i
dane stałe programu znane w czasie kompilacji, np. literały
łańcuchowe.  Ta pamięć jest współdzielona przez wszystkie procesy
programu, co znacząco oszczędza pamięć w przypadku dużych programów
uruchamianych w dużej liczbie, np. przglądarek czy serwerów
internetowych.

Zadanie może być uprzywilejowane albo nieuprzywilejowane.  Tylko
zadania jądra systemu operacyjnego są uprzywilejowane.  Procesy są
zadaniami nieuprzywilejowanymi.  *Zadanie nieuprzywilejowane* nie może
naruszyć danych innych zadań, w szczególności nie może pisać do swojej
pamięci tylko do odczytu.

W poniższym przykładzie próbujemy pisać do literału łańcuchowego,
który jest znajduje się w pamięci tylko do odczytu.  Program się
kompiluje, ale proces jest unicestwiony przez system operacyjny
sygnałem SIGSEGV (segment violation).

{% highlight c++ %}
{% include_relative sigsegv.cc %}
{% endhighlight %}

Wszystkie inne dane programu (poza tymi w pamięci tylko do odczytu) są
w pamięci do odczytu i zapisu, bo na tych danych program wykonuje
obliczenia.  Każd proces tego samego programu ma osobną pamięć do
odczytu i zapisu.

## Co zależy od C++

C++ jest wydajny czasowo i pamięciowo, co wynika głównie z organizacji
pamięci i użycia wskaźników, czyli niskopoziomowego mechanizmu.  Co
więcej, C++ zapewnia swobodne zarządzanie danymi: np., programista
może alokować dane statycznie, globalnie, lokalnie lub dynamicznie.
Organizacja pamięci jest także *deterministyczna*: możemy dokładnie
wskazać, które dane i gdzie są niszczone, bo C++ niszczy je dokładnie
wtedy, kiedy nie są już potrzebne.

Pod tym względem C++ znacznie różni się od innych języków, takich jak
Java czy C#, gdzie zarządzanie pamięcią jest uproszczone, ale kosztem
spadku wydajności i ograniczonej swobody zarządzania danym.  Na
przykład, te języki pozwalają na alokację obiektów wyłącznie na
stercie, co pogarsza wydajność i swobodę zarządzania danymi, ale
pozwala na łatwą implementację odśmiecania pamięci (ang. garbage
collection).  Odśmiecanie pamięci może być *niedeterministyczne*: nie
ma gwarancji, kiedy dane będą niszczone, a to powoduje dalsze
pogorszenie wydajności programu.

Komitet Standaryzacyjny C++ rozważał wprowadzenie odśmiecania pamięci,
ale zaniechał tego z powodu oczekiwanego spadku wydajności programów.
Dzisiaj programy pisane w C++ nie wymagają odśmiecania pamięci,
ponieważ jest dostępna bogada funkcjonalność kontenerów i
inteligentnych wskaźników, które mogą być uznane za rodzaj odśmiecania
pamięci.

# Dane i ich miejsce w pamięci

Pamięć do zapisu i odczytu przechowuje:

* globalne i statyczne dane w obszarze pamięci o ustalonym rozmiarze,

* dane lokalne odłożone na stosie (a dokładnie na stosie dla każdego w
  wątków osobno),

* dane dynamiczne na stercie.

## Dane globalne i statyczne

Dane globalne są zainicjalizowane przed wywołaniem funkcji `main`:

{% highlight c++ %}
{% include_relative global.cc %}
{% endhighlight %}

Dane statyczne są zainicjalizowane przed ich pierwszym użyciem:

Static data are initialized before its first use:

{% highlight c++ %}
{% include_relative static.cc %}
{% endhighlight %}

W przykładzie wyżej, proszę usunąć `static` i zauważyć zmianę w
zachowaniu programu.

## Lokalne dane

Dane lokalne funkcji albo bloku są tworzone na stosie.  Dane lokalne
są automatycznie niszczone, kiedy wychodzą poza zakres (funkcji albo
bloku) -- to nie tylko poręczna własność danych lokalnych, ale także
konieczność, bo stos musi się zmniejszyć, kiedy zakres się kończy.

Lokalne dane są niszczone w kolejności odwrotnej do kolejności ich
tworzenia, bo stos jest strukturą FILO (ang. first in, last out).

{% highlight c++ %}
{% include_relative local.cc %}
{% endhighlight %}

## Dynamiczne dane

Dynamiczne dane (albo precyzyjniej: dane alokowane dynamicznie) są
tworzone na stercie i powinny być zarządzane przez *inteligentny
wskaźnik*, który to z kolei jest zaimplementowany z użyciem
nisko-poziomowej funkcjonalności surowych wskaźników, w szczególności
operatorów `new` and `delete`.

Dane stworzone przez operator `new` muszą być potem zniszczone przez
operator `delete`, żeby uniknąć wycieku pamięci.  Próba zniszczenia
tych samych danych dwa razy skutkuje niezdefiniowanym zachowaniem
(np., naruszenie ochrony pamięci, bugi).

Powinniśmy używać inteligentnych wskaźników, bo chronią przed błędami
i upraszczają kod, ale są trudniejsze w użyciu niż surowe wskaźniki.
Użycie surowych wskaźników jest narażone na błędy (ang. error-prone),
które powracają jako uciążliwe heisenbugi.  Ponieważ inteligentne
wskaźniki zostały wprowadzone w C++11, to nowy kod zazwyczaj używa
inteligentnych wskaźników, a stary kod surowych wskaźników.

W poniższym przykładzie użyliśmy operatorów `new` i `delete`, czego
już lepiej nie robić, ale jest to najprostszy przykład użycia danych
dynamicznych.

{% highlight c++ %}
{% include_relative dynamic.cc %}
{% endhighlight %}

## Lokalne a dynamiczne dane

Alokacja pamięci dla danych na stosie jest najszybsza: wystarczy
zwiększyć (albo zmniejszyć, w zależności od architektury procesora)
wskaźnik stosu (zwany także rejestrem stosu) o wielkość potrzebnej
pamięci.

Stos może mieć ustalony rozmiar albo jego rozmiar może rosnąć
automatycznie: dodatkowa pamięć dla stosu może być alokowana bez
potrzeby żądania tego przez proces, jeżeli system operacyjny to
potrafi.  Jeżeli nie, to proces zostanie zakończony z błędem, kiedy
dojdzie do przepełnienia stosu.

Poniższy kod testuje, jak duży jest stos i czy system operacyjny
potrafi automatycznie przydzielać więcej pamięci dla stosu.  Funcja
wywołuje siebie (rekursywnie) i wypisuje na standardowe wyjście, ile
razy była wywołana.  Jeżeli widzimy małe liczby (poniżej miliona),
kiedy proces był zakończony, to system nie jest w stanie automatycznie
zwiększać rozmiaru stosu.  Jeżeli widzimy duże liczby (znacznie
powyżej miliona), to najprawdopodobniej system automatycznie zwiększał
rozmiar stosu.

{% highlight c++ %}
{% include_relative stack_test.cc %}
{% endhighlight %}

Alokacja pamięci na stercie jest wolna, bo sterta jest złożoną
stukturą danych, która nie tylko alokuje i dealokuje pamięć dowolnego
rozmiaru, ale także defragmentuje pamięć.  Taka funkcjonalność wymaga
kilku zapisów i odczytów pamięci dla jednej alokacji.

System operacyjny alokuje więcej pamięci dla sterty, kiedy proces tego
żąda, a dokładnie żąda tego bilioteka, która dostarcza funkcjonalność
dynamicznej alokacji pamięci (na Linuxie to libstdc++).  Bilioteka
prosi system o przydzielenie pamięci do zapisu i odczytu, ale system
nie wie, że ma to być dla sterty.

Sterta może być zwiększana do dowolnego rozmiaru, ograniczonego
jedynie przez system operacyjny.  Kiedy system w końcu odmawia
przydzielenia więcej pamięci, operator `new` rzuca wyjątek
`std::bad_alloc`.  Oto przykład:

{% highlight c++ %}
{% include_relative heap_test.cc %}
{% endhighlight %}

Dane na stosie są upakowane razem w zależności od tego, kiedy były
tworzone, tak więc dane powiązane ze sobą znajdują się blisko siebie w
pamięci.  Nazywamy to *kolokacją danych*.  Lokalizacja jest korzystna,
ponieważ dane potrzebne procesowi (a dokładniej jakiejś funkcji
procesu) w pewnym momencie najprawdopodobniej znajdują się w pamięci
podręcznej procesora (która przechowuje strony pamięci),
przyspieszając kilkakrotnie dostęp do danych.

Powiązane ze sobą dane są mniej kolokowane na stercie (w porównaniu ze
stosem): prawdopodobnie są rozrzucone po różnych miejscach sterty, co
spowolnia do nich dostęp, bo prawdopodobnie nie znajdują się w pamięci
podręcznej procesora.

# Wywołania funkcji

Wywołując funkcję możemy przekazać argument przez wartość albo przez
referencję.  Funkcja może wrócić wynik także przez wartość albo
referencję.  Nie ma innych sposobów przekazywania argumentów i
zwracania wartości.

Funkcja ma *parametry*, a funkcję wywołujemy z *argumentami*.
Parametr funkcji jest dostępny wewnątrz funkcji.  Parametr ma typ i
nazwę podawane przy deklaracji lub definicji funkcji.  Argument jest
wyrażeniem, które jest częścią wyrażenia wywołania.  Parametr jest
inicjalizowany z użyciem argumentu.

## Przekazywanie argumentów

Jeżeli parametr funkcji jest typu niereferencyjnego, to mówimy, że
funkcja przyjmuje argument przez wartość albo że przekazujemy argument
do funkcji przez wartość.  W starszym C++ parametr niereferencyjny był
inicjalizowany przez skopiowanie wartości argumentu do parametru.

Jeżeli parametr funkcji jest typu referencyjnego, to mówimy, że
funkcja przyjmuje argument przez referencję albo że przekazujemy
argument do funkcji przez referencję.  Inicjalizacja czyni parametr
nazwą (aliasem) danych argumentu.

Przykład niżej pokazuje jak przekazujemy argumenty przez wartość i
przez referencję.  Proszę skompilować przykład z flagą
`-fno-elide-constructors` (flaga kompilatora GCC), żeby kompilator nie
unikał konstruktorów.

{% highlight c++ %}
{% include_relative args.cc %}
{% endhighlight %}

## Returning values

A function can return a result either by value or reference.

If the return type is of a non-reference type, we say that a function
returns the result by value.  In the deep past (before C++ was
standardized) that always entailed copying the result (i.e., the data
local to the function) from one location on the stack to a temporary
on the stack, and then to its final location, e.g., a variable.

If the return type is of a reference type, we say that a function
returns the results by reference.  The reference should be bound to
data that will exist when the function returns (i.e., the data should
outlive the function).  Containers (e.g., `std::vector`), for
instance, return a reference to dynamically-allocated data in, for
instance, `operator[]` or `front` functions.

This example shows how to return results by value and by reference.
Compile the example with the flag `-fno-elide-constructors`.

{% highlight c++ %}
{% include_relative return.cc %}
{% endhighlight %}

# Function call convention

The technical details on how exactly a function is called is known as
the *call convention*, which depends on the system architecture, the
operating system, and the compiler.  C++ does not specify a call
convention, but some C++ functionality (like the constructor elision
and the return value optimization) follows from a typical call
convention.

Typically, a call convention requires that the caller of the function
(i.e., the code that calls the function):

* creates the function parameters on the stack,

* allocates memory for the return value on the stack.

Small data may be passed or returned in processor registers.  For
instance, if a function returns an integer, the return value can be
returned in a register, e.g., EAX for x86, Linux, and GCC.

Legacy call conventions required the memory for the return value be
the last data on the stack before a function was called, so that it
could located with the pointer register.  This, however, entailed
copying of the return value from that temporary (the last on the
stack) location to its final destination, e.g., a local variable.

Modern call conventions allow the memory for the return value be
allocated anywhere in memory (on the stack, on the heap, or in the
fixed-size memory for the static and global data), and the address be
passed to a function in a processor register (e.g., RDI for x86,
Linux, and GCC), so that the function can create the return value in
the pointed location.

The following example demonstrates that the return value can be
created anywhere (as the modern call convention allows), and not only
on the stack (as the legacy call convention stipulated).  In the
example a function returns an object which is created directly in the
memory location for global and static data, without copying the object
from the stack as the legacy call convention would require.

{% highlight c++ %}
{% include_relative mcc.cc %}
{% endhighlight %}

# Constructor elision

C++ elides (avoids) constructors (specifically, two constructors: the
copy constructor, and the *move* constructor) for temporary or local
objects that would soon be destroyed.  Instead of creating a
temporary, the object is created in the final location where it would
end up.

This example that demonstrates the constructor elision.  Compile the
example with, then without the flag `-fno-elide-constructors`.  Notice
the differences at run-time.

{% highlight c++ %}
{% include_relative elide.cc %}
{% endhighlight %}

Compile the previous examples of passing arguments to and returning
results from functions but without disabling the constructor elision.
Notice that with constructor elision, objects are not copied
unnecessarily.

When a temporary is passed by value as an argument, that temporary is
created directly (i.e., with the constructor elided) in the location
of the function parameter.

# Return value optimization

When a result is returned by value from a function, it can be created
directly (i.e., with the constructor elided) in the location for the
return value.  This is known as the return value optimization (RVO).

RVO not always can take place, because of technical reasons.  First,
because we return data, which has to be created prior to deciding
which data exactly to return:

{% highlight c++ %}
{% include_relative rvo_no1.cc %}
{% endhighlight %}

Second, because we try to return a function parameter, which was
created by the caller, not the function, and so the function cannot
create the parameter in the location for the return value:

{% highlight c++ %}
{% include_relative rvo_no2.cc %}
{% endhighlight %}

Finally, because we try to return static or global data, which has to
be available after the function returns, and so the function can only
copy the result from the static or global data:

{% highlight c++ %}
{% include_relative rvo_no3.cc %}
{% endhighlight %}

# Conclusion

Data can be allocated statically, globally, locally or dynamically.

Allocating memory for local data (on the stack) is ultra fast, while
for dynamic data (on the heap) is much slower.

Don't use the dynamically-allocated data, if local data is good
enough.

Passing parameters or return results by value is not that bad, because
most likely their copying or moving will be elided.

# Quiz

* Is memory allocation on the stack faster than on the heap?

* Where can we allocate objects?

* What is the return value optimization?

{% include rid %}

<!-- LocalWords: enum  sigsegv endhighlight heisenbugs -->
<!-- LocalWords: deallocates defragmentation manyfold args -->
<!-- LocalWords: EAX RDI RVO SIGSEGV -->