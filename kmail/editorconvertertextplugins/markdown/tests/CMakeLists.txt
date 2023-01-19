# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(markdown_gui_SRCS main.cpp markdowndemowidget.cpp markdowndemowidget.h markdown_gui.qrc)
add_executable(markdown_gui ${markdown_gui_SRCS})
target_link_libraries(markdown_gui
    KF5::MessageComposer KF5::I18n KF5::XmlGui Qt::WebEngineWidgets discount::Lib KF5::SyntaxHighlighting kmailmarkdown
)

