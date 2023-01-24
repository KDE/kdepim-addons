# SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_checkbeforedeleting_unittest _source)
    set( _test ${_source} ${kmail_markdownplugin_debug_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test}  ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_checkbeforedeleting-${_name})
    target_link_libraries( ${_name} Qt::Test KF${KF_MAJOR_VERSION}::XmlGui KF5::MessageViewer KF${KF_MAJOR_VERSION}::I18n kmailconfirmbeforedeleting)
endmacro ()

add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingdialogtest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingwidgettest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingruletest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingcreaterulewidgettest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingcreateruledialogtest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingmessageboxdialogtest.cpp)
add_kmail_checkbeforedeleting_unittest(confirmbeforedeletingmessageboxwidgettest.cpp)
