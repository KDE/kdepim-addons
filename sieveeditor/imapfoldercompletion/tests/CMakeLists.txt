set(sieveeditor_imapfoldercompletion_SRCS
   main.cpp
)

add_executable(sieveeditorimapfoldercompletion_gui ${sieveeditor_imapfoldercompletion_SRCS})
target_link_libraries(sieveeditorimapfoldercompletion_gui
     KF5::PimCommon KF5::Completion KF5::I18n
)

