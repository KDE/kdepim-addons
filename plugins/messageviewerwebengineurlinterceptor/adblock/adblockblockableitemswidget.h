/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#ifndef ADBLOCKBLOCKABLEITEMSWIDGET_H
#define ADBLOCKBLOCKABLEITEMSWIDGET_H

#include <QWidget>
namespace PimCommon
{
class CustomTreeView;
}
class QWebEngineView;
class AdBlockBlockableItemsWidget : public QWidget
{
    Q_OBJECT
public:
    enum TypeElement {
        None = 0,
        Image,
        Script,
        StyleSheet,
        Font,
        Frame,
        XmlRequest,
        Object,
        Media,
        Popup,

        MaxTypeElement
    };

    explicit AdBlockBlockableItemsWidget(QWidget *parent = Q_NULLPTR);
    ~AdBlockBlockableItemsWidget();

    void setWebEngineView(QWebEngineView *view);

    QString elementType(AdBlockBlockableItemsWidget::TypeElement type);
    QString elementTypeToI18n(AdBlockBlockableItemsWidget::TypeElement type);
private Q_SLOTS:
    void customContextMenuRequested(const QPoint &);
    void slotCopyFilterItem();
    void slotOpenItem();
    void slotBlockItem();
    void slotCopyItem();
    void handleSearchBlockableImageItems(const QVariant &var);
    void handleSearchBlockableScriptsItems(const QVariant &var);
private:
    enum BlockType {
        FilterValue = 0,
        Url,
        Type
    };
    enum TypeItem {
        Element = Qt::UserRole + 1
    };

    void writeConfig();
    void searchBlockableItems();
    void readConfig();
    void adaptSrc(QString &src, const QString &hostName);
    PimCommon::CustomTreeView *mListItems;
    QWebEngineView *mWebEngineView;
};

#endif // ADBLOCKBLOCKABLEITEMSWIDGET_H
