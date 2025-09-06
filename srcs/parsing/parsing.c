#include <unistd.h> //write
#include "cub3D.h"

int parsing(int argc, char *argv[])
{
    argc = 0;
    argv[0] = NULL;
    write(1,"got into parsing\n", 17);
    return (0);
}