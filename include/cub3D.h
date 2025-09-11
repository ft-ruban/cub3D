#ifndef CUB3D_H
# define CUB3D_H

#include "debug.h"
#include <stdlib.h> //size_t

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1

typedef enum e_error_status
{
    ALL_OK ,
	MALLOC_ERROR_SET = 1 ,
    ERR ,
    PARSING_NBR_ARGC ,
    PARSING_FILE_EXTENSION ,
    PARSING_CANT_OPEN_FILE ,
    MALLOC_ERROR_BUFFER ,
    PARSING_ELEMENT_INVALID_CONTENT ,
    PARSING_READ_FAILURE ,

}		t_error_status;

typedef struct s_settings
{
    char    **map;
    char    *buff;
    char    *rp_no;
    char    *rp_so;
    char    *rp_we;
    char    *rp_ea;
    int     floor_r;
    int     floor_g;
    int     floor_b;
    int     cell_r;
    int     cell_g;
    int     cell_b;
    size_t  error_type;
}						t_settings;
#endif