# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(kitinerary_grantlee_extension MODULE grantleeextension.cpp grantleeextension.h)
target_link_libraries(kitinerary_grantlee_extension
    KPim6::Itinerary
    KF6::Contacts
    ${TEMPLATES_LIB}
)
install(TARGETS kitinerary_grantlee_extension DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/kf6/ktexttemplate)
