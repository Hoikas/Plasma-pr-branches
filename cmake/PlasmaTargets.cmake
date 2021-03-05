include(BuildOptimizations)
#TODO (#854): include(Sanitizers)

function(plasma_executable TARGET)
    cmake_parse_arguments(_pex
        "WIN32;QT_GUI;EXCLUDE_FROM_ALL"     # Flags
        ""                                  # Single values
        "SOURCES"                           # Multiple values
        ${ARGN}
    )

    if(_pex_WIN32)
        list(APPEND addexe_args WIN32)
    endif()
    if(_pex_QT_GUI)
        list(APPEND addexe_args WIN32 MACOSX_BUNDLE)
    endif()
    if(_pex_EXCLUDE_FROM_ALL)
        list(APPEND addexe_args EXCLUDE_FROM_ALL)
    endif()
    add_executable(${TARGET} ${addexe_args} ${_pex_SOURCES})

    if(_pex_QT_GUI)
        set_target_properties(${TARGET}
            PROPERTIES
                AUTOMOC ON
                AUTORCC ON
                AUTOUIC ON
        )

        target_include_directories(${TARGET}
            PRIVATE
                # Needed for custom widget includes
                ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()

    #TODO (#854): plasma_sanitize_target(${TARGET})
endfunction()

function(plasma_library TARGET)
    cmake_parse_arguments(_plib
        "UNITY_BUILD;SHARED"                            # Flags
        ""                                              # Single values
        "PRECOMPILED_HEADERS;SOURCES"                   # Multiple values
        ${ARGN}
    )

    if(_plib_SHARED)
        set(libtype SHARED)
    else()
        set(libtype STATIC)
    endif()
    add_library(${TARGET} ${libtype} ${_plib_SOURCES})

    if(PLASMA_USE_PCH AND _plib_PRECOMPILED_HEADERS)
        target_precompile_headers(${TARGET} PRIVATE ${_plib_PRECOMPILED_HEADERS})
    endif()

    if(PLASMA_UNITY_BUILD AND _plib_UNITY_BUILD)
        set_target_properties(${TARGET} PROPERTIES UNITY_BUILD TRUE)
    endif()

    #TODO (#854): plasma_sanitize_target(${TARGET})
endfunction()

function(plasma_test TARGET)
    plasma_executable(${TARGET} ${ARGN})
    add_test(NAME ${TARGET} COMMAND ${TARGET})
    add_dependencies(check ${TARGET})
endfunction()
