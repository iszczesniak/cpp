---
title: Organizacja pamięci
---

# Wprowadzenie

C++ przetwarza dane typów *wbudowanych* (np. `int`, `long double`)
albo *zdefiniowanych przez użytkownika* (np., `struct A`, `class B`,
`enum C`, `union D`).  Standard C++ opisuje:

* kiedy dane są tworzone i niszczone,

* gdzie (w którym miejscu pamięci, w jakiej strukturze danych) dane
  się znajdują.

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

W poniższym przykładzie próbujemy pisać do pamięci tylko do odczytu --
proszę odkomentować niektóre linie.  Program się kompiluje, ale proces
jest unicestwiony przez system operacyjny sygnałem SIGSEGV (segment
violation).

{% highlight c++ %}
{% include_relative sigsegv.cc %}
{% endhighlight %}

Możemy sprawdzić miejsce zmiennych poniższą komendą.  Proszę zwrócić
uwagę na literę 'r' na wyjściu, która symbolizuje pamięć tylko do
odczytu:

```
nm ./sigsegv | c++filt | grep test
```

Wszystkie inne dane programu (poza tymi w pamięci tylko do odczytu) są
w pamięci do odczytu i zapisu, bo na tych danych program wykonuje
obliczenia.  Każd proces tego samego programu ma osobną pamięć do
odczytu i zapisu.

## Co zależy od C++

C++ jest wydajny czasowo i pamięciowo, co wynika głównie z organizacji
pamięci i użycia wskaźników, czyli niskopoziomowego mechanizmu.  Co
więcej, C++ zapewnia swobodne zarządzanie danymi: np., programista
może alokować dane globalnie, statycznie, lokalnie lub dynamicznie.
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
ponieważ jest dostępna bogata funkcjonalność kontenerów i
inteligentnych wskaźników, które mogą być uznane za rodzaj odśmiecania
pamięci.

# Dane i ich miejsce w pamięci

Pamięć do zapisu i odczytu przechowuje:

* globalne i statyczne dane w miejscu pamięci o ustalonym rozmiarze,

* dane lokalne odłożone na stosie (a dokładnie na stosie dla każdego w
  wątków osobno),

* dane dynamiczne na stercie.

## Dane globalne i statyczne

Dane globalne są zainicjalizowane przed wywołaniem funkcji `main` i są
dostępne wszędzie w programie:

{% highlight c++ %}
{% include_relative global.cc %}
{% endhighlight %}

Dane statyczne są zainicjalizowane przed ich pierwszym użyciem i są
lokalne (czyli niedostępne poza funkcją):

{% highlight c++ %}
{% include_relative static.cc %}
{% endhighlight %}

W przykładzie wyżej, proszę usunąć `static` i zauważyć zmianę w
zachowaniu programu.

Zmienne globalne i statyczne wydają się podobne, ponieważ utrzymują
dane między wywołaniami funkcji.  Jednak są dwa powody, aby użyć
zmiennej statycznej zamiast globalnej:

* statyczna zmienna jest inicjalizowane tylko wtedy, kiedy trzeba
  (kiedy wywołujemy funkcję), a zmienna globalna jest zawsze
  inicjalizowana, co może pogorszyć wydajność, jeżeli zmienna nie jest
  używana,

* utrzymanie kodu w porządku i zapobieganie błędom.

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
pamięci.  Nazywamy to *kolokacją danych*.  Kolokacja jest korzystna,
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
przez referencję.  Proszę skompilować przykład z flagami
`-fno-elide-constructors -std=c++14` (flagi kompilatora GCC), żeby
kompilator nie unikał konstruktorów.  Jeżeli kompilujemy z użyciem
C++17 lub nowszego (np. użyliśmy flagi `-std=c++17`), to kompilator
zignoruje flagę `-fno-elide-constructors` w przypadkach, kiedy
pomijanie konstruktorów jest wymagane począwszy od C++17.

{% highlight c++ %}
{% include_relative args.cc %}
{% endhighlight %}

## Zwracanie wyniku

Jeżeli typ zwracanego wyniku jest niereferencyjny, to mówimy, że
funkcja zwraca wynik przez wartość.  W nowoczesnym C++ zwracanie przez
wartość jest bardzo szybkie, nie wprowadza żadnego niepożądanego
narzutu i dlatego jest zalecane.  To nie to, co kiedyś w dalekiej
przeszłości, kiedy C++ nie był jeszcze ustandaryzowany.

Niegdyś zwracanie przez wartość zawsze kopiowało wynik dwa razy.  Raz
ze zmiennej lokalnej funkcji do tymczasowego miejsca na stosie dla
zwracanego wyniku.  Drugi raz z tymczasowego miejsca do miejsca
docelowego, np. zmiennej, której wynik przypisywano.

Jeżeli typ zwracanego wyniku jest referencyjny, to mówimy, że funkcja
zwraca wynik przez referencję.  Referencja powinna odnosić się do
danych, które będą istnieć po wyjściu z funkcji (czyli dane powinny
przeżyć funkcję).  Na przykład, kontenery (np. `std::vector`) zwracają
referencję do dynamicznie zaalokowanych danych z użyciem operatora
indeksowania (czyli `operator[]`) albo funkcji `front`.

Poniższy przykład pokazuje jak zwrócić wynik przez wartość i przez
referencję.  Na nowoczesnym systemie i z nowoczesnym kompilatorem,
wynik zwracany przez wartość nie jest kopiowany.  Żeby zobaczyć stare
zachowanie C++, proszę skompilować przykład z flagami
`-fno-elide-constructors -std=c++14`.  Gdzie i dlaczego obiekty są
kopiowane?  To zależy od konwencji wywołania funkcji, optymalizacji
wartości powrotu czy unikania konstruktorów.

{% highlight c++ %}
{% include_relative return.cc %}
{% endhighlight %}

# Konwencja wywołania funkcji

*Konwencja wywołania funkcji* to szczegóły techniczne dotyczące
wywołania funkcji, które zależą od architektury systemu, systemu
operacyjnego i kompilatora.  C++ nie definiuje konwencji wywołania
funkcji, ale pewne funkcjonalności (jak unikanie konstruktorów czy
optymalizacja wartości powrotu) wynikają z typowej konwencji wywołania
funkcji.

Typowa konwencja wywołania funkcji wymaga od kodu wywołującego:

* utworzenia parametrów na stosie,

* alokacji pamięci dla zwracanej wartości.

Małe dane mogą być przekazywane i zwracane w rejestrach procesora.  Na
przykład, funkcja może przyjąć jako argument albo zwrócić jako wynik
liczbę całkowitą w rejestrze, np. EAX dla x86, Linuxa i GCC.

W starej konwencji funkcja zwracała wynik w tyczasowym miejscu na
szczycie stosu, które można było łatwo zlokalizować z użyciem rejestru
stosu -- to była zaleta.  Wadą jednak była konieczność kopiowania
wyniku z miejsca tymczasowego do miejsca docelowego, np. zmiennej,
której wynik przypisywano.

Nowoczesna konwencja wywołania funkcji pozwala na alokację miejsca dla
zwracanej wartości gdziekolwiek w pamięci (nie tylko na stosie, ale
także na stercie czy pamięci dla danych globalnych i statycznych) i
przekazanie adresu tego miejsca w rejestrze procesora (np. RDI dla
x86, Linuxa i GCC), żeby funkcja zwróciła wynik pod wskazanym adresem.
Nie potrzebujemy tymczasowego miejsca, a jedynie dodatkowy rejestr.

Przykład niżej pokazuje, że wynik może być zwracany gdziekolwiek (na
co pozwala nowoczesna konwencja wywołania), a nie tylko na stosie (jak
narzucała to stara konwencja).  W przykładzie funkcja zwraca obiekt
bezpośrednio w miejscu pamięci dla danych globalnych i statycznych,
bez kopiowania obiektu z udziałem tymczasowego miejsca wymaganego
przez starą konwencję.

{% highlight c++ %}
{% include_relative mcc.cc %}
{% endhighlight %}

# Pomijanie konstruktorów

C++ pomija wywołanie konstruktora kopiującego i przenoszącego dla
obiektów (np. tymczasowych albo lokalnych), które wkrótce zostaną
zniszczone.  Pominięcie wywołania konstruktora (ale tylko kopiującego
i przenoszącego) jest możliwe, ponieważ obiekt tymczasowy albo lokalny
jest tworzony w miejscu docelowym.

Przykład niżej demonstruje pomijanie konstruktorów.  Przykład proszę
skompilować z flagami `-fno-elide-constructors -std=c++14`, a potem
bez nich i zwrócić uwagę na różnice.

{% highlight c++ %}
{% include_relative elide.cc %}
{% endhighlight %}

Proszę skompilować różne poprzednie przykłady przekazywania argumentów
i zwracania wartości z włączonym i wyłączonym pomijaniem
konstruktorów.  Proszę zwrócić uwagę, że pomijanie konstruktorów
eliminuje zbędne kopiowanie obiektów.

Kiedy obiekt tymczasowy jest przekazywany przez wartość do funkcji, to
pominięcie konstruktora powoduje stworzenie tego obiektu bezpośrednio
w miejscu na stosie dla tego parametru.

# Zwracanie wyniku przez wartość

Funkcja może zwrócić wynik przez wartość bezpośrednio w miejscu
docelowym, np. w zmiennej, której wynik przypisujemy.  Chodzi o to,
żeby wyniku nie kopiować ani nie przenosić, czyli żeby pominąć zbędne
wywołanie konstruktora.  **Pominięcie konstruktora dla zwracanej
wartości wymaga zastosowania nowoczesnej konwencji wywołania
funkcji.**

Ta funkcjonalność jest cechą języka od C++17, ale wcześniej była
nazywana optymalizacją wartości powrotu (ang. return value
optimization, RVO), bo była opcjonalną cechą optymalizatora
kompilatora.  Od C++17 nie wymaga się, żeby konstruktory były
dostępne, jeżeli są pomijane, więc poniższy kod jest poprawny w myśl
C++17 (opcja `-std=c++17` GCC), ale nie C++14 (opcja `-std=c++14`
GCC):

{% highlight c++ %}
{% include_relative rvo_or_not.cc %}
{% endhighlight %}

Pomijanie konstruktorów dla zwracanej wartości nie zawsze może być
zastosowane z powodów technicznych.  Przede wszystkim dlatego, że
pewne obiekty muszą być pierwsze stworzone, a dopiero potem jest
podejmowana decyzja, który obiekt zwrócić:

{% highlight c++ %}
{% include_relative rvo_no1.cc %}
{% endhighlight %}

Także dlatego, że próbujemy zwrócić przez wartość parametr funkcji,
który już został stworzony przez kod wywołujący, nie funkcję.  Funkcja
może jedynie skopiować wartość parametru do miejsca, gdzie ma być
zwrócony wynik:

{% highlight c++ %}
{% include_relative rvo_no2.cc %}
{% endhighlight %}

I także dlatego, że próbujemy zwrócić przez wartość dane globalne albo
statyczne, które muszą istnieć po powrocie z funkcji.  Funkcja może
wtedy jedynie skopiować wynik:

{% highlight c++ %}
{% include_relative rvo_no3.cc %}
{% endhighlight %}

# Podsumowanie

* Dane mogą być alokowane statycznie, globalnie, lokalnie i
  dynamicznie.

* Alokacja pamięci na stosie jest super szybka, a na stercie znacznie
  wolniejsza.

* Nie używaj danych dynamicznych, jeżeli wystarczą dane lokalne.

* Obecnie przekazywanie parametru i zwracanie wyniku przez wartość
  są wydajne, bo wartość nie jest już niepotrzebnie kopiowana czy
  przenoszona.

# Quiz

* Czy alokacja pamięci na stosie jest szybsza niż na stercie?

* W jakich miejscach pamięci możemy tworzyć obiekty?

* Na czym polega pomijanie konstruktorów przy zwracaniu wyniku przez
  wartość?

<!-- LocalWords: enum  sigsegv endhighlight heisenbugs -->
<!-- LocalWords: deallocates defragmentation manyfold args -->
<!-- LocalWords: EAX RDI RVO SIGSEGV -->
