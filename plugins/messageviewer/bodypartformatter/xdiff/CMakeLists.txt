
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_xdiff_plugin\")
set(messageviewer_bodypartformatter_text_xdiff_PART_SRCS text_xdiff.cpp diffhighlighter.cpp)

add_library(messageviewer_bodypartformatter_text_xdiff MODULE ${messageviewer_bodypartformatter_text_xdiff_PART_SRCS})

target_link_libraries(messageviewer_bodypartformatter_text_xdiff
    Qt5::Core
    KF5::MessageViewer
    KF5::SyntaxHighlighting
    Grantlee5::Templates
)

install(TARGETS messageviewer_bodypartformatter_text_xdiff  DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
