find_package(Doxygen REQUIRED dot)

if (DOXYGEN_FOUND)

    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "readme.md")
    set(DOXYGEN_EXTRACT_ALL "YES")
    set(DOXYGEN_GENERATE_TREEVIEW "YES")
    set(DOXYGEN_INLINE_SOURCES "YES") 
    set(DOXYGEN_SOURCE_BROWSER "YES")
    set(DOXYGEN_HTML_EXTRA_STYLESHEET "${CMAKE_CURRENT_SOURCE_DIR}/stylesheet.css")

    set(DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../doc/cfsmDoxlayout.xml")

    doxygen_add_docs(doc
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        readme.md
        LICENSE.md
        src/c_fsm.h
        src/c_fsm.c

        ${CFSM_EXAMPLE_MARIO_SRC}

        ALL
        COMMENT "Generate HTML documentation"
    )
endif(DOXYGEN_FOUND)