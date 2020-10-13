s/([\,\(\s]*)(RGB|FloatList|IntList|StringList|Object)(\s+)(\w+)\s*([:;,\)\(\=])/\1p\2\3\4\5/g
s/<(Link)>/<p\1>/g
s/aNetworkType\./aNetworkType\:\:/g
