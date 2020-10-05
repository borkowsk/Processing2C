#/bin/bash
#egrep "^([^#^/\s]*)([A-Za-z][A-Za-z0-9_]*)(\s+)([A-Za-z][A-Za-z0-9_]*)" *.h* ???
egrep '^([^#]\s)*(const|inline)*(\s+)(\w+\s+)+([A-Za-z][_A-Za-z0-1]*)([<(,])' *.hpp
