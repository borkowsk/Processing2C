#!/bin/bash
if [ $# -ne 1 ]; 
then
   echo -e "${COLOR2}$# ${COLOR1}is invalid number of parameters!"$NORMCO 1>&2
   exit -1
fi

echo "//Processing to C++ converter $0"
echo "//Source: $1"
echo "#include \"processing_consts.hpp\""
echo "#include \"processing_templates.hpp\""
echo "#include \"processing_library.hpp\""
echo "#include \"processing_inlines.hpp\" //...is optional. Use when project is already compilable!"
echo "#include \"processing_window.hpp\""
#TODO - nagłówki opcjonalne powinny być dodawane na podstawie wyniku grep'a!
${SCRIPTS}/includeOptionals.sh $1
echo "#include \"project.h\" //...is for you. Could be deleted when not needed."
echo "using namespace Processing;"
echo "#include \"local.h\""
echo "//=================================================================================="
echo ""

echo -e $COLOR1 1>&2 #ERRORS!

cat $1 |\
${SCRIPTS}/tools "${SRCDIR}toolsouts/" |\
#Enumeracje są kopiowane do globalnego headera, a nie mogą występować w kodzie dwukrotnie
sed -E 's|enum([^\{]*)\{([^\}]*)\}|//enum\1 : \2|' |\
#także globalne "finale" muszą być skopiowane do głównego headera i wykomentowane w oryginalnym miejscu
sed -E 's|final\s+|const |g' |\
# Może: static constexpr ?
sed -E 's#^\s*(const\s+int|const\s+float|const\s+double|const\s+String|const\s+boolean|const\s+\w+)\s+(\w+)\s*[;=].*///#//declared in local@@@h: &#' |\
#przeorganizowywanie konstruktorow
sed -E 's|\{(\s*)super\/\*(\w+)\*\/\((.*)\)(s*);|\:\1\2\(\3\)\4{|' |\
#Dodawanie ENTER po { ale nie dla "enum"
sed -E 's|\{(.*)}|{\n\t\1\n\t}|' |\
sed -E 's|(\s*)([;}])(\s*)return([^;]+);|\1\2\n\3\treturn \4;|' |\
#wolne public/private przed funkcjami i zmiennymi - rzadko stosowane w Processingu
sed -E "s/^(\s*)public/\1public:\n\t/g" |\
sed -E "s/^(\s*)private/\1private:\n\t/g" |\
#sed -E 's|\)\s+\{(.+)$|){\n\t\t\1|' |\
#w deklaracjach klas (działa tylko dla deklaracji klas z { w tej samej linii! )
sed -E 's|\s*abstract\s*class(.+)\{|//abstract\nclass\1{|' |\
sed -E 's|class(\s+)(\w+)(\s*)extends|class\1\2\3: public |g' |\
#dla klas reprezentujacych interface'y JAVA'y dziedziczenie jest tylko wirtualne
sed -E 's|\s*interface(.+)\{|//interface\nclass\1\{|' |\
sed -E 's|class(.+)\{|class\1\, public virtual Object{|' |\
sed 's|extends|: public virtual |g' |\
#implementacje interfejsow sa tylko wirtualne
sed 's|implements|: public virtual|g' |\
#i czasem trzeba to jawnie podpowiedziec DYREKTYWĄ
sed 's|\/\*_pubext\*\/|public virtual|g' |\
#jak sie wygeneruje za duzo : to je zmieniamy na przecinki
sed -E 's|class(.+)(:\s*public\s*\s+)(\w+)\s*\:(\s*public\s*virtual)(.*)\{|class\1\2\3,\4\5\{|g' |\
sed -E 's|class(.+)(:\s*public\s*virtual\s+)(\w+)\s*\:(\s*public\s*virtual)(.*)\{|class\1\2\3,\4\5\{|g' |\
#gdy nie bylo zadnej klasy bazowej?
sed -E 's|class\s+(\w+)\s*\,\s*public|class \1: public|' |\
#dodanie public:
sed -E 's|(\s*)class(\s+)(\w+)(.*)\{|&\n\1  public:|' |\
#...i jak nie ma komentarza
#sed -E 's|class(\s+)(\w+)(.*)\{|&\npublic:|M' |\ ?????
#https://serverfault.com/questions/272033/sed-replace-across-multiple-lines
#składnia prostych tablic
sed -E 's/(int|float|double|boolean|char|String)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])/scuboid<\1>/' |\
sed -E 's/(int|float|double|boolean|char|String)(\s*)(\[\s*]\s*\[\s*])/smatrix<\1>/g' |\
sed -E 's/(int|float|double|boolean|char|String)(\s*)(\[\s*])/sarray<\1>/g' |\
sed -E 's/new(\s+)(int|float|double|boolean|char|String)(\s*)\[(.+)](\s*)\[(.+)](\s*)\[(.+)]/new\1cuboid<\2>(\4,\6,\8)/' |\
sed -E 's/new(\s+)(int|float|double|boolean|char|String)(\s*)\[(.+)](\s*)\[(.+)]/new\1matrix<\2>(\4,\6)/' |\
sed -E 's/new(\s+)(int|float|double|boolean|char|String)(\s*)\[(.+)]/new\1array<\2>(\4)/' |\
#pozostałe to składnia tablic obiektów
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])|scuboid<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*])|smatrix<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*])|sarray<p\1>|g' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)](\s*)\[(.+)](\s*)\[(.+)]|new\1cuboid<p\2>(\4,\6,\8)|' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)](\s*)\[(.+)]|new\1matrix<p\2>(\4,\6)|' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)]|new\1array<p\2>(\4)|' |\
#listy i mapy obiektów np.
#ArrayList<Link> connections;
#connections=new ArrayList<Link>();
#TODO - to dodawanie p do typu w ArrayList jest podejrzane. Powinno działać ogólnie a nie tak dziwnie
#sed -E 's|ArrayList<(\s*)(\w+)(\s*)>(\s+)(\w+)(\s*)([\),;:=])|pArrayList<p\2>\4\5\6\7|g' |\
sed -E 's|new(\s+)ArrayList<(\s*)(\w+)(\s*)>|new ArrayList<p\3>|g' |\
#sed -E 's|HashMap\s*<(.+)>(\s+)(\w+)(\s*)([\),;:=])|pHashMap<\1>\2\3\4\5|g' |\
sed -E 's|HashMap\s*<([^,]+),\s*Integer\s*>|HashMap<\1,int>|g' |\
sed -E 's|HashMap\s*<\s*Integer\s*,|HashMap<int,|g' |\
sed -E 's|HashMap\s*<([^,]+),\s*Float\s*>|HashMap<\1,float>|g' |\
sed -E 's|HashMap\s*<\s*Float\s*,|HashMap<float,|g' |\
sed 's|Map.Entry|auto|g' |\
#modyfikacja składni asercji - chyba spacje po assert zbędne
#sed -E 's|assert (.+);|assert(\1);|g'
sed -E 's|assert (.+):|assert \1; // |g' |\
sed -E 's|assert ([^;]+);|assert(\1);\t//|g' |\
#modyfikacja print i println do plikow
sed -E 's|(\w+)\.print\(|print(\1,|g' |\
sed -E 's|(\w+)\.println\(|println(\1,|g' |\
#zmiany bardziej generalne
sed -E 's|boolean([ >)])|bool\1|g'  |\
sed -E 's|char([ >)])|char16_t\1|g' |\
sed 's/this\./this->/g' |\
sed -E 's/([(,]\s*)(this)(\s*[,)])/\1SAFE_THIS\3/g' |\
sed -E 's|super\/\*(\w+)\*\/\.|\1::|g' |\
sed 's/super\./super::/' |\
sed -E 's/(\w+)(\s+)instanceof(\s+)(\w+)/instanceof< \4 >( \1 )/g' |\
sed "s/frameRate(/setFrameRate(/" |\
#sed 's/\.length/.length()/g' |\ #zbyt brutalne
sed 's/null/nullptr/g' |\
#MATH & FLOATs
sed 's/Float.MAX_VALUE/FLT_MAX/g' |\
sed 's/Float.MIN_VALUE/FLT_MIN/g' |\
sed 's/Integer.parseInt/std::stoi/g' |\
sed 's/Float.parseFloat/std::stof/g' |\
sed 's|hex(|Processing::hex(|g' |\
#sed 's|binary(|Processing::binary(|g' |\
sed 's/Math\./std::/g'  |\
sed -E 's|>>>(\s*)([0-9]+)|>>\1\2/*UNSIGNED SHIFT EXPECTED*/|g' |\
#sed 's/abs(/std::abs(/g' |\
#DIRECTIVES
sed 's|\/\*_OnlyCppBlockBegin|/*_OnlyCppBlockBegin*/|i' |\
sed 's|_OnlyCppBlockEnd\*\/|/*_OnlyCppBlockEnd*/|i' |\
sed 's|\/\*_OnlyProcessingBlockBegin\*\/|/*_OnlyProcessingBlockBegin|i' |\
sed 's|\/\*_OnlyProcessingBlockEnd\*\/|_OnlyProcessingBlockEnd*/|i' |\
sed 's|\/\*_interfunc\*\/|virtual|g'|\
sed -E 's|abstract(\s+)virtual|virtual|' |\
sed 's|\/\*_forcebody\*\/|=0|g' |\
sed 's|\/\*_emptybody\*\/|{}|g' |\
sed 's|\/\*_endOfClass|;/*_endOfClass|i'  |\
sed 's|\/\/\_endOfClass|;//_endOfClass|i'  |\
#Opakowywanie stałych znakowych i stringowych w operacjach konkatenacji ""
sed -E "s|\+(\s*)('[^']')|\+\1String(\2)|g" |\
sed -E 's|(\"[^"]*\")(\s*)\+|String(\1)\2\+|g' |\
sed -E 's|\+(\s*)(\"[^"]*\")|+\1 String(\2)|g' |\
#Stała stringowa jako drugi argument ?:
sed -E 's|\?(\s*)(\"[^"]*\")|?\1 String(\2) |g' |\
#IMPORTY 
sed 's/import java.util.Collections;/#include\<algorithm\>/' |\
#TE SĄ JUŻ PRZESTARZAŁE W PROCESSINGU
sed 's#import java.util.Map;#//HashMap is used here#' |\
sed 's#import java.util.Arrays;#//ArrayList is used here#' |\
#COLLECTIONS ALGORITHMS
sed -E 's/Collections.sort\((\w+)\);/std::sort(\1.begin(),\1.end());/g' |\
#processing_window METHODS
sed 's/void setup()/void processing_window::setup()/' |\
sed 's/void draw()/void processing_window::draw()/' |\
sed 's/void exit()/void processing_window::exit()/' |\
sed 's/super::exit()/processing_window_base::exit()/g' |\
#processing_window EVENTS
sed 's/void keyPressed()/void processing_window::onKeyPressed()/' |\
sed 's/void keyReleased()/void processing_window::onKeyReleased()/' |\
sed 's/void mouseClicked()/void processing_window::onMouseClicked()/' |\
sed 's/void mousePressed()/void processing_window::onMousePressed()/' |\
sed 's/void mouseReleased()/void processing_window::onMouseReleased()/' |\
sed 's/void mouseMoved()/void processing_window::onMouseMoved()/' |\
sed 's/void mouseDragged()/void processing_window::onMouseDragged()/' |\
#WYJĄTKI - EXCEPTIONS http://www.cplusplus.com/reference/ios/ios/exceptions/
sed 's/IOException/std::ifstream::failure/g' |\
sed 's/Exception/std::runtime_error/g' |\
sed -E 's/throw(\s+)new/throw/g' |\
#PODMIANA TYPÓW UŻYTKOWNIKA NA inteligentne wskaźniki pAAAA
sed -E -f userclasses.sed  |\
#Tutaj dopiero dyrektywy zależne od templeatów C++
sed -E 's|\/\*_downcast\*\/\((\w+)\)|std::dynamic_pointer_cast\<\1\>|g' |\
sed -E 's|\/\*_dncast\*\/\((\w+)\)|std::dynamic_pointer_cast\<\1\>|g' |\
sed -E 's|\/\*_upcast\*\/\((\w+)\)|static_cast\<p\1\>|g' |\
sed -E 's|\/\*_tmpfree\*\/\((\w+)\)|_free_ptr_to\<\1\>|g' |\
sed -E 's|\/\*_reference\*\/|\& |g'|\
sed -E 's|\s*\/\*_tmpptr\*\/|\* |g'|\
#ZAMIANA ODWOŁAŃ KROPKOWYCH NA STRZAŁKOWE
#kropki zamkniete w "" próbujemy zabezpieczyć - głównie dotyczy to nazw plików w includach
#Może sprawiać kłopoty w dłuższych konkatenacjach tekstów
sed -E 's/"([^"]*)\.([^"]+)"/"\1@@@\2"/g' |\
#WŁAŚCIWA ZAMIANA 
#sed -E  's/^([^#]*)([_a-zA-Z][_a-zA-Z0-9]*)\.([_a-zA-Z][_a-zA-Z0-9]*)/\1\2->\3/g' |\ #dawna próba uniknięcia ingerencji w dyrektywy kompilatora (#)
#sed -E  's|([_a-zA-Z][_a-zA-Z0-9]*)(\s*)\.|\1->|g' |\ #TO PSUJE KOŃCE ZDAŃ W KOMENTARZACH!!!
# patern <.><white><ident> też jest niedozwolony bo nie do odróżnienia od końca zdania w komentarzu!
sed -E   's|([^.])\.([_a-zA-Z][_a-zA-Z0-9]*)|\1->\2|g' |\
sed -E   's|\](\s*)\.([_a-zA-Z][_a-zA-Z0-9]*)|]->\2|g' |\
sed -E   's|\)(\s*)\.([_a-zA-Z][_a-zA-Z0-9]*)|)->\2|g' |\
sed -E   's|([_a-zA-Z][_a-zA-Z0-9]*)(\s*)\.([_a-zA-Z][_a-zA-Z0-9]*)|\1->\3|g' |\
#Odbezpieczenie kropek w cudzysłowach
sed -E 's/\@\@\@/./g' |\
#jeśli przypadkiem któryś z typów podstawowych zostanie potraktowany jako object w <> szablonu:
sed -E 's/\<p(bool|int|long|float|double|String)(\s*)\>/\1\2/g' |\
#CZYSZCZENIE NADMIAROWYCH ZNAKÓW SPACJI I KOMENTARZY
sed -E 's|//\s+//|//|g'
#echo 's/"(.+)\.(.+)"/-TEST-TEST-TEST-/g' 1>&2
echo -e "//$(dirname $0) did it\n"

echo -e "END" $NORMCO 1>&2 #end of colored errors


#/********************************************************************/
#/*               PROCESSING2C  version 2022-05-09                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studów Społecznych Uniwersytetu Warszawskiego        */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

