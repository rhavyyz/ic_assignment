cmake_minimum_required(VERSION 3.12)
project(dummy)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_EXTENSIONS Off)
cmake_policy(SET CMP0072 NEW)


set(agent 
  ${PROJECT_SOURCE_DIR}/src/agent/
  )


set(sensor
${PROJECT_SOURCE_DIR}/src/agent/sensor/
)


set(actuator 
${PROJECT_SOURCE_DIR}/src/agent/actuator/
)

set(environment 
  ${PROJECT_SOURCE_DIR}/src/environment/
)

set(floor_utils
  ${PROJECT_SOURCE_DIR}/src/floor_utils/
)

set(logging
  ${PROJECT_SOURCE_DIR}/src/logging/
)

add_executable(dummy dummy.cpp 
                    src/agent/agent.cpp                
)
add_executable(smart smart.cpp 
                    src/agent/agent.cpp                
)

target_include_directories(smart PUBLIC ${floor_utils})
target_include_directories(smart PUBLIC ${logging})
target_include_directories(smart PUBLIC ${sensor})
target_include_directories(smart PUBLIC ${actuator})
target_include_directories(smart PUBLIC ${agent})
target_include_directories(smart PUBLIC ${environment})


target_include_directories(dummy PUBLIC ${floor_utils})
target_include_directories(dummy PUBLIC ${logging})
target_include_directories(dummy PUBLIC ${sensor})
target_include_directories(dummy PUBLIC ${actuator})
target_include_directories(dummy PUBLIC ${agent})
target_include_directories(dummy PUBLIC ${environment})


# target_link_libraries()

# target_include_directories(server PUBLIC ${utils})
# target_include_directories(server PUBLIC ${types})
# target_include_directories(server PUBLIC ${server_src})
# target_include_directories(server PUBLIC ${modules})
# target_sources(server PUBLIC ${server_source})
# CMakeLists.txt
# ...
# add_library(foo ...)
# ...
# find_package(nlohmann_json 3.2.0 REQUIRED)
# target_link_libraries(server PUBLIC_HEADER nlohmann_json::nlohmann_json)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    CXX_STANDARD 20
)

# target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
# target_include_directories(${PROJECT_NAME} PUBLIC ${sources})
