/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "grammarcommon_export.h"
#include "grammarerror.h"

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>

#include <QTextFormat>

namespace GrammarResultUtil
{
enum TextInfo {
    ReplaceFormatInfo = QTextFormat::UserProperty + 1,
};
GRAMMARCOMMON_EXPORT void applyGrammarResult(const QVector<GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor);
GRAMMARCOMMON_EXPORT void replaceWord(const MessageComposer::PluginGrammarAction &act, const QString &replacementWord, QTextDocument *document);
}
