#! /bin/sh
$EXTRACT_GRANTLEE_TEMPLATE_STRINGS `find templates -name \*.html` >> rc.cpp
$XGETTEXT *.cpp -o $podir/messageviewer_application_gnupgwks_plugin.pot
