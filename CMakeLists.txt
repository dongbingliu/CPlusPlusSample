cmake_minimum_required(VERSION 3.17)
project(CPlusPlusSample)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/
        3rdparty/
        src/jsonutil/
        src/utils/)

file(GLOB SRCS
        src/utils/*)

#add_executable(JsonUtils sample/main.cpp src/jsonutil/CJsonUtils.cpp src/callback/MyCallback.h src/callback/Finance.cpp src/callback/MainCallbackSample.cpp)

add_executable(CallbackSample sample/callback/MyCallback.h sample/callback/Finance.cpp sample/callback/MainCallbackSample.cpp sample/callback/MyFinance.cpp sample/callback/MyFinance.h sample/thread/ThreadSample.cpp sample/thread/ThreadSample.h src/utils/CLog.cpp src/utils/CLog.h)

#C11 Thread sample
add_executable(ThreadSample ${SRCS} sample/thread/ThreadSample.cpp sample/thread/ThreadSample.h sample/thread/threadpool.h)

#pthread 线程sample
add_executable(PThreadSample ${SRCS} sample/thread/PThreadSample.cpp sample/thread/PThreadSample.h)#pthread 线程sample

#add_executable(EncryptedSample ${SRCS} sample/encrypted/EncryptedSample.cpp sample/encrypted/AES.cpp sample/encrypted/AES.cpp)

#ReadInitFile sample
add_executable(ReadIniFileSample ${SRCS} sample/readIniFile/ReadIniFileSample.cpp sample/readIniFile/iniFileUtils.cpp sample/readIniFile/iniFileUtils.h)
