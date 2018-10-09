%{Cpp:LicenseTemplate}\

#include "%{ProjectNameLower}plugineditor.h"
#include "%{ProjectNameLower}plugineditorinterface.h"
#include <kpluginfactory.h>

K_PLUGIN_CLASS_WITH_JSON(%{CN}PluginEditor, "%{ProjectNameLower}editorplugin.json")

%{CN}PluginEditor::%{CN}PluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorConvertText(parent)
{
}

%{CN}PluginEditor::~%{CN}PluginEditor()
{
}

MessageComposer::PluginEditorConvertTextInterface *%{CN}PluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
   %{CN}PluginEditorInterface *interface = new %{CN}PluginEditorInterface(parent);
    interface->createAction(ac);
    return interface;
}

#include "%{ProjectNameLower}plugineditor.moc"
