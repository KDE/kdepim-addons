# SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(languagetool_gui)
target_sources(languagetool_gui PRIVATE main.cpp languagetoolwidget.cpp languagetoolwidget.h)
target_link_libraries(languagetool_gui
    KF5::I18n kmaillanguagetool grammarcommon
)

