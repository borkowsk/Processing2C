#!/bin/bash
grep -H3 -n "implemented" lib/src/*.c* | grep -E --color "(int|void|bool|float|String|sarray|long|not implemented)"
grep -H3 -n "implemented" lib/src/*.c* | grep -E "(int|void|bool|float|String|long|sarray)" > not_implemented.h
