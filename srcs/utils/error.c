
#include "utils.h"

//TODO faire le param errormsg prout
int error_handler(t_settings *set, int error_type, char *emplacement_error_msg, char *err_msg)
{
    write(2,emplacement_error_msg, ft_strlen(emplacement_error_msg));
    write(2,err_msg, ft_strlen(err_msg));
    if(error_type == MAL_ERR_SET)
        return(MAL_ERR_SET);
    set->error_type = error_type;
    return(RETURN_FAILURE);
}