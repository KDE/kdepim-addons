# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(markdown_gui_SRCS main.cpp markdowndemowidget.cpp markdowndemowidget.h markdown_gui.qrc)
add_executable(markdown_gui ${markdown_gui_SRCS})
target_link_libraries(markdown_gui
    KF5::MessageComposer KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::XmlGui Qt::WebEngineWidgets discount::Lib KF${KF_MAJOR_VERSION}::SyntaxHighlighting kmailmarkdown
)

