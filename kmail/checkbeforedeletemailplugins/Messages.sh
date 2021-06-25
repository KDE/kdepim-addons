#! /bin/sh
$XGETTEXT `find . -name '*.cpp' -o -name '*.h' | grep -v '/tests/' | grep -v '/autotests/''` -o $podir/kmail_checkbeforedeleting_plugins.pot
