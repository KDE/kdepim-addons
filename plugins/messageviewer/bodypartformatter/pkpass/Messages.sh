#! /bin/sh
$EXTRACT_GRANTLEE_TEMPLATE_STRINGS `find templates -name \*.html` >> html.cpp
$XGETTEXT html.cpp *.cpp -o $podir/messageviewer_bodypartformatter_pkpass.pot
rm -f html.cpp
