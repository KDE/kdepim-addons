set(grammalecte_gui_SRCS main.cpp grammalectewidget.cpp)
add_executable(grammalecte_gui ${grammalecte_gui_SRCS})
target_link_libraries(grammalecte_gui
    KF5::I18n kmailgrammalecte
)

