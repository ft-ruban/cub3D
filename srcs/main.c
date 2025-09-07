#include <unistd.h> //write
#include "parsing.h"

//We init them at those value 
static int init_struct_value(t_settings *set)
{
    set->rp_no = NULL;
    set->rp_so = NULL;
    set->rp_we = NULL;
    set->rp_ea = NULL;
    set->cell_r = NONE_ASSIGNED;
    set->cell_g = NONE_ASSIGNED;
    set->cell_b = NONE_ASSIGNED;
    set->floor_r = NONE_ASSIGNED;
    set->floor_g = NONE_ASSIGNED;
    set->floor_b = NONE_ASSIGNED;
    return(RETURN_SUCCESS);
}

int main(int argc, char *argv[])
{
    t_settings *set;

    set = malloc(sizeof(t_settings));
    if(!set)
    {
        write(2, "malloc error\n",13);
        return(1);
    }
    init_struct_value(set);
    if(parsing(argc, argv, set))
    {
        free(set);
        write(2, "placeholder failed parsing\n", 27);
        return(1);
    }
    //init structures/data
        //if fail return error with right msg + free close
    //init minilibx + I guess the controls? 
        //if fail return error with right msg + free/close
    //running part
    //write(1,"Hello, world\n", 13);
    free(set);
    write(1, "return Success\n", 15);
    return (0);
}