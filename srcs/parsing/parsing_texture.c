#include "parsing.h"
#include "utils.h"
#include "linux/limits.h"

static int find_texture_element_path(int fd_sd, char **element, t_settings *set)
{
    if(read(fd_sd, set->buff, 1) == -1)
    {
        set->error_type = PARSING_READ_FAILURE;
        return(RETURN_FAILURE);
    }
    while(set->buff[0] == ' ')
    {
        if(read(fd_sd, set->buff, 1) == -1)
        {
            set->error_type = PARSING_READ_FAILURE;
            return(RETURN_FAILURE);
        }
    }
    *element = get_next_line(fd_sd);
    if(!*element)
    {
        set->error_type = PARSING_READ_FAILURE;
        return(RETURN_FAILURE);
    }
    return(RETURN_SUCCESS);
}
//if fail here it mean we already got the information (let's assume we DO NOT accept duplicates to not make things more confusing)
//TODO create an utils function that would setup an error type and return failure to avoid repetition
int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter)
{
    if(first_letter == 'N')
    {
        if(set->rp_no || second_letter != 'O')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }    
        return(find_texture_element_path(fd_sd, &set->rp_no, set));
    }
    else if(first_letter == 'S')
    {
        if(set->rp_so || second_letter != 'O')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }    
        return(find_texture_element_path(fd_sd, &set->rp_so, set));
    }
    else if(first_letter == 'W')
    {
        if(set->rp_we || second_letter != 'E')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }    
        return(find_texture_element_path(fd_sd, &set->rp_we, set));
    }
    else if(first_letter == 'E')
    {
        if(set->rp_ea || second_letter != 'A')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }    
        return(find_texture_element_path(fd_sd, &set->rp_ea, set));
    }
    return(RETURN_FAILURE);
} 
