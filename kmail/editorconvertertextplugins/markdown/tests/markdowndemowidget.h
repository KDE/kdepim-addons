/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNDEMOWIDGET_H
#define MARKDOWNDEMOWIDGET_H

#include <QWidget>
class QTextEdit;
class MarkdownPreviewWidget;
class MarkdownDemoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownDemoWidget(QWidget *parent = nullptr);
    ~MarkdownDemoWidget() = default;

private:
    QTextEdit *mEdit = nullptr;
    MarkdownPreviewWidget *mPreview = nullptr;
};

#endif // MARKDOWNDEMOWIDGET_H
