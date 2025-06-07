
cmake_minimum_required(VERSION 3.22.1)

project("test")
# 设置编译器选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(
         ${CMAKE_CURRENT_SOURCE_DIR}/jni/static-libs/include
         ${CMAKE_CURRENT_SOURCE_DIR}/jni/static-libs/include
         ${CMAKE_CURRENT_SOURCE_DIR}/jni/static-libs/include)
add_library(z STATIC IMPORTED)
set_target_properties(z PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jni/static-libs/${ANDROID_ABI}/libz.a  # ${ANDROID_ABI} 自动匹配当前 ABI（如 armeabi-v7a）:ml-citation{ref="5,6" data="citationList"}
)
add_library(json STATIC IMPORTED)
set_target_properties(json PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jni/static-libs/${ANDROID_ABI}/libjsoncpp.a  # ${ANDROID_ABI} 自动匹配当前 ABI（如 armeabi-v7a）:ml-citation{ref="5,6" data="citationList"}
)
# 引入 libssl.a
add_library(ssl STATIC IMPORTED)
set_target_properties(ssl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jni/static-libs/${ANDROID_ABI}/libssl.a
)

add_library(curl STATIC IMPORTED)
set_target_properties(curl PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jni/static-libs/${ANDROID_ABI}/libcurl.a
)
add_library(crypto STATIC IMPORTED)
set_target_properties(crypto PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jni/static-libs/${ANDROID_ABI}/libcrypto.a
)

add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        ${CMAKE_SOURCE_DIR}/jni/src/native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        crypto
        ssl
        json
        curl
         "-Wl,--unresolved-symbols=ignore-all"
       )
set(CMAKE_CXX_FLAGS "-mllvm -sub -mllvm -bcf -mllvm -sobf")


