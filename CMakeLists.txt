cmake_minimum_required( VERSION 2.8.5 )
project( ITKExamples )

set( ITKExamples_MAJOR_VERSION 4 )
set( ITKExamples_MINOR_VERSION 0 )
set( ITKExamples_PATCH_VERSION 0 )

set( ITKExamples_VERSION
  "${ITKExamples_MAJOR_VERSION}.${ITKExamples_MINOR_VERSION}"
)

set( ITKExamples_RELEASE_VERSION
   "${ITKExamples_MAJOR_VERSION}.${ITKExamples_MINOR_VERSION}.${ITKExamples_PATCH_VERSION}"
)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ITKExamples_BINARY_DIR}/bin )

# -------------------------------------------------------------------------
# Check to make sure the submodules have been created.
if( NOT EXISTS "${ITKExamples_SOURCE_DIR}/utilities/ext/breathelink/.git" )
  message( SEND_ERROR "The git submodules are not available.  Please run
  git submodule update --init --recursive"
  )
endif()

if( NOT EXISTS "${ITKExamples_SOURCE_DIR}/utilities/ext/breathe/.git" )
  message( SEND_ERROR "The git submodules are not available.  Please run
  git submodule update --init --recursive"
  )
endif()

if( NOT EXISTS "${ITKExamples_SOURCE_DIR}/utilities/ext/gitstats/.git" )
  message( SEND_ERROR "The git submodules are not available.  Please run
  git submodule update --init --recursive"
  )
endif()
# -------------------------------------------------------------------------

include( CTest )
# Tests are added with add_test() can be run with the 'ctest' command line program.
enable_testing()

# ExternalData setup.  We use the CMake ExternalData features to download binary
# files from a configurable location(s) -- including the local filesystem -- to
# avoid storing the potentially large files in the Git history.
set( CMAKE_MODULE_PATH ${ITKExamples_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )
# The CMake magic to download the data.
set( ExternalData_SOURCE_ROOT "${ITKExamples_SOURCE_DIR}" )
set( ExternalData_BINARY_ROOT "${ITKExamples_BINARY_DIR}" )

include( ITKExamplesExternalData )
set( _RootSubDirs
  cmake
  formatting
  utilities
  src
  superbuild
)

set( content_links )

# By default we copy all the content links in the source tree to their
# corresponding locations in the binary tree.
foreach( _dir ${_RootSubDirs} )
  file( GLOB_RECURSE ${_dir}_content_links
    RELATIVE "${ITKExamples_SOURCE_DIR}" "${_dir}/*.md5" )
  set( content_links ${content_links} ${${_dir}_content_links} )
endforeach()

foreach(link ${content_links})
  string( REGEX REPLACE "\\.md5$" "" link ${link} )
  ExternalData_Expand_Arguments( ITKExamplesData
    link_location
    DATA{${link}}
  )
endforeach()
ExternalData_Add_Target( ITKExamplesData )

# Build the documentation?
option( BUILD_DOCUMENTATION "Build the examples documentation." OFF )
if( BUILD_DOCUMENTATION )

  # We must also duplicate the source tree since the images need to be present
  # with the source.
  add_custom_target( copy_sources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKExamples_SOURCE_DIR}/src"
    "${ITKExamples_BINARY_DIR}/src"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKExamples_SOURCE_DIR}/formatting"
    "${ITKExamples_BINARY_DIR}/formatting"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKExamples_SOURCE_DIR}/utilities"
    "${ITKExamples_BINARY_DIR}/utilities"
    COMMENT "Copying sources"
    )
  # For unknown reasons, this was the only effective way to ensure ITKExamplesData
  # was built before build_html.
  add_dependencies( copy_sources ITKExamplesData )

  execute_process( COMMAND ${ITKExamples_SOURCE_DIR}/utilities/ext/gitstats/gitstats --rst
    ${ITKExamples_SOURCE_DIR} ${ITKExamples_BINARY_DIR}/src/gitstats
    WORKING_DIRECTORY ${ITKExamples_BINARY_DIR}
    OUTPUT_QUIET
    )

  configure_file( ${ITKExamples_SOURCE_DIR}/utilities/CodeSwarm.sh.in
    ${ITKExamples_BINARY_DIR}/utilities/CodeSwarm.sh
    @ONLY
  )

  # A high level target that the individual targets depend on.
  add_custom_target( CreateTarballs ALL
    ${CMAKE_COMMAND} -E echo "Done creating individual example tarballs..."
  )

  if(NOT ITKDoxygenXML_DIR )
    include( ${CMAKE_SOURCE_DIR}/cmake/ITKDoxygenXML.cmake )
  endif()

  if(NOT ITKDoxygenTAG_DIR )
    include( ${CMAKE_SOURCE_DIR}/cmake/ITKDoxygenTAG.cmake )
  endif()

  # Builds the documentation.
  find_package( Sphinx REQUIRED )

  set( SPHINX_CONF_DIR ${ITKExamples_BINARY_DIR}/formatting )
  set( SPHINX_INPUT_DIR ${ITKExamples_BINARY_DIR}/src )
  set( SPHINX_DESTINATION ${ITKExamples_BINARY_DIR} )
  set( SPHINX_DEPENDENCIES copy_sources ITKDoxygenXML ITKExamplesData ITKDoxygenTAG CreateTarballs )

  option( DOC_WITH_LOCAL_DOXYGEN "Generate documentation with local doxygen" ON )

  if( DOC_WITH_LOCAL_DOXYGEN )
    set( ITKDoxygen_LINK_ADDRESS ${ITKDoxygen_DIR} )
    set( SPHINX_DEPENDENCIES ${SPHINX_DEPENDENCIES} ITKDoxygen )
    if(NOT ITKDoxygen_DIR )
      include( ${CMAKE_SOURCE_DIR}/cmake/ITKDoxygen.cmake )
    endif()
  else()
    set( ITKDoxygen_LINK_ADDRESS "http://www.itk.org/Doxygen/html" )
  endif()

  Sphinx_add_targets( build ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${SPHINX_DESTINATION} ${SPHINX_DEPENDENCIES} )

  if( ${SPHINX_HTML_OUTPUT} )
    install( DIRECTORY ${SPHINX_DESTINATION}/html
      DESTINATION share/ITKExamples/doc
      COMPONENT Doc
      PATTERN "${SPHINX_DESTINATION}/html/*"
    )
  endif()

  if( ${SPHINX_LATEX_OUTPUT} )
    # Build the PDF with pdflatex
    find_package( LATEX )
    if( NOT PDFLATEX_COMPILER )
      message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
    else()
      # Needs to be executed twice to get table of contents.
      add_custom_command( TARGET build_latex
        POST_BUILD
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/ITKExamples.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/ITKExamples.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        WORKING_DIRECTORY ${SPHINX_DESTINATION}/latex
        COMMENT "Building PDF"
        )

    install( FILES ${SPHINX_DESTINATION}/latex/ITKExamples.pdf
      DESTINATION share/ITKExamples/doc/pdf
      COMPONENT Doc
      )
    endif()
  endif()

  add_subdirectory( formatting )
endif()

# Build the example executables?
option( BUILD_EXECUTABLES "Build the example executables." ON )
if( BUILD_EXECUTABLES )
  add_subdirectory( src )
endif()

configure_file( ${CMAKE_SOURCE_DIR}/utilities/CreateNewExample.py.in
  ${CMAKE_BINARY_DIR}/utilities/CreateNewExample.py
  @ONLY
)

include( CPack )
