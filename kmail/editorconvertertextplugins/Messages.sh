#! /bin/sh
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
$XGETTEXT `find . -name '*.cpp' -o -name '*.h' | grep -v '/tests/' | grep -v '/autotests/' | grep -v '/qtcreator-template/'` -o $podir/kmail_editorconvertertext_plugins.pot
