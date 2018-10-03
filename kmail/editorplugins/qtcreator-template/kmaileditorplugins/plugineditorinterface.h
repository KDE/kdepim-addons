%{Cpp:LicenseTemplate}\

#ifndef %{JS: Cpp.headerGuard('%{HeaderPluginEditorInterface}')}
#define %{JS: Cpp.headerGuard('%{HeaderPluginEditorInterface}')}

#include <messagecomposer/plugineditorinterface.h>

class %{CN}PluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit %{CN}PluginEditorInterface(QObject *parent = nullptr);
    ~%{CN}PluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
};

#endif
