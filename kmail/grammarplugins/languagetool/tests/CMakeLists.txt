set(languagetool_gui_SRCS main.cpp languagetoolwidget.cpp)
add_executable(languagetool_gui ${languagetool_gui_SRCS})
target_link_libraries(languagetool_gui
    KF5::I18n kmaillanguagetool grammarcommon
)

