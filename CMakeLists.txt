cmake_minimum_required(VERSION 2.8)
project (dap_server_http_db)

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



file(GLOB DAP_SERVER_HTTP_DB_SOURCES src/*.c)
file(GLOB DAP_SERVER_HTTP_DB_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${DAP_SERVER_HTTP_DB_SOURCES} ${DAP_SERVER_HTTP_DB_HEADERS} )

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} dap_core dap_crypto dap_http_server dap_enc_server
    ${BSON_LIBRARIES} ${MONGO_LIBRARIES})
target_include_directories(${PROJECT_NAME} INTERFACE .
    PUBLIC ${BSON_INCLUDE_DIRS} ${MONGO_INCLUDE_DIRS}
    )
