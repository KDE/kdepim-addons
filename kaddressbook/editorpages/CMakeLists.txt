# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"cryptopageplugin\")

########### next target ###############
add_library(cryptopageplugin MODULE)
target_sources(cryptopageplugin PRIVATE cryptopageplugin.cpp cryptopageplugin.h)

target_link_libraries(cryptopageplugin KF${KF_MAJOR_VERSION}::Contacts KPim${KF_MAJOR_VERSION}::ContactEditor KPim${KF_MAJOR_VERSION}::Libkleo KF${KF_MAJOR_VERSION}::IconThemes KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Completion Gpgmepp)

install(TARGETS cryptopageplugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/contacteditor/editorpageplugins/)
