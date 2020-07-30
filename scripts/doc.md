Processing2C - skrypty i biblioteka do portowania aplikacji w Processingu na C++
=================================================================================

Skrypty służą przekształceniu projektu w _Processingu_ w projekt w C++ w systemach _linux_
Platforma docelowa musi zawierać kompilator C++ (najlepiej __gcc__) oraz programy __cmake__ i __make__.

Translacja została zaimplementowana za pomocą programu __sed__ więc kontekst składniowy ograniczony jest zawsze do jednej linii, co wymusza pewne zmiany z kodzie PDE, których trzeba dokonać przed translacją, i konieczność uzupełnień w wynikowym kodzie C++.

Największą różnicą semantyczną między kodami jest widoczność identyfikatorów. W _Processingu_ kolejność wprowadania identyfikatorów globalnych nie ma znaczenia - wszystkie widoczne są wszędzie. W C++ identyfikator widoczny jest od miejsca deklaracji w dół. Deklaracje klas są odnajdywane i tworzone są z nich deklaracje zapowiadające, co nieco ogranicza ten problem, ale go nie eliminuje. Zmienne globalne, które przy kontekście jednoliniowym są nie do odróżnienia od globalnych muszą być specjalnie markowane. Wybrano komentarz zaczynający się od trzech slashy używany też przez programy do automatycznej dokumentacji kodu. Podobna sytuacja dotyczy globalnych funkcji, jeśli są używane przed zdefiniowanie. Trzeba wtedy, analogicznie jak dla zmiennych globalnych, wymusić wygenerowania deklaracji zapowiadającej.

Drugi poważny problem stanowią domyślne ustawienia klas - w Processingu cała zawartość klasy jest domyślnie publiczna, w C++ prywatna. Z kolei metody w Processingu są domyślnie wirtualne, w C++ nie - ten prolem nie jest na razie rozwiązany.

Ponadto użycie słowa kluczowego super reprezentującego w Processingu klasę bazową nie może być przetłumaczone automatycznie gdyż wymagałoby to wieloliniowego kontekstu i zapamiętania nazwy klasy bazowej. 

 
Jakie zmiany należy wykonać:
----------------------------

1) Nawiasy '{' otwierające definicje klas przenieść do lini deklaracji klasy. Całość (łącznie z klasą bazową i ewentualnymi interfejsami) od słowa kluczowego class do '{' musi zawierać się w jednej linii.

2) Po nawiasie zamykającym klasę dopisujemy ';' - Processingowi to nie przeszkadza, a w C++ jest wymagane.

3) Zmienne globalne, które mają  być widoczne we wszystkich plikach projektu należy skomentować używająć potrójnego slasha zamiast podwójnego (czyli '///' a nie '//'). Analogicznie należy postąpic w przypadku globalnych funkcji. Znak '{' musi się znajdować w linii deklaracji, a '///' za tym znakiem.

4) Pliki definiujące bardziej podstawowe klasy powinny mieć nazwy alfabetycznie wcześniejsze niż pliki z tych klas korzystające, ponieważ skrypty używają kolejności alfabetycznej umieszczajac pliki w projekcie. Można także po translacji zmienić kolejność plików załączanych (#include) do pliku __project_at_once.cpp__

