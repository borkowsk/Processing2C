s/([\,\(\s]*)(FloatList|IntList|StringList|bulba)(\s+)(\w+)([:;,\)\(\=])/\1p\2\3\4\5/g
s/<(Link)>/<p\1>/g
s/aNetworkType\./aNetworkType\:\:/g
