/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmailmarkdown_export.h"
#include <QObject>
class LIBKMAILMARKDOWN_EXPORT MarkdownConverter : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConverter(QObject *parent = nullptr);
    ~MarkdownConverter() override;
    [[nodiscard]] QString convertTextToMarkdown(const QString &str);

    [[nodiscard]] bool enableEmbeddedLabel() const;
    void setEnableEmbeddedLabel(bool enableEmbeddedLabel);

    [[nodiscard]] bool enableExtraDefinitionLists() const;
    void setEnableExtraDefinitionLists(bool enableExtraDefinitionLists);

Q_SIGNALS:
    void failed(const QString &str);

private:
    Q_DISABLE_COPY(MarkdownConverter)
    bool mEnableEmbeddedLabel = false;
    bool mEnableExtraDefinitionLists = false;
};
