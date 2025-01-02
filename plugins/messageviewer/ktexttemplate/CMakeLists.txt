# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(kitinerary_ktexttemplate_extension MODULE ktexttemplateextension.cpp ktexttemplateextension.h)
target_link_libraries(kitinerary_ktexttemplate_extension
    KPim6::Itinerary
    KF6::Contacts
    KF6::TextTemplate
)
install(TARGETS kitinerary_ktexttemplate_extension DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/kf6/ktexttemplate)
