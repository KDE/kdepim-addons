# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_messageviewer_openwithurl_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "messageviewer-"
        LINK_LIBRARIES KPim6::MessageViewer KPim6::Libkdepim openurlwithconfigure Qt::Test KF6::KIOWidgets
    )
endmacro ()

add_messageviewer_openwithurl_unittest(openurlwithconfigurewidgettest.cpp)
add_messageviewer_openwithurl_unittest(openurlwithconfiguredialogtest.cpp)
add_messageviewer_openwithurl_unittest(openurlwithconfigurecreatedialogtest.cpp)
add_messageviewer_openwithurl_unittest(openurlwithconfigurecreatewidgettest.cpp)
