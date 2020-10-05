#/bin/bash
#egrep "^([^#^/\s]*)([A-Za-z][A-Za-z0-9_]*)(\s+)([A-Za-z][A-Za-z0-9_]*)" *.h* ???
egrep -h '^([^#]\s)*(friend|virtual|const|inline)*(\s+)(\w+\s+)+([A-Za-z][_A-Za-z0-1]*)([<(,])' *.hpp |\
sed -E 's@(\s*)((friend|virtual|const|inline)\s*)*(.*)$@\4@g' |\
sed -E 's@(auto|bool|void|int|size_t|long|float|double|String)(\s*)([A-Za-z][_A-Za-z0-1]*)([<(,])(.*)$@\3@'|\
sort | uniq
