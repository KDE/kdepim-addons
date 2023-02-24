# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_sieveeditorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${sieveeditor_plugin_categories_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(sieveeditorplugin-${_name})
    target_link_libraries( ${_name} Qt::Widgets Qt::Test KPim${KF_MAJOR_VERSION}::IMAP KF${KF_MAJOR_VERSION}::CoreAddons KF${KF_MAJOR_VERSION}::KIOCore KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::KIOWidgets KPim${KF_MAJOR_VERSION}::KSieveUi KPim${KF_MAJOR_VERSION}::MailTransport KF${KF_MAJOR_VERSION}::ItemModels)
endmacro ()

add_sieveeditorplugin_unittest(selectimapfolderdialogtest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapfolderdialog.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapfolderwidgettest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapwidgettest.cpp "../selectimapfoldertreeview.cpp;../selectimaplineedit.cpp;../selectimapcreatefolderjob.cpp;../selectimaplineeditcompletermodel.cpp;../selectimapwidget.cpp;../selectimapfolderdialog.cpp;../selectimapfolderwidget.cpp;../selectimaploadfoldersjob.cpp;../selectimapfoldermodel.cpp")
add_sieveeditorplugin_unittest(selectimapfoldermodeltest.cpp "../selectimapfoldermodel.cpp;../selectimaploadfoldersjob.cpp;../selectimapcreatefolderjob.cpp")
add_sieveeditorplugin_unittest(selectimapcreatefolderjobtest.cpp "../selectimapcreatefolderjob.cpp")
