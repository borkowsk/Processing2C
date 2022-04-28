#!/bin/bash
#See: https://askubuntu.com/questions/927064/grep-pattern-with-leading-spaces
echo -e "//Automagically generated file\n//Dont edit!\n#pragma once\n#ifndef LOCAL_H\n#define LOCAL_H\n"\
        > local.h

echo -e "\n\n//All classes from Processing files" >> local.h

egrep -h '^\s*(class|abstract\s+class|interface|enum)\s+(\w+)' *.pde |\
sed 's|abstract |/*abstract*/|g' |\
sed 's|interface|/*interface*/class|g' |\
sed 's/  / /g' | tee headers.tmp |\
sed -E 's|class(\s+)(\w+)|&\; typedef Processing::ptr<\2> p\2; //|g' | LC_COLLATE=C sort -i >> local.h
#see: https://superuser.com/questions/178171/gnu-sort-by-case-sensitive
#see: https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm

#sed program for replacing user defined classes
#egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's|(\w+)|s/(&)(\\s+)(\\w+)/bla/g|'

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

#TO DZIAŁA NIE TAK JAK BYM CHCIAŁ TODO!!!
#echo "_@ENTER_" >> userclasses.sed
#echo "s/\<(" >> userclasses.sed
#egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
#echo "bulba)\>/<p\1>/g" >> userclasses.sed


#https://stackoverflow.com/questions/1251999/how-can-i-replace-a-newline-n-using-sed
sed -i ':a;N;$!ba;s/\n//g' userclasses.sed 
sed -i "s/_@ENTER_/\n/g" userclasses.sed

#TEMPORARY
echo "s/<(Link)>/<p\1>/g"  >> userclasses.sed
echo "s/(aNetworkType|aCriterion)\./\1\:\:/g" >> userclasses.sed

#Stałe czyli 'finals'
echo -e "\n//All global finals (consts) from Processing files" >> local.h

egrep -h '^\s*(final\s+int|final\s+float|final\s+double|final\s+String|final\s+boolean|final\s+\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's|final\s+|const |g' |\
# Może: static constexpr ?
sed -E 's/^\s*(const\s+int|const\s+float|const\s+double|const\s+String|const\s+boolean|const\s+\w+)/static \t\1/' |\
#podmiana boolean i nazw klas
sed 's|boolean|bool   |g' |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g'  >> local.h
#sed 's|=|;//=|' >> local.h --- bez usuwania =

#zmienne
echo -e "\n//All global variables from Processing files" >> local.h

egrep -h '^\s*(int|float|double|String|boolean|char|\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's/^\s*(int|float|double|String|boolean|char|\w+)\s+/extern\t&\t\t/' |\
#podmiana boolean i nazw klas
sed 's|boolean |bool |g'  |\
sed 's|char |char16_t |g' |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g' |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;//=|' |\
sed -E 's|//(.*)///|///< \1|' >> local.h


#zmienne tablicowe
echo -e "\n//All global arrays from Processing files" >> local.h

egrep -h '^\s*(int|float|double|String|boolean|char|\w+)\[\s*\]\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*])/extern\tsarray<\1>/g' |\
#podmiana boolean i nazw klas
sed 's|boolean |bool |g'  |\
sed 's|char |char16_t |g' |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g' |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;//=|' |\
sed -E 's|//(.*)///|///< \1|' >> local.h

#zmienne matrycowe
echo -e "\n//All global matrices from Processing files" >> local.h

egrep -h '^\s*(int|float|double|String|boolean|char|\w+)\[\s*\]\s*[\s*\]\s+(\w+)\s*[;=].*///' *.pde |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*]\s*\[\s*])/extern\tsmatrix<\1>/g' |\
#podmiana boolean i nazw klas
sed 's|boolean |bool |g'  |\
sed 's|char |char16_t |g' |\
sed -E -f userclasses.sed  |\
sed 's|\/\*_reference\*\/|\&|g' |\
#poprawianie komentarzy i interpunkcji
sed 's|=|;//=|' |\
sed -E 's|//(.*)///|///< \1|' >> local.h


#Funkcje wymagające deklaracji zapowiadających
echo -e "\n//All global functions from Processing files" >> local.h

egrep -h '^\s*(void|int|float|double|String|boolean|char)\s+(\w+)\s*\(.*\)\s*\{*\s*///' *.pde |\
sed -E 's#^\s*(void|int|float|double|String|boolean|char)\s+(\w+)\s*(\(.*\)\s*)#\1\t\2\3; //#' |\
#składnia prostych tablic w parametrach
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])/scuboid<\1>/g' |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*]\s*\[\s*])/smatrix<\1>/g' |\
sed -E 's/(int|float|double|boolean|String|char)(\s*)(\[\s*])/sarray<\1>/g' |\
#pozostałe to składnia tablic obiektów w parametrach
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])|scuboid<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*])|smatrix<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*])|sarray<p\1>|g' |\
#podmiana boolean i nazw klas
sed 's|boolean |bool |g'  |\
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

#/********************************************************************/
#/*               PROCESSING2C  version 2022-04-21                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

