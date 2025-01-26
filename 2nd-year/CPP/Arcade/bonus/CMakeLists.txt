cmake_minimum_required(VERSION 3.10)
project(B_OOP_400)
INCLUDE(FindPkgConfig)
add_compile_options(-Wall -Wextra -g -std=c++20)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../lib/")

add_executable(arcade Core.cpp main.cpp Time.cpp LibHandler.cpp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

add_library(arcade_sfml SHARED graphical/SFML/SFMLEvent.cpp graphical/SFML/SFMLModule.cpp graphical/SFML/SFMLWindow.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp graphical/EventInfo.cpp)
set_target_properties(arcade_sfml PROPERTIES PREFIX "")
target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system)

add_library(arcade_sdl2 SHARED graphical/SDL2/SDLEvent.cpp graphical/SDL2/SDL2Module.cpp graphical/SDL2/SDLWindow.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp graphical/EventInfo.cpp)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
target_link_libraries(arcade_sdl2 ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

add_library(arcade_snake SHARED game/snake/snake.cpp game/AGameModule.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp)
set_target_properties(arcade_snake PROPERTIES PREFIX "")
target_link_libraries(arcade_snake vlc)

add_library(arcade_menu SHARED game/menu/menu.cpp game/AGameModule.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp LibHandler.cpp)
set_target_properties(arcade_menu PROPERTIES PREFIX "")
target_link_libraries(arcade_menu vlc)

add_library(arcade_solarfox SHARED game/solarfox/solarfox.cpp game/AGameModule.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp)
set_target_properties(arcade_solarfox PROPERTIES PREFIX "")
target_link_libraries(arcade_solarfox vlc)

add_library(arcade_ncurses SHARED graphical/NCURSES/NCURSESEvent.cpp graphical/NCURSES/NCURSESModule.cpp graphical/NCURSES/NCURSESWindow.cpp game/APixels.cpp game/Pixel.cpp game/ATexts.cpp game/Text.cpp graphical/EventInfo.cpp)
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
target_link_libraries(arcade_ncurses ncurses)
