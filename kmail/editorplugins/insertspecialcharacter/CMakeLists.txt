# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_insertspecialcharactereditorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditor)
target_sources(kmail_insertspecialcharactereditorplugin PRIVATE
    insertspecialcharacterplugineditor.cpp
    insertspecialcharacterplugineditorinterface.cpp
    insertspecialcharacterplugineditor.h
    insertspecialcharacterplugineditorinterface.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertspecialcharactereditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_insertspecialcharactereditorplugin
  KF5::MessageComposer KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

