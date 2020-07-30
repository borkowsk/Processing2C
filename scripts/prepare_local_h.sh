#!/bin/bash
echo -e "//Automagically generated file\n//Dont edit!\n#pragma once\n#ifndef LOCAL_H\n#define LOCAL_H\n"\
        > local.h

echo -e "\n//All global finals (consts) from Processing files" >> local.h
egrep -h '^\s*(final int|final float|final double|final String|final boolean)\s+(\w+)\s*[;=].*///' *.pde |\
sed 's|boolean|bool|g' |\
sed 's|final|const|g' |\
#sed 's|String|std::string|g' |\
sed -E 's/^\s*(const int|const float|const double|const String|const bool)/extern &/' |\
sed 's|=|;//=|' >> local.h

echo -e "\n//All global variables from Processing files" >> local.h
egrep -h '^\s*(int|float|double|String|boolean)\s+(\w+)\s*[;=].*///' *.pde |\
sed 's|boolean|bool|g' |\
#sed 's|String|std::string|g' |\
sed -E 's/^\s*(int|float|double|String|bool)/extern &/' |\
sed 's|=|;//=|' >> local.h

#Funkcje wymagające deklaracji zapowiadających
echo -e "\n//All global functions from Processing files" >> local.h
#echo "///" '^\s*(void|int|float|double|String|boolean)\s+(\w+)\s*\(.*\)\s*\\{.*///'
egrep -h '^\s*(void|int|float|double|String|boolean)\s+(\w+)\s*\(.*\)\s*\{.*///' *.pde |\
sed 's|boolean|bool|g' |\
sed 's|String|std::string|g' |\
sed -E 's#^\s*(void|int|float|double|String|boolean)\s+(\w+)\s*\(.*\)\s*#&; //#' |\
sed -E 's|//\s*\{\s*///|///|' |\
sed 's|) ;|);|' >> local.h


echo -e "\n\n//All classes from Processing files" >> local.h
egrep -h '^\s*(class|abstract\s+class|interface)\s+(\w+)' *.pde |\
sed 's|abstract |/*abstract*/|g' |\
sed 's|interface|/*interface*/class|g' |\
sed 's/  / /g' | tee headers.tmp |\
sed -E 's|class(\s+)(\w+)|&\; typedef Processing::ptr<\2> p\2; //|g' | LC_COLLATE=C sort -i >> local.h
#see: https://superuser.com/questions/178171/gnu-sort-by-case-sensitive
#see: https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
echo "#endif" >> local.h
#cat local.h

#sed program for replacing user defined classes
#egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's|(\w+)|s/(&)(\\s+)(\\w+)/bla/g|'
echo "s/([\,\s]*)(" > userclasses.sed
egrep -o 'class(\s+)(\w+)' headers.tmp | sed 's|class ||' | sed -E 's/(\w+)$/&|/' >> userclasses.sed
echo "bulba)(\s+)(\w+)([;,\)\(\=])/\1p\2\3\4\5/g"  >> userclasses.sed

sed -i ':a;N;$!ba;s/\n//g' userclasses.sed 

#cat userclasses.sed

