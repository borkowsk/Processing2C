#!/bin/bash
# Processing2C version 22h. 
# @date 2024-10-15 (last modification)
#
#echo STAGE0 1>&2

if [ $# -ge 4 ]; 
then
   echo -e "${COLOR2}$# ${COLERR}is invalid number of parameters!"$NORMCO 1>&2
   exit -1
else
   echo -e ${COLOR6}$1 ${COLOR7}$2 ${COLOR2}$3 $NORMCO 1>&2
fi

#echo STAGE1 1>&2

TEEOUT="/dev/null"

if [[ $SOURCEMODE == "multisrc" ]] && [[ "$3" == "-ECLL" ]]
then
        $ECHO ${COLOR2}Multisource mode${NORMCO} 1>&2
	echo "/// @note Automatically made from _$1_ by __Processing to C++__ converter ($0)."
	echo "/// @date $TIMEMARK (translation)"
	echo "//"
	echo "#include \"processing_consts.hpp\""
	echo "#include \"processing_templates.hpp\""
	echo "#include \"processing_library.hpp\""
	echo "#include \"processing_window.hpp\""
	echo "#ifndef _NO_INLINE"
	echo "#include \"processing_inlines.hpp\" //...is optional."
	echo "#endif // _NO_INLINE"
	# nagłówki opcjonalne powinny być dodawane na podstawie wyniku grep'a!
	echo -e $COLOR4 $1 $NORMCO 1>&2
	${SCRIPTS}/includeOptionals.sh $1 ${SRCDIR}local.h
	echo "using namespace Processing;"
	if [ -f "project.h" ];then
		echo "#include \"project.h\" // This could be deleted when not needed."
	fi
	echo "#include \"local.h\" //???."
	echo "#include <iostream>"
	echo "//================================================================"
	echo ""
	TEEOUT="$2/$1_imp.pde"
fi

#echo STAGE2 1>&2
echo -e "\n${COLOR4}START TRANSLATION OF $COLOR1 $1 $COLOR3 OPTIONS:$COLOR1 $2 $3 $NORMCO" 1>&2 #Colored ERRORS!

cat $1 |\
${SCRIPTS}/tools $2 $3 2> tools.err   | tee $TEEOUT                           |\
#Brutalne dodawanie średników za końcem klasy.
sed -E 's|\/\/([ _]*)EndOfClass(.*)|; //_EndOfClass\1\n|i'                    |\
#//_endofsuperclass:_anyPreviousSuperClass
sed -E 's|\/\/([ _]*)endofsuperclass:(.*)|//Undefining any base class preprocessor definition: \1\n#undef _superclass|i'  |\
#//_superclass:
sed -E 's|\/\/([ _]*)superclass:(.*)|//Base class is now:\n#define _superclass \1|i'  |\
#Enumeracje są kopiowane do globalnego headera, a nie mogą występować w kodzie dwukrotnie
sed -E 's|enum([^\{]*)\{([^\}]*)\}|//enum\1 : \2|' |\
#także globalne "finale" muszą być skopiowane do głównego headera i wykomentowane w oryginalnym miejscu
sed -E 's|final\s+|const |g' |\
# Może: static constexpr ?
sed -E 's#^\s*(const\s+int|const\s+float|const\s+double|const\s+String|const\s+boolean|const\s+\w+)\s+(\w+)\s*[;=].*///#//declared in local@@@h: &#' |\
#przeorganizowywanie konstruktorow
sed -E 's|(\s*)\{(\s*)super\/\*(\w+)\*\/\((.*)\)(s*);|\1\t\:\2\3\(\4\)\5\n\1{|' |\
#Dodawanie ENTER po { ale nie dla "enum""!!!"
sed -E 's|(\s+)\{(.*)}|\1{\n\t\2\n\t}|' |\
sed -E 's|(\s*)([;}])(\s*)return([^;]+);|\1\2\n\3\treturn \4;|' |\
#wolne public/private przed funkcjami i zmiennymi - rzadko stosowane w Processingu
sed -E "s/^(\s*)public /\1public:\n\t/g" |\
sed -E "s/^(\s*)private /\1private:\n\t/g" |\
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
#TODO - to dodawanie p do typu w `ArrayList` jest podejrzane. Powinno działać ogólnie a nie tak dziwnie
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
#zmiany bardziej generalne i wczesne...
sed -E 's|boolean([ >)])|bool   \1|g'  |\
sed -E 's|char([ >)])|char16_t\1|g' |\
sed 's/this\./this->/g' |\
sed -E 's/([(,]\s*)(this)(\s*[,)])/\1SAFE_THIS\3/g' |\
sed -E 's|super\/\*(\w+)\*\/\.|\1::|g' |\
sed 's/super\./super::/' |\
sed -E 's/(\w+)(\s+)instanceof(\s+)(\w+)/instanceof< \4 >( \1 )/g' |\
sed 's/frameRate(/setFrameRate(/' |\
sed 's/System.currentTimeMillis()/system_ctime_in_ms()/' |\
sed 's/System.exit(/::exit(/'   |\
sed 's/processing.core.PApplet/Processing::pApplet/' |\
sed -E 's/(^\s*)(flush\(\));/\1std::cout@@@flush();std::cerr@@@flush();/' |\
#sed 's/\.length/.length()/g' |\ #zbyt brutalne
sed 's/null/nullptr/g' |\
#MATH & FLOATs & chars
sed 's/Float.MAX_VALUE/FLT_MAX/g' 	|\
sed 's/Float.MIN_VALUE/FLT_MIN/g' 	|\
sed 's/Float.isNaN(/std::isnan(/g'      |\
sed 's/Double.isNaN(/std::isnan(/g'     |\
sed 's/Integer.parseInt/std::stoi/g' 	|\
sed 's/Float.parseFloat/std::stof/g' 	|\
sed 's|hex(|Processing::hex(|g' 	|\
# https://docs.oracle.com/javase/8/docs/api/java/lang/Character.html
sed 's/Character.isAlphabetic(/std::isalpha(/g'   |\
sed 's/Character.isLetter(/std::isalpha(/g'       |\
sed 's/Character.isDigit(/std::isdigit(/g'        |\
sed 's/Character.isSpace(/std::isspace(/g'        |\
sed 's/Character.isWhitespace(/std::isspace(/g'   |\
sed 's/Character.isLowerCase(/std::islower(/g'    |\
sed 's/Character.isUpperCase(/std::isupper(/g'    |\
sed 's/Character.toLowerCase(/std::tolower(/g'    |\
sed 's/Character.toUpperCase(/std::toupper(/g'    |\
#sed 's|binary(|Processing::binary(|g' |\
sed 's/Math\./std::/g'  |\
sed -E 's|>>>(\s*)([0-9]+)|>>\1\2/*UNSIGNED SHIFT EXPECTED*/|g' |\
sed -E 's|abs(\s*)(\()|std::abs\1\2|g' |\
#Math functions may appeared both in Math. and in global Processing spacename
sed 's|std::std::|std::|g' |\
#DIRECTIVES
sed 's|\/\*_OnlyCppBlockBegin|/*_OnlyCppBlockBegin*/|i' |\
sed 's|_OnlyCppBlockEnd\*\/|/*_OnlyCppBlockEnd*/|i'     |\
sed 's|\/\*_OnlyProcessingBlockBegin\*\/|/*_OnlyProcessingBlockBegin|i' |\
sed 's|\/\*_OnlyProcessingBlockEnd\*\/|_OnlyProcessingBlockEnd*/|i'     |\
sed -E 's|abstract(\s+)virtual|virtual|'  |\
sed -E 's|abstract(\s)|/*_interfunc*/\1|g'|\
sed -E 's|virtual(\s+)virtual|virtual |g' |\
sed 's|\/\*_inline\*\/|inline |g'         |\
sed 's|\/\*_const\*\/|const |g'           |\
sed 's|\/\*_interfunc\*\/|virtual |g'     |\
sed 's|\/\*_pvi\*\/|public virtual |g'    |\
sed 's|\/\*_virtual\*\/|virtual |g'       |\
sed 's|\/\*_override\*\/|override |g'     |\
sed 's|\/\*_forcebody\*\/|=0|g'           |\
sed 's|\/\*_emptybody\*\/|{}|g'           |\
sed 's|\/\*_endOfClass|;/*_endOfClass|i'  |\
sed -E 's|\/\/\s*_EofCl|;//_EofCl|i'            |\
#Opakowywanie stałych znakowych i stringowych w operacjach konkatenacji ""
sed -E "s|\+(\s*)('[^']')|\+\1String(\2)|g" |\
sed -E 's|(\"[^"]*\")(\s*)\+|String(\1)\2\+|g' |\
sed -E 's|\+(\s*)(\"[^"]*\")|+\1 String(\2)|g' |\
#Stała stringowa jako drugi argument ?:
sed -E 's|\?(\s*)(\"[^"]*\")|?\1 String(\2) |g' |\
#IMPORTY 
sed 's/import java.util.Collections;/#include\<algorithm\>/' |\
#TE SĄ JUŻ PRZESTARZAŁE W PROCESSINGU
sed 's#import java.util.Map;#//HashMap will be used here#' |\
sed 's#import java.util.Arrays;#//ArrayList will be used here#' |\
#COLLECTIONS ALGORITHMS
sed -E 's/Collections.sort\((\w+)\);/std::sort(\1.begin(),\1.end());/g' |\
#processing_window METHODS
sed 's/void settings()/void processing_window::settings()/' |\
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
#sed -E 's|\/\*_import_class:\s*(\w+)\s*\*\/|#include "\1_class@@@pde@@@hpp"|' |\
#DYREKTYWY PREPROCESORA C
sed -E 's|\/\/_include|#_include|'                                            |\
sed -E 's|\/\/_pragma|#pragma|'                                               |\
sed -E 's|\/\/_ifndef|#ifndef|'                                               |\
sed -E 's|\/\/_define|#define|'                                               |\
sed -E 's|\/\/_endif|#endif|'                                                 |\
#Tutaj dopiero dyrektywy zależne od template-ów C++
sed -E 's|\/\*_downcast\*\/\((\w+)\)|std::dynamic_pointer_cast\<\1\>|g'       |\
sed -E 's|\/\*_dncast\*\/\((\w+)\)|std::dynamic_pointer_cast\<\1\>|g'         |\
sed -E 's|\/\*_dynamic_cast\*\/\((\w+)\)|std::dynamic_pointer_cast\<\1\>|g'   |\
sed -E 's|\/\*_upcast\*\/\((\w+)\)|static_cast\<p\1\>|g'                      |\
sed -E 's|\/\*_stcast\*\/\((\w+)\)|static_cast\<p\1\>|g'                      |\
sed -E 's|\/\*_static_cast\*\/\((\w+)\)|static_cast\<p\1\>|g'                 |\
sed -E 's|\/\*_tmpfree\*\/\((\w+)\)|_free_ptr_to\<\1\>|g'                     |\
sed -E 's|\/\*_tmpptr\*\/|\* |g'                                              |\
sed -E 's|\/\*_rawptr\*\/|\* |g'                                              |\
sed -E 's|\/\*_ref\*\/|\& |g'                                                 |\
sed -E 's|\/\*_reference\*\/|\& |g'                                           |\
#ZAMIANA ODWOŁAŃ KROPKOWYCH NA STRZAŁKOWE
#kropki zamkniete w "" próbujemy zabezpieczyć - głównie dotyczy to nazw plików w includach
#Globalizacja tego może sprawiać kłopoty w dłuższych konkatenacjach tekstów, bo w takiej sytuacji:
# " bla.bla " obiekt.składowa " bla.bla " - nie sposób odróżnić czy obiekt.składowa jest wewnatrz 
#czy na zewnątrz cudzysłowu. I tak więc trzeba wielokrotne cudzysłowy dzielić pomiędzy liniami.
sed -E 's/"([^"]*)\.([^"]+)"/"\1@@@\2"/' |\
#WŁAŚCIWA ZAMIANA 
#sed -E  's|([_a-zA-Z][_a-zA-Z0-9]*)(\s*)\.|\1->|g' |\ #TO PSUJE KOŃCE ZDAŃ W KOMENTARZACH!!!
# pattern <.><white><ident> też jest niedozwolony bo nie do odróżnienia od końca zdania w komentarzu!
sed -E   's|([^.])\.([_a-zA-Z][_a-zA-Z0-9]*)|\1->\2|g' |\
sed -E   's|\](\s*)\.([_a-zA-Z][_a-zA-Z0-9]*)|]->\2|g' |\
sed -E   's|\)(\s*)\.([_a-zA-Z][_a-zA-Z0-9]*)|)->\2|g' |\
sed -E   's|([_a-zA-Z][_a-zA-Z0-9]*)\s*(\.)\s*([_a-zA-Z][_a-zA-Z0-9]*)|\1->\3|g' |\
#Odbezpieczenie kropek w cudzysłowach
sed -E 's/\@\@\@/./g' |\
#jeśli przypadkiem któryś z typów podstawowych zostanie potraktowany jako object w <> szablonu:
sed -E 's/\<p(bool|int|long|float|double|String)(\s*)\>/\1\2/g' |\
#CZYSZCZENIE NADMIAROWYCH ZNAKÓW SPACJI I KOMENTARZY
sed -E 's|//\s+//|//|g'
#echo 's/"(.+)\.(.+)"/-TEST-TEST-TEST-/g' 1>&2
echo -e "//MADE NOTE: $(dirname $0) did it $TIMEMARK !\n"

echo -e $COLOR3 1>&2
#cat tools.err 1>&2     #DEBUG!
#head -3 tools.err 1>&2 #DEBUG!
echo -e $NORMCO 1>&2
grep -E "(Line\s+[0-9]*|'.*')" --color=always  tools.err 1>&2

echo -e $COLOR4"\nEND OF$COLOR1 $* $NORMCO\n" 1>&2 #end of colored errors


#/********************************************************************/
#/*                 PROCESSING2C  release 2024                       */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

