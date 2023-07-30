#include <stdio.h>

void test() {
    FILE *file_stream = fopen("./mafile", "r");

    if (file_stream == NULL) {
        printf("File stream is null");
        return;
    }

    // reading file one character at a time
    int c = fgetc(file_stream);

    while (c != EOF) {
        printf("c=%c\n",(char)c);
        c = fgetc(file_stream);
    }
}

void read_write_binary() {
    FILE *in, *out;

    struct pirate {
        char name[100];
        unsigned long bounty;
        unsigned int beard_len;
    } p, blackbeard = { "Edward Teach", 950, 49 };

    out =  fopen("test_files/data", "w");

    if (!out) {
        perror("fopen");
        return;
    }

    // if (!fwrite(&blackbeard, sizeof (struct pirate), 1, out)) {
    //     perror("fwrite");
    //     return;
    // }

    if (fclose(out)) {
        perror("fclose");
        return;
    }

    in =  fopen("test_files/data", "r");

    if (!in) {
        perror("fopen");
        return;
    }

    if (!fread(&p, sizeof (struct pirate), 1, in)) {
        perror("fread");
        return;
    }

    if (fclose(in)) {
        perror("fclose");
        return;
    }

    printf("name='%s' bounty=%lu beard_len=%u\n", p.name, p.bounty, p.beard_len);
}

int main() {
    read_write_binary();
    return 0;
}
