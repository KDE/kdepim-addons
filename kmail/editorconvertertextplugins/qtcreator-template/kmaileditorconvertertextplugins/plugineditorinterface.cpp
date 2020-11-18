

#include "%{ProjectNameLower}plugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <MessageComposer/PluginEditorConverterInitialData>
#include <KPIMTextEdit/RichTextComposer>
#include <KActionCollection>

%{CN}PluginEditorInterface::%{CN}PluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

%{CN}PluginEditorInterface::~%{CN}PluginEditorInterface()
{
}

void %{CN}PluginEditorInterface::createAction(KActionCollection *ac)
{
}

MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus %{CN}PluginEditorInterface::convertTextToFormat(MessageComposer::TextPart *textPart)
{
    Q_UNUSED(textPart)
    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
}

bool %{CN}PluginEditorInterface::reformatText()
{
    return true;
}

void %{CN}PluginEditorInterface::setInitialData(const MessageComposer::PluginEditorConverterInitialData &data)
{
    Q_UNUSED(data)
}
