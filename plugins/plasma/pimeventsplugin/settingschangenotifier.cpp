#include "settingschangenotifier.h"
#include "pimeventsplugin_debug.h"

#include <QCoreApplication>

#define APP_PROPERTY_NAME "PIMEventsPluginSettingsChangeNotifier"

SettingsChangeNotifier *SettingsChangeNotifier::self()
{
    // We can't easilly use a global static (or a static member) to store the
    // global instance of SettingsChangeNotifier. We need the same instance to
    // be accessible by both PimEventsPlugin and PimCalendarsPlugin so I would
    // have to put this class to a .so and link it from both to get a
    // singleton that actually works across the plugins. But being the lazy
    // bastard that I am I decided to just abuse QObject::property() and the qApp
    // singleton which already comes from an .so linked by both plugins.
    //
    // Also note the cast to quintptr: we have the same problem as above with
    // SettingsChangeNotifier::staticMetaObject as each "copy" of the class
    // has its own instance of it, which causes  pointer comparision in
    // QMetaObject::inherits() to fail. This leads to v.isValid() being true but
    // v.value<SettingsChangeNotifier*>() returning a null pointer, because
    // the internal qobject_cast fails.
    //
    // Yeah, I could have totally spent 30 seconds of my time and write the 6
    // lines of CMake code to get my own .so and have it linked from both plugins,
    // but instead I decided to explain myself in this comment, probably because
    // short code with long comments makes it look like I know what I'm doing.
    const QVariant v = qApp->property(APP_PROPERTY_NAME);
    if (v.isValid()) {
        return reinterpret_cast<SettingsChangeNotifier*>(v.value<quintptr>());
    }

    SettingsChangeNotifier *notifier = new SettingsChangeNotifier();
    qApp->setProperty(APP_PROPERTY_NAME, reinterpret_cast<quintptr>(notifier));
    return notifier;
}

SettingsChangeNotifier::SettingsChangeNotifier(QObject *parent)
    : QObject(parent)
{
    qCDebug(PIMEVENTSPLUGIN_LOG) << this << "created";
}

SettingsChangeNotifier::~SettingsChangeNotifier()
{
}

void SettingsChangeNotifier::notifySettingsChanged()
{
    Q_EMIT settingsChanged();
}
