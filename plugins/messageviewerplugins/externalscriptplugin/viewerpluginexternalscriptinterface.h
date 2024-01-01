/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
class QActionGroup;
namespace MessageViewer
{
class ViewerPluginExternalscriptInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginExternalscriptInterface() override;

    [[nodiscard]] QList<QAction *> actions() const override;
    [[nodiscard]] ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;
    void execute() override;

    void setText(const QString &text) override;
    void setMessage(const KMime::Message::Ptr &msg) override;
    void refreshActionList(KActionCollection *ac) override;
    void setMessageItem(const Akonadi::Item &item) override;
private Q_SLOTS:
    void slotScriptActivated(QAction *act);

Q_SIGNALS:
    void configChanged();

private:
    void createAction(KActionCollection *ac);
    void clear();
    void slotConfigure();
    QList<QAction *> mAction;
    [[nodiscard]] QStringList adaptArguments(const QStringList &scriptArguments);
    QStringList mCurrentInfo;
    QString mText;
    QString mAkonadiUrl;
    KMime::Message::Ptr mMessage;
    QActionGroup *mActionGroup = nullptr;
};
}
