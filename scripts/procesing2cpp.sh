#!/bin/bash
if [ $# -ne 1 ]; 
then
   echo "$# is invalid number of parameters!" 1>&2
   exit -1
fi

echo "//Processing to C++ converter $0"
echo "//Source: $1"
echo "#include \"processing_window.hpp\""
echo "#include \"processing_library.hpp\""
echo "#include \"processing_console.hpp\" //is optional. Should be deleted when not needed"
echo "//include \"processing_inlines.hpp\" //is optional. Use when project is already compilable"
echo "using namespace Processing;"
echo "#include \"local.h\""
echo "#include \"project.h\" //Is's for you. Could be deleted when not needed"
echo "//=================================================================================="
echo ""

cat $1 |\
sed -E 's|\{(.*)}|{\n\t\1\n\t}|' |\
sed -E 's|(\s*)([;}])(\s*)return([^;]+);|\1\2\n\3\treturn \4;|' |\
#wolne public/private przed funkcjami i zmiennymi - rzadko stosowane w Processingu
sed "s/public/public:\n\t/g" |\
sed "s/private/private:\n\t/g" |\
#sed -E 's|\)\s+\{(.+)$|){\n\t\t\1|' |\
#w deklaracjach klas (działa tylko dla deklaracji klas z { w tej samej linii! )
sed -E 's|abstract(.+)class(.+)\{|//abstract\n\1class\2{|' |\
sed -E 's|interface(.+)\{|//interface\nclass\1{|' |\
#dodanie public:
sed -E 's|(\s*)class(\s+)(\w+)(.*)\{|&\n\1  public:|g' |\
#...i jak nie ma komentarza
#sed -E 's|class(\s+)(\w+)(.*)\{|&\npublic:|M' |\ ?????
#https://serverfault.com/questions/272033/sed-replace-across-multiple-lines
sed 's|extends|: public|g' |\
sed 's|implements|: public|g' |\
sed -E 's|class(.+)(: public)(.*)(: public)(.*)\{|class\1\2\3,\5\{|' |\
#składnia prostych tablic
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])/scuboid<\1>/' |\
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*]\s*\[\s*])/smatrix<\1>/' |\
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*])/sarray<\1>/' |\
sed -E 's/new(\s+)(int|float|double|boolean|String)(\s*)\[(.+)](\s*)\[(.+)](\s*)\[(.+)]/new\1cuboid<\2>(\4,\6,\8)/' |\
sed -E 's/new(\s+)(int|float|double|boolean|String)(\s*)\[(.+)](\s*)\[(.+)]/new\1matrix<\2>(\4,\6)/' |\
sed -E 's/new(\s+)(int|float|double|boolean|String)(\s*)\[(.+)]/new\1array<\2>(\4)/' |\
#pozostałe to składnia tablic obiektów
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])|scuboid<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*])|smatrix<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*])|sarray<p\1>|g' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)](\s*)\[(.+)](\s*)\[(.+)]|new\1cuboid<p\2>(\4,\6,\8)|' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)](\s*)\[(.+)]|new\1matrix<p\2>(\4,\6)|' |\
sed -E 's|new(\s+)(\w+)(\s*)\[(.+)]|new\1array<p\2>(\4)|' |\
#modyfikacja składni asercji - chyba spacje po assert zbędne
#sed -E 's|assert (.+);|assert(\1);|g'
sed -E 's|assert (.+):|assert \1; // |g' |\
sed -E 's|assert ([^;]+);|assert(\1);\t//|g' |\
#modyfikacja print i println do plikow
sed -E 's|(\w+)\.print\(|print(\1,|g' |\
sed -E 's|(\w+)\.println\(|println(\1,|g' |\
#zmiany bardziej generalne
sed 's/boolean /bool /g' |\
sed 's/this\./this->/g' |\
sed 's/\.length/.length()/g' |\
sed 's/null/nullptr/g' |\
sed 's/final /const /g' |\
#IMPORTY
sed 's/import java.util.Map;/#include "processing_map.hpp"/' |\
sed 's/import java.util.Arrays;/#include "processing_lists.hpp"/' |\
#POJEDYNCZE FUNKCJE O ZNACZENIU SPECJALNYM
sed "s/void setup()/void processing_window::setup()/g" |\
sed "s/void draw()/void processing_window::draw()/g" |\
sed "s/void mouseClicked()/void processing_window::mouseClicked()/g" |\
sed "s/void exit()/void processing_window::exit()/g" |\
sed "s/super.exit();/processing_window_base::exit()/g" |\
sed -E -f userclasses.sed  |\
#ZAMIANA ODWOŁAŃ KROPKOWYCH NA STRZAŁKOWE - może być za brutalne
sed -E 's/(\w+)\.(\w+)/\1->\2/g' |\
sed -E 's/\]\.(\w+)/]->\1/g' |\
#CZYSZCZENIE NADMIAROWYCH ZNAKÓW SPACJI I KOMENTARZY
sed -E 's|//\s+//|//|g'

echo -e "//$0 did it\n"

