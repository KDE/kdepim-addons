find_package(Discount "2")
set_package_properties("discount" PROPERTIES
        DESCRIPTION "A library that gives you formatting functions suitable for marking down entire documents or lines of text"
        URL "http://www.pell.portland.or.us/~orc/Code/discount/"
        TYPE RECOMMENDED
	PURPOSE "Generate Markdown file.")

if(discount_FOUND)
	add_subdirectory(markdown)
endif()
add_subdirectory(inserttemplatecommand)
