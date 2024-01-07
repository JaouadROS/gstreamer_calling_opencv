cmake_minimum_required(VERSION 3.5)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(OPENCV REQUIRED opencv4)

include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    ${OPENCV_INCLUDE_DIRS}
)

add_library(cvimageprocessing SHARED ${CMAKE_CURRENT_SOURCE_DIR}/gst_opencv_call_plugin.cpp)
target_link_libraries(cvimageprocessing PUBLIC
    ${GSTREAMER_LIBRARIES}
    ${OPENCV_LIBRARIES}
    gstopencv-1.0
)

install(TARGETS
        cvimageprocessing
        LIBRARY DESTINATION /usr/lib/gstreamer-1.0)

add_executable(gstImageProcessor main.cpp)
target_link_libraries(gstImageProcessor PRIVATE
    ${GSTREAMER_LIBRARIES}
    ${OPENCV_LIBRARIES}
)