/*
  This file is part of KOrganizer.
  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2007 Loïc Corbasson <loic.corbasson@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <EventViews/CalendarDecoration>
using namespace EventViews::CalendarDecoration;

#include <KIO/Job>
#include <QUrl>
class Picoftheday : public Decoration
{
public:
    Picoftheday();
    ~Picoftheday() override;

    Q_REQUIRED_RESULT Element::List createDayElements(const QDate &) override;

    void configure(QWidget *parent) override;

    Q_REQUIRED_RESULT QString info() const override;

private:
    QSize mThumbSize;
};

class PicofthedayFactory : public DecorationFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.korganizer.Picoftheday")
public:
    Decoration *createPluginFactory() override
    {
        return new Picoftheday;
    }
};

class POTDElement : public StoredElement
{
    Q_OBJECT

public:
    POTDElement(const QString &id, QDate date, QSize initialThumbSize);
    ~POTDElement() override
    {
    }

    void setThumbnailSize(QSize size);
    /** @reimp from Element */
    QPixmap newPixmap(const QSize &size) override;

    /**
      Returns the thumbnail URL for a given width corresponding to a full-size image URL. */
    Q_REQUIRED_RESULT QUrl thumbnailUrl(const QUrl &fullSizeUrl, const int width = 0) const;

Q_SIGNALS:
    void gotNewPixmap(const QPixmap &) const;
    void gotNewShortText(const QString &) const;
    void gotNewLongText(const QString &) const;
    void gotNewUrl(const QUrl &) const;
    // The following three signals are only used internally
    void step1Success();
    void step2Success();
    void step3Success();

protected Q_SLOTS:
    void step1StartDownload();
    void step2GetImagePage();
    void step3GetThumbnail();

private:
    void step1Result(KJob *job);
    void step2Result(KJob *job);
    void step3Result(KJob *job);
    QDate mDate;
    QString mDescription;
    QSize mDlThumbSize;
    QString mFileName;
    QUrl mFullSizeImageUrl;
    float mHWRatio;
    QSize mThumbSize;
    QUrl mThumbUrl;
    bool mFirstStepCompleted = false;
    bool mSecondStepCompleted = false;
    KIO::SimpleJob *mFirstStepJob = nullptr;
    KIO::SimpleJob *mSecondStepJob = nullptr;
    KIO::SimpleJob *mThirdStepJob = nullptr;
    QTimer *mTimer = nullptr;
};

