find_package(Doxygen REQUIRED dot)

if (DOXYGEN_FOUND)

    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "readme.md")
    set(DOXYGEN_EXTRACT_ALL "YES")
    set(DOXYGEN_GENERATE_TREEVIEW "YES")
    set(DOXYGEN_FULL_SIDEBAR "NO")
    set(DOXYGEN_INLINE_SOURCES "YES") 
    set(DOXYGEN_SOURCE_BROWSER "YES")
    set(DOXYGEN_DISABLE_INDEX  "NO")
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C  "YES")

    set(DOXYGEN_HTML_EXTRA_STYLESHEET 
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome.css"
#        ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-sidebar-only.css"
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css"
        "${CMAKE_CURRENT_SOURCE_DIR}/stylesheet.css"
    )
    set(DOXYGEN_SEARCHENGINE "YES")
    set(DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../doc/cfsmDoxlayout.xml")
    set(DOXYGEN_HTML_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/header.html")
    set(DOXYGEN_HTML_FOOTER "${CMAKE_CURRENT_SOURCE_DIR}/footer.html")
    set(DOXYGEN_HTML_COLORSTYLE "LIGHT")
    set(DOXYGEN_HTML_EXTRA_FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-interactive-toc.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-paragraph-link.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js"
    )

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