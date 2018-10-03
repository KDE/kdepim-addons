%{Cpp:LicenseTemplate}\
		
#include "%{CN}plugineditorinterface.h"
#include "%{CN}editorplugin_debug.h"
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <KLocalizedString>
#include <QAction>

%{CN}PluginEditorInterface::%{CN}PluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

%{CN}PluginEditorInterface::~%{CN}PluginEditorInterface()
{
}

void %{CN}PluginEditorInterface::createAction(KActionCollection *ac)
{
}

void %{CN}PluginEditorInterface::exec()
{
    //TODO
}
