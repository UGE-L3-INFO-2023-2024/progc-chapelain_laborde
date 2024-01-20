/**
 * @file Parser.c
 * @author CHAPELAIN Nathan & LABORDE Quentin
 * @brief
 * @date 17-01-2024
 *
 */

#include "Parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void print_help(char* path) {
    printf(
        "\ngemcraft helper :\n\n"
        "%s [-w WIDTHxHEIGHT] [-f] [-d] [-h]\n\n"
        "-w / --window (WIDTHxHEIGHT) :\n"
        "\t Change the width of the graphic window. (minimum size 720x480)\n\n"
        "-f / --full-screen :\n"
        "\t Change the graphic window to full-screen mode (ignore -w).\n\n"
        "-d / --difficult-mode :\n"
        "\t Make the game harder : when the user skip wave it will no longer gain mana.\n\n"
        "-h / --help :\n"
        "\t Print this menu.\n\n",
        path);
}

Option init_option() {
    return (Option){.flag_help = 0,
                    .flag_width = 0,
                    .flag_full_screen = 0,
                    .flag_difficult_mode = 0,
                    .width = DEFAULT_WIDTH,
                    .height = DEFAULT_HEIGHT};
}

Option parser(int argc, char** argv) {
    Option option = init_option();
    int option_index = 0;
    int opt;
    int w;
    int h;
    int ok;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"window", required_argument, 0, 'w'},
        {"full-screen", no_argument, 0, 'f'},
        {"difficult-mode", no_argument, 0, 'd'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "hw:fd", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'w':
                ok = sscanf(optarg, "%dx%d", &w, &h);
                if (ok == 2 && w >= MIN_HEIGHT && h >= MIN_WIDTH) {
                    option.flag_width = 1;
                    option.width = w;
                    option.height = h;
                } else {
                    fprintf(stderr, "/!\\ Unexpected character in -w option /!\\ \n");
                    fprintf(stderr, "Modification will not be considered.\n");
                }
                break;

            case 'f':
                option.flag_full_screen = 1;
                break;

            case 'd':
                option.flag_difficult_mode = 1;
                break;

            case 'h':
                option.flag_help = 1;
                print_help(argv[0]);
                break;

            default:
                break;
        }
    }
    return option;
}