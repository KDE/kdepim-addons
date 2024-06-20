# SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"importwizard_plugins\")
add_subdirectory(evolutionv1)
add_subdirectory(evolutionv2)
add_subdirectory(geary)
if(APPLE)
  add_subdirectory(mailapp)
endif()
add_subdirectory(opera)
if(WIN32)
   add_subdirectory(pmail)
   add_subdirectory(thebat)
   add_subdirectory(oe)
endif()
