#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.0.1"
#define TABSTOP (8)

void detab(FILE*);
void usage(void);

main(int argc, char** argv)
{
    FILE* target;

    if (argc > 2) {
        fprintf(stderr, "detab: too much argument.\n");
        usage();
        return 2;
    }

    if (argc == 1)
        target = stdin;
    else {
        if (strcmp(argv[1], "--help") == 0) {
            printf(
                    "usage: detab [FILENAME]\n"
                    "   expand tab to space.\n"
                    "   An implementation of K&R 1-20.\n"
                    "\n"
                    "   options:\n"
                    "       --version  print version of detab.\n"
                    "       --help     print this help.\n");
            return 0;
        }
        if (strcmp(argv[1], "--version") == 0) {
            printf(
                    "detab %s in\n"
                    "\n"
                    "Written by Yutaka Goy,\n"
                    "in C, on 2025-08-27.\n", VERSION);
            return 0;
        }

        target = fopen(argv[1], "r");
        if (target == NULL) {
            fprintf(stderr, "detab: %s: no such file.\n", argv[1]);
            return 1;
        }
    }

    detab(target);

    if (target != stdin)
        fclose(target);

    return 0;
}

void usage(void)
{
    fprintf(stderr, "detab: usage: detab [FILENAME].\n");
    fprintf(stderr, "Use `detab --help` for more information.\n");
    return;
}

void detab(FILE* fp)
{
    int c, i;
    int space = TABSTOP;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\t') {
            for (i = 0; i < space; i++)
                putchar(' ');
            space = TABSTOP;
        } else {
            putchar(c);

            if (c == '\n')
                space = TABSTOP;
            else if (c >= ' ' || c != 127)
                space = ((space <= 1) ? TABSTOP : (space-1));
        }
    }

    return;
}
