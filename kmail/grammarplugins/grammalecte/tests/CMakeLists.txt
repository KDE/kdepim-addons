add_executable(grammalecte_gui ${grammalecte_gui_SRCS})
target_sources(grammalecte_gui PRIVATE main.cpp grammalectewidget.cpp)
target_link_libraries(grammalecte_gui
    KF5::I18n kmailgrammalecte grammarcommon
)

