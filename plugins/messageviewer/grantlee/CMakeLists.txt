# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(kitinerary_grantlee_extension MODULE grantleeextension.cpp)
target_link_libraries(kitinerary_grantlee_extension
    KPim::Itinerary
    KF5::Contacts
    Grantlee5::Templates
)
install(TARGETS kitinerary_grantlee_extension DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/grantlee/5.0)
