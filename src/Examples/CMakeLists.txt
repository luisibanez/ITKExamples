find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

if( ${ITK_VERSION_MAJOR} LESS 4 )
  message( SEND_ERROR "ITKExamples require at least ITK 4.0.0" )
endif()

if( BUILD_DOCUMENTATION )
  find_package( PythonInterp )

  # Set here the proper version of Python required to be able to build
  # tarballs for each example
  set( PYTHON_REQUIRED_VERSION 2.7 )
  if( ${PYTHON_VERSION_STRING} LESS ${PYTHON_REQUIRED_VERSION} )
    message( SEND_ERROR "Building the documentation requires Python >= ${PYTHON_REQUIRED_VERSION}" )
  endif()
endif()

# A high level target that the individual targets depend on.
#add_custom_target( CreateTarballs ALL
#  ${CMAKE_COMMAND} -E echo "Done creating individual example tarballs..."
#)

# Macro for adding an example.
#
# Most of the CMake logic for the example should live in the examples
# CMakeLists.txt.  That file should be standalone for building the example.
# This macro is intended to be instantiated in the CMakeLists.txt one directory
# above where the example exists.  It does things like creating the example
# tarball's in the example output directory, and custom targets for building
# the Sphinx documentation for an individual example.  The Sphinx target will be
# called ${example_name}Doc.
macro( add_example example_name )

  if( BUILD_DOCUMENTATION )
    if( SPHINX_HTML_OUTPUT )
      add_custom_target( ${example_name}Tarball
        COMMAND ${PYTHON_EXECUTABLE} ${ITKExamples_SOURCE_DIR}/utilities/CreateTarball.py
          ${example_name} ${SPHINX_DESTINATION}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Creating tarballs for ${example_name}"
        DEPENDS copy_sources
        )
      add_dependencies( CreateTarballs ${example_name}Tarball )
    endif()
  endif()

  # Process the example's CMakeLists.txt
  add_subdirectory( ${example_name} )

endmacro()

# For comparing example outputs to their regression baseline's.
add_executable( ImageCompare ImageCompare.cxx )
target_link_libraries( ImageCompare ${ITK_LIBRARIES} )

# Creates a test that compares the output image of an example to its baseline
# image.  The first argument is the example name.  It is assumed that the
# corresponding test is ${example_name}Test.  The second argument is the
# baseline file prefix.  It expected that the baseline image file will live in
# the source tree at ${example_name}/${baseline_prefix}Baseline.ext.md5 and the
# output of the example to compare against will be placed in the binary tree at
# ${example_name}/${baseline_prefix}.ext.
function( compare_to_baseline example_name baseline_prefix )
  file( GLOB baseline_image ${CMAKE_CURRENT_SOURCE_DIR}/${example_name}/${baseline_prefix}Baseline.* )
  string( REPLACE .md5 "" baseline_image "${baseline_image}" )
  get_filename_component( baseline_image_file "${baseline_image}" NAME )
  set( baseline_image "${CMAKE_CURRENT_BINARY_DIR}/${example_name}/${baseline_image_file}" )
  string( REPLACE Baseline "" test_image "${baseline_image}" )
  add_test( NAME ${example_name}TestBaselineComparison
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImageCompare" "${test_image}" "${baseline_image}"
  )
  set_tests_properties( ${example_name}TestBaselineComparison
    PROPERTIES DEPENDS ${example_name}Test )
endfunction()

add_subdirectory( Bridge )
add_subdirectory( Core )
add_subdirectory( Compatibility )
add_subdirectory( External )
add_subdirectory( Filtering )
add_subdirectory( GPU )
add_subdirectory( IO )
add_subdirectory( Numerics )
add_subdirectory( Registration )
add_subdirectory( Segmentation )
add_subdirectory( Video )
