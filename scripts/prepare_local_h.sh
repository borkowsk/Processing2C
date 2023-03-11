#!/bin/bash
#See: https://askubuntu.com/questions/927064/grep-pattern-with-leading-spaces
#
# Processing2C version 22b. (2023-03-11)
#

echo -e $COLOR1"Making $COLOR2'local.h'$COLOR3" $COLERR 

echo -e "//Automagically generated file\n//Dont edit!\n#pragma once\n#ifndef LOCAL_H\n#define LOCAL_H\n"\
        > local.h

#awaryjnie
#echo 'typedef bool boolean;' >> local.h

echo -e "\n\n//All classes but not templates from Processing files" >> local.h

egrep -h '^\s*(class|abstract\s+class|interface|enum)[ ]+(\w+)([^<]*)$' *.pde |\
sed 's|abstract |/*abstract*/|g' |\
sed 's|interface|/*interface*/class|g' |\
sed 's/  / /g' | LC_COLLATE=C sort -i | uniq | tee headers.tmp |\
sed -E 's|class(\s+)(\w+)|&\; typedef Processing::ptr<\2> p\2; //|g'  >> local.h
#see: https://superuser.com/questions/178171/gnu-sort-by-case-sensitive
#see: https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm

#DEBUG
#echo "/*" >> local.h
#cat headers.tmp >> local.h
#echo "*/" >> local.h

#sed program for replacing user defined classes & enums

#... inside declarations
echo "s/([\,\(\s*]*\s*)(" > userclasses.sed
egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed

# (\&*)(\s+) -> \/\*_reference\*\/ : & powinien pojawiać tylko w wyniku rozwinięcia dyrektywy, więc po wszystkim innym
echo 'FloatList|IntList|StringList|FloatDict|IntDict|StringDict|Object)(\s*\/\*_reference\*\/\s*|\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5/g'  >> userclasses.sed 
#... predefined JAVA templates
echo -e "_@ENTER_" >> userclasses.sed
# (\&*)(\s+) ? Potrzebne?
echo 's/([\,\(\s*]*\s*)(ArrayList|HashMap)\s*(<[A-Za-z1-9_,<>]+>)(\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g'  >> userclasses.sed  

#...inside templates parameter lists
echo -e "_@ENTER_" >> userclasses.sed
echo "s/([,<])(" >> userclasses.sed
egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
echo 'Object)>/\1p\2>/g' >> userclasses.sed

#Class/enum name with dot. Eg. String. MyClass.  --> String:: MyClass::
echo -e "_@ENTER_" >> userclasses.sed
#[^a-zA-Z\d] czyli nie znak alfanumeryczny gwarantuje, że nazwy klas pasują tylko jako całe wyrazy
echo "s/([^[:alnum:]])(" >> userclasses.sed
egrep -o '(class|enum)(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed 's|enum ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
#awaryjnie - tylko enums
#egrep -o 'enum(\s+)(\w+)' headers.tmp | sed 's|enum ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
echo "Object)\.(\w)/\1\2\:\:\3/g" >> userclasses.sed

#https://stackoverflow.com/questions/1251999/how-can-i-replace-a-newline-n-using-sed
sed -i ':a;N;$!ba;s/\n//g' userclasses.sed 
sed -i "s/_@ENTER_/\n/g" userclasses.sed

#TEMPORARY - problem enum'ów inaczej rozwiązany
#echo "s/(NetworkTopology|Criterion)\./\1\:\:/g" >> userclasses.sed

#Proste stałe czyli 'finals'
echo -e "\n//All global finals (consts) from Processing files" >> local.h

egrep -h '^\s*(final\s+int|final\s+float|final\s+double|final\s+String|final\s+boolean|final\s+\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's|final\s+|const |g' |\
# Może: static constexpr ?
sed -E 's/^\s*(const\s+int|const\s+float|const\s+double|const\s+String|const\s+boolean|const\s+\w+)/static \t\1/' |\
#podmiana boolean, char i nazw klas
sed -E 's|boolean([<(\t >)])|bool\1|g'  |\
sed 's|char |char16_t |g'  |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g'  >> local.h
#sed 's|=|;//=|' >> local.h --- bez usuwania =

#zmienne proste:
echo -e "\n//All global variables from Processing files" >> local.h

egrep -h '^\s*(int|float|double|String|boolean|char|\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's/^\s*(int|float|double|String|boolean|char|\w+)\s+/extern\t&\t\t/' |\
#podmiana boolean, char i nazw klas
sed -E 's|boolean([<(\t >)])|bool\1|g' |\
sed 's|char |char16_t |g'              |\
sed -E -f userclasses.sed              |\
sed 's|\/\*_reference\*\/|\&|g'        |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;///=|'                       |\
sed 's|///<|// -|'                     |\
sed -E 's|//+(.*)//+|\t///< \1|' >> local.h


#zmienne tablicowe (ale tylko typów prostych!)
echo -e "\n//All global arrays from Processing files" >> local.h

egrep -h '^\s*(final\s+|)(int|float|double|String|boolean|char)\s*\[\s*\]\s+\w+.*///' *.pde |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*])/extern\tsarray<\1>/g' |\
#podmiana boolean, char i nazw klas
sed -E 's|boolean([<(\t >)])|bool\1|g' |\
sed 's|char |char16_t |g'              |\
sed -E -f userclasses.sed              |\
sed 's|\/\*_reference\*\/|\&|g'        |\
sed -E 's|final\s+|const |g'           |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;///=|'                       |\
sed 's|///<|// -|'                     |\
sed -E 's|//+(.*)//+|\t///< \1|' >> local.h

#zmienne matrycowe (ale tylko typów prostych!)
echo -e "\n//All global matrices from Processing files" >> local.h

egrep -h '^\s*(final |)(int|float|double|String|boolean|char)\[\s*\]\s*[\s*\]\s+\w+.*///' *.pde |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*]\s*\[\s*])/extern\tsmatrix<\1>/g' |\
#podmiana boolean, char i nazw klas
sed -E 's|boolean([<(\t >)])|bool\1|g' |\
sed 's|char |char16_t |g'              |\
sed -E -f userclasses.sed              |\
sed 's|\/\*_reference\*\/|\&|g'        |\
sed -E 's|final\s+|const |g'           |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;///=|'                       |\
sed 's|///<|// -|'                     |\
sed -E 's|//+(.*)//+|\t///< \1|' >> local.h


#Funkcje wymagające deklaracji zapowiadających
echo -e "\n//All global functions from Processing files" >> local.h

egrep -h '^\s*(void|int|float|double|String|boolean|char|\w+)\s+(\w+)\s*\(.*\)\s*\{*\s*///' *.pde |\
#funkcja o dowolnych parametrach
sed -E 's#^\s*(void|int|float|double|String|boolean|char|\w+)\s+(\w+)\s*(\(.*\)\s*)#\1\t\2\3; //#' |\
#podmiana prostych tablic w parametrach
sed -E 's/(int|float|double|boolean|String|char|\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])/scuboid<\1>/g' |\
sed -E 's/(int|float|double|boolean|String|char|\w+)(\s*)(\[\s*]\s*\[\s*])/smatrix<\1>/g' |\
sed -E 's/(int|float|double|boolean|String|char|\w+)(\s*)(\[\s*])/sarray<\1>/g' |\
#pozostałe to składnia tablic obiektów w parametrach (TODO można by użyć też w zapowiedziach tablic!) 
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])|scuboid<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*])|smatrix<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*])|sarray<p\1>|g' |\
#podmiana boolean i nazw klas
sed -E 's|boolean([<(\t >)])|bool\1|g'  |\
sed 's|char |char16_t |g' |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g' |\
#poprawianie komentarzy i interpunkcji
sed -E 's|//\s*\{*\s*///|///|' |\
sed -E 's|(//)(.*)///|///< \2|' |\
#usuwanie zbędnych odstępów
sed -E 's|\)\s+;|); |' >> local.h
#sed 's|) ;|);|' >> local.h
echo "#endif" >> local.h
#cat local.h
#cat userclasses.sed

echo -e $COLOR1"File $COLOR2'local.h'$COLOR1 prepared" $NORMCO 

#/********************************************************************/
#/*               PROCESSING2C  version 2023                         */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

