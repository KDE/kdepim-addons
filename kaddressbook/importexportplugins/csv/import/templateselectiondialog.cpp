/*
  This file is part of KAddressBook.
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateselectiondialog.h"

#include <KConfig>
#include <KLocalizedString>
#include <KMessageBox>
#include <QDir>
#include <QIcon>
#include <QStandardPaths>
#include <QVBoxLayout>

#include <KConfigGroup>
#include <QAbstractTableModel>
#include <QDialogButtonBox>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QListView>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyledItemDelegate>

using TemplateInfo = struct TemplateInfo {
    QString displayName;
    QString fileName;
    bool isDeletable = false;
};

class TemplatesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TemplatesModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent)
    {
        update();
    }

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (!parent.isValid()) {
            return mTemplates.count();
        } else {
            return 0;
        }
    }

    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (!parent.isValid()) {
            return 2;
        } else {
            return 0;
        }
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || index.row() >= mTemplates.count() || index.column() >= 2) {
            return {};
        }

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) {
                return mTemplates[index.row()].displayName;
            } else {
                return mTemplates[index.row()].fileName;
            }
        }

        if (role == Qt::UserRole) {
            return mTemplates[index.row()].isDeletable;
        }

        return {};
    }

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override
    {
        if (parent.isValid() || row < 0 || row >= mTemplates.count()) {
            return false;
        }

        beginRemoveRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i) {
            if (!QFile::remove(mTemplates[row].fileName)) {
                return false;
            }
            mTemplates.removeAt(row);
        }

        endRemoveRows();
        return true;
    }

    void update()
    {
        beginResetModel();
        mTemplates.clear();
        const QStringList dirs =
            QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("/kaddressbook/csv-templates/"), QStandardPaths::LocateDirectory);
        for (const QString &dir : dirs) {
            const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.desktop"));
            for (const QString &file : fileNames) {
                const QString fileName = dir + QLatin1Char('/') + file;

                KConfig config(fileName, KConfig::SimpleConfig);

                if (!config.hasGroup(QLatin1String("csv column map"))) {
                    continue;
                }

                KConfigGroup group(&config, QStringLiteral("Misc"));
                TemplateInfo info;
                info.displayName = group.readEntry("Name");
                info.fileName = fileName;

                const QFileInfo fileInfo(info.fileName);
                info.isDeletable = QFileInfo(fileInfo.absolutePath()).isWritable();

                mTemplates.append(info);
            }
        }
        endResetModel();
    }

    [[nodiscard]] bool templatesAvailable() const
    {
        return !mTemplates.isEmpty();
    }

private:
    QList<TemplateInfo> mTemplates;
};

class TemplateSelectionDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TemplateSelectionDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
        , mIcon(QIcon::fromTheme(QStringLiteral("list-remove")))
    {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        if (index.data(Qt::UserRole).toBool()) {
            mIcon.paint(painter, option.rect, Qt::AlignRight);
        }
    }

    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QSize hint = QStyledItemDelegate::sizeHint(option, index);

        if (index.data(Qt::UserRole).toBool()) {
            hint.setWidth(hint.width() + 16);
        }

        return hint;
    }

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override
    {
        if (event->type() == QEvent::MouseButtonRelease && index.data(Qt::UserRole).toBool()) {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QRect buttonRect = option.rect;
            buttonRect.setLeft(buttonRect.right() - 16);

            if (buttonRect.contains(mouseEvent->pos())) {
                const QString templateName = index.data(Qt::DisplayRole).toString();
                const int answer = KMessageBox::questionTwoActions(nullptr,
                                                                   i18nc("@label", "Do you really want to delete template '%1'?", templateName),
                                                                   QString(),
                                                                   KStandardGuiItem::del(),
                                                                   KStandardGuiItem::cancel());
                if (answer == KMessageBox::ButtonCode::PrimaryAction) {
                    model->removeRows(index.row(), 1);
                    return true;
                }
            }
        }

        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

private:
    const QIcon mIcon;
};

TemplateSelectionDialog::TemplateSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Template Selection"));
    auto mainLayout = new QVBoxLayout(this);

    auto lab = new QLabel(i18nc("@info", "Please select a template, that matches the CSV file:"), this);
    mainLayout->addWidget(lab);

    mView = new QListView(this);
    mainLayout->addWidget(mView);

    mView->setModel(new TemplatesModel(this));
    mView->setItemDelegate(new TemplateSelectionDelegate(this));

    connect(mView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TemplateSelectionDialog::updateButtons);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setDefault(true);
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TemplateSelectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TemplateSelectionDialog::reject);
    mOkButton->setEnabled(false);
    mainLayout->addWidget(buttonBox);
}

bool TemplateSelectionDialog::templatesAvailable() const
{
    return static_cast<TemplatesModel *>(mView->model())->templatesAvailable();
}

QString TemplateSelectionDialog::selectedTemplate() const
{
    const QModelIndex rowIndex = mView->currentIndex();
    const QModelIndex index = mView->model()->index(rowIndex.row(), 1);

    return index.data(Qt::DisplayRole).toString();
}

void TemplateSelectionDialog::updateButtons()
{
    mOkButton->setEnabled(mView->currentIndex().isValid());
}

#include "templateselectiondialog.moc"

#include "moc_templateselectiondialog.cpp"
