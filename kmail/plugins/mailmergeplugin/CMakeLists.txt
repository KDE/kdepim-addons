# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
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
)

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

if(BUILD_TESTING)
   add_subdirectory(autotests)
   add_subdirectory(tests)
endif()
