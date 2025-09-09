#include "parsing.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //printf
#include <stdbool.h> //bool duh

static int blue_fill(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    bool  stop_loop;

    stop_loop = false;
    read(fd_sd, buff, 1);
    if(ft_isnum((int)buff[0]))
        return(-42);
    if(first_letter == 'F')
    {
        printf("buff = %c\n", buff[0]);
        set->floor_b = ft_atoi(&buff[0]);
    }
        
    else
        set->cell_b = ft_atoi(&buff[0]);
    read(fd_sd, buff, 1);
    while(!stop_loop)
    {
        if(ft_isnum((int)buff[0]) && buff[0] != '\n')
            return(-42);
        if(buff[0] == '\n')
            return(RETURN_SUCCESS);
        else
        {
            if(first_letter == 'F')
            {
                set->floor_b = set->floor_b * 10;
                set->floor_b = set->floor_b + ft_atoi(&buff[0]);
            }
            else
            {
                set->cell_b = set->cell_b * 10;
                set->cell_b = set->cell_b + ft_atoi(&buff[0]);
            }
            read(fd_sd, buff, 1);
        }
    }
    return(RETURN_SUCCESS);
}

static int green_fill(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    bool  stop_loop;

    stop_loop = false;
    read(fd_sd, buff, 1);
    if(ft_isnum((int)buff[0]))
        return(-42);
    if(first_letter == 'F')
        set->floor_g = ft_atoi(&buff[0]);
    else
        set->cell_g = ft_atoi(&buff[0]);
    read(fd_sd, buff, 1);
    while(!stop_loop)
    {
        if(ft_isnum((int)buff[0]) && buff[0] != ',')
            return(-42);
        else if (buff[0] == ',')
        {
            stop_loop = true;
            blue_fill(fd_sd, set, first_letter, buff);
        }
        else
        {
            if(first_letter == 'F')
            {
                set->floor_g = set->floor_g * 10;
                set->floor_g = set->floor_g + ft_atoi(&buff[0]);
            }
                
            else
            {
                set->cell_g = set->cell_g * 10;
                set->cell_g = set->cell_g + ft_atoi(&buff[0]);
            }
            read(fd_sd, buff, 1);
        }
    }
    return(RETURN_SUCCESS);
}

static int red_fill(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    bool  stop_loop;

    stop_loop = false;
    read(fd_sd, buff, 1);
    while(!stop_loop)
    {
        if(ft_isnum((int)buff[0]) && buff[0] != ',')
            return(RETURN_FAILURE);
        else if (buff[0] == ',')
        {
            stop_loop = true;
            green_fill(fd_sd, set, first_letter, buff);
        }
        else
        {
            if(first_letter == 'F')
            {
                set->floor_r = set->floor_r * 10;
                set->floor_r = set->floor_r + ft_atoi(&buff[0]);
            }
            else
            {
                set->cell_r = set->cell_r * 10;
                set->cell_r = set->cell_r + ft_atoi(&buff[0]);
            }
            read(fd_sd, buff, 1);
        }
    }
    return(RETURN_SUCCESS);
}
//this is not the releasable name!!!
int rgb_thing(int fd_sd, t_settings *set, char first_letter)
{
    bool exit_loop;

    exit_loop = false;
    while(!exit_loop)
    {
        if(read(fd_sd, set->buff, 1) == -1)
        {
            set->error_type = PARSING_READ_FAILURE;
            return(RETURN_FAILURE);
        }

        if(ft_isnum((int)set->buff[0]) == RETURN_SUCCESS)
        {
            if(first_letter == 'F')
            {
                set->floor_r = ft_atoi(&set->buff[0]);
            }
                
            else
            {
                set->cell_r = ft_atoi(&set->buff[0]);
                //red_fill(fd_sd, set, )
            }
                
            red_fill(fd_sd, set, first_letter, set->buff);//c un num donc faut poursuivre jusqua trouver un ,
            exit_loop = true;
        }
        else if(set->buff[0] != ' ')
            return(RETURN_FAILURE);
    }
    return(RETURN_SUCCESS);
}
