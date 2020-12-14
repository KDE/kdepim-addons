set(mardown_engine_SRCS)
set(discount_LIB)
if(USE_DISCOUNT_LIB)
    add_definitions(-DUSE_DISCOUNT_LIB)
    set(mardown_engine_SRCS markdowndiscount.cpp)
    set(discount_LIB discount::Lib)
else()
    set(mardown_engine_SRCS markdownqtextdocument.cpp)
endif()

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_markdown_plugin\")
set(messageviewer_bodypartformatter_text_markdown_PART_SRCS textmarkdownplugin.cpp ${mardown_engine_SRCS} markdownabstract.cpp)

add_library(messageviewer_bodypartformatter_text_markdown MODULE ${messageviewer_bodypartformatter_text_markdown_PART_SRCS})
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_markdown PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_markdown
    Qt5::Core
    KF5::MessageViewer
    Grantlee5::Templates
    ${discount_LIB}
)

install(TARGETS messageviewer_bodypartformatter_text_markdown DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
