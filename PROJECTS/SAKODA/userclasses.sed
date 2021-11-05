s/([\,\(\s]*)(Agent|World|FloatList|IntList|StringList|HashMap|Object)\s*(\&*)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/<(Link)>/<p\1>/g
s/(aNetworkType|aCriterion)\./\1\:\:/g
