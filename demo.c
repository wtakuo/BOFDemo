/*
 * BOFDemo: A simple buffer overflow vulnerability demo for IA-32
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int dump_stack = 0;

unsigned char pc(unsigned char c) {
    return c < 32 || c > 126 ? '.' : c;
}

void stack_dump(void *p, int n) {
    unsigned int *up = (unsigned int *)p;
    printf("----------------------------------------------\n");
    printf(" #  |   addr  |  uint    | +0 +1 +2 +3 | 0123 \n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        unsigned char *ub = (unsigned char *)&up[i];
        printf("%3d | %08x| %08x", i, (unsigned int)&up[i], up[i]);
        printf(" | %02x %02x %02x %02x", ub[0], ub[1], ub[2], ub[3]);
        printf(" | %c%c%c%c\n",
               pc(ub[0]), pc(ub[1]), pc(ub[2]), pc(ub[3]));
    }
    printf("----------------------------------------------\n");
}

int f(char *input) {
    char buf[64];
    strcpy(buf, input);
    if (dump_stack)
        stack_dump(buf, 32);
    int a = atoi(buf);
    return a * a;
}

void usage(char *name) {
    fprintf(stderr, "usage: %s [-d] file\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int opt;
    char *this = argv[0];
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
        case 'd':
            dump_stack = 1;
            break;
        default:
            usage(this);
        }
    }
    if (argc - optind != 1)
        usage(this);
    char *dat_file = argv[optind];
    FILE *in = fopen(dat_file, "r");
    if (in == NULL) {
        perror(dat_file);
        exit(EXIT_FAILURE);
    }
    char input[1024];
    if (fgets(input, sizeof(input), in) != NULL)
        printf("%d\n", f(input));
    fclose(in);
    return EXIT_SUCCESS;
}
