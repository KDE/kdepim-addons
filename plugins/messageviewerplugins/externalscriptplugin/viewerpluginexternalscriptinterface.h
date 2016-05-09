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

#ifndef VIEWERPLUGINEXTERNALSCRIPTINTERFACE_H
#define VIEWERPLUGINEXTERNALSCRIPTINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
class KActionCollection;
namespace MessageViewer
{

class ViewerPluginExternalscriptInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent = Q_NULLPTR);
    ~ViewerPluginExternalscriptInterface();

    QList<QAction *> actions() const Q_DECL_OVERRIDE;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;

    void setText(const QString &text) Q_DECL_OVERRIDE;
    void setMessage(const KMime::Message::Ptr &msg) Q_DECL_OVERRIDE;
private Q_SLOTS:
    void slotScriptActivated(QAction *act);

private:
    void createAction(KActionCollection *ac);
    void clear();
    QList<QAction *> mAction;
    QStringList adaptArguments(const QStringList &scriptArguments);
    QStringList mCurrentInfo;
    QString mSelectedText;
    KMime::Message::Ptr mMessage;
};
}
#endif // VIEWERPLUGINEXTERNALSCRIPTINTERFACE_H
