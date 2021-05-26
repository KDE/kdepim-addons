add_library(kmailmarkdown)

target_sources(kmailmarkdown PRIVATE
    markdownpreviewwidget.cpp
    markdownconfigurewidget.cpp
    markdownconfiguredialog.cpp
    markdownconverter.cpp
    markdownpreviewdialog.cpp
    markdownenginepage.cpp
    markdowncreatelinkwidget.cpp
    markdowncreatelinkdialog.cpp
    markdowncreateimagewidget.cpp
    markdowncreateimagedialog.cpp
    markdownhighlighter.cpp
    markdownutil.cpp
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmailmarkdown PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(kmailmarkdown BASE_NAME libkmailmarkdown)
target_link_libraries(kmailmarkdown
    KF5::MessageComposer
    KF5::I18n
    Qt::WebEngineWidgets
    discount::Lib
    KF5::SyntaxHighlighting
)

set_target_properties(kmailmarkdown
    PROPERTIES OUTPUT_NAME kmailmarkdown VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS kmailmarkdown ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
