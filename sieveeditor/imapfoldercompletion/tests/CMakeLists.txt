add_executable(sieveeditorimapfoldercompletion_gui)
target_sources(sieveeditorimapfoldercompletion_gui PRIVATE
   main.cpp
   selectimapwidgettest.cpp
)

target_link_libraries(sieveeditorimapfoldercompletion_gui
     KF5::PimCommon KF5::Completion KF5::I18n KF5::KSieveUi
)

