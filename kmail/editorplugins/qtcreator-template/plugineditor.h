%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{FileName}')}
#define %{JS: Cpp.headerGuard('%{FileName}')}

#include <messagecomposer/plugineditor.h>

#include <messagecomposer/plugineditorinterface.h>
#include <QVariant>

class %{CN}PluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit %{CN}PluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~%{CN}PluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(KActionCollection *ac, QObject *parent = nullptr) override;
    bool hasPopupMenuSupport() const override;
};

#endif // %{JS: Cpp.headerGuard('%{FileName}')}
