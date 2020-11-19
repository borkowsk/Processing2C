#/bin/bash
rm -f automatic_*.txt
#egrep "^([^#^/\s]*)([A-Za-z][A-Za-z0-9_]*)(\s+)([A-Za-z][A-Za-z0-9_]*)" *.h* ???
egrep -h '^([^#]\s)*(friend|virtual|const|inline)*(\s+)(\w+\s+)+([A-Za-z][_A-Za-z0-1]*)([<(,])' *.hpp |\
sed -E 's@(friend|virtual|const|inline)@@g' |\
sed -E 's@\s+@ @g' |\
sed -E 's@(\s*)(.*)@\2@g' |\
sort | uniq | tee "automatic_full_list.txt" |\
sed -E 's@(return|value|auto|bool|void|int|size_t|long|float|double|String|PFont)(\s*)([A-Za-z][_A-Za-z0-1]*)([<(,])(.*)$@\3@'|\
sort | uniq > automatic_list_of_symbols.txt

echo "(\s*)([A-Za-z][A-Za-z]*)(\s+)(" > symbols_pattern.grep

cat  automatic_list_of_symbols.txt | grep -Ev '(setup|exit|draw)' | sed -E 's/(\w+)$/&|/' >> symbols_pattern.grep
cat  user_list_of_symbols.txt | sed -E 's/(\w+)$/&|/' >> symbols_pattern.grep

echo "buuulba)([,;=\(])" >> symbols_pattern.grep

#https://stackoverflow.com/questions/1251999/how-can-i-replace-a-newline-n-using-sed
sed -i ':a;N;$!ba;s/\n//g' symbols_pattern.grep 

cat symbols_pattern.grep
