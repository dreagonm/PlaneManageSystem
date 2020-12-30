cmake_minimum_required(VERSION 3.17)
project(PlaneManageSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(PlaneManageSystem main.cpp database/database.cpp database/database.h backend/backend.cpp backend/backend.h lib/serializer.cpp lib/serializer.h frontend/frontend.cpp frontend/frontend.h tests/test_database.cpp tests/test_database.h global_config.h lib/filetool.cpp lib/filetool.h)