s/([\,\(\s*]*\s*)(Agent|MousePairOfInt|World|FloatList|IntList|StringList|FloatDict|IntDict|StringDict|Object)(\s*\/\*_reference\*\/\s*|\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5/g
s/([\,\(\s*]*\s*)(ArrayList|HashMap)\s*(<[A-Za-z1-9_,<>]+>)(\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/([,<])(Agent|MousePairOfInt|World|Object)>/\1p\2>/g
s/([^[:alnum:]])(Agent|MousePairOfInt|World|Object)\.(\w)/\1\2\:\:\3/g
