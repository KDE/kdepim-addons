%{Cpp:LicenseTemplate}\

#ifndef %{JS: Cpp.headerGuard('%{HeaderPluginEditorInterface}')}
#define %{JS: Cpp.headerGuard('%{HeaderPluginEditorInterface}')}

#include <MessageComposer/PluginEditorConvertTextInterface>
class %{CN}PluginEditorInterface : public MessageComposer::PluginEditorConvertTextInterface
{
    Q_OBJECT
public:
    explicit %{CN}PluginEditorInterface(QObject *parent = nullptr);
    ~%{CN}PluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    bool convertTextToFormat(MessageComposer::TextPart *textPart) override;
    bool reformatText() override;
    void setInitialData(const MessageComposer::PluginEditorConverterInitialData &data) override;
};

#endif
