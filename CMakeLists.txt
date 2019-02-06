cmake_minimum_required(VERSION 3.13)
project(ft_ls C)

set(CMAKE_C_STANDARD 99)

add_library(lib1 STATIC IMPORTED)
add_library(lib2 STATIC IMPORTED)
set_property(TARGET lib1 PROPERTY IMPORTED_LOCATION /Users/ggavryly/ClionProjects/ft_ls/libft.a)
set_property(TARGET lib2 PROPERTY IMPORTED_LOCATION /Users/ggavryly/ClionProjects/ft_ls/libftprintf.a)

add_executable(ft_ls
        main.c)

target_link_libraries(ft_ls lib1 lib2)