%{Cpp:LicenseTemplate}\
		
#include "sharetextplugineditorinterface.h"
#include "sharetexteditorplugin_debug.h"
#include "sharetextpurposemenuwidget.h"
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <KLocalizedString>
#include <QAction>

ShareTextPluginEditorInterface::ShareTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

ShareTextPluginEditorInterface::~ShareTextPluginEditorInterface()
{
}

void ShareTextPluginEditorInterface::createAction(KActionCollection *ac)
{
}

void ShareTextPluginEditorInterface::exec()
{
    //Nothing
}
