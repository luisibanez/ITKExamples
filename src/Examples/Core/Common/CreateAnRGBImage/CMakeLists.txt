cmake_minimum_required( VERSION 2.8 )

project( CreateAnRGBImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAnRGBImage CreateAnRGBImage.cxx )
target_link_libraries( CreateAnRGBImage ${ITK_LIBRARIES} )

install( TARGETS CreateAnRGBImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES CreateAnRGBImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAnRGBImage
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAnRGBImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnRGBImage )
