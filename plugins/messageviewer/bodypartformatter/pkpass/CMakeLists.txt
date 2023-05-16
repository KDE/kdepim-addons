# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_bodypartformatter_pkpass\")
add_library(messageviewer_bodypartformatter_pkpass MODULE)

target_sources(messageviewer_bodypartformatter_pkpass PRIVATE
    pkpass_plugin.cpp
    templates.qrc
    )
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_pkpass HEADER pkpass_debug.h IDENTIFIER PKPASS_LOG CATEGORY_NAME org.kde.pim.pkpass
    DESCRIPTION "kdepim-addons (pkpass formatter)"
    EXPORT KDEPIMADDONS
    )


target_link_libraries(messageviewer_bodypartformatter_pkpass
    KF6::Archive
    KF6::Prison
    KPim6::MessageViewer
    KF6::TextTemplate
    KPim6::PkPass
    )
install(TARGETS messageviewer_bodypartformatter_pkpass DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/bodypartformatter)

