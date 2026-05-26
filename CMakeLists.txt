cmake_minimum_required(VERSION 3.10)

project(voyageur_de_commerce)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:/SFML/include")
link_directories("C:/SFML/lib")

add_executable(voyageur_de_commerce
    main.cpp
    tsp.cpp
    algorithmes.cpp
    affichage.cpp
)

target_link_libraries(voyageur_de_commerce
    sfml-graphics
    sfml-window
    sfml-system
)