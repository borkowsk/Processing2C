s/([\,\(\s*]*\s*)(Ant|Back|World|FloatList|IntList|StringList|Object)\s*(\&*)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/([\,\(\s*]*\s*)(ArrayList|HashMap)\s*(<[A-Za-z1-9_,<>]+>)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/([,<])(Ant|Back|World|Object)>/\1p\2>/g
s/<(Link)>/<p\1>/g
s/(aNetworkType|aCriterion)\./\1\:\:/g
