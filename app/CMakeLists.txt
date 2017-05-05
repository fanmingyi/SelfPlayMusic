
#cmake最小支持版本
cmake_minimum_required(VERSION 3.4.1)
#添加函数库
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

#设置变量
set(libs "${CMAKE_SOURCE_DIR}/src/main/jniLibs")
#添加预编译so库
add_library(fmod-lib SHARED IMPORTED )
#设置预编译so库文件
set_target_properties( # Specifies the target library.
                      fmod-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                     "${libs}/${ANDROID_ABI}/libfmodL.so")
 #导入so的头文件 这样不写也可以 但是导入的时候需要写
 # #include"inc/xxx" 写下面这句话之后可以直接 #include"xxxx"
include_directories(  src/main/cpp/inc  )


#链接so库文件
target_link_libraries(
                       native-lib
                       #导入fmod源码
                        fmod-lib
                     )