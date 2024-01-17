/**
 * @file Parser.h
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 17-01-2024
 *
 */

#ifndef PARSER_H
#define PARSER_H

#define DEFAULT_WIDTH 1400
#define DEFAULT_HEIGHT 880

typedef struct {
    int flag_help;
    int flag_width;
    int flag_full_screen;
    int width;
    int height;
} Option;

void print_help(char* path);

Option init_option();

Option parser(int argc, char** argv);

#endif  // PARSER_H