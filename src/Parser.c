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
        "%s [-w int] [-f] [-h]\n\n"
        "-w / --width (int) :\n"
        "\t Change the width of the grahpic window.\n\n"
        "-f / --full-screen :\n"
        "\t Change the grahpic window to full-screen mode (ignore -w).\n\n"
        "-h / --help :\n"
        "\t Prints this menu.\n\n",
        path);
}

Option init_option() {
    return (Option){.flag_help = 0,
                    .flag_width = 0,
                    .flag_full_screen = 0,
                    .width = DEFAULT_WIDTH};
}

Option parser(int argc, char** argv) {
    Option option = init_option();
    int option_index = 0, opt, r, ok;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"width", required_argument, 0, 'w'},
        {"full-screen", no_argument, 0, 'f'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "hw:f", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'w':
                ok = sscanf(optarg, "%d", &r);
                if (ok == 1) {
                    option.flag_width = 1;
                    option.width = r;
                } else {
                    fprintf(stderr, "/!\\ Unexpected character in -r option /!\\ \n");
                    fprintf(stderr, "Modification will not be considered.\n");
                }
                break;

            case 'f':
                option.flag_full_screen = 1;
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