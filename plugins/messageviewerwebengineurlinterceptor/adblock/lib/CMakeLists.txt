set(adblocklibprivate_SRCS
    adblockmanager.cpp)

add_library(adblocklibprivate ${adblocklibprivate_SRCS})
generate_export_header(adblocklibprivate BASE_NAME adblocklib)

target_link_libraries(adblocklibprivate
PRIVATE
    Qt5::Core
)

set_target_properties(adblocklibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS adblocklibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

add_subdirectory(autotests)
