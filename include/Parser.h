/**
 * @file Parser.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 17-01-2024
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define DEFAULT_WIDTH 1400
#define DEFAULT_HEIGHT 880
#define MIN_WIDTH 720
#define MIN_HEIGHT 480

typedef struct {
    bool flag_help;
    bool flag_width;
    bool flag_full_screen;
    bool flag_difficult_mode;
    int width;
    int height;
} Option;

/**
 * @brief Print the help menu.
 *
 * @param path The path of the executable.
 */
void print_help(char* path);

/**
 * @brief Initialize the option structure.
 *
 * @return Option The initialized option structure.
 */
Option init_option();

/**
 * @brief Parse the command line arguments. With getopt_long.
 *
 * @param argc Argument count.
 * @param argv Argument array.
 * @return Option
 */
Option parser(int argc, char** argv);

#endif  // PARSER_H