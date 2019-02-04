/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammarresultjob.h"
#include "grammalecteplugin_debug.h"
#include <QProcess>

GrammarResultJob::GrammarResultJob(QObject *parent)
    : QObject(parent)
{

}

GrammarResultJob::~GrammarResultJob()
{

}

void GrammarResultJob::start()
{
    if (canStart()) {
        //TODO
    } else {
        qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Impossible to start grammarresultjob";
        Q_EMIT error();
        deleteLater();
    }
}

static bool hasNotEmptyText(const QString &text)
{
    for (int i = 0; i < text.length(); ++i) {
        if (!text.at(i).isSpace()) {
            return true;
        }
    }
    return false;
}

bool GrammarResultJob::canStart() const
{
    if (hasNotEmptyText(mText)) {
        return true;
    }
    return false;
}

QString GrammarResultJob::text() const
{
    return mText;
}

void GrammarResultJob::setText(const QString &text)
{
    mText = text;
}
