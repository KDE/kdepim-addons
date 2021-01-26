%
{
Cpp:
    LicenseTemplate
}
#ifndef %
{
JS:
    Cpp.headerGuard('%{HeaderPluginEditor}')
}
#define % {JS : Cpp.headerGuard('%{HeaderPluginEditor}') }

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class % {CN} PluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit % {CN} PluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ % {CN} PluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    bool hasPopupMenuSupport() const override;
};

#endif // %{JS: Cpp.headerGuard('%{HeaderPluginEditor}')}
