project(kdepim-addons)

cmake_minimum_required(VERSION 2.8.12)

# Do NOT add quote
set(KDEPIMADDONS_DEV_VERSION pre)

# add an extra space
if(DEFINED KDEPIMADDONS_DEV_VERSION)
  set(KDEPIMADDONS_DEV_VERSION " ${KDEPIMADDONS_DEV_VERSION}")
endif()

set(KDEPIMADDONS_VERSION_NUMBER "5.1.40")
set(KDEPIMADDONS_VERSION "${KDEPIMADDONS_VERSION_NUMBER}${KDEPIMADDONS_DEV_VERSION}")

set(KDEPIMADDONS_LIB_VERSION "${KDEPIMADDONS_VERSION_NUMBER}")
set(KDEPIMADDONS_LIB_SOVERSION "5")

set(QT_REQUIRED_VERSION "5.4.0")
set(KF5_VERSION "5.16.0")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)
find_package(Qt5X11Extras NO_MODULE)
find_package(Qt5Designer NO_MODULE)
set_package_properties(Qt5Designer PROPERTIES
   PURPOSE "Required to build the Qt Designer plugins"
   TYPE OPTIONAL
)

option(KDEPIMADDONS_BUILD_EXAMPLES "Build the kdepim example applications." FALSE)

if (KDEPIMADDONS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()
