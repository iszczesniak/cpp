---
title: Kontenery
---

# Wprowadzenie

Lista, tablica asocjacyjna, zbiór i inne typy danych są nazywane
**kontenerami** w C++.  Kontener:

* jest *uogólnioną* strukturą danych,

* przechowuje elementy *dowolnego, ale tylko jednego typu*, 

* przechowuje elementy przez wartość, nie referencję,

* przechowuje elementy na stercie,

* może zmieniać rozmiar dynamiczne, czyli w czasie uruchomienia.

Kontener jest uogólniony, bo może przechowywać elementy dowolnego typu
`T`.  Typ kontenera (np. `std::vector<T>`) jest **szablonowy**, więc
możemy przekazać mu *argument szablonu* `T` w czasie kompilacji.

Podczas gdy kontener (obiekt typu kontenera) może być gdziekolwiek w
pamięci, to jego elementy są przechowywane na stercie, bo rozmiar
kontenera może się zmieniać w czasie uruchomienia.

Kontenery są uzupełniane przez iteratory i algorytmy.  Iterator jest
uogólnieniem wskaźnika.  Algorytmy, np. `std::sort`, są uogólnione,
czyli można ich użyć z różnymi konteneramim, ponieważ dostęp do ich
elementów jest zapewniony przez iteratory.

Standardowe kontenery, iteratory i algorytmy pasują do siebie,
ponieważ stosują te same konwencje nazw i semantyki.  Jeżeli chodzi o
konwencję nazw, to na przykład każdy kontener ma funkcje `begin`,
`end`, `size`.  Jeżeli chodzi o konwencję semantyki, to na przykład
otrzymujemy dane iteratora `i` przez wyłuskanie `*i`.

## Historia

Na początku lat dziewięćdziesiątych kontenery były:

* najnowszą technologią, tematem badań naukowych,

* zaimplementowane jako Standard Template Library (STL), przełomowa
  biblioteka Alexandra Stepanova.

Teraz kontenery są:

* nieodzownym narzędziem codziennego użycia,

* częścią biblioteki standardowej.

**Nie ma wymówki, trzeba używać.**

## Typy podstawowych kontenerów

Kontenery sekwencyjne:

* `std::vector<T>` - wektor,

* `std::list<T>` - lista dwukierunkowa,

* `std::deque<T>` - kontener z cechami wektora i listy,

* `std::forward_list<T>` - lista jednokierunkowa,

Kontenery asocjacyjne:

* `std::map<K, V>` - tablica asocjacyjna (aka słownik),

* `std::multimap<K, V>` - tablica asocjacyjna z możliwymi równymi
  kluczami,

* `std::set<T>` - zbiór,

* `std::multiset<T>` - zbiór z możliwymi równymi elementami.

Adaptery:

* `std::stack<T>` - stos,

* `std::queue<T>` - kolejka,

* `std::priority_queue<T>` - kolejka priorytetowa.

Typy kontenerów mogą być zagnieżdżone, czyli `T` też może być
kontenerem.

## Porównanie typów podstawowych kontenerów

### `std::vector<T>`

Wektor zapewnia:

* **swobodny dostęp** do elementów z użyciem operatora swobodnego
  dostępu, czyli operatora `[]` zwanego także operatorem indeksowania,

* **ciągłość pamięci**: wszystkie elementy są przechowywane w pamięci
    obok siebie, z czego wynika że:

  - operator swobodnego dostępu jest maksymalnie szybki, ponieważ
    jedynie zwiększa wskaźnik

  - dostęp do pamięci jest maksymalnie szybki: elementy są
    przechowywane obok siebie, co zwiększa efektywność pamięci
    podręcznej procesora,

  - **usuwanie i wstawianie elementów jest wolne**.

Wektor realokuje elementy, kiedy aktualnie zaalokowana pamięć jest
niewystarczająca, żeby wstawić nowy element na koniec wektora.  Na
początku nowy obszar pamięci jest alokowany.  Następnie elementy
wektora są kopiowane (albo przenoszone, jeżeli typ elementów ma
zaimplementowaną semantykę przeniesiena), a potem nowy element jest
dodawany (przez kopiowanie albo przeniesienie).  Na końcu jest
zwalniana stara pamięć.

Wydajność wektora spada nie tylko wtedy, kiedy elementy są często
dodawane na koniec wektora, ale także wtedy, kiedy elementy są często
wstawiane albo usuwane.  Kiedy element jest wstawiany albo usuwany, to
elementy następujące muszą być kopiowane (albo przenoszone), ponieważ
wektor gwarantuje ciągłość pamięci.

W porównaniu z innymi kontenerami, wektor jest bardzo szybki, jeżeli
realokacja, dodawanie, wstawianie i usuwanie nie są często wykonywane,
np. kiedy tworzymy wektor o zadanym rozmiarze, wypełniamy go
wartościami, a następnie jedynie odwołujemy się do elementów.

### `std::list<T>`

Lista nie przechowuje elementów w ciągłej pamięci, ale w różnych
miejscach na stercie, które były osobno alokowane.  Lista jest
dwukierunkowa (ang. doubly-linked), więc:

* **wstawianie i usuwanie elementów jest szybkie**, ponieważ elementy
  nie muszą być realokowane, kopiowane czy przenoszone,

* **dostęp do elementów jest tylko iteracyjny**: żeby dostać się
  elementy, to musimy przejść przez elementy poprzedzające albo
  następujące.

Lista nie zapewnia swobodnego dostępu do elementów, chociaż mogłaby z
bardziej rozbudowaną implementacją.  Jednak celem C++ jest zapewnienie
wydajnej funkcjonalności, a taka rozbudowana lista miałaby gorszą
wydajność.  Lista typu `std::list` ma ograniczoną funkcjonalność, ale
maksymalną wydajność.

### `std::deque<T>`

Ten kontener jest kompromisem między funkcjonalnością a wydajnością
wektora i listy.  Kontener jest przydatny, jeżeli potrzebujemy
swobodnego dostępu i jednocześnie często wstawiamy czy usuwamy
elementy na początku czy końcu kontenera.  Kontener zapewnia:

* **swobodny dostęp o stałym czasie** - jak wektor,

* **wstawianie i usuwanie o stałym czasie, ale tylko w przypadku
    początku i końca kontenera** - jak lista.

Jak to możliwe?  Trzeba wspomnieć, że:

* swobodny dostęp, mimo że jest o stałym czasie (czyli nie zależy od
  wielkości kontenera), nie jest tak szybki, jak dla wektora,

* wstawianie i usuwanie poza początkiem i końcem jest czasu
  liniowego, a dla listy jest stałego czasu.

Kontener jest zaimplementowany bez gwarancji ciągłości w pamięci, jako
lista tablic (języka C) o stałej długości.  Swobodny dostęp jest mniej
wydajny w porównaniu z wektorem, ponieważ znalezienie adresu elementu
wymaga nieco więcej obliczeń niż w przypadku wektora.  Wstawianie czy
usuwanie poza początkiem i końcem jest czasu liniowego, ponieważ
wymaga przesunięcia wszystkich elementów "na prawo" od miejsca
wstawiania czy usuwania.

Używamy `std::deque` tylko wtedy, kiedy wektor czy lista to za mało.

### `std::forward_list<T>`

Czasami `std::list` oferuje więcej, niż potrzebujemy.  Czasamy
potrzebujemy iterować po elementach tylko do przodu i nie potrzebujemy
funkcjonalności iterowania do tyłu, którą zapewnia `std::list` i za
którą płacimy spadkiem wydajności.

Typ `std::forward_list` jest mniej funkcjonalny, ale za to bardziej
wydajny, niż `std::list`, ponieważ jest to lista jednokierunkowa:
możemy iterować do przodu, ale nie do tyłu.

### `std::set<T>`, and `std::multiset<T>`

Zbiór (kontener `std::set`) przechowuje unikalne elementy, a
wielozbiór (kontener `std::multiset`) pozwala na przechowywanie
elementów, które mają równe wartości.  Oba kontenery przechowują
elementy w sposób **posortowany**.  Domyślnie porządek jest rosnący,
ale możemy ustalić dowolny porządek z użyciem callable.

Co ciekawe, nie można zmieniać wartości elementów w kontenerach
posortowanych, ponieważ to zaburzyłoby porządek w kontenerze i
uczyniło go niespójnym.  Z tego powodu elementy mają typ stały, nawet
jeżeli argumentem szablonu jest typ niestały.

Jeżeli chcemy zmienić wartość elementu, to pierwsze musimy usunąć
element, a następnie wstawić nowy element o nowej wartości.

```cpp
{% include_relative set.cc %}
```

# Iteratory

Iteratory są spoiwem, które łączy kontenery i algorytmy.  Na przykład,
funkcja `std::sort` może być zastosowana dla różnych kontenerów
właśnie dzięki iteratorom.  Iteratory zapewniają dostęp do elementów
kontenera, żeby typ kontenera nie był dla nas istotny.

Iterator jest uogólnieniem wskaźnika.  Możemy powiedzieć, że wskaźnik
jest iteratorem tablicy języka C.  Wskaźnik możemy zainicjalizować,
porównać z innym wskaźnikiem, wyłuskać (żeby dostać się do elementu) i
także inkrementować.  Co więcej, możemy mieć swobodny dostęp do
dowolnego elementu tablicy języka C przez zwiększenie (operatorem `+`)
wskaźnika na element numer 0 o indeks elementu:

```cpp
{% include_relative pointer.cc %}
```

Typy iteratorów mogą być definiowane przez programistę, czyli
programista może zaimplementować swój typ kontenera i typ jego
iteratora.  Iteratory są obudowanymi wskaźnikami, których operatory
implementują wymaganą funkcjonalność.  Na przykład, jeżeli w
przykładzie wyżej zamienimy tablicę języka C z `std::deque`, to reszta
kodu pozostaje bez zmian:

```cpp
{% include_relative iterator_intro.cc %}
```

Iteratory biblioteki standardowej są małe i wydajne.  Najczęściej
przechowują jeden wskaźnik, więc możemy je kopiować i używać przez
wartość.  Możemy także używać iteratorów przez referencję, ale to
byłoby dosyć dziwne, jak podobnie dziwne byłoby używanie wskaźników
przez referencję.

Standardowy kontener typu `T` ma zawsze zdefiniowane dwa typy
iteratorów:

* niestały iterator typu `T::iterator`,

* stały iterator typu `T::const_iterator`.

Nie możemy zmieniać elementów kontenera, jeżeli odnosimy się do nich z
użyciem iteratora stałego.  Dla lepszego kodu, jeżeli nie zmieniamy
elementów, powinniśmy zawsze używać iteratorów stałych.

## Funkcje `begin`, `end`

Wiemy, gdzie są elementy kontenera dzięki funkcjom `begin` i `end`.
Funkcja `begin` zwraca iterator na pierwszy element.  Funkcja `end`
zwraca **iterator końcowy** (ang. past-the-end iterator), który
otrzymamy, jeżeli zinkrementujemy iterator na ostatni element; możemy
powiedzieć, że funkcja `end` zwraca iterator na **urojony** element
(urojony, bo on nie istnieje), który następowałby po ostatnim
elemencie.  Jeżeli kontener nie ma elementów, to iteratory zwrócone
przez `begin` i `end` są sobie równe.

Funkcje `begin` i `end` zwracają iteratory niestałe dla kontenerów
niestałych i iteratory stałe dla kontenerów stałych.  Jeżeli otrzymać
iteratory stałe dla kontenerów niestałych, to możemy użyć funkcji
`cbegin` i `cend`.

Funkcje `cbegin` i `cend` są tylko dla naszej wygody, poradzilibyśmy
sobie bez nich.  Dla kontenerów niestałych możemy osiągnąć tą samą
funkcjonalność przez wywołanie `begin` i `end`, jeżeli odwołamy się do
tych kontenerów z użyciem funkcji `std::as_const`, która zwraca nam
referencję stałą do przekazanego argumentu.

Iteratory mogą być podzielone na kilka kategorii (spełniających
koncepty) w zależności od oferowanej funkcjonalności:

* iterator jednokierunkowy,

* iterator dwukierunkowy,

* iterator swobodnego dostępu.

## Iterator jednokierunkowy

Iterator jednokierunkowy oferuje tylko najbardziej podstawowe
operacje: `*i` i `++i`.  Przykładem operatora jednokierunkowego jest
iterator listy jednokierunkowej.  Oto przykład:

```cpp
{% include_relative iterator_forward.cc %}
```

## Iterator dwukierunkowy

Iterator dwukierunkowy to iterator jednokierunkowy z dodatkowym
definiowanym operatorem: `--i`, czyli może cofnąć się o jeden element.
Lista ma iterator dwukierunkowy.  Na przykład:

```cpp
{% include_relative iterator_bidirectional.cc %}
```

## Iterator swobodnego dostępu

Iterator swobodnego dostępu pozwala na poruszanie się po kontenerze w
obu kierunkach o dowolną liczbę elementów, jak robiliśmy to w
przykładzie wyżej z `std::deque`.  Wektor ma iterator swobodnego
dostępu.  Wskaźnik też jest iteratorem swobodnego dostępu.

# Pętla `for`

Możemy iterować po elementach kontenera (albo ogólniej po zakresie, w
tym po tablicy języka C) z użyciem pętli `for` na dwa sposoby: stary i
nowy.

## Stary sposób

Jak pokazano w przykładzie niżej, możemy iterować po elementach
kontenera w stary sposób, ale jest to trochę uciążliwe, ponieważ
pierwsze musimy zainicjalizować *zmienną iteracyjną* `i`, napisać
warunek pętli, a potem zwiększyć zmienną.  Łatwo się pomylić i napisać
`--i` zamiast `++i` albo `begin` zamiast `end`.

```cpp
{% include_relative iterate_old.cc %}
```

Podobnie dla tablicy języka C:

```cpp
{% include_relative iterate_old_ca.cc %}
```

## Nowy sposób

Od C++11 możemy iterować w nowy sposób, używając nowej składni pętli
`for` dla zakresów, zwanej także pętlą foreach.  Semantyka jest taka
sama jak dla starego sposobu.  Pisać musimy mniej, więc ryzyko
popełnienia błędu jest mniejsze.

Taka jest składnia:

```cpp
for(declaration: expression) statement
```

Gdzie:

* `declaration` deklaruje zmienną, która jest inicjalizowana
  elementami kontenera (a dokładniej elementami zakresu) w każdej
  iteracji pętli.  Tę zmienną nazywamy *zadeklarowaną zmienną*.

* `expression` jest *wyrażeniem zakresu*.  Najczęściej jest nim
  kontener.  Dla wyrażenia zakresu możemy wywołać funkcje `begin` i
  `end`.

* `statement` jest zdaniem wykonywanym w każdej iteracji pętli.  W tym
  zdaniu używamy zadeklarowanej zmiennej.

Przykład:

```cpp
{% include_relative iterate_new.cc %}
```

## Jak działa iterowanie po nowemu?

Pętla `for` dla zakresu jest tłumaczona przez kompilator do zwykłej
pętli `for`, której zmienna iteracyjna jest typu iteratora.  Zmienna
iteracyjna jest inicjalizowana wartością zwracaną przez funkcję
`begin`.  Pętla iteruje do momentu, w którym wartość iteratora jest
równa wartości zwracanej przez funkcję `end`.  W każdej iteracji
pętli, **zmienna deklarowana** jest inicjalizowana przez **wyrażenie
wyłuskania zmiennej iteracyjnej**.  Po iteracji, iterator jest
inkrementowany.

Żeby użyć nowej składni pętli `for`, to powinniśmy się upewnić, że:

* możemy wywołać funkcję `begin` i `end` dla wyrażenia zakresu,

* typ wartości zwracanych przez funkcje `begin` i `end` powinny mieć
  zdefiniowane następujące operatory:
  
  - porównania `!=`,

  - wyłuskania `*`,

  - inkrementacji prefiksowej `++`.

Oto przykład implementacji własnego typu zakresu:

```cpp
{% include_relative range.cc %}
```

# Zarządzanie elementami kontenera

Element możemy wstawić (przez skopiowanie albo przenoszenie) do
kontenera, albo możemy go usunąć z kontenera.  Możemy także przenieść
element z kontenera za wyjątkiem kontenerów asocjacyjnych, w przypadku
których element możemy **wyciągnąć** (ang. extract).  Element możemy
także **umieścić** (ang. emplace) w kontenerze.

Kontenery mają zaimplementowaną semantykę przeniesienia.  Oto
przykład:

```cpp
{% include_relative container_move.cc %}
```

## Semantyka przeniesiena dla typów elementów

Elementy mogą być przenoszone do kontenerów: wystarczy, że wstawiany
element będzie użyty w r-wartości.  Możemy także przenieść element z
kontenera sekwencyjnego.  Przykład:

```cpp
{% include_relative element_move.cc %}
```

## Wyciąganie elementów

Nie możemy przenieść wartości obiektu z *kontenera asocjacyjnego*,
ponieważ nie możemy modyfikować tego elementu, nawet jeżeli używamy
iteratora niestałego, bo typ elementu w kontenerze jest stały.  Nawet
nie powinniśmy przenosić, bo obiekt w kontenerze po przeniesieniu jego
wartości pozostałby w kontenerze, ale w stanie niezdefiniowanym, co
doprowadziłoby do niespójności kontenera.  Zamiast przenosić wartość
obiektu, to powinniśmy obiekt **wyciągnąć**.  Wyciąganie jest
zaimplementowane tylko dla kontenerów asocjacyjnych, bo tylko tam jest
potrzebne.

Wyciąganie jest zaimplementowane przez odlinkowanie (operacje na
wskaźnikach) elementu z kontenera.  Jako wynik wyciągnięcia
otrzymujemy *uchywt węzła* (objekt typu tylko do przenoszenia), który
posiada wyciągnięty element: kiedy uchwyt węzła jest niszczony, to
element też jest niszczony, jeżeli ciągle był w posiadaniu uchwytu.
Uchwyt węzła może być zaimplementowany z użyciem inteligentnego
wskaźnika o semantyce wyłącznej własności, czyli `std::unique_ptr`.

Mając uchwyt węzła, możemy wstawić element do innego kontenera tego
samego typu, co typ kontenera, z którego element wyciągnęliśmy.
Podczas wyciągania i wstawiania, element pozostaje nietknięty (ciągle
w tym samym miejscu i z tą samą wartością), tylko jego właściciel się
zmienia z kontenera źródłowego na kontener docelowy, przechodząc przez
uchwyt.

Mając uchwyt węzła, możemy uzyskać dostęp do posiadanego obiektu przez
użycie funkcji `value`, a potem przenieść jego wartość do, np.,
kontenera innego typu.  Kiedy uchwyt będzie niszczony, to zniszczy on
obiekt, którego wartość przenieśliśmy.  Oto przykład:

```cpp
{% include_relative extract.cc %}
```

## Umieszczanie

Element może być wstawiony (przez kopiowanie albo przenoszenie) do
kontenera albo w nim *umieszczony*.  Kopiowanie jest potrzebne, kiedy
chcemy, żeby element źródłowy pozostał nietknięty.  Przenoszenie jest
szybsze i w ten sposób lepsze od kopiowania, jeżeli element źródłowy
nie będzie później potrzebny.  We wstawianiu przekazujemy obiekt,
który sami stworzyliśmy.  **Umieszczanie samo tworzy obiekt** z
użyciem argumentów, które przekazujemy.

Umieszczanie jest najszybsze, bo kontener próbuje stworzyć element we
wymaganym miejscu: element jest **tworzyony w miejscu**
(ang. in-place), czyli w miejscu pamięci wymaganym przez kontener.
Bez kopiowania czy przenoszenia, jeżeli wszystko pójdzie dobrze.

Funkcja umieszczająca przyjmuje argumenty dla konstruktora elementu i
przekazuje mu je wtedy, kiedy wiadomo, gdzie (czyli w którym miejscu
pamięci) element powinien być stworzony.

Umieszczamy wywołując funkcję `emplace` kontenera.  Kontenery mają
także inne funkcje dla umieszczania z drobnymi różnicami
semantycznymi, np. `std::list` ma funkcję `emplace_front`, a
`std::forward_list` ma `emplace_after`.

W niektórych kontenerach sekwencyjnych, podczas umieszczania, tak jak
podczas wstawiania, elementy następujące są "przesuwane w prawo".
Dlatego umieszczanie pociąga za sobą te same problemy z wydajnością
jak wstawianie.

Kontener *stara się* umieścić element, ale może zawieść, jeżeli
docelowe miejsce już jest zajęte przez inny element, na przykład kiedy
umieszczamy element na początku niepustego wektora.  W takim przypadku
nowy element jest tworzony w jakimś innymi miejscu (na przykład w
zmiennej lokalnej), a następnie jego wartość jest przenoszona do
miejsca docelowego.

```cpp
{% include_relative emplace.cc %}
```

# Podsumowanie

* Nie należy implementować podstawowych struktur danych, bo to już
  zostało zrobione.

* Należy używać kontenerów i robić to coraz lepiej.  Ich
  funkcjonalność jest całkiem bogata.

* Używając kontenerów można budować złożone struktury danych.

* Razem z kontenerami warto używać standardowych algorytmów, bo własne
  implementacje najprawdopodobniej będą znacznie gorsze.

# Quiz

* Jakie są najważniejsze różnice między kontenerami?

* Dlaczego nie można zmieniać wartości elementu zbioru?

* Jak działa umieszczanie?

<!-- LocalWords: cbegin -->
<!-- LocalWords: cend -->
<!-- LocalWords: const -->
<!-- LocalWords: deque -->
<!-- LocalWords: dereference -->
<!-- LocalWords: dereferenced -->
<!-- LocalWords: dereferencing -->
<!-- LocalWords: emplace -->
<!-- LocalWords: emplaced -->
<!-- LocalWords: emplacing -->
<!-- LocalWords: rvalue -->
<!-- LocalWords: multiset -->
<!-- LocalWords: performant -->
<!-- LocalWords: Stepanov -->
<!-- LocalWords: STL -->
<!-- LocalWords: templated -->
<!-- LocalWords: unlinking -->
