#include "parsing.h"
#include "utils.h"
#include "linux/limits.h"

static char *get_path(int fd_sd, char **element)
{
    *element = get_next_line(fd_sd);
    return(*element);
}

static int find_texture_element_path(int fd_sd, char **element)
{
    char *buff;

    buff = malloc(1); //TOPROTECT
    while(!*element)
    {
        read(fd_sd, buff, 1); //to protect
        if(buff[0] == '.')
        {
            read(fd_sd,buff, 1);//to protect
            if(buff[0] != '/')
            {
                free(buff);
                return(RETURN_FAILURE);
            }
            else
                get_path(fd_sd, element);   
        }
        else if (buff[0] != ' ')
        {
            free(buff);
            return(RETURN_FAILURE);
        }
    }
    return(RETURN_SUCCESS);
}

int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter)
{
    if(first_letter == 'N')
    {
        if(set->rp_no || second_letter != 'O')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, &set->rp_no);
    }
    if(first_letter == 'S')
    {
        if(set->rp_so || second_letter != 'O')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, &set->rp_so);
    }
    if(first_letter == 'W')
    {
        if(set->rp_we || second_letter != 'E')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, &set->rp_we);
    }
    if(first_letter == 'E')
    {
        if(set->rp_ea || second_letter != 'A')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, &set->rp_ea);
    }
    return(RETURN_SUCCESS);
} 
