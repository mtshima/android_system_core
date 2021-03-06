#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern int setxattr(const char *, const char *, const void *, size_t, int);

static int usage(const char *s)
{
    fprintf(stderr, "Usage: %s -n name -v value pathname\n", s);
    fprintf(stderr, "  -n name      name of the extended attribute to set\n");
    fprintf(stderr, "  -v value     new value of the attribute\n");
    fprintf(stderr, "  -h           display this help and exit\n");

    exit(10);
}

int setfattr_main(int argc, char **argv)
{
    int i;
    char *name = NULL;
    char *valuestr = NULL;

    for (;;) {
        int ret;

        ret = getopt(argc, argv, "hn:v:");

        if (ret < 0)
            break;

        switch(ret) {
            case 'h':
                usage(argv[0]);
                break;
            case 'n':
                name = optarg;
                break;
            case 'v':
                valuestr = optarg;
                break;
        }
    }

    if (!name || !valuestr || optind == argc)
        usage(argv[0]);

    for (i = optind ; i < argc ; i++)
        setxattr(argv[i], name, valuestr, strlen(valuestr), 0);

    return 0;
}
