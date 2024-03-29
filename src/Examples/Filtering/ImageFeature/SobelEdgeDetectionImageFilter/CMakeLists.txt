cmake_minimum_required( VERSION 2.8 )

project( SobelEdgeDetectionImageFilter )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( SobelEdgeDetectionImageFilter SobelEdgeDetectionImageFilter.cxx )
target_link_libraries( SobelEdgeDetectionImageFilter ${ITK_LIBRARIES} )

install( TARGETS SobelEdgeDetectionImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES SobelEdgeDetectionImageFilter.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/SobelEdgeDetectionImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME SobelEdgeDetectionImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SobelEdgeDetectionImageFilter CellsFluorescence1.png SobelEdgeDectionImageFilterOutput.png
)
