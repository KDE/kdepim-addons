# SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(grammalecte_gui)
target_sources(grammalecte_gui PRIVATE main.cpp grammalectewidget.cpp)
target_link_libraries(grammalecte_gui
    KF5::I18n kmailgrammalecte grammarcommon
)

