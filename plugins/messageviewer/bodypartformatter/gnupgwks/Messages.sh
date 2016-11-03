#! /bin/sh
$EXTRACT_GRANTLEE_TEMPLATE_STRINGS `find templates -name \*.html` >> html.cpp
$XGETTEXT html.cpp *.cpp -o $podir/messageviewer_application_gnupgwks_plugin.pot
rm -f html.cpp
