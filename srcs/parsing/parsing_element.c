
#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh



static int element_found(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    read(fd_sd, buff, 1); //toprotect if fail probably bcs EOF reached before getting all the elements
    if(first_letter == 'N' || first_letter == 'S' || 
        first_letter == 'W' || first_letter == 'E')
    {
        if(is_texture_valid(fd_sd, set, first_letter, buff[0]))
            return(RETURN_FAILURE);
    }
    else
    {
        rgb_thing(fd_sd, set, first_letter, buff[0]);
    }
    return(RETURN_SUCCESS);
}
//that function's goal is to check if all our settings are assigned.
//to exit the loop at collect_elements. the loop is supposed to continue
//until everything got filled
static int all_elements_filled(t_settings *set)
{
    if(!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea || set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED ||
        set->floor_b == NONE_ASSIGNED || set->cell_r == NONE_ASSIGNED || set->cell_g == NONE_ASSIGNED || set->cell_b == NONE_ASSIGNED)
            return(RETURN_FAILURE);
    else
        return(RETURN_SUCCESS);
}

//TODO lot of error case, need a function to warn the user with the
//proper message + free potential things like buff for ex

int collect_elements(int fd_sd, t_settings *set)
{
    char *buff;

    buff = malloc(1); //to protect
    if(!buff)
        return(RETURN_FAILURE); //TODO ERRORHANDLER
    while(all_elements_filled(set))
    {
        if(read(fd_sd, buff, 1) == -1) //toprotect
        {
            free(buff);
            return(RETURN_FAILURE); //TODO ERRORHANDLER + FREE here if fail probably bcs EOF reached before getting all the elements
        }
        if (buff[0] == 'N' || buff[0] == 'S' || buff[0] == 'W' || buff[0] == 'E' || buff[0] == 'F' || buff[0] == 'C')
        {
            element_found(fd_sd, set, buff[0], buff); //protect?
        }
        else if(buff[0] != '\n')
        {
            printf("ERROR INVALID FILE CONTENT ((DETAIL W.I.P))\n"); //something probably went wrong (invalid char or a format we cannot accept)
            free(buff);
            return(RETURN_FAILURE);
        }
    }
    return(RETURN_SUCCESS);
}
