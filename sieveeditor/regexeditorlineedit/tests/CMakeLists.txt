set(sieveeditor_regexpeditor_SRCS
   main.cpp
   regexpeditorwidget.cpp
   ../regexpeditorlineedit.cpp
   ${sieveeditorregexp_plugin_categories_SRCS}
)

add_executable(sieveeditorregexpeditor_gui ${sieveeditor_regexpeditor_SRCS})
target_link_libraries(sieveeditorregexpeditor_gui
     KF5::PimCommon KF5::I18n KF5::KSieveUi KF5::TextWidgets KF5::Service
)
