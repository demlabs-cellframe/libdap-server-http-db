cmake_minimum_required(VERSION 2.8)
project (dap_server_http_db_auth)

# fix implicit declaration warnings
add_definitions ("-D_GNU_SOURCE")

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")

 

if(WIN32)
  include_directories(../libdap/src/win32/)
  include_directories(../3rdparty/libmemcached/)
  include_directories(../3rdparty/libmemcached/win32/)
  include_directories(../3rdparty/wepoll/include/)
  include_directories(../3rdparty/uthash/src/)
  include_directories(../3rdparty/libjson-c/)
  include_directories(../3rdparty/libmagic/src/)
  include_directories(../3rdparty/curl/include/)
  include_directories(../3rdparty/libsqlite3/)
else()
    find_package(PkgConfig)
    pkg_check_modules(MONGO REQUIRED libmongoc-1.0)
    pkg_check_modules(BSON REQUIRED libbson-1.0)
endif()



file(GLOB FILE_SOURCES *.c)
file(GLOB FILE_HEADERS *.h)

set(SOURCES db_core.c  db_http.c  db_http_file.c)

add_library(${PROJECT_NAME} STATIC ${DB_SRCS})



add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

target_link_libraries(${PROJECT_NAME} dap_core dap_crypto dap_http_server dap_enc_server
    ${BSON_LIBRARIES} ${MONGO_LIBRARIES})
target_include_directories(${PROJECT_NAME} INTERFACE .
    PUBLIC ${BSON_INCLUDE_DIRS} ${MONGO_INCLUDE_DIRS}
    )


#set(${PROJECT_NAME}_DEFINITIONS CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
#set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
