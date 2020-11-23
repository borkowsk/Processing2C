Processing2C - skrypty i biblioteka do portowania aplikacji w Processingu na C++
=================================================================================

Skrypty służą przekształceniu projektu w _Processingu_ w projekt w C++ w systemach __linux__
Platforma docelowa musi zawierać kompilator C++ (najlepiej __gcc__) oraz programy __cmake__ i __make__.
Oczywiście potrzebna jest też załączona biblioteka inplementująca interface Processingu oraz biblioteka
pakiet SymShellLight zapewniający grafikę w __X11__, __MS Windows__, oraz grafikę __SVG__ do uruchamiania aplikacji
na serwerach do których nie ma dostępu za pomoca _GUI_ a jedynie przez terminal tekstowy.

Translacja została zaimplementowana za pomocą programu __sed__ więc kontekst składniowy ograniczony jest zawsze do jednej linii,
co wymusza pewne zmiany z kodzie PDE, których trzeba dokonać przed translacją. Czasem konieczne są też drobne uzupełnienia 
w wynikowym kodzie C++, które staramy się ograniczać przez zestaw dyrektyw w komentarzach takich jak:

    - /*_reference*/ transformowane na '&'
    - /*_pubext*/ transformowane na 'public virtual'
    - /*_interfunc*/ transformowane na 'virtual'
    - /*_forcebody*/ transformowane na '=0'
    - /*_downcast*/ transformowane na 'std::dynamic_pointer_cast\<\1\>'
    - /*_dncast*/ transformowane na 'std::dynamic_pointer_cast\<\1\>'
    - /*_upcast*/ transformowane na 'static_cast\<p\1\>'
    - /*_tmpfree*/ transformowane na '_free_ptr_to\<\1\>'
    - /*_tmpptr*/ transformowane na '*'


**Widoczność identyfikatorów - największą różnica semantyczna między PDE a C++:**

W _Processingu_ kolejność wprowadzania identyfikatorów globalnych nie ma znaczenia - wszystkie widoczne są wszędzie.
W C++ identyfikator widoczny jest od miejsca deklaracji w dół!

Pierwszym krokiem do rozwiązania tego problemu jest tworzenie _pliku project_at_once.cpp_, który za pomocą dyrektywy #include włącza wszystkie pliki wynikowe _\*.cpp_ *w kolejności alfabetycznej*.

Zmienne globalne, które przy kontekście jednoliniowym są nie do odróżnienia od lokalnych muszą być specjalnie markowane.
Wybrano komentarz zaczynający się od trzech slashy ('///') używany też przez programy do automatycznej dokumentacji kodu.
Podobna sytuacja dotyczy globalnych funkcji, jeśli są używane przed zdefiniowaniem. Trzeba wtedy, analogicznie jak dla zmiennych globalnych,
wymusić wygenerowania deklaracji zapowiadającej.

Skrypty odnajdują też deklaracje klas i tworzą z nich deklaracje zapowiadające, co nieco ogranicza ten problem, ale go nie eliminuje.
Niestety deklaracje zapowiadające klas działają w C++ tylko częściowo - nie da się utworzyć obiektu klasy ani użyć jakiejkolwiek
jego właściwości bez pełnego zdefiniowania. Tu pomóc może jedynie zmiana kolejności dyrektyw include w pliku wynikowym.

Ponadto w _Processingu_ zmienne i funkcje mają rozdzielne przestrzenie nazw. Oznacza to, że zmienna globalna może mieć taką samą
nazwę jak lokalna metoda i obie będą odróżniane. Takie mieszanie nazw nie jest dopuszczalne w C++ ponieważ identyfikatory funkcji
i metod mogą występować także bez nawiasów '()' w kontekście wskaźnikowym. Stąd lokalna metoda o tej samej nazwie co zmienna
globalna zakryje tą zmienną, i vice versa, prowadząc do dziwnych zjawisk. Takie sytuacje dla symboli z interfejsu _Processingu_
staramy się wykrywać i ostrzegać o nich.

**Klasy:**

Poważny problem stanowią domyślne ustawienia klas - w _Processingu_ cała zawartość klasy jest domyślnie publiczna, w C++
prywatna. Z kolei metody w Processingu są domyślnie wirtualne, w C++ nie. Pierwszy problem na razie został rozwiązany częściowo dla
deklaracji klas które mają otwierajacy znak '{' w tej samej linii. Kwestię funkcji wirtualnych rozwiązuje dyrektywa /\*_interfunc\*/.

Trzecim problemem jest sposób dziedziczenia klas w JAVA'ie. Klasa może mieć tylko jedną klasę bazową, oraz dowolną liczbę implementowanych
interfejsów. W C++ klas bazowych może być dowolnie dużo, ale nie ma interfejsów.
Rozwiązujemy to w ten sposób że interfejsy są zmieniane na klasy abstrakcyjne C++ bez pól i implementacji metod, do czego konieczne jest
użycie w definicji takiego interfejsu dyrektyw /\*_interfunc\*/ i /\*_forcebody\*/, a w definicji klasy implementującej interface uprzed
każdym DODATKOWYM interfejsem trzeba użyć dyrektywy /\*_pubext\*/.

Użycie słowa kluczowego __super__ reprezentującego w _Processingu_ klasę bazową nie może być przetłumaczone
automatycznie gdyż wymagałoby to wieloliniowego kontekstu z zapamiętaniem nazwy klasy bazowej.
(por. https://stackoverflow.com/questions/357307/how-to-call-a-parent-class-function-from-derived-class-function/357380#357380)
Radzimy sobie tylko w prostych sytuacjach gdy chodzi o wywołanie konstruktora, i to pod warunkiem zachowania nieco nienaturalnej
składni.

Ostatnia kwestia to ';' wymagany w C++ po deklaracji klasy. Na szczęście _Processing_ toleruje takie średniki, więc można je wstawić
w pliku PDE.

Te rozwiązania pozwoliły mi na uzycie Processing2C do moich modeli symulacyjnych, ale nie jest to wygodne. Planuje napisać osobny
programik który wstawiony w strumień translacyjny będzie radził sobie całościowo z deklaracjami klas.

**Konkatenacje stringów**

W _Processingu_ stałe napisowe są traktowane jak obiekty typu __String__, które z kolei podlegają konkatenacji niemal z każdym
innym podstawowym typem zmiennych. W C++ konwersja stałych łańcuchowych na typ __Processing::String__ musi zostać wymuszona jawnie przez dodanie
wywołania konstruktora w wyrażeniach.

Skrypty dodają takie wywołanie w wykrytych operacjach konkatenacji, ale niestety kompilator C++ często w tym miejscu sygnalizuje ostrzeżenie. Generalnie lepiej jest konkatenacje maksymalnie upraszczać przed translacją.

Mam pewne pomysły jak to usprawnić, ale wymagają dosyć dużo pracy i testów, a aktualne rozwiązanie jakoś działa.

 
Jakie zmiany należy wykonać w plikach PDE?
------------------------------------------

Przed translacją na C++ należy dokonać nieco zmian w kodzie _Processingu_ i sprawdzić czy przez przypadek nie zmienił się sposób
działania programu.

1) Nawiasy '{' otwierające definicje klas przenieść do lini deklaracji klasy. Całość (łącznie z klasą bazową i ewentualnymi
interfejsami) od słowa kluczowego class do '{' musi zawierać się w jednej linii.

2) Po nawiasie zamykającym klasę dopisujemy ';' - _Processingowi_ to nie przeszkadza, a w C++ jest wymagane.

3) Zmienne globalne, które mają  być widoczne we wszystkich plikach projektu należy skomentować używająć potrójnego slasha zamiast podwójnego (czyli '///' a nie '//'). Analogicznie należy postąpic w przypadku globalnych funkcji. Znak '{', jeśli ma wystąpić w lini, musi się znajdować za deklaracją, a '///' za tym znakiem.

4) Zmienne oraz pola obiektów o tych samych nazwach co funkcje lub metody stosowane w tych samych kontekstach przemianowujemy

5) Uzupełniamy interfejsy i klasy implementujace  o niezbędne dyrektywy

6) Pliki definiujące bardziej podstawowe klasy powinny mieć nazwy alfabetycznie wcześniejsze niż pliki z tych klas korzystające, ponieważ skrypty używają kolejności alfabetycznej umieszczajac pliki w projekcie. Można także po translacji zmienić kolejność plików załączanych (#include) do pliku _project_at_once.cpp_



```C
/********************************************************************/
/*               PROCESSING2C  version 2020-11-23                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
```
