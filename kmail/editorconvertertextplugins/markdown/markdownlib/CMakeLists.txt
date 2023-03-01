# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kmailmarkdown)

target_sources(kmailmarkdown PRIVATE
    markdownpreviewwidget.cpp
    markdownconfigurewidget.cpp
    markdownconfiguredialog.cpp
    markdownconverter.cpp
    markdownpreviewdialog.cpp
    markdownenginepage.cpp
    markdowncreatelinkwidget.cpp
    markdowncreatelinkdialog.cpp
    markdowncreateimagewidget.cpp
    markdowncreateimagedialog.cpp
    markdownhighlighter.cpp
    markdownutil.cpp

    markdownpreviewwidget.h
    markdownconfigurewidget.h
    markdownconfiguredialog.h
    markdownconverter.h
    markdownpreviewdialog.h
    markdownenginepage.h
    markdowncreatelinkwidget.h
    markdowncreatelinkdialog.h
    markdowncreateimagewidget.h
    markdowncreateimagedialog.h
    markdownhighlighter.h
    markdownutil.h
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmailmarkdown PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(kmailmarkdown BASE_NAME libkmailmarkdown)
target_link_libraries(kmailmarkdown
    KPim${KF_MAJOR_VERSION}::MessageComposer
    KF${KF_MAJOR_VERSION}::I18n
    Qt::WebEngineWidgets
    discount::Lib
    KF${KF_MAJOR_VERSION}::SyntaxHighlighting
)

set_target_properties(kmailmarkdown
    PROPERTIES OUTPUT_NAME kmailmarkdown VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS kmailmarkdown ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
