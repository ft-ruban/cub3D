
#include "utils.h"

//TODO faire le param errormsg prout
int error_handler(t_settings *set, int error_type)
{
    set->error_type = error_type;
    write(2,"ceci est un placeholder il faut me complete\n", 46);
    return(RETURN_FAILURE);
}