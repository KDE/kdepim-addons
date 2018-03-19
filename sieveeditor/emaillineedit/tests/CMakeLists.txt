set(sieveeditor_emailline_widget_SRCS
   main.cpp
   emaillineeditwidget.cpp
   ../emaillineedit.cpp
   ${sieveeditoremaillinedit_plugin_categories_SRCS}
)

add_executable(sieveeditoremailinedit_gui ${sieveeditor_emailline_widget_SRCS})
target_link_libraries(sieveeditoremailinedit_gui
     KF5::I18n KF5::KSieveUi KF5::AkonadiContact
)
