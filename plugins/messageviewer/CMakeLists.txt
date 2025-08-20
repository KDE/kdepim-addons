# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_subdirectory(bodypartformatter)
if (TARGET KPim6::Itinerary)
    add_subdirectory(ktexttemplate)
endif ()
