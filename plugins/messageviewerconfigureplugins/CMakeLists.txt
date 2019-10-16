add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerconfiguresettingsplugins\")

add_subdirectory(gravatar)

set(CMAKE_REQUIRED_LIBRARIES KF5::MessageViewer)
check_cxx_source_compiles("
#include <MessageViewer/DKIMWidgetInfo>
int main()
{
  MessageViewer::DKIMWidgetInfo *l = 0;
  return 0;
}
" HAVE_DKIMSUPPORT)


if (${HAVE_DKIMSUPPORT})
    add_subdirectory(dkim-verify)
endif()
