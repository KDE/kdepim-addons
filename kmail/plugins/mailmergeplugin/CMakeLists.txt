# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(mailmerge)
target_sources(mailmerge PRIVATE
    mailmergedialog.cpp
    widgets/addressbookwidget.cpp
    widgets/attachmentlistwidget.cpp
    widgets/csvwidget.cpp
    widgets/mailmergewidget.cpp
    widgets/selectattachmentdialog.cpp
    widgets/mailmergemenu.cpp
    widgets/mailmergeutil.cpp
    widgets/mailmergepreviewdialog.cpp
    widgets/mailmergepreviewwidget.cpp

    mailmergedialog.h
    widgets/addressbookwidget.h
    widgets/attachmentlistwidget.h
    widgets/csvwidget.h
    widgets/mailmergewidget.h
    widgets/selectattachmentdialog.h
    widgets/mailmergemenu.h
    widgets/mailmergeutil.h
    widgets/mailmergepreviewdialog.h
    widgets/mailmergepreviewwidget.h
)

generate_export_header(mailmerge BASE_NAME mailmerge)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(mailmerge PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(mailmerge
    KF${KF_MAJOR_VERSION}::I18n
    KPim${KF_MAJOR_VERSION}::MessageComposer
    KF${KF_MAJOR_VERSION}::KIOWidgets
    )

set_target_properties(mailmerge
    PROPERTIES OUTPUT_NAME mailmerge VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

if(BUILD_TESTING)
   add_subdirectory(autotests)
   add_subdirectory(tests)
endif()
