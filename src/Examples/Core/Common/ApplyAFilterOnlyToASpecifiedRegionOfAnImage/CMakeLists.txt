cmake_minimum_required( VERSION 2.8 )

project( ApplyAFilterOnlyToASpecifiedRegionOfAnImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ApplyAFilterOnlyToASpecifiedRegionOfAnImage ApplyAFilterOnlyToASpecifiedRegionOfAnImage.cxx )
target_link_libraries( ApplyAFilterOnlyToASpecifiedRegionOfAnImage ${ITK_LIBRARIES} )

install( TARGETS ApplyAFilterOnlyToASpecifiedRegionOfAnImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES ApplyAFilterOnlyToASpecifiedRegionOfAnImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ApplyAFilterOnlyToASpecifiedRegionOfAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAFilterOnlyToASpecifiedRegionOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAFilterOnlyToASpecifiedRegionOfAnImage )
