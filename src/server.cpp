#include <iostream>
#include <getopt.h>

// TODO
static const char short_opts[] = "";

static const struct option long_opts[] = {
    {NULL,      0, NULL , 0},
};

int main(int argc, char **argv) {
    int c{};
    int flg{};

    while((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) >= 0) {
        switch(c) {
        }
    }

    return 0;
}