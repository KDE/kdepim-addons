/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

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

#ifndef ShortUrlWidgetNg_H
#define ShortUrlWidgetNg_H

#include <QWidget>

class KLineEdit;
class QPushButton;
class QLabel;
class QLineEdit;
namespace KPIM {
class ProgressIndicatorLabel;
}

class ShortUrlEngineInterface;
class ShortUrlWidgetNg : public QWidget
{
    Q_OBJECT
public:
    explicit ShortUrlWidgetNg(QWidget *parent = nullptr);
    ~ShortUrlWidgetNg();

    void setStandalone(bool b);
public Q_SLOTS:
    void settingsUpdated();

Q_SIGNALS:
    void toolsWasClosed();
    void insertText(const QString &Url);

private:
    void slotConvertUrl();
    void slotPasteToClipboard();
    void slotOriginalUrlChanged(const QString &text);
    void slotShortUrlChanged(const QString &text);
    void slotShortUrlDone(const QString &url);
    void slotShortUrlFailed(const QString &errMsg);
    void slotCloseWidget();
    void slotConfigure();
    void slotInsertShortUrl();
    void slotOpenShortUrl();
    void initializePlugins();
    void loadEngine();
    QLabel *mShorturlServiceName;
    KLineEdit *mOriginalUrl;
    QLineEdit *mShortUrl;
    QPushButton *mConvertButton;
    QPushButton *mCopyToClipboard;
    QPushButton *mInsertShortUrl;
    QPushButton *mOpenShortUrl;
    KPIM::ProgressIndicatorLabel *mIndicatorLabel;
    QHash<QString, ShortUrlEngineInterface *> mLstInterface;
    ShortUrlEngineInterface *mCurrentEngine;
};

#endif // ShortUrlWidgetNg_H
