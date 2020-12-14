
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_xdiff_plugin\")
set(messageviewer_bodypartformatter_text_highlighter_PART_SRCS texthighlighterplugin.cpp highlighter.cpp)

add_library(messageviewer_bodypartformatter_text_highlighter MODULE ${messageviewer_bodypartformatter_text_highlighter_PART_SRCS})
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_highlighter PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_highlighter
    Qt5::Core
    KF5::MessageViewer
    KF5::SyntaxHighlighting
    Grantlee5::Templates
)

install(TARGETS messageviewer_bodypartformatter_text_highlighter DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
