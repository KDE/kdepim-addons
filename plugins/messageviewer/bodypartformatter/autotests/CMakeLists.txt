set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
add_definitions( -DMAIL_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DDIFF_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/diffdata" )

include(${CMAKE_SOURCE_DIR}/cmake/modules/kdepim_add_gpg_crypto_test.cmake)
add_subdirectory(gnupg_home)

macro(add_kdepimaddons_crypto_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_source})
    target_link_libraries( ${_name}
        KF5::MessageViewer
        Qt5::Test
        KF5::IconThemes
    )
    add_gpg_crypto_test(${_name} messageviewerplugins-${_name})
    ecm_mark_as_test(messageviewerplugins-${_name})
endmacro ()


add_kdepimaddons_crypto_unittest(rendertest.cpp)

macro(add_messageviewer_bodyformatter_class_unittest _source _additional)
    set( _test ${_source} ${common_SRCS} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)

    ecm_add_test(${_test}
                 TEST_NAME ${_name}
                 NAME_PREFIX "messageviewerplugins-"
		 LINK_LIBRARIES KF5::MessageViewer Qt5::Test KF5::PimTextEdit KF5::I18n KF5::Completion KF5::LibkdepimAkonadi
                )
endmacro ()
add_messageviewer_bodyformatter_class_unittest(reactiontoinvitationdialogtest.cpp "../calendar/reactiontoinvitationdialog.cpp")
add_messageviewer_bodyformatter_class_unittest(delegateselectortest.cpp "../calendar/delegateselector.cpp")

macro(add_diff_bodyformatter_class_unittest _source _additional)
    set( _test ${_source} ${common_SRCS} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)

    ecm_add_test(${_test}
                 TEST_NAME ${_name}
                 NAME_PREFIX "messageviewerplugins-"
                 LINK_LIBRARIES KF5::MessageViewer Qt5::Test KF5::PimTextEdit KF5::I18n KF5::SyntaxHighlighting
                )
endmacro ()

add_diff_bodyformatter_class_unittest(diffhighlightertest.cpp "../highlighter/highlighter.cpp")

ecm_add_test(
    airportdbtest.cpp
    NAME_PREFIX "messageviewerplugins-"
    LINK_LIBRARIES Qt5::Test semantic_extractor
)
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
ecm_add_test(
    structureddataextractortest.cpp
    NAME_PREFIX "messageviewerplugins-"
    LINK_LIBRARIES Qt5::Test semantic_extractor
)
ecm_add_test(
    unstructureddataextractortest.cpp
    NAME_PREFIX "messageviewerplugins-"
    LINK_LIBRARIES Qt5::Test semantic_extractor
)
