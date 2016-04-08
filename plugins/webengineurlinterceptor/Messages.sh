#! /bin/sh
$EXTRACTRC `find . -name \*.ui -o -name \*.kcfg` >> rc.cpp
$XGETTEXT `find . -name '*.cpp' -o -name '*.h' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/webengineurlinterceptor.pot
rm -f rc.cpp
