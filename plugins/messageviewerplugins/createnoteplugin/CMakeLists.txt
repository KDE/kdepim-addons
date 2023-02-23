# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_createnoteplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/viewerplugin)
target_sources(messageviewer_createnoteplugin PRIVATE
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
    viewerplugincreatenote.h
    viewerplugincreatenoteinterface.h
    noteedit.h
    createnotejob.h
    )
ecm_qt_declare_logging_category(messageviewer_createnoteplugin HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin
    DESCRIPTION "kdepim-addons (create note plugin)"
    OLD_CATEGORY_NAMES log_createnoteplugin
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_createnoteplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(messageviewer_createnoteplugin
    KF5::MessageViewer KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::CalendarCore KPim${KF_MAJOR_VERSION}::AkonadiNotes KF5::IncidenceEditor KF5::AkonadiWidgets
    )

