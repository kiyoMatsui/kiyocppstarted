list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/sdl2)


option(BUILDCLIENT  "Build Client" ON)
option(BUILDSERVER  "Build Server" ON)

option(USE_SDL "Enable compilation of SDL sample" ON)
option(USE_BOOST "Enable compilation of boost" ON)

# boost
if(USE_BOOST AND NOT EMSCRIPTEN)
  ## boost include locations when using different boost
  #SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ~/boost_1_76_0/)
  #INCLUDE_DIRECTORIES(SYSTEM ~/boost_1_76_0)

  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  find_package(OpenSSL 1.1.1 REQUIRED)
  INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIRS})
  LINK_DIRECTORIES(${OPENSSL_LIBRARIES})

  find_package(Boost 1.71.0 REQUIRED )
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
endif()  

# sdl
if(USE_SDL AND NOT EMSCRIPTEN)
  #message("Using SDL2")
  #add_subdirectory(sdl)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_gfx REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_ttf REQUIRED)
endif()


# Generic test that uses conan libs
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src/")
INCLUDE_DIRECTORIES(SYSTEM "${PROJECT_SOURCE_DIR}/thirdParty/")
INCLUDE_DIRECTORIES(SYSTEM "${PROJECT_SOURCE_DIR}/thirdParty/sdlgui" ) # needed...
FILE(GLOB_RECURSE ROOTHEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE ROOTSOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE TPARTY_HEADERS ${PROJECT_SOURCE_DIR}/thirdParty/tplib/*.hh)
FILE(GLOB_RECURSE TPARTY_SOURCES ${PROJECT_SOURCE_DIR}/thirdParty/tplib/*.cc)
FILE(GLOB_RECURSE CLIENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/client/*.h)
FILE(GLOB_RECURSE CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)
FILE(GLOB_RECURSE SERVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/server/*.h)
FILE(GLOB_RECURSE SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)

if(USE_SDL AND NOT EMSCRIPTEN)
add_library (
  tplib STATIC
  ${TPARTY_SOURCES}
  ${TPARTY_HEADERS}
)

target_link_libraries (
  tplib PUBLIC
  SDL2::Main
  SDL2::Image
  SDL2::TTF
  SDL2::Mixer
  )
endif()

if(BUILDCLIENT AND NOT EMSCRIPTEN)
add_executable(kiyogameclient clientMain.cpp ${CLIENT_SOURCES} ${ROOTHEADERS} )
target_link_libraries(
  kiyogameclient
  PRIVATE project_options
  project_warnings
  Threads::Threads
  tplib

#          CONAN_PKG::docopt.cpp
#          CONAN_PKG::fmt
#          CONAN_PKG::spdlog)
)


endif()

if(BUILDSERVER AND NOT EMSCRIPTEN)
add_executable(beastserver serverMain.cpp ${SERVER_SOURCES} ${ROOTHEADERS} )
target_link_libraries(
  beastserver
  PRIVATE project_options
  project_warnings
  Threads::Threads
  tplib
#          CONAN_PKG::docopt.cpp
#          CONAN_PKG::fmt
#          CONAN_PKG::spdlog)
)

endif()

if(EMSCRIPTEN)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -O2 -gsource-map -s PTHREAD_POOL_SIZE=4 -s INITIAL_MEMORY=1073741824 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2  --preload-file ./resources  --source-map-base https://192.168.1.139/ --emrun")
add_library (
  tplib STATIC
  ${TPARTY_SOURCES}
)

target_link_libraries (
  tplib PUBLIC
  )

  
add_executable(emscriptenclient clientMain.cpp ${CLIENT_SOURCES}  )
target_link_libraries(
  emscriptenclient
  tplib
)


endif()
