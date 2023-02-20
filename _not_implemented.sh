#!/bin/bash
source scripts/screen.ini
grep -H3 -n "implemented" lib/src/*.c* | grep -E --color=always "(int|void|bool|float|String|sarray|long|not implemented)"
grep -H3 -n "implemented" lib/src/*.c* | grep -E "(int|void|bool|float|String|long|sarray)" > docs/not_implemented.h
