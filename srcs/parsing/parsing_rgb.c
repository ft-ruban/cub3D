#include "parsing.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //printf
#include <stdbool.h> //bool duh

static int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (RETURN_SUCCESS);
	else
		return (RETURN_FAILURE); //TODO RETURN_ERROR MARCHE PAS JSP PK
}

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
            printf("floor_rAA = %d\n", set->floor_r);
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
int rgb_thing(int fd_sd, t_settings *set, char first_letter, char second_letter)
{
    char *buff;
    bool exit_loop;

    second_letter = 'b'; //TORM COMPILATOR
    exit_loop = false;
    buff = malloc(1);//protect
    while(!exit_loop)
    {
        read(fd_sd, buff, 1); //protect
        if(ft_isnum((int)buff[0]) == RETURN_SUCCESS)
        {
            if(first_letter == 'F')
                set->floor_r = ft_atoi(&buff[0]);
            else
                set->cell_r = ft_atoi(&buff[0]);
            printf("FLOOR R = %d\n", set->floor_r);
            printf("cell R = %d\n", set->cell_r);
            red_fill(fd_sd, set, first_letter, buff);//c un num donc faut poursuivre jusqua trouver un ,
            exit_loop = true;
        }
        else if(buff[0] != ' ')
            return(RETURN_FAILURE);
    }
    //printf("TEST?????\n");
    return(RETURN_SUCCESS);
}
