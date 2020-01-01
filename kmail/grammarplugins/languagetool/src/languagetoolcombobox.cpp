/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#include "languagetoolcombobox.h"
#include "languageinfo.h"
#include <KLocalizedString>

LanguageToolComboBox::LanguageToolComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fillComboBox();
}

LanguageToolComboBox::~LanguageToolComboBox()
{
}

void LanguageToolComboBox::fillComboBox(const QVector<LanguageInfo> &info)
{
    clear();
    for (int i = 0; i < info.count(); ++i) {
        const LanguageInfo infoLang = info.at(i);
        addItem(infoLang.name(), infoLang.code());
    }
}

void LanguageToolComboBox::fillComboBox()
{
    //TODO add more
    addItem(i18n("French"), QStringLiteral("fr"));
    addItem(i18n("English"), QStringLiteral("en"));
    addItem(i18n("Asturian"), QStringLiteral("ast"));
    addItem(i18n("Belarusian"), QStringLiteral("be"));
    addItem(i18n("Breton"), QStringLiteral("br"));
    addItem(i18n("Catalan"), QStringLiteral("ca"));
    addItem(i18n("Chinese"), QStringLiteral("zh"));
    addItem(i18n("Danish"), QStringLiteral("da"));
    addItem(i18n("Dutch"), QStringLiteral("nl"));
    addItem(i18n("English (Australian)"), QStringLiteral("en-AU"));
    addItem(i18n("English (Canadian)"), QStringLiteral("en-CA"));
    addItem(i18n("Esperanto"), QStringLiteral("eo"));
    addItem(i18n("Galician"), QStringLiteral("gl"));
    addItem(i18n("German"), QStringLiteral("de"));
    addItem(i18n("Greek"), QStringLiteral("el"));
    addItem(i18n("Italian"), QStringLiteral("it"));
    addItem(i18n("Japanese"), QStringLiteral("ja"));
    addItem(i18n("Khmer"), QStringLiteral("km"));
    addItem(i18n("Persian"), QStringLiteral("fa"));
    addItem(i18n("Polish"), QStringLiteral("pl"));
    addItem(i18n("Portuguese"), QStringLiteral("pt"));
    addItem(i18n("Romanian"), QStringLiteral("ro"));
    addItem(i18n("Russian"), QStringLiteral("ru"));
    addItem(i18n("Slovak"), QStringLiteral("sk"));
    addItem(i18n("Slovenian"), QStringLiteral("sl"));
    addItem(i18n("Spanish"), QStringLiteral("es"));
    addItem(i18n("Swedish"), QStringLiteral("sv"));
    addItem(i18n("Tagalog"), QStringLiteral("tl"));
    addItem(i18n("Tamil"), QStringLiteral("ta"));
    addItem(i18n("Ukrainian"), QStringLiteral("uk-UA"));
}

void LanguageToolComboBox::setLanguage(const QString &str)
{
    const int pos = findData(str);
    if (pos != -1) {
        setCurrentIndex(pos);
    }
}

QString LanguageToolComboBox::language() const
{
    return currentData().toString();
}
