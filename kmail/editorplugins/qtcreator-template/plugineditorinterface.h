%{Cpp:LicenseTemplate}\

#ifndef SHARETEXTPLUGINEDITORINTERFACE_H
#define SHARETEXTPLUGINEDITORINTERFACE_H

#include <messagecomposer/plugineditorinterface.h>

class ShareTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorInterface(QObject *parent = nullptr);
    ~ShareTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
};

#endif
