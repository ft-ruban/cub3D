
#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh



static int element_found(int fd_sd, t_settings *set, char first_letter)
{
    char *buff;

    buff = malloc(1); //toprotect
    read(fd_sd, buff, 1); //toprotect
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

static int all_elements_filled(t_settings *set)
{
    if(!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea || set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED ||
        set->floor_b == NONE_ASSIGNED || set->cell_r == NONE_ASSIGNED || set->cell_g == NONE_ASSIGNED || set->cell_b == NONE_ASSIGNED)
            return(RETURN_FAILURE);
    else
        return(RETURN_SUCCESS);
}

int collect_elements(int fd_sd, t_settings *set)
{
    char *buff;

    while(all_elements_filled(set))
    {
        buff = malloc(2); //to protect
        read(fd_sd, buff, 1); //toprotect
        buff[1] = '\0';
        if (buff[0] == '\n')
        {
            printf("RETOUR A LA LIGNE\n");
        }
        else if (buff[0] == 'N' || buff[0] == 'S' || buff[0] == 'W' || buff[0] == 'E' || buff[0] == 'F' || buff[0] == 'C')
        {
            element_found(fd_sd, set, buff[0]);
        }
        else
        {
            printf("ERROR INVALID FILE CONTENT\n");
            free(buff);
            print_struct_set(set);
            return(RETURN_FAILURE);
        }
        free(buff);
    }
    return(RETURN_SUCCESS);
}
