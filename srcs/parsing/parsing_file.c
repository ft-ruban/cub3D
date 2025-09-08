
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
    fd = open(path, O_RDONLY);
    if(fd == -1)
    {
        write(2,"Error while opening file be sure the file exist\n", 49);
        {
            free(path);
            return(-1);
        }
    }
    free(path);
    return(fd);
}

//here we collect all the info in the file scene descriptions
//by reading the 2 first char, if no match found get next line
//until we successfully get the first informations before getting to the map parsing

static int read_collect_parse_fd(int fd_sd, t_settings *set)
{
    if(collect_elements(fd_sd, set))
    {
        printf("error during collect_elements\n");
        return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}

//TODO PENSER A CLOSE LE FD!!!

int open_and_parse_file(char *file, t_settings *set)
{
    int fd;

    fd = open_file_give_fd(file);
    if(fd == -1)
        return(RETURN_FAILURE);
    if(read_collect_parse_fd(fd, set))
        return(RETURN_FAILURE);
    return(RETURN_SUCCESS);
}