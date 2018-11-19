#! /bin/sh
$XGETTEXT `find . -name '*.cpp' -o -name '*.h' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/messageviewerconfiguresettingsplugins.pot
