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

echo "s/([\,\(\s]*)(" > userclasses.sed
egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
echo "FloatList|IntList|StringList|Object)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5/g"  >> userclasses.sed

#TO DZIAŁA NIE TAK JAK BYM CHCIAŁ TODO!!!
#echo "_@ENTER_" >> userclasses.sed
#echo "s/\<(" >> userclasses.sed
#egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
#echo "bulba)\>/<p\1>/g" >> userclasses.sed


#https://stackoverflow.com/questions/1251999/how-can-i-replace-a-newline-n-using-sed
sed -i ':a;N;$!ba;s/\n//g' userclasses.sed 
#sed -i "s/_@ENTER_/\n/" userclasses.sed

#TEMPORARY
echo "s/<(Link)>/<p\1>/g"  >> userclasses.sed
echo "s/(aNetworkType|aCriterion)\./\1\:\:/g" >> userclasses.sed


echo -e "\n//All global finals (consts) from Processing files" >> local.h

egrep -h '^\s*(final\s+int|final\s+float|final\s+double|final\s+String|final\s+boolean|final\s+\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed 's|boolean|bool   |g' |\
sed 's|final|const|g' |\
sed -E 's/^\s*(const\s+int|const\s+float|const\s+double|const\s+String|const\s+bool|const\s+\w+)/extern &/' |\
sed -E -f userclasses.sed  |\
sed 's|=|;//=|' >> local.h

echo -e "\n//All global variables from Processing files" >> local.h
egrep -h '^\s*(int|float|double|String|boolean|\w+)\s+(\w+)\s*[;=].*///' *.pde |\
sed 's|boolean|bool|g' |\
sed -E 's/^\s*(int|float|double|String|bool|\w+)/extern &/' |\
sed -E -f userclasses.sed  |\
sed 's|=|;//=|' >> local.h

#Funkcje wymagające deklaracji zapowiadających
echo -e "\n//All global functions from Processing files" >> local.h

egrep -h '^\s*(void|int|float|double|String|boolean)\s+(\w+)\s*\(.*\)\s*\{*\s*///' *.pde |\
sed -E 's#^\s*(void|int|float|double|String|boolean)\s+(\w+)\s*\(.*\)\s*#&; //#' |\
#składnia prostych tablic w parametrach
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])/scuboid<\1>/' |\
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*]\s*\[\s*])/smatrix<\1>/' |\
sed -E 's/(int|float|double|boolean|String)(\s*)(\[\s*])/sarray<\1>/' |\
#pozostałe to składnia tablic obiektów w parametrach
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*]\s*\[\s*])|scuboid<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*]\s*\[\s*])|smatrix<p\1>|g' |\
sed -E 's|(\w+)(\s*)(\[\s*])|sarray<p\1>|g' |\
#podmiana boolean i String
sed 's|boolean|bool   |g' |\
#sed 's|String|std::string|g' |\
sed -E -f userclasses.sed  |\
sed -E 's|//\s*\{*\s*///|///|' |\
sed 's|) ;|);|' >> local.h

echo "#endif" >> local.h
#cat local.h
#cat userclasses.sed

