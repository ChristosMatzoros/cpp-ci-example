# cmake/FindAndInstallDoxygen.cmake

# Function to check and install Doxygen
function(find_and_install_doxygen)

    option(BUILD_DOC "Build documentation" ON)

    if(NOT BUILD_DOC)
        message(STATUS "Documentation generation is disabled (BUILD_DOC=OFF).")
        return()
    endif()

    find_package(Doxygen QUIET)

    if(DOXYGEN_FOUND)
        message(STATUS "Found Doxygen: ${DOXYGEN_EXECUTABLE}")
    else()
        message(WARNING "Doxygen not found. Attempting to install Doxygen.")

        # Attempt to install Doxygen based on the platform
        if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
            # For Linux systems using apt-get (Debian/Ubuntu)
            execute_process(
                COMMAND apt-get --version
                RESULT_VARIABLE APT_GET_AVAILABLE
                OUTPUT_QUIET ERROR_QUIET
            )

            if(APT_GET_AVAILABLE EQUAL 0)
                message(STATUS "Installing Doxygen using apt-get...")
                execute_process(
                    COMMAND sudo apt-get update && sudo apt-get install -y doxygen
                    RESULT_VARIABLE INSTALL_DOXYGEN_RESULT
                )
            else()
                message(WARNING "apt-get not available. Please install Doxygen manually.")
                set(DOXYGEN_INSTALL_FAILED TRUE)
            endif()
        elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            # For macOS systems using Homebrew
            execute_process(
                COMMAND brew --version
                RESULT_VARIABLE BREW_AVAILABLE
                OUTPUT_QUIET ERROR_QUIET
            )

            if(BREW_AVAILABLE EQUAL 0)
                message(STATUS "Installing Doxygen using Homebrew...")
                execute_process(
                    COMMAND brew install doxygen
                    RESULT_VARIABLE INSTALL_DOXYGEN_RESULT
                )
            else()
                message(WARNING "Homebrew not available. Please install Doxygen manually.")
                set(DOXYGEN_INSTALL_FAILED TRUE)
            endif()
        else()
            message(WARNING "Automatic Doxygen installation is not supported on this platform. Please install Doxygen manually.")
            set(DOXYGEN_INSTALL_FAILED TRUE)
        endif()

        # Re-run find_package after attempting installation
        if(NOT DEFINED DOXYGEN_INSTALL_FAILED)
            find_package(Doxygen QUIET)
            if(DOXYGEN_FOUND)
                message(STATUS "Doxygen installed successfully: ${DOXYGEN_EXECUTABLE}")
            else()
                message(WARNING "Doxygen installation failed or Doxygen not found after installation.")
                set(DOXYGEN_INSTALL_FAILED TRUE)
            endif()
        endif()
    endif()

    if(DOXYGEN_FOUND)
        # Configure and add the docs target
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        if(NOT EXISTS ${DOXYGEN_IN})
            message(FATAL_ERROR "Doxygen input file not found: ${DOXYGEN_IN}")
        endif()

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(WARNING "Doxygen not found. Documentation will not be generated.")
    endif()

endfunction()
