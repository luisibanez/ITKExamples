cmake_minimum_required( VERSION 2.8 )

project( ComputeTimeBetweenPoints )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputeTimeBetweenPoints ComputeTimeBetweenPoints.cxx )
target_link_libraries( ComputeTimeBetweenPoints ${ITK_LIBRARIES} )

install( TARGETS ComputeTimeBetweenPoints
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES ComputeTimeBetweenPoints.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ComputeTimeBetweenPoints
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeTimeBetweenPointsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeTimeBetweenPoints )
