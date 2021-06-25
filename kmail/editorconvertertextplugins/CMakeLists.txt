add_definitions(-DTRANSLATION_DOMAIN=\"kmail_editorconvertertext_plugins\")
if(discount_FOUND)
	add_subdirectory(markdown)
endif()

add_subdirectory(qtcreator-template)
