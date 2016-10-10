set(kaddressbookimportexportprivatelib_SRCS
)

add_library(kaddressbookimportexportlibprivate ${kaddressbookimportexportprivatelib_SRCS})
generate_export_header(kaddressbookimportexportlibprivate BASE_NAME kaddressbookimportexportlibprivate)


target_link_libraries(kaddressbookimportexportlibprivate
PRIVATE
    KF5::I18n KF5::Contacts KF5::AkonadiContact KF5::Contacts KF5::AkonadiWidgets
)

set_target_properties(kaddressbookimportexportlibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS kaddressbookimportexportlibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
