/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdowninterface.h"
#include "markdownconverter.h"
#include "markdowncreateimagedialog.h"
#include "markdowncreatelinkdialog.h"
#include "markdownplugin_debug.h"
#include "markdownpreviewdialog.h"
#include "markdownutil.h"
#include <KActionCollection>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KPIMTextEdit/RichTextComposer>
#include <KPIMTextEdit/RichTextComposerControler>
#include <KSharedConfig>
#include <QAction>
#include <QMenu>

#include <MessageComposer/TextPart>

#include <MessageComposer/StatusBarLabelToggledState>

MarkdownInterface::MarkdownInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

MarkdownInterface::~MarkdownInterface() = default;

void MarkdownInterface::createAction(KActionCollection *ac)
{
    mAction = new QAction(i18nc("@action", "Generate HTML from markdown language."), this);
    mAction->setCheckable(true);
    mAction->setChecked(false);
    ac->addAction(QStringLiteral("generate_markdown"), mAction);
    connect(mAction, &QAction::triggered, this, &MarkdownInterface::slotActivated);
    MessageComposer::PluginActionType type(mAction, MessageComposer::PluginActionType::Edit);
    addActionType(type);

    mStatusBarLabel = new MessageComposer::StatusBarLabelToggledState(parentWidget());
    connect(mStatusBarLabel, &MessageComposer::StatusBarLabelToggledState::toggleModeChanged, this, [this](bool checked) {
        mAction->setChecked(checked);
        slotActivated(checked);
    });
    QFont f = mStatusBarLabel->font();
    f.setBold(true);
    mStatusBarLabel->setFont(f);
    setStatusBarWidget(mStatusBarLabel);
    mStatusBarLabel->setStateString(i18n("Markdown"), QString());

    mPopupMenuAction = new QAction(i18nc("@action", "Markdown Action"), this);

    auto mardownMenu = new QMenu(parentWidget());
    mPopupMenuAction->setMenu(mardownMenu);
    mPopupMenuAction->setEnabled(false);
    auto titleMenu = new QMenu(i18n("Add Title"), mardownMenu);
    mardownMenu->addMenu(titleMenu);
    for (int i = 1; i < 5; ++i) {
        titleMenu->addAction(i18n("Level %1", QString::number(i)), this, [this, i]() {
            addTitle(i);
        });
    }
    mardownMenu->addAction(i18n("Horizontal Rule"), this, &MarkdownInterface::addHorizontalRule);
    mardownMenu->addSeparator();
    mBoldAction = mardownMenu->addAction(i18n("Change Selected Text as Bold"), this, &MarkdownInterface::addBold);
    mBoldAction->setEnabled(false);
    mItalicAction = mardownMenu->addAction(i18n("Change Selected Text as Italic"), this, &MarkdownInterface::addItalic);
    mItalicAction->setEnabled(false);
    mCodeAction = mardownMenu->addAction(i18n("Change Selected Text as Code"), this, &MarkdownInterface::addCode);
    mCodeAction->setEnabled(false);
    mBlockQuoteAction = mardownMenu->addAction(i18n("Change Selected Text as Block Quote"), this, &MarkdownInterface::addBlockQuote);
    mBlockQuoteAction->setEnabled(false);
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
    mBlockQuoteAction->setEnabled(enabled);
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

void MarkdownInterface::addBlockQuote()
{
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.isEmpty()) {
        richTextEditor()->composerControler()->addQuotes(QStringLiteral(">"));
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

void MarkdownInterface::addTitle(int index)
{
    QString tag = QStringLiteral("#");
    for (int i = 1; i < index; ++i) {
        tag += QLatin1Char('#');
    }
    const QString selectedText = richTextEditor()->textCursor().selectedText();
    if (!selectedText.trimmed().isEmpty()) {
        richTextEditor()->textCursor().insertText(QStringLiteral("%1 %2").arg(tag, selectedText));
    } else {
        richTextEditor()->textCursor().insertText(QStringLiteral("%1 ").arg(tag));
    }
}

bool MarkdownInterface::reformatText()
{
    return false;
}

void MarkdownInterface::addEmbeddedImages(MessageComposer::TextPart *textPart, QString &textVersion, QString &htmlVersion) const
{
    QStringList listImage = MarkdownUtil::imagePaths(textVersion);
    QList<QSharedPointer<KPIMTextEdit::EmbeddedImage>> lstEmbeddedImages;
    if (!listImage.isEmpty()) {
        listImage.removeDuplicates();
        QStringList imageNameAdded;
        for (const QString &urlImage : std::as_const(listImage)) {
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
            const QString imageName = fi.baseName().isEmpty() ? QStringLiteral("image.png") : QString(fi.baseName() + QLatin1StringView(".png"));

            QString imageNameToAdd = imageName;
            int imageNumber = 1;
            while (imageNameAdded.contains(imageNameToAdd)) {
                const int firstDot = imageName.indexOf(QLatin1Char('.'));
                if (firstDot == -1) {
                    imageNameToAdd = imageName + QString::number(imageNumber++);
                } else {
                    imageNameToAdd = imageName.left(firstDot) + QString::number(imageNumber++) + imageName.mid(firstDot);
                }
            }

            QSharedPointer<KPIMTextEdit::EmbeddedImage> embeddedImage =
                richTextEditor()->composerControler()->composerImages()->createEmbeddedImage(image, imageNameToAdd);
            lstEmbeddedImages.append(embeddedImage);

            const QString newImageName = QLatin1StringView("cid:") + embeddedImage->contentID;
            const QString quote(QStringLiteral("\""));
            htmlVersion.replace(QString(quote + urlImage + quote), QString(quote + newImageName + quote));
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
    // It can't work on html email
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
    KConfigGroup grp(KSharedConfig::openConfig(), QStringLiteral("Markdown"));

    mEnableEmbeddedLabel = grp.readEntry("Enable Embedded Latex", false);
    mEnableExtraDefinitionLists = grp.readEntry("Enable Extra Definition Lists", false);
}

void MarkdownInterface::slotActivated(bool checked)
{
    if (mDialog.isNull()) {
        mDialog = new MarkdownPreviewDialog(parentWidget());
        mDialog->setText(richTextEditor()->toPlainText());
        connect(richTextEditor(), &TextCustomEditor::RichTextEditor::textChanged, this, [this]() {
            if (mDialog) {
                mDialog->setText(richTextEditor()->toPlainText());
            }
        });
    }
    mStatusBarLabel->setToggleMode(checked);
    if (checked) {
        mDialog->show();
    } else {
        mDialog->hide();
    }
    mPopupMenuAction->setEnabled(checked);
}

#include "moc_markdowninterface.cpp"
