#include "parsing.h"
#include "utils.h"
#include "linux/limits.h"

static int find_texture_element_path(int fd_sd, char **element)
{
    char *buff;

    buff = malloc(1);
    if(!buff)
        return(RETURN_FAILURE);
    if(read(fd_sd, buff, 1) == -1)
    {
        free(buff);
        return(RETURN_FAILURE);
    }
    while(buff[0] == ' ')
    {
        if(read(fd_sd, buff, 1) == -1)
        {
            free(buff);
            return(RETURN_FAILURE);
        }
    }
    free(buff);
    *element = get_next_line(fd_sd);
    if(!*element)
        return(RETURN_FAILURE);
    return(RETURN_SUCCESS);
}
//if fail here it mean we already got the information (let's assume we DO NOT accept duplicates to not make things more confusing)
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
