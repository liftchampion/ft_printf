cmake_minimum_required(VERSION 3.13)
project(printf1 C)

set(CMAKE_C_STANDARD 11)

FILE(GLOB LIBFT_SRCS ./libft/*.c)

FILE(GLOB LIBFT_HEADERS ./libft/*.h)

#add_library(object_lib OBJECT libft/libft.a)

include_directories(./libft/)

#add_custom_target(extern_lib libft/libft.a)

#add_library(libft STATIC IMPORTED libft/libft.a)



add_executable(printf1 main.c ${LIBFT_SRCS} ${LIBFT_HEADERS}
        ft_find_cntrl.c ft_set_color.c
        ft_printf.c ft_printf.h
        ft_printf_parser.c ft_printf_parser.h ft_printf_parser_arg_data_setters.c
        ft_printf_parser_flags_proceeding.c
        ft_stringify.c ft_printf_compose.c
        ft_printf_int_compose.c
        ft_printf_float_compose.c
        libft/ft_tolower_str.c libft/ft_toupper_str.c libft/ft_int_to_unicode.c ft_printf_string_compose.c libft/ft_intlen.c ft_printf_date_compose.c ft_unixtime.h ft_unixtime.c ft_unixtime_utils.c ft_float_compose_utils.c)
#target_link_libraries(printf1 "/Users/ggerardy/CLION/printf1/libft/libft.a")