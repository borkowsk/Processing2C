s/([\,\(\s]*)(Mew|Eat|Animal|Cat|Dog|AnimalFeeder|FloatList|IntList|StringList|Object)\s*(\&*)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5\6/g
s/<(Link)>/<p\1>/g
s/(aNetworkType|aCriterion)\./\1\:\:/g
