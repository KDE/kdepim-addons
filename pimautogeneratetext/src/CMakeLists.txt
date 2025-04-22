# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(KPim6AutoGenerateText)

add_library(KPim6::AutoGenerateText ALIAS KPim6AutoGenerateText)

target_sources(KPim6AutoGenerateText PRIVATE
)

target_link_libraries(KPim6AutoGenerateText
)

set_target_properties(KPim6AutoGenerateText PROPERTIES
    VERSION ${KDEPIMADDONS_LIB_VERSION}
    SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS KPim6AutoGenerateText ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

