# cmake/AddGitSubmodule.cmake

function(add_git_submodule path url)
    if(NOT EXISTS ${path}/.git)
        message(STATUS "Initializing Git submodule at ${path}")
        execute_process(
            COMMAND git submodule update --init --recursive ${path}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            RESULT_VARIABLE result
        )
        if(NOT result EQUAL 0)
            message(FATAL_ERROR "Failed to initialize Git submodule at ${path}")
        endif()
    else()
        message(STATUS "Git submodule at ${path} already initialized")
    endif()
endfunction()
