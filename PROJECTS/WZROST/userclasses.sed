s/([\,\(\s*]*\s*)(KLASA|FloatList|IntList|StringList|Object)(\s*\/\*_reference\*\/\s*|\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5/g
s/([\,\(\s*]*\s*)(ArrayList|HashMap)\s*(<[A-Za-z1-9_,<>]+>)(\s+)([A-Za-z1-9_]+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/([,<])(KLASA|Object)>/\1p\2>/g
s/<(Link)>/<p\1>/g
s/(aNetworkType|aCriterion)\./\1\:\:/g
