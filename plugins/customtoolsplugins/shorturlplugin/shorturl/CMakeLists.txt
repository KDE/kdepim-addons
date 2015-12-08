if (BUILD_TESTING)
   add_subdirectory(tests)
   add_subdirectory(autotests)
endif()

set(common_engineplugin_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/shorturlengineplugin/shorturlengineinterface.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/shorturlengineplugin/shorturlengineplugin.cpp
)


add_subdirectory(shorturlengineplugin)

