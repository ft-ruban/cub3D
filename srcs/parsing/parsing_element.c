
#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //getline TORM

static char *get_path(int fd_sd, char *element)
{
    char *buff;
    int   i;
    int   j;
    size_t len;

    len = PATH_MAX;
    i = 0;
    j = 0;

    buff = malloc(PATH_MAX); //protect
    getline(&buff, &len, fd_sd); //IL FAUT TRANSFORMER EN NOTRE GNL
    //getnextline de fd_sd
    return(buff);
}

static int find_texture_element_path(int fd_sd, char *element)
{
    char *buff;

    buff = malloc(1); //TOPROTECT
    while(!element)
    {
        read(fd_sd, buff, 1); //to protect
        if(buff == '.')
        {
            read(fd_sd,buff, 1);//to protect
            if(buff != '/')
            {
                free(buff);
                return(RETURN_FAILURE);
            }
            else
                element = get_path;   
        }
        else if (buff != ' ')
        {
            free(buff);
            return(RETURN_FAILURE);
        }
    }
}

static int is_texture_valid(int fd_sd, t_settings *set, char first_letter, char second_letter)
{
    if(first_letter == 'N')
    {
        if(set->rp_no || second_letter != 'O')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, set->rp_no);
    }
    if(first_letter == 'S')
    {
        if(set->rp_so || second_letter != 'O')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, set->rp_so);
    }
    if(first_letter == 'W')
    {
        if(set->rp_we || second_letter != 'E')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, set->rp_we);
    }
    if(first_letter == 'E')
    {
        if(set->rp_ea || second_letter != 'A')
            return(RETURN_FAILURE);
        find_texture_element_path(fd_sd, set->rp_ea);
    }
} 

static int element_found(int fd_sd, t_settings *set, char first_letter)
{
    char *buff;

    if(first_letter == 'N' || first_letter == 'S' || 
        first_letter == 'W' || first_letter == 'E')
    {
        buff = malloc(1); //toprotect
        read(fd_sd, buff, 1); //toprotect
        if(is_texture_valid(fd_sd, set, first_letter, buff[0]))
            return(RETURN_FAILURE);
    }
    //do the RGB thing

}

static int all_elements_present(t_settings *set)
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

    while(all_elements_present)
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
            printf("buff = %s\n", buff);
        }
        else
        {
            printf("ERROR INVALID FILE CONTENT\n");
            free(buff);
            return(RETURN_FAILURE);
        }
        free(buff);
    }
    return(RETURN_SUCCESS);
}
