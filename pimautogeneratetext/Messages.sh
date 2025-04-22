#! /bin/sh
$XGETTEXT `find . -name '*.h' -o -name '*.cpp' | grep -v '/tests/' |grep -v '/autotests/'` -o $podir/libpimautogeneratetext.pot
