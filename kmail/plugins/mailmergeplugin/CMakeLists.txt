set(kmail_mailmergeplugin_SRCS
    mailmergedialog.cpp
    widgets/addressbookwidget.cpp
    widgets/attachmentlistwidget.cpp
    widgets/csvwidget.cpp
    widgets/mailmergewidget.cpp
    widgets/selectattachmentdialog.cpp
)

add_library(mailmerge ${kmail_mailmergeplugin_SRCS})
generate_export_header(mailmerge BASE_NAME mailmerge)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(mailmerge PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(mailmerge
    KF5::I18n
    KF5::MessageComposer
    KF5::KIOWidgets
    )

set_target_properties(mailmerge
    PROPERTIES OUTPUT_NAME mailmerge VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

#kcoreaddons_add_plugin(kmail_logactivitiesplugin JSON kmail_logactivitiesplugin.json SOURCES
#    ${kmail_logactivitiesplugin_SRCS} INSTALL_NAMESPACE kmail/mainview)

#target_link_libraries(kmail_logactivitiesplugin
#  KF5::PimCommon KF5::PimCommonAkonadi KF5::XmlGui KF5::Libkdepim KF5::I18n
#)
#if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
#    set_target_properties(kmail_logactivitiesplugin PROPERTIES UNITY_BUILD ON)
#endif()

if(BUILD_TESTING)
   #add_subdirectory(autotests)
   #add_subdirectory(tests)
endif()
