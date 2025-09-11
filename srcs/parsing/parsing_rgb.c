#include "parsing.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //printf
#include <stdbool.h> //bool duh

static int retrieve_rgb(int fd_sd, t_settings *set, int *red, bool is_blue)
{
    int i;

    i = 0;
    *red = ft_atoi(&set->buff[0]);
    read(fd_sd, set->buff, 1);
    while(set->buff[0] != ',')
    {
        if(ft_isnum((int)set->buff[0]) || i > 3)
            return(RETURN_FAILURE);
        *red = *red * 10;
        *red = *red + ft_atoi (&set->buff[0]);
        read(fd_sd, set->buff, 1); //toprotect
        i++;
        if(is_blue && set->buff[0] == '\n')
            return(RETURN_SUCCESS);
    }
    return(RETURN_SUCCESS);
}

//this is not the releasable name!!!
int rgb_thing(int fd_sd, t_settings *set, char first_letter, bool exit_loop)
{
    while(!exit_loop)
    {
        if(read(fd_sd, set->buff, 1) == -1)
            return(error_handler(set, PARSING_READ_FAILURE));
        if(ft_isnum((int)set->buff[0]) == RETURN_SUCCESS)
        {
            if(first_letter == 'F')
            {
                retrieve_rgb(fd_sd, set, &set->floor_r, false);
                retrieve_rgb(fd_sd, set, &set->floor_g, false);
                retrieve_rgb(fd_sd, set, &set->floor_b, true);
            }
            else
            {
                retrieve_rgb(fd_sd, set, &set->cell_r, false);
                retrieve_rgb(fd_sd, set, &set->cell_g, false);
                retrieve_rgb(fd_sd, set, &set->cell_b, true);
            }
            exit_loop = true;
        }
        else if(set->buff[0] != ' ')
            return(RETURN_FAILURE);
    }
    return(RETURN_SUCCESS);
}
