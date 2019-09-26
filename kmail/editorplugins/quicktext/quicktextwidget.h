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

#ifndef QUICKTEXTWIDGET_H
#define QUICKTEXTWIDGET_H

#include <QWidget>
#include "quicktext_export.h"
class QuicktextTreeWidget;
namespace MailCommon {
class SnippetWidget;
}
class QuicktextManager;
class QUICKTEXT_EXPORT QuickTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuickTextWidget(QWidget *parent = nullptr);
    ~QuickTextWidget();

    void save();
private:
    enum class EditMode {
        AddSnippet,
        EditSnippet,
        AddGroup,
        EditGroup,
        Unknown
    };
    void addSnippet();
    void editSnippet();
    void addSnippetGroup();
    void editSnippetGroup();

    void saveAddSnippet();
    void saveEditSnippet();
    void saveAddGroup();
    void saveEditGroup();



    EditMode mMode = EditMode::Unknown;

    QuicktextTreeWidget *mTreeWidget = nullptr;
    MailCommon::SnippetWidget *mSnippetWidget = nullptr;
    QuicktextManager *mSnippetsManager = nullptr;
};

#endif // QUICKTEXTWIDGET_H
