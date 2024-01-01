# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_createnoteplugin INSTALL_NAMESPACE pim6/messageviewer/viewerplugin)
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
    KPim6::MessageViewer KF6::XmlGui KF6::CalendarCore KPim6::AkonadiNotes KPim6::IncidenceEditor KPim6::AkonadiWidgets
    )

