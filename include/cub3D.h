#ifndef CUB3D_H
# define CUB3D_H

#include "debug.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1

typedef struct s_settings
{
    char *rp_no;
    char *rp_so;
    char *rp_we;
    char *rp_ea;
    int floor_r;
    int floor_g;
    int floor_b;
    int cell_r;
    int cell_g;
    int cell_b;
}						t_settings;
#endif