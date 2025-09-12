#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh
#include <errno.h>

static int element_found(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    if(read(fd_sd, buff, 1) == -1)
    {
        set->error_type = PARSING_READ_FAILURE;
        return(RETURN_FAILURE);
    }
    if(first_letter == 'N' || first_letter == 'S' || 
        first_letter == 'W' || first_letter == 'E')
    {
        if(is_texture_valid(fd_sd, set, first_letter, buff[0]))
            return(RETURN_FAILURE);
    }
    else if(first_letter == 'F' || first_letter == 'C')
    {
        if((first_letter == 'F' && set->floor_r == -1) || (first_letter == 'C' && set->cell_r == -1))
            rgb_thing(fd_sd, set, first_letter, false);
        else
        {
            //printf("TEST\n");
            return(RETURN_FAILURE);
        }
    }
    return(RETURN_SUCCESS);
}
//that function's goal is to check if all our settings are assigned.
//to exit the loop at collect_elements. the loop is supposed to continue
//until everything got filled
static int are_all_elements_filled(t_settings *set)
{
    if(!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea || set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED ||
        set->floor_b == NONE_ASSIGNED || set->cell_r == NONE_ASSIGNED || set->cell_g == NONE_ASSIGNED || set->cell_b == NONE_ASSIGNED)
            return(RETURN_FAILURE);
    else
        return(RETURN_SUCCESS);
}

//TODO lot of error case, need a function to warn the user with the
//proper message + free potential things like buff for ex

int collect_elements(char *file, int fd_sd, t_settings *set)
{
    while(are_all_elements_filled(set))
    {
        if(read(fd_sd, set->buff, 1) == -1) //toprotect
        {
            set->error_type = PARSING_READ_FAILURE;
            return(RETURN_FAILURE); //TODO ERRORHANDLER + FREE here if fail probably bcs EOF reached before getting all the elements
        }
        if (set->buff[0] == 'N' || set->buff[0] == 'S' || set->buff[0] == 'W' || set->buff[0] == 'E' || set->buff[0] == 'F' || set->buff[0] == 'C')
        {
            if(element_found(fd_sd, set, set->buff[0], set->buff))
            {
                set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
                return(RETURN_FAILURE);
            }
        }
        else if(set->buff[0] != '\n')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }
    }
    // print_struct_set(set);
    if (collect_check_map(file, set, fd_sd) != ALL_OK)
        return (ERR);
    return(RETURN_SUCCESS);
}
