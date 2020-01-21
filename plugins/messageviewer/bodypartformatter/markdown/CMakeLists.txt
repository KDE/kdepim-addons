
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_markdown_plugin\")
set(messageviewer_bodypartformatter_text_markdown_PART_SRCS textmarkdownplugin.cpp)

add_library(messageviewer_bodypartformatter_text_markdown MODULE ${messageviewer_bodypartformatter_text_markdown_PART_SRCS})

target_link_libraries(messageviewer_bodypartformatter_text_markdown
    Qt5::Core
    KF5::MessageViewer
    Grantlee5::Templates
)

install(TARGETS messageviewer_bodypartformatter_text_markdown DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
