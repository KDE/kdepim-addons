# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(messageviewer_bodypartformatter_semantic MODULE)

target_sources(messageviewer_bodypartformatter_semantic PRIVATE
    itinerary_plugin.cpp
    itinerarymemento.cpp
    itineraryprocessor.cpp
    itineraryrenderer.cpp
    itineraryurlhandler.cpp
    itinerarykdeconnecthandler.cpp
    itinerarymemento.h
    itineraryprocessor.h
    itineraryrenderer.h
    itineraryurlhandler.h
    itinerarykdeconnecthandler.h
    templates/templates.qrc
    )
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_semantic HEADER itinerary_debug.h IDENTIFIER ITINERARY_LOG CATEGORY_NAME org.kde.pim.messageviewer.itinerary
    DESCRIPTION "kdepim-addons (Itinerary plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_semantic PROPERTIES UNITY_BUILD ON)
endif()

target_compile_definitions(messageviewer_bodypartformatter_semantic PRIVATE -DTRANSLATION_DOMAIN=\"messageviewer_semantic_plugin\")
target_link_libraries(messageviewer_bodypartformatter_semantic
    KF6::KIOGui
    KPim6::MessageViewer
    KPim6::CalendarSupport
    KF6::I18n
    KPim6::GrantleeTheme
    ${TEMPLATES_LIB}
    Qt::DBus
    KF6::Prison
    KPim6::Itinerary
    KPim6::PkPass
    )
install(TARGETS messageviewer_bodypartformatter_semantic DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/messageviewer/bodypartformatter)
