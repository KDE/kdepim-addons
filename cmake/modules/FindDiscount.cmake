# - Find Discount
# Find the discount markdown library.
#
# This module defines
#  discount_FOUND - whether the discount library was found
#  discount_LIBRARIES - the discount library
#  discount_INCLUDE_DIR - the include path of the discount library

# SPDX-FileCopyrightText: 2017 Julian Wolff <wolff@julianwolff.de>
# SPDX-FileCopyrightText: 2018 Sune Vuorela <sune@kde.org>
# SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>
#
# SPDX-License-Identifier: BSD-3-Clause


if (discount_INCLUDE_DIRS AND discount_LIBRARIES)
  # Already in cache
  set (discount_FOUND TRUE)
else ()
  if (NOT WIN32)
      find_package(PkgConfig QUIET)
      PKG_CHECK_MODULES(PC_LIBMARKDOWN QUIET libmarkdown)
      set(PC_LIBMARKDOWN_VERSION_STRING ${PC_LIBMARKDOWN_VERSION})
      MESSAGE(STATUS "VERSION ${PC_LIBMARKDOWN_VERSION_STRING}")
  endif ()	
  find_library (discount_LIBRARY
    NAMES markdown libmarkdown
  )

  find_path (discount_INCLUDE_DIR
    NAMES mkdio.h
  )

  set(discount_LIBRARIES ${discount_LIBRARY})
  set(discount_INCLUDE_DIRS ${discount_INCLUDE_DIR})
  
  include (FindPackageHandleStandardArgs)
  find_package_handle_standard_args (discount DEFAULT_MSG discount_LIBRARIES discount_INCLUDE_DIR)

endif()

mark_as_advanced(discount_INCLUDE_DIRS discount_LIBRARIES)
if (discount_FOUND)
   add_library(discount::Lib UNKNOWN IMPORTED)
   set_target_properties(discount::Lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${discount_INCLUDE_DIRS} IMPORTED_LOCATION ${discount_LIBRARIES})
endif()
