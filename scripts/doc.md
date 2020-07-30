Processing2C - skrypty i biblioteka do portowania aplikacji w Processingu na C++
=================================================================================

Skrypty służą przekształceniu projektu w _Processingu_ w projekt w C++ w systemach _linux_
Platforma docelowa musi zawierać kompilator C++ (najlepiej __gcc__) oraz programy __cmake__ i __make__.

Translacja została zaimplementowana za pomocą programu __sed__ więc kontekst składniowy ograniczony jest zawsze do jednej linii, co wymusza pewne zmiany z kodzie PDE, których trzeba dokonać przed translacją, i konieczność uzupełnień w wynikowym kodzie C++.

**Widoczność identyfikatorów - największą różnica semantyczna między PDE a C++:**

W _Processingu_ kolejność wprowadzania identyfikatorów globalnych nie ma znaczenia - wszystkie widoczne są wszędzie. W C++ identyfikator widoczny jest od miejsca deklaracji w dół. Skrypty odnajdują deklaracje klas i tworzą z nich deklaracje zapowiadające, co nieco ogranicza ten problem, ale go nie eliminuje. Zmienne globalne, które przy kontekście jednoliniowym są nie do odróżnienia od globalnych muszą być specjalnie markowane. Wybrano komentarz zaczynający się od trzech slashy używany też przez programy do automatycznej dokumentacji kodu. Podobna sytuacja dotyczy globalnych funkcji, jeśli są używane przed zdefiniowanie. Trzeba wtedy, analogicznie jak dla zmiennych globalnych, wymusić wygenerowania deklaracji zapowiadającej. 

Ponadto w _Processingu_ zmienne i funkcje mają rozdzielne przestrzenie nazw. Oznacza to że zmienna globalna może mieć taką samą nazwę jak lokalna metoda i obie będą odróżniane. Takie mieszanie nazw nie jest dopuszczalne w C++ ponieważ identyfikatory funkcji i metod mogą występować także bez nawiasów '()' w kontekście wskaźnikowym. Stąd lokalna metoda o tej samej nazwie co zmienna globalna zakryje tą zmienną.

**Klasy:**

Poważny problem stanowią domyślne ustawienia klas - w _Processingu_ cała zawartość klasy jest domyślnie publiczna, w C++ prywatna. Z kolei metody w Processingu są domyślnie wirtualne, w C++ nie (i ten prolem nie jest na razie rozwiązany w żaden sposób)

Ponadto użycie słowa kluczowego __super__ reprezentującego w _Processingu_ klasę bazową nie może być przetłumaczone automatycznie gdyż wymagałoby to wieloliniowego kontekstu z zapamiętaniem nazwy klasy bazowej.
(por. https://stackoverflow.com/questions/357307/how-to-call-a-parent-class-function-from-derived-class-function/357380#357380) 

 
Jakie zmiany należy wykonać?
----------------------------

Przed translacją na C++ nalezy dokonać nieco zmian w kodzie _Processingu_ i sprawdzić czy przez przypadek nie zmienił się sposób działania programu. 

1) Nawiasy '{' otwierające definicje klas przenieść do lini deklaracji klasy. Całość (łącznie z klasą bazową i ewentualnymi interfejsami) od słowa kluczowego class do '{' musi zawierać się w jednej linii.

2) Po nawiasie zamykającym klasę dopisujemy ';' - Processingowi to nie przeszkadza, a w C++ jest wymagane.

3) Zmienne globalne, które mają  być widoczne we wszystkich plikach projektu należy skomentować używająć potrójnego slasha zamiast podwójnego (czyli '///' a nie '//'). Analogicznie należy postąpic w przypadku globalnych funkcji. Znak '{' musi się znajdować w linii deklaracji, a '///' za tym znakiem.

6) Zmienne globalne oraz pola obiektów o tych samych nazwach co funcje lub metody stosowane w tych samych kontekstach przemianowujemy

5) Pliki definiujące bardziej podstawowe klasy powinny mieć nazwy alfabetycznie wcześniejsze niż pliki z tych klas korzystające, ponieważ skrypty używają kolejności alfabetycznej umieszczajac pliki w projekcie. Można także po translacji zmienić kolejność plików załączanych (#include) do pliku __project_at_once.cpp__

