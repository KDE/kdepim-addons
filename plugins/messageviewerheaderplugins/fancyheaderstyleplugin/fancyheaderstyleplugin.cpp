/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "fancyheaderstyleinterface.h"
#include "fancyheaderstyleplugin.h"
#include "fancyheaderstyle.h"
#include "messageviewer/richheaderstrategy.h"
#include <kpluginfactory.h>
#include <QApplication>

using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(FancyHeaderStylePlugin, "messageviewer_fancyheaderstyleplugin.json")

FancyHeaderStylePlugin::FancyHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new FancyHeaderStyle)
    , mHeaderStrategy(new RichHeaderStrategy)
{
}

FancyHeaderStylePlugin::~FancyHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *FancyHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *FancyHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

HeaderStyleInterface *FancyHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    MessageViewer::HeaderStyleInterface *view = new MessageViewer::FancyHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString FancyHeaderStylePlugin::name() const
{
    return QStringLiteral("fancy");
}

int FancyHeaderStylePlugin::elidedTextSize() const
{
    return 1000;
}

QString FancyHeaderStylePlugin::extraScreenCss(const QString &headerFont) const
{
    Q_UNUSED(headerFont);
    const QPalette &pal = QApplication::palette();
    const QString val = QStringLiteral("div.fancy.header > div {\n"
                                       "  background-color: %1 ! important;\n"
                                       "  color: %2 ! important;\n"
                                       "  border: solid %3 1px ! important;\n"
                                       "  line-height: normal;\n"
                                       "}\n\n"

                                       "div.fancy.header > div a[href] { color: %2 ! important; }\n\n"

                                       "div.fancy.header > div a[href]:hover { text-decoration: underline ! important; }\n\n"

                                       "div.fancy.header > div.spamheader {\n"
                                       "  background-color: #cdcdcd ! important;\n"
                                       "  border-top: 0px ! important;\n"
                                       "  padding: 3px ! important;\n"
                                       "  color: black ! important;\n"
                                       "  font-weight: bold ! important;\n"
                                       "  font-size: smaller ! important;\n"
                                       "}\n\n"

                                       "div.fancy.header > table.outer {\n"
                                       "  all: inherit;\n"
                                       "  width: auto ! important;\n"
                                       "  border-spacing: 0;\n"
                                       "  background-color: %4 ! important;\n"
                                       "  color: %3 ! important;\n"
                                       "  border-bottom: solid %3 1px ! important;\n"
                                       "  border-left: solid %3 1px ! important;\n"
                                       "  border-right: solid %3 1px ! important;\n"
                                       "}\n\n"
                                       ).arg(pal.color(QPalette::Highlight).name(),
                                             pal.color(QPalette::HighlightedText).name(),
                                             pal.color(QPalette::WindowText).name(),
                                             pal.color(QPalette::Window).name());
    return val;
}

QString FancyHeaderStylePlugin::extraPrintCss(const QString &headerFont) const
{
    Q_UNUSED(headerFont);
    const QPalette &pal = QApplication::palette();
    const QString val = QStringLiteral("div.fancy.header > div {\n"
                                       "  background-color: %1 ! important;\n"
                                       "  color: %2 ! important;\n"
                                       "  padding: 4px ! important;\n"
                                       "  border: solid %2 1px ! important;\n"
                                       "  line-height: normal;\n"
                                       "}\n\n"

                                       "div.fancy.header > div a[href] { color: %2 ! important; }\n\n"

                                       "div.fancy.header > table.outer{\n"
                                       "  all: inherit;\n"
                                       "  width: auto ! important;\n"
                                       "  border-spacing: 0;\n"
                                       "  background-color: %1 ! important;\n"
                                       "  color: %2 ! important;\n"
                                       "  border-bottom: solid %2 1px ! important;\n"
                                       "  border-left: solid %2 1px ! important;\n"
                                       "  border-right: solid %2 1px ! important;\n"
                                       "}\n\n"
                                       ).arg(pal.color(QPalette::Window).name(),
                                             pal.color(QPalette::WindowText).name());
    return val;
}

QString FancyHeaderStylePlugin::extraCommonCss(const QString &headerFont) const
{
    const QPalette &pal = QApplication::palette();
    const QString val = QStringLiteral(
        "div.fancy.header table {\n"
        "  width: 100% ! important;\n"
        "   table-layout: auto;\n"
        "  border-width: 0px ! important;\n"
        "  line-height: normal;\n"
        "}\n\n"

        "div.fancy.header > div {\n"
        "  font-weight: bold ! important;\n"
        "  padding: 4px ! important;\n"
        "  line-height: normal;\n"
        "}\n\n"

        "div.fancy.header table {\n"
        "  padding: 2px ! important;\n"
        "  text-align: left ! important;\n"
        "  border-collapse: separate ! important;\n"
        "}\n\n"

        "div.fancy.header table th {\n"
        "  %3\n"
        "  padding: 0px ! important;\n"
        "  white-space: nowrap ! important;\n"
        "  border-spacing: 0px ! important;\n"
        "  text-align: left ! important;\n"
        "  vertical-align: top ! important;\n"
        "  background-color: %1 ! important;\n"
        "  color: %2 ! important;\n"
        "  border: 1px ! important;\n"

        "}\n\n"

        "div.fancy.header table td {\n"
        "  %3\n"
        "  padding: 0px ! important;\n"
        "  border-spacing: 0px ! important;\n"
        "  text-align: left ! important;\n"
        "  vertical-align: top ! important;\n"
        "  width: 100% ! important;\n"
        "  background-color: %1 ! important;\n"
        "  color: %2 ! important;\n"
        "  border: 1px ! important;\n"
        "}\n\n"

        "div.fancy.header table a:hover {\n"
        "  background-color: transparent ! important;\n"
        "}\n\n")
                        .arg(pal.color(QPalette::Window).name())
                        .arg(pal.color(QPalette::WindowText).name())
                        .arg(headerFont);
    return val;
}

#include "fancyheaderstyleplugin.moc"
