# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_messageviewer_dkim_verify_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source}
        TEST_NAME ${_name}
        NAME_PREFIX "messageviewer-"
        LINK_LIBRARIES KPim6::MessageViewer dkimverifyconfigure Qt::Test
    )
endmacro ()

add_messageviewer_dkim_verify_unittest(dkimconfiguredialogtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimconfiguretabtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimconfigurewidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimgeneralwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimkeyrecordwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimadvancedwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimpolicywidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimauthenticationverifiedserverwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimauthenticationverifiedserverdialogtest.cpp)
