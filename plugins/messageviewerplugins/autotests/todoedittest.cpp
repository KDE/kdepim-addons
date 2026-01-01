/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "todoedittest.h"
#include "../createtodoplugin/todoedit.h"
#include <Akonadi/Collection>
#include <Akonadi/CollectionComboBox>
#include <Akonadi/EntityTreeModel>
#include <KMessageWidget>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTest>
#include <messageviewer/globalsettings_messageviewer.h>
#include <qtestkeyboard.h>
#include <qtestmouse.h>

#include <QLineEdit>
#include <QShortcut>
#include <QSignalSpy>

namespace MessageViewer
{
extern MESSAGEVIEWER_EXPORT QAbstractItemModel *_k_todoEditStubModel;
}

TodoEditTest::TodoEditTest()
{
    qRegisterMetaType<Akonadi::Collection>();
    qRegisterMetaType<std::shared_ptr<KMime::Message>>();
    qRegisterMetaType<KCalendarCore::Todo::Ptr>();
    QStandardPaths::setTestModeEnabled(true);

    auto model = new QStandardItemModel;
    for (int id = 42; id < 51; ++id) {
        Akonadi::Collection collection(id);
        collection.setRights(Akonadi::Collection::AllRights);
        collection.setName(QString::number(id));
        collection.setContentMimeTypes(QStringList() << KCalendarCore::Todo::todoMimeType());

        auto item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection), Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()), Akonadi::EntityTreeModel::CollectionIdRole);

        model->appendRow(item);
    }
    MessageViewer::_k_todoEditStubModel = model;

    // Fake a default-selected collection for shouldHaveDefaultValuesOnCreation test
    MessageViewer::MessageViewerSettingsBase::self()->setLastSelectedFolder(43);
}

void TodoEditTest::shouldHaveDefaultValuesOnCreation()
{
    MessageViewer::TodoEdit edit;
    QVERIFY(edit.collection().isValid());
    QVERIFY(!edit.message());
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    auto openEditor = edit.findChild<QPushButton *>(QStringLiteral("open-editor-button"));
    auto save = edit.findChild<QPushButton *>(QStringLiteral("save-button"));
    QVERIFY(openEditor);
    QVERIFY(save);
    QCOMPARE(openEditor->isEnabled(), false);
    QCOMPARE(save->isEnabled(), false);
    QVERIFY(noteedit);
    QCOMPARE(noteedit->text(), QString());
}

void TodoEditTest::shouldEmitCollectionChanged()
{
    MessageViewer::TodoEdit edit;
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::collectionChanged);
    edit.setCollection(Akonadi::Collection(42));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<Akonadi::Collection>(), Akonadi::Collection(42));
}

void TodoEditTest::shouldEmitMessageChanged()
{
    MessageViewer::TodoEdit edit;
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::messageChanged);
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    edit.setMessage(msg);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<std::shared_ptr<KMime::Message>>(), msg);
}

void TodoEditTest::shouldNotEmitWhenCollectionIsNotChanged()
{
    MessageViewer::TodoEdit edit;
    edit.setCollection(Akonadi::Collection(42));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::collectionChanged);
    edit.setCollection(Akonadi::Collection(42));
    QCOMPARE(spy.count(), 0);
}

void TodoEditTest::shouldNotEmitWhenMessageIsNotChanged()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    edit.setMessage(msg);
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::messageChanged);
    edit.setMessage(msg);
    QCOMPARE(spy.count(), 0);
}

void TodoEditTest::shouldHaveSameValueAfterSet()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    edit.setCollection(Akonadi::Collection(42));
    edit.setMessage(msg);
    QCOMPARE(edit.collection(), Akonadi::Collection(42));
    QCOMPARE(edit.message(), msg);
}

void TodoEditTest::shouldHaveASubject()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);

    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QVERIFY(noteedit);
    QCOMPARE(noteedit->text(), QString());

    QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");

    edit.setMessage(msg);
    edit.showToDoWidget();

    QCOMPARE(noteedit->text(), QStringLiteral("Reply to \"%1\"").arg(subject));
}

void TodoEditTest::shouldEmptySubjectWhenMessageIsNull()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    edit.setMessage(std::shared_ptr<KMime::Message>());
    QCOMPARE(noteedit->text(), QString());
}

void TodoEditTest::shouldEmptySubjectWhenMessageHasNotSubject()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    std::shared_ptr<KMime::Message> msgSubjectEmpty(new KMime::Message);
    edit.setMessage(msgSubjectEmpty);
    QCOMPARE(noteedit->text(), QString());
}

void TodoEditTest::shouldSelectLineWhenPutMessage()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QVERIFY(noteedit->hasSelectedText());
    const QString selectedText = noteedit->selectedText();
    QCOMPARE(selectedText, QStringLiteral("Reply to \"%1\"").arg(subject));
}

void TodoEditTest::shouldEmitCollectionChangedWhenChangeComboboxItem()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(akonadicombobox);
    QVERIFY(akonadicombobox->currentCollection().isValid());
}

void TodoEditTest::shouldEmitNotEmitTodoWhenTextIsEmpty()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 0);
}

void TodoEditTest::shouldEmitNotEmitTodoWhenTextTrimmedIsEmpty()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    noteedit->setText(QStringLiteral("      "));
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 0);

    noteedit->setText(QStringLiteral("      F"));
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
}

void TodoEditTest::shouldEmitTodoWhenPressEnter()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
}

void TodoEditTest::shouldTodoHasCorrectSubject()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
    auto todoPtr = spy.at(0).at(0).value<KCalendarCore::Todo::Ptr>();
    QVERIFY(todoPtr);
    QCOMPARE(todoPtr->summary(), QStringLiteral("Reply to \"%1\"").arg(subject));
}

void TodoEditTest::shouldClearAllWhenCloseWidget()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    edit.activateWindow();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);

    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    edit.slotCloseWidget();
    QCOMPARE(noteedit->text(), QString());
    QVERIFY(!edit.message());
}

void TodoEditTest::shouldEmitCollectionChangedWhenCurrentCollectionWasChanged()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    akonadicombobox->setCurrentIndex(0);
    QCOMPARE(akonadicombobox->currentIndex(), 0);
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::collectionChanged);
    akonadicombobox->setCurrentIndex(3);
    QCOMPARE(akonadicombobox->currentIndex(), 3);
    QCOMPARE(spy.count(), 1);
}

void TodoEditTest::shouldEmitCorrectCollection()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();
    akonadicombobox->setCurrentIndex(3);
    Akonadi::Collection col = akonadicombobox->currentCollection();
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(1).value<Akonadi::Collection>(), col);
}

void TodoEditTest::shouldHideWidgetWhenClickOnCloseButton()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QVERIFY(edit.isVisible());
    auto close = edit.findChild<QPushButton *>(QStringLiteral("close-button"));
    QTest::mouseClick(close, Qt::LeftButton);
    QCOMPARE(edit.isVisible(), false);
}

void TodoEditTest::shouldHideWidgetWhenPressEscape()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    // make sure the window is active so we can test for focus
    edit.activateWindow();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setFocus();
    QVERIFY(noteedit->hasFocus());
    QTest::keyPress(&edit, Qt::Key_Escape);
    QCOMPARE(edit.isVisible(), false);
}

void TodoEditTest::shouldHideWidgetWhenSaveClicked()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto save = edit.findChild<QPushButton *>(QStringLiteral("save-button"));
    QTest::mouseClick(save, Qt::LeftButton);
    QCOMPARE(edit.isVisible(), true);
}

void TodoEditTest::shouldSaveCollectionSettings()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    akonadicombobox->setCurrentIndex(3);
    const Akonadi::Collection::Id id = akonadicombobox->currentCollection().id();
    auto close = edit.findChild<QPushButton *>(QStringLiteral("close-button"));
    QTest::mouseClick(close, Qt::LeftButton);
    QCOMPARE(MessageViewer::MessageViewerSettingsBase::self()->lastSelectedFolder(), id);
}

void TodoEditTest::shouldSaveCollectionSettingsWhenCloseWidget()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    akonadicombobox->setCurrentIndex(4);
    const Akonadi::Collection::Id id = akonadicombobox->currentCollection().id();
    edit.writeConfig();
    QCOMPARE(MessageViewer::MessageViewerSettingsBase::self()->lastSelectedFolder(), id);
}

void TodoEditTest::shouldSaveCollectionSettingsWhenDeleteWidget()
{
    auto edit = new MessageViewer::TodoEdit;
    auto akonadicombobox = edit->findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    akonadicombobox->setCurrentIndex(4);
    const Akonadi::Collection::Id id = akonadicombobox->currentCollection().id();
    delete edit;
    QCOMPARE(MessageViewer::MessageViewerSettingsBase::self()->lastSelectedFolder(), id);
}

void TodoEditTest::shouldSetFocusWhenWeCallTodoEdit()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    // make sure the window is active so we can test for focus
    edit.activateWindow();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QCOMPARE(noteedit->hasFocus(), true);
    edit.setFocus();
    QCOMPARE(noteedit->hasFocus(), false);
    edit.showToDoWidget();
    QCOMPARE(noteedit->hasFocus(), true);
}

void TodoEditTest::shouldNotEmitTodoWhenMessageIsNull()
{
    MessageViewer::TodoEdit edit;
    QString subject = QStringLiteral("Test Note");
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setText(subject);
    QSignalSpy spy(&edit, &MessageViewer::TodoEdit::createTodo);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 0);
}

void TodoEditTest::shouldClearLineAfterEmitNewNote()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");

    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(noteedit->text(), QString());
}

void TodoEditTest::shouldHaveLineEditFocus()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    // make sure the window is active so we can test for focus
    edit.activateWindow();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    QCOMPARE(noteedit->hasFocus(), true);
}

void TodoEditTest::shouldShowMessageWidget()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setText(QStringLiteral("Test Note"));
    auto msgwidget = edit.findChild<KMessageWidget *>(QStringLiteral("msgwidget"));
    QCOMPARE(msgwidget->isVisible(), false);
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(msgwidget->isVisible(), true);
}

void TodoEditTest::shouldHideMessageWidget()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setText(QStringLiteral("Test note"));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto msgwidget = edit.findChild<KMessageWidget *>(QStringLiteral("msgwidget"));
    msgwidget->show();
    QCOMPARE(msgwidget->isVisible(), true);
    noteedit->setText(QStringLiteral("Another note"));
    QCOMPARE(msgwidget->isVisible(), false);
}

void TodoEditTest::shouldHideMessageWidgetWhenAddNewMessage()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setText(QStringLiteral("Test Note"));
    auto msgwidget = edit.findChild<KMessageWidget *>(QStringLiteral("msgwidget"));
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(msgwidget->isVisible(), true);

    std::shared_ptr<KMime::Message> msg2(new KMime::Message);
    msg2->subject(KMime::CreatePolicy::Create)->fromUnicodeString(QStringLiteral("Test note 2"));
    edit.setMessage(msg2);
    edit.showToDoWidget();
    QCOMPARE(msgwidget->isVisible(), false);
}

void TodoEditTest::shouldHideMessageWidgetWhenCloseWidget()
{
    MessageViewer::TodoEdit edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    noteedit->setText(QStringLiteral("Test Note"));
    auto msgwidget = edit.findChild<KMessageWidget *>(QStringLiteral("msgwidget"));
    QTest::keyClick(noteedit, Qt::Key_Enter);
    QCOMPARE(msgwidget->isVisible(), true);
    edit.slotCloseWidget();

    QCOMPARE(msgwidget->isHidden(), true);
}

void TodoEditTest::shouldEnabledSaveOpenEditorButton()
{
    MessageViewer::TodoEdit edit;
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);
    edit.showToDoWidget();

    auto noteedit = edit.findChild<QLineEdit *>(QStringLiteral("noteedit"));
    auto openEditor = edit.findChild<QPushButton *>(QStringLiteral("open-editor-button"));
    auto save = edit.findChild<QPushButton *>(QStringLiteral("save-button"));
    QCOMPARE(openEditor->isEnabled(), true);
    QCOMPARE(save->isEnabled(), true);
    noteedit->clear();

    QCOMPARE(openEditor->isEnabled(), false);
    QCOMPARE(save->isEnabled(), false);
    noteedit->setText(QStringLiteral("test 2"));
    QCOMPARE(openEditor->isEnabled(), true);
    QCOMPARE(save->isEnabled(), true);

    noteedit->setText(QStringLiteral(" "));
    QCOMPARE(openEditor->isEnabled(), false);
    QCOMPARE(save->isEnabled(), false);

    noteedit->setText(QStringLiteral(" foo"));
    QCOMPARE(openEditor->isEnabled(), true);
    QCOMPARE(save->isEnabled(), true);
}

void TodoEditTest::shouldDisabledSaveOpenEditorButtonWhenCollectionComboBoxIsEmpty()
{
    MessageViewer::TodoEdit edit;
    auto akonadicombobox = edit.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    // Create an empty combobox
    akonadicombobox->setModel(new QStandardItemModel());

    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    const QString subject = QStringLiteral("Test Note");
    msg->subject(KMime::CreatePolicy::Create)->fromUnicodeString(subject);
    msg->subject(KMime::CreatePolicy::DontCreate)->setRFC2047Charset("us-ascii");
    edit.setMessage(msg);

    auto openEditor = edit.findChild<QPushButton *>(QStringLiteral("open-editor-button"));
    auto save = edit.findChild<QPushButton *>(QStringLiteral("save-button"));
    QCOMPARE(openEditor->isEnabled(), false);
    QCOMPARE(save->isEnabled(), false);
}

QTEST_MAIN(TodoEditTest)

#include "moc_todoedittest.cpp"
