# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_sieveeditorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${sieveeditor_plugin_categories_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test})
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(sieveeditorplugin-${_name})
    target_link_libraries( ${_name} Qt::Widgets Qt::Test KF5::IMAP KF5::CoreAddons KF5::KIOCore KF5::I18n KF5::Completion KF5::KIOWidgets KF5::KSieveUi KF5::MailTransport KF5::ItemModels)
endmacro ()

add_sieveeditorplugin_unittest(selectimapfolderdialogtest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapfolderdialog.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapfolderwidgettest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapwidgettest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapwidget.cpp;../selectimapfolderdialog.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapfoldermodeltest.cpp "../selectimapfoldermodel.cpp;../selectimaploadfoldersjob.cpp;../selectimapcreatefolderjob.cpp")
add_sieveeditorplugin_unittest(selectimapcreatefolderjobtest.cpp "../selectimapcreatefolderjob.cpp")
