set(grammarcommon_SRCS
    grammarerror.cpp
    grammarresulttextedit.cpp
    grammarresultwidget.cpp
    )

ecm_qt_declare_logging_category(grammarcommon_SRCS HEADER grammarcommon_debug.h IDENTIFIER LIBGRAMMARCOMMON_LOG CATEGORY_NAME org.kde.pim.libgrammarcommon
    DESCRIPTION "kdepim-addons (libgramalecte common)"
    EXPORT KDEPIMADDONS
    )



add_library(grammarcommon ${grammarcommon_SRCS})
generate_export_header(grammarcommon BASE_NAME grammarcommon)
target_link_libraries(grammarcommon
    KF5::I18n
    KF5::MessageComposer
    )

set_target_properties(grammarcommon
    PROPERTIES OUTPUT_NAME grammarcommon VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS grammarcommon ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
