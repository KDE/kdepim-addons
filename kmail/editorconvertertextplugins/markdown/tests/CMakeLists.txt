# SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(markdown_gui_SRCS
    main.cpp
    markdowndemowidget.cpp
    markdowndemowidget.h
    markdown_gui.qrc
)
add_executable(markdown_gui ${markdown_gui_SRCS})
target_link_libraries(
    markdown_gui
    KPim6::MessageComposer
    KF6::I18n
    KF6::XmlGui
    Qt::WebEngineWidgets
    discount::Lib
    KF6::SyntaxHighlighting
    kmailmarkdown
)
