There is given a structure `student` with fields `m_year` of type
`int` and `m_name` of type `string`.

Proszę napisać wyrażenie lambda, które będzie porównywało dwa obiekty
struktury student: `a` i `b`.  Wyrażenie lambda przechwytuje wartość
logiczną, od której zależy wynik porównania: jeżeli przechwyconą
wartością jest:

* `false`, to porównywane są pola `m_year`: `a.m_year < b.m_year`,

* `true`, to porównywane są pola `m_name`: `a.m_name < b.m_name`.

Następnie proszę zaimplementować tą samą funkcjonalność z użyciem
struktury funkcyjnej i funktora.
