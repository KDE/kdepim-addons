macro(add_messageviewer_dkim_verify_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source}
        TEST_NAME ${_name}
        NAME_PREFIX "messageviewer-"
        LINK_LIBRARIES KF5::MessageViewer dkimverifyconfigure Qt5::Test
    )
endmacro ()

add_messageviewer_dkim_verify_unittest(dkimconfiguredialogtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimconfiguretabtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimconfigurewidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimgeneralwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimkeyrecordwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimadvancedwidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimpolicywidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimruledialogtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimrulewidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimmanagerulesdialogtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimmanageruleswidgettest.cpp)
add_messageviewer_dkim_verify_unittest(dkimmanagerulescomboboxtest.cpp)
add_messageviewer_dkim_verify_unittest(dkimauthenticationverifiedserverwidgettest.cpp)
