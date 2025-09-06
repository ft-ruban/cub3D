
#include "parsing.h"
#include <sys/stat.h> //open
#include <fcntl.h> //open

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

// is map composed of only 6 possible chars
// 0 for empty spaces
// 1 for a wall
// N,S,E,W for the player start pos + orientation at spawn
// is map closed/surrounded by wall?
// map content has to be the last
// is the infos above? (check excalidraw/notion)

//TODO PENSER A CLOSE LE FD!!!

int open_and_parse_file(char *file)
{
    int fd;

    fd = open_file_give_fd(file);
    if(fd == -1)
        return(RETURN_FAILURE);

    //-read into it to parse potential error (refer to notion for all possible errors)
    return(RETURN_SUCCESS);
}