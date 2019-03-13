#macro(add_messageviewer_dkim_verify_unittest _source)
#    get_filename_component(_name ${_source} NAME_WE)
#    ecm_add_test(${_source}
#        TEST_NAME ${_name}
#        NAME_PREFIX "messageviewer-"
#        LINK_LIBRARIES KF5::MessageViewer KF5::WebEngineViewer KF5::Libkleo QGpgme Qt5::Test
#    )
#endmacro ()

#add_messageviewer_dkim_verify_unittest(dkiminfotest.cpp)
