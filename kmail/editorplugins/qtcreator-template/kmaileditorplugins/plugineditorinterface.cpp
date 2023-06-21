%
{
Cpp:
    LicenseTemplate
}

#include "%{ProjectNameLower}editorplugin_debug.h"
#include "%{ProjectNameLower}plugineditorinterface.h"
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <KPIMTextEdit/RichTextEditor>

% {CN} PluginEditorInterface::
        % {CN} PluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent){}

    % {CN} PluginEditorInterface::~ % {CN} PluginEditorInterface()
{
}

void % {CN} PluginEditorInterface::createAction(KActionCollection *ac)
{
}

void % {CN} PluginEditorInterface::exec()
{
    // TODO
}

#include "moc_plugineditorinterface.cpp"
