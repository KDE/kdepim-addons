
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_xdiff_plugin\")
add_library(messageviewer_bodypartformatter_text_highlighter MODULE )
target_sources(messageviewer_bodypartformatter_text_highlighter PRIVATE texthighlighterplugin.cpp highlighter.cpp)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_highlighter PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_highlighter
    Qt::Core
    KF5::MessageViewer
    KF5::SyntaxHighlighting
    Grantlee5::Templates
)

install(TARGETS messageviewer_bodypartformatter_text_highlighter DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
