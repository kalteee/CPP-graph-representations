cmake_minimum_required(VERSION 3.10)
project(GraphImplementation)

# C++ szabvány beállítása (C++17 ajánlott a structured binding-ok miatt, pl. auto [u,v])
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Keresd meg az összes .cpp fájlt a src könyvtárban és alkönyvtáraiban
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Hozd létre a futtatható fájlt a forráskódokból
add_executable(graph_app ${SOURCES})

# Fejlécek (header-ek) elérésének megadása
target_include_directories(graph_app PRIVATE include)
