# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_messageviewer_expireaccounttrash_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source}
        TEST_NAME ${_name}
        NAME_PREFIX "messageviewer-"
        LINK_LIBRARIES KPim6::MessageViewer Qt::Test expireaccounttrashfolderconfig
    )
endmacro()

add_messageviewer_expireaccounttrash_unittest(expireaccounttrashfolderconfigdialogtest.cpp)
add_messageviewer_expireaccounttrash_unittest(expireaccounttrashfolderconfigwidgettest.cpp)
