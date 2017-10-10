include(ECMMarkAsTest)

set(contacteditor_addresslocation_web_editor_SRCS
    ../webengine/addresseslocationengineviewer.cpp
    ../webengine/addresseslocationenginepage.cpp
    )
set(contacteditor_webengine_LIB Qt5::WebEngine Qt5::WebEngineWidgets)

ecm_qt_declare_logging_category(contacteditor_addresslocation_web_editor_SRCS HEADER contacteditor_debug.h IDENTIFIER CONTACTEDITOR_LOG CATEGORY_NAME org.kde.pim.contacteditor)

set(addresseslocationviewer_SRCS addresseslocationviewertest.cpp ${contacteditor_addresslocation_web_editor_SRCS} ../addresseslocationgrantleeformater.cpp
    ../addressgrantleeobject.cpp ../iconnamecache.cpp)
add_executable(addresseslocationviewer ${addresseslocationviewer_SRCS})
add_test(NAME addresseslocationviewer COMMAND addresseslocationviewer)
ecm_mark_as_test(addresseslocationviewer)
target_link_libraries(addresseslocationviewer Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n ${contacteditor_webengine_LIB} Grantlee5::Templates
    KF5::IconThemes KF5::WidgetsAddons)

set(addresslocationwidget_SRCS addresslocationwidgettest.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresslocationwidget ${addresslocationwidget_SRCS})
add_test(NAME addresslocationwidget COMMAND addresslocationwidget)
ecm_mark_as_test(addresslocationwidget)
target_link_libraries(addresslocationwidget Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion)

set(addresseslocationwidget_SRCS addresseslocationwidgettest.cpp ../addresseslocationwidget.cpp ${contacteditor_addresslocation_web_editor_SRCS} ../addresseslocationgrantleeformater.cpp
    ../addressgrantleeobject.cpp ../iconnamecache.cpp ../addresslocationwidget.cpp ../selectaddresstypecombobox.cpp ../addresstypedialog.cpp)
add_executable(addresseslocationwidget ${addresseslocationwidget_SRCS})
add_test(NAME addresseslocationwidget COMMAND addresseslocationwidget)
ecm_mark_as_test(addresseslocationwidget)
target_link_libraries(addresseslocationwidget Qt5::Test  Qt5::Widgets KF5::ContactEditor KF5::Contacts KF5::I18n KF5::Completion ${contacteditor_webengine_LIB}
    Grantlee5::Templates KF5::IconThemes KF5::WidgetsAddons)
