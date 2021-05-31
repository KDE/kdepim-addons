set(mardown_engine_SRCS)
set(discount_LIB)
add_library(messageviewer_bodypartformatter_text_markdown MODULE)
if(USE_DISCOUNT_LIB)
    add_definitions(-DUSE_DISCOUNT_LIB)
    target_sources(messageviewer_bodypartformatter_text_markdown PRIVATE markdowndiscount.cpp)
    target_link_libraries(messageviewer_bodypartformatter_text_markdown discount::Lib)
else()
    set(messageviewer_bodypartformatter_text_markdown PRIVATE markdownqtextdocument.cpp)
endif()

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_markdown_plugin\")
target_sources(messageviewer_bodypartformatter_text_markdown PRIVATE textmarkdownplugin.cpp markdownabstract.cpp)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_markdown PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_markdown
    Qt::Core
    KF5::MessageViewer
    Grantlee5::Templates
)

install(TARGETS messageviewer_bodypartformatter_text_markdown DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
