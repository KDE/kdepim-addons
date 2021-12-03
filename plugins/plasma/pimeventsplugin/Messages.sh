#! /usr/bin/env bash
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
$XGETTEXT `find . -name *.qml` -L Java -o $podir/pimeventsplugin.pot
