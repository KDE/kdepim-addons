/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "rot13plugineditortest.h"
#include "../rot13plugineditor.h"
#include <KActionCollection>
#include <QTest>

Rot13PluginEditorTest::Rot13PluginEditorTest(QObject *parent)
    : QObject(parent)
{

}

Rot13PluginEditorTest::~Rot13PluginEditorTest()
{

}

void Rot13PluginEditorTest::shouldHaveDefaultValue()
{
    Rot13PluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
}

QTEST_MAIN(Rot13PluginEditorTest)
