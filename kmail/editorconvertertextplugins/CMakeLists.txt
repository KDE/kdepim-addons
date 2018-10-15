if(discount_FOUND)
	add_subdirectory(markdown)
endif()

if (KMAIL_EDITORCONVERTERPLUGIN_TEMPLATE_BUILD)
	add_subdirectory(inserttemplatecommand)
endif()
add_subdirectory(qtcreator-template)
