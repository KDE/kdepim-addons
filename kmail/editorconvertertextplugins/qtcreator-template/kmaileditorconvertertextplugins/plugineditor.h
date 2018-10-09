%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{HeaderPluginEditor}')}
#define %{JS: Cpp.headerGuard('%{HeaderPluginEditor}')}

#include <MessageComposer/PluginEditorConvertText>
#include <QVariant>
class KActionCollection;
class %{CN}PluginEditor : public MessageComposer::PluginEditorConvertText
{
    Q_OBJECT
public:
    explicit %{CN}PluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~%{CN}PluginEditor() override;

    MessageComposer::PluginEditorConvertTextInterface *createInterface(KActionCollection *ac, QObject *parent = nullptr) override;
};

#endif
