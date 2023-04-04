# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"cryptopageplugin\")

########### next target ###############
add_library(cryptopageplugin MODULE)
target_sources(cryptopageplugin PRIVATE cryptopageplugin.cpp cryptopageplugin.h)

target_link_libraries(cryptopageplugin KF6::Contacts KPim6::ContactEditor KPim6::Libkleo KF6::IconThemes KF6::I18n KF6::Completion Gpgmepp)

install(TARGETS cryptopageplugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/contacteditor/editorpageplugins/)
