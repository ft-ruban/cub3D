#ifndef CUB3D_H
# define CUB3D_H

#include "debug.h"
//#include "utils.h"
#include <stdlib.h> //size_t

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1

typedef enum e_error_status
{
    ALL_OK ,
	MAL_ERR_SET = 1 ,
    ERR ,
    PAR_NBR_ARGC ,
    PAR_EXTENSION ,
    INV_FAIL ,
    MAL_ERR_BUFF ,
    INV_CON ,
    INV_READ ,
    PAR_INV_RGB ,
    INV_MAP ,

}		t_error_status;

typedef struct s_settings
{
    char **map;
    char *buff;
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
    unsigned char error_type;
}						t_settings;
#endif