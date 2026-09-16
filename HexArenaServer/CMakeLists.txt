cmake_minimum_required(VERSION 4.3)
project(HexArenaServer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_NAME HexArenaServer)

# ============================================
# Find System Dependencies
# ============================================
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Automatically download and include json library
include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

file(GLOB USOCKETS_SRC
        "external/uWebSockets/uSockets/src/*.c"
        "external/uWebSockets/uSockets/src/eventing/*.c"
        "external/uWebSockets/uSockets/src/crypto/*.c"
        "external/uWebSockets/uSockets/src/crypto/*.cpp"
)
add_library(uSockets STATIC ${USOCKETS_SRC})
target_compile_definitions(uSockets PUBLIC LIBUS_USE_EPOLL LIBUS_USE_OPENSSL)
target_include_directories(uSockets PUBLIC external/uWebSockets/uSockets/src)

# ============================================
# Build the Application
# ============================================
file(GLOB TARGET_SOURCES "src/*.cpp")
list(FILTER TARGET_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

add_library(app_lib STATIC ${TARGET_SOURCES})
target_include_directories(app_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        external/uWebSockets/src
        external/uWebSockets/uSockets/src
)

add_executable(${TARGET_NAME} src/main.cpp)

target_include_directories(${TARGET_NAME} PRIVATE
        external/uWebSockets/src
        external/uWebSockets/uSockets/src
)

target_link_libraries(${TARGET_NAME} PRIVATE
        app_lib
        uSockets
        ZLIB::ZLIB
        OpenSSL::SSL
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json
)

# Compiler warnings (because we're professionals)
if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
        target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()