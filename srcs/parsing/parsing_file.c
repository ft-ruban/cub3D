
#include "parsing.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //printf

//here we open a given file by checking in
//the scene description folder (TODO may have to do a DEFINE here)
//if no readable file with the right name found send a invalid FD(DEFINE TOO)
//otherwise send the related fd of our file

static int open_file_give_fd(char *file)
{
    char *path;
    int   fd;

    path = ft_strjoin("scene_descriptions/", file);
    if(!path)
        return(-1);
    fd = open(path, O_RDONLY);
    free(path);
    return(fd);
}

//here we collect all the info in the file scene descriptions
//by reading the 2 first char, if no match found get next line
//until we successfully get the first informations before getting to the map parsing

//TODO PENSER A CLOSE LE FD!!!

int open_file_collect_elements(char *file, t_settings *set)
{
    int fd;

    fd = open_file_give_fd(file);
    if(fd == OPEN_FAILED)
    {
        set->error_type = PARSING_CANT_OPEN_FILE;
        return(RETURN_FAILURE);
    }
    set->buff = malloc(2);
    if(!set->buff)
    {
        set->error_type = MALLOC_ERROR_BUFFER;
        return(RETURN_FAILURE);
    }
    set->buff[1] = '\0';
    if(collect_elements(file, fd, set))
    {
        //free(set->buff);
        printf("error during collect_elements\n"); //TORM AT SOME POINT?
        return(RETURN_FAILURE);
    }
    
    return(RETURN_SUCCESS);
}