cmake_minimum_required(VERSION 3.12.0)
project(CppStudy VERSION 0.1.0 LANGUAGES C CXX)


#set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
#set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

#include_directories(${INCLUDE_DIR})

#file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

#add_executable(CppStudy ${SOURCES} ${INCLUDE_DIR}/headertry.h)


add_executable(CondVar ${PROJECT_SOURCE_DIR}/src/CondVar.cpp)
#add_executable(deadlock ${PROJECT_SOURCEDIR}/src/deadlock.cpp)
add_executable(LockGaurd ${PROJECT_SOURCE_DIR}/src/LockGaurd.cpp)
add_executable(ScopedLock ${PROJECT_SOURCE_DIR}/src/ScopedLock.cpp)
add_executable(SharingOneMutex ${PROJECT_SOURCE_DIR}/src/SharingOneMutex.cpp)
add_executable(Overloading ${PROJECT_SOURCE_DIR}/src/overloading.cpp)

#target_compile_features(CppStudy PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


