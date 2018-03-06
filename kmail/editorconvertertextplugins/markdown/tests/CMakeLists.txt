set(markdown_gui_SRCS main.cpp markdowndemowidget.cpp ../markdownpreviewwidget.cpp ../markdowndocument.cpp ../markdownpreviewpage.cpp)
qt5_add_resources(markdown_gui_SRCS ../data/markdown.qrc)
add_executable(markdown_gui ${markdown_gui_SRCS})
target_link_libraries(markdown_gui
    KF5::MessageComposer KF5::I18n KF5::XmlGui Qt5::WebEngineWidgets
)

