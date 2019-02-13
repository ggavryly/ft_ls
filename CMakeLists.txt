cmake_minimum_required(VERSION 3.13)
project(1 C)

set(CMAKE_C_STANDARD 99)

add_library(lib1 STATIC IMPORTED)
add_library(lib2 STATIC IMPORTED)
set_property(TARGET lib1 PROPERTY IMPORTED_LOCATION /Users/ggavryly/Desktop/git_ft_ls/1/libft.a)
set_property(TARGET lib2 PROPERTY IMPORTED_LOCATION /Users/ggavryly/Desktop/git_ft_ls/1/libftprintf.a)

add_executable(1
        src/init_info.c
        src/errors.c
        src/path_manage.c
        src/list_job.c
        src/display.c
        src/parse_flags.c
        src/main.c
        src/sort_list.c)

target_link_libraries(1 lib1 lib2)