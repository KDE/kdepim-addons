/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATEIMAGEWIDGETTEST_H
#define MARKDOWNCREATEIMAGEWIDGETTEST_H

#include <QObject>

class MarkdownCreateImageWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageWidgetTest(QObject *parent = nullptr);
    ~MarkdownCreateImageWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldGenerateLink();
    void shouldChangeState();
    void shouldAddSize();
    void shouldEmitSignal();
};

#endif // MARKDOWNCREATEIMAGEWIDGETTEST_H
