/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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

#include "markdowninterface.h"
#include "markdownpreviewdialog.h"
#include "markdownplugin_debug.h"
#include "markdownconverter.h"
#include "markdowncreatelinkdialog.h"
#include "markdownutil.h"
#include "markdowncreateimagedialog.h"
#include <KPIMTextEdit/RichTextComposer>
#include <KPIMTextEdit/RichTextComposerControler>
#include <KLocalizedString>
#include <QAction>
#include <KActionCollection>
#include <KSharedConfig>
#include <KConfigGroup>
#include <QPointer>
#include <QLabel>
#include <QMenu>

#include <QTextCursor>
#include <MessageComposer/TextPart>

MarkdownInterface::MarkdownInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

MarkdownInterface::~MarkdownInterface()
{
}

void MarkdownInterface::createAction(KActionCollection *ac)
{
    mAction = new QAction(i18n("Generate HTML from markdown language."), this);
    mAction->setCheckable(true);
    mAction->setChecked(false);
    ac->addAction(QStringLiteral("generate_markdown"), mAction);
    connect(mAction, &QAction::triggered, this, &MarkdownInterface::slotActivated);
    MessageComposer::PluginActionType type(mAction, MessageComposer::PluginActionType::Edit);
    addActionType(type);

    mStatusBarLabel = new QLabel;
    QFont f = mStatusBarLabel->font();
    f.setBold(true);
    mStatusBarLabel->setFont(f);
    setStatusBarWidget(mStatusBarLabel);

    mPopupMenuAction = new QAction(i18n("Markdown Action"), this);

    QMenu *mardownMenu = new QMenu;
    mPopupMenuAction->setMenu(mardownMenu);
    mPopupMenuAction->setEnabled(false);
    mardownMenu->addAction(i18n("Add Title"), this, &MarkdownInterface::addTitle);
    mardownMenu->addAction(i18n("Horizontal Rule"), this, &MarkdownInterface::addHorizontalRule);
    mardownMenu->addSeparator();
    mBoldAction = mardownMenu->addAction(i18n("Change Selected Text as Bold"), this, &MarkdownInterface::addBold);
    mBoldAction->setEnabled(false);
    mItalicAction = mardownMenu->addAction(i18n("Change Selected Text as Italic"), this, &MarkdownInterface::addItalic);
    mItalicAction->setEnabled(false);
    mCodeAction = mardownMenu->addAction(i18n("Change Selected Text as Code"), this, &MarkdownInterface::addCode);
    mCodeAction->setEnabled(false);
    mardownMenu->addSeparator();
    mardownMenu->addAction(i18n("Add Link"), this, &MarkdownInterface::addLink);
    mardownMenu->addAction(i18n("Add Image"), this, &MarkdownInterface::addImage);
    MessageComposer::PluginActionType typePopup(mPopupMenuAction, MessageComposer::PluginActionType::PopupMenu);
    addActionType(typePopup);
    connect(richTextEditor(), &KPIMTextEdit::RichTextComposer::selectionChanged, this, &MarkdownInterface::slotSelectionChanged);
}

void MarkdownInterface::slotSelectionChanged()
{
    const bool enabled = richTextEditor()->textCursor().hasSelection();
    mBoldAction->setEnabled(enabled);
    mItalicAction->setEnabled(enabled);
    mCodeAction->setEnabled(enabled);
}

void MarkdownInterface::addHorizontalRule()
{
    richTextEditor()->insertPlainText(QStringLiteral("\n---"));
}

void MarkdownInterface::addBold()
{
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.isEmpty()) {
        richTextEditor()->textCursor().insertText(QStringLiteral("**%1**").arg(selectedText));
    } else {
        qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Any text selected";
    }
}

void MarkdownInterface::addCode()
{
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.isEmpty()) {
        richTextEditor()->textCursor().insertText(QStringLiteral("`%1`").arg(selectedText));
    } else {
        qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Any text selected";
    }
}

void MarkdownInterface::addItalic()
{
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.isEmpty()) {
        richTextEditor()->textCursor().insertText(QStringLiteral("_%1_").arg(selectedText));
    } else {
        qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Any text selected";
    }
}

void MarkdownInterface::addLink()
{
    QPointer<MarkdownCreateLinkDialog> dlg = new MarkdownCreateLinkDialog(parentWidget());
    if (dlg->exec()) {
        const QString str = dlg->linkStr();
        if (!str.isEmpty()) {
            richTextEditor()->textCursor().insertText(str);
        }
    }
    delete dlg;
}

void MarkdownInterface::addImage()
{
    QPointer<MarkdownCreateImageDialog> dlg = new MarkdownCreateImageDialog(parentWidget());
    if (dlg->exec()) {
        const QString str = dlg->linkStr();
        if (!str.isEmpty()) {
            richTextEditor()->textCursor().insertText(str);
        }
    }
    delete dlg;
}

void MarkdownInterface::addTitle()
{
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.isEmpty()) {
        richTextEditor()->textCursor().insertText(QStringLiteral("#%1#").arg(selectedText));
    } else {
        richTextEditor()->textCursor().insertText(QStringLiteral("# #"));
    }
}

bool MarkdownInterface::reformatText()
{
    return false;
}

void MarkdownInterface::addEmbeddedImages(MessageComposer::TextPart *textPart, QString &textVersion, QString &htmlVersion) const
{
    QStringList listImage = MarkdownUtil::imagePaths(textVersion);
    QList< QSharedPointer<KPIMTextEdit::EmbeddedImage> > lstEmbeddedImages;
    if (!listImage.isEmpty()) {
        listImage.removeDuplicates();
        QStringList imageNameAdded;
        for (const QString &urlImage : listImage) {
            const QUrl url = QUrl::fromUserInput(urlImage);
            if (!url.isLocalFile()) {
                qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Url is not a local file " << url;
                continue;
            }
            QImage image;
            if (!image.load(urlImage)) {
                qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Impossible to load " << urlImage;
                continue;
            }
            const QFileInfo fi(urlImage);
            const QString imageName
                = fi.baseName().isEmpty()
                  ? QStringLiteral("image.png")
                  : QString(fi.baseName() + QLatin1String(".png"));

            QString imageNameToAdd = imageName;
            int imageNumber = 1;
            while (imageNameAdded.contains(imageNameToAdd)) {
                const int firstDot = imageName.indexOf(QLatin1Char('.'));
                if (firstDot == -1) {
                    imageNameToAdd = imageName + QString::number(imageNumber++);
                } else {
                    imageNameToAdd = imageName.left(firstDot) + QString::number(imageNumber++)
                                     +imageName.mid(firstDot);
                }
            }

            QSharedPointer<KPIMTextEdit::EmbeddedImage> embeddedImage = richTextEditor()->composerControler()->composerImages()->createEmbeddedImage(image, imageNameToAdd);
            lstEmbeddedImages.append(embeddedImage);

            const QString newImageName = QLatin1String("cid:") + embeddedImage->contentID;
            const QString quote(QStringLiteral("\""));
            htmlVersion.replace(QString(quote + urlImage + quote),
                                QString(quote + newImageName + quote));
            textVersion.replace(urlImage, newImageName);
            imageNameAdded << imageNameToAdd;
        }
        if (!lstEmbeddedImages.isEmpty()) {
            textPart->setEmbeddedImages(lstEmbeddedImages);
        }
    }
}

MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus MarkdownInterface::convertTextToFormat(MessageComposer::TextPart *textPart)
{
    //It can't work on html email
    if (richTextEditor()->composerControler()->isFormattingUsed()) {
        qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "We can't convert html email";
        return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
    }
    if (mAction->isChecked()) {
        QString textVersion = richTextEditor()->composerControler()->toCleanPlainText();
        if (!textVersion.isEmpty()) {
            MarkdownConverter converter;
            converter.setEnableEmbeddedLabel(mEnableEmbeddedLabel);
            converter.setEnableExtraDefinitionLists(mEnableExtraDefinitionLists);
            QString result = converter.convertTextToMarkdown(textVersion);
            if (!result.isEmpty()) {
                addEmbeddedImages(textPart, textVersion, result);
                textPart->setCleanPlainText(textVersion);

                textPart->setWrappedPlainText(textVersion);
                textPart->setCleanHtml(result);
                return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::Converted;
            } else {
                qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Impossible to convert text";
                return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::Error;
            }
        } else {
            qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "empty text! Bug ?";
            return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
        }
    }
    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
}

void MarkdownInterface::enableDisablePluginActions(bool richText)
{
    if (mAction) {
        mAction->setEnabled(!richText);
        mPopupMenuAction->setEnabled(!richText && mAction->isChecked());
    }
}

void MarkdownInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Markdown");

    mEnableEmbeddedLabel = grp.readEntry("Enable Embedded Latex", false);
    mEnableExtraDefinitionLists = grp.readEntry("Enable Extra Definition Lists", false);
}

void MarkdownInterface::slotActivated(bool checked)
{
    if (mDialog.isNull()) {
        mDialog = new MarkdownPreviewDialog(parentWidget());
        mDialog->setText(richTextEditor()->toPlainText());
        connect(richTextEditor(), &KPIMTextEdit::RichTextEditor::textChanged, this, [this]() {
            if (mDialog) {
                mDialog->setText(richTextEditor()->toPlainText());
            }
        });
    }
    if (checked) {
        mDialog->show();
    } else {
        mDialog->hide();
    }
    mStatusBarLabel->setText(checked ? i18n("Markdown") : QString());
    mPopupMenuAction->setEnabled(checked);
}
