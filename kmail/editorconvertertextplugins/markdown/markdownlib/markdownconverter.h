/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNCONVERTER_H
#define MARKDOWNCONVERTER_H

#include <QObject>
#include "libkmailmarkdown_export.h"
class LIBKMAILMARKDOWN_EXPORT MarkdownConverter : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConverter(QObject *parent = nullptr);
    ~MarkdownConverter() override;
    Q_REQUIRED_RESULT QString convertTextToMarkdown(const QString &str);

    Q_REQUIRED_RESULT bool enableEmbeddedLabel() const;
    void setEnableEmbeddedLabel(bool enableEmbeddedLabel);

    Q_REQUIRED_RESULT bool enableExtraDefinitionLists() const;
    void setEnableExtraDefinitionLists(bool enableExtraDefinitionLists);

Q_SIGNALS:
    void failed(const QString &str);

private:
    Q_DISABLE_COPY(MarkdownConverter)
    bool mEnableEmbeddedLabel = false;
    bool mEnableExtraDefinitionLists = false;
};

#endif // MARKDOWNCONVERTER_H
