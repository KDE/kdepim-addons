set(adblocksettings_gui_SRCS adblocksettings_gui.cpp)
add_executable(adblocksettings_gui ${adblocksettings_gui_SRCS})
target_link_libraries(adblocksettings_gui
    adblocklibprivate
    KF5::ItemViews
    KF5::I18n
    KF5::CoreAddons
    )

set(adblocksettingsdialog_gui_SRCS adblocksettingsdialog_gui.cpp)
add_executable(adblocksettingsdialog_gui ${adblocksettingsdialog_gui_SRCS})
target_link_libraries(adblocksettingsdialog_gui
    adblocklibprivate
    KF5::ItemViews
    KF5::I18n
    KF5::CoreAddons
    )
set(adblockautomaticruleslistwidget_gui_SRCS adblockautomaticruleslistwidget_gui.cpp)
add_executable(adblockautomaticruleslistwidget_gui ${adblockautomaticruleslistwidget_gui_SRCS})
target_link_libraries(adblockautomaticruleslistwidget_gui
    adblocklibprivate
    KF5::ItemViews
    KF5::I18n
    KF5::CoreAddons
    )
