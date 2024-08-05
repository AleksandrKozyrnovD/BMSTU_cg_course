cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(Cursovaya)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/inc")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/dependencies")

#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse
#remote name - curse


# --- START PROJECT ---


file(GLOB source CONFIGURE_DEPENDS 
                "${SRC_DIR}/*.cpp"
                "${LIB_DIR}/imgui/src/*.cpp" 
)



add_executable(${PROJECT_NAME} ${source})

target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_DIR}/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_DIR}/imgui/inc")

target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/BasicGraphic")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Objects")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Visitor")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Loader")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Scene")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Managers")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/UserInterface")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Canvas")
target_include_directories(${PROJECT_NAME} PUBLIC "${INC_DIR}/Drawer")



# --- END PROJECT ---

# ==================

# --- START DEPENDENCIES ---

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)

# set(DEPS_DIR "${PROJECT_SOURCE_DIR}/dependencies")

# target_include_directories(${PROJECT_NAME} PUBLIC "${DEPS_DIR}/glad/include/")

# add_subdirectory("${DEPS_DIR}/glfw")
# target_link_libraries(${PROJECT_NAME} "glfw")

# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# add_library(gladlib STATIC "${DEPS_DIR}/glad/src/gl.c")
# target_include_directories(gladlib PUBLIC "${DEPS_DIR}/glad/include/")
# target_link_libraries(${PROJECT_NAME} gladlib)

# file(GLOB imguisource CONFIGURE_DEPENDS "${SRC_DIR}/vendor/imgui/*.cpp")
# add_library(imguilib STATIC "${imguisource}")
# target_link_libraries(imguilib "glfw")
# target_link_libraries(${PROJECT_NAME} imguilib)

# --- END DEPENDENCIES ---