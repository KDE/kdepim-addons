# SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(messageviewer_scamconfiguresettingsplugin INSTALL_NAMESPACE messageviewer/configuresettings)

target_sources(messageviewer_scamconfiguresettingsplugin PRIVATE
   scamconfiguresettingsplugin.cpp
)


target_link_libraries(messageviewer_scamconfiguresettingsplugin
  KF5::MessageViewer
)


if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
