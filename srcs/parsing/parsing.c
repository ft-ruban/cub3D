#include "cub3D.h"
#include <string.h> //TORM FOR STRLEN
#include <stdio.h> //for printf TORM
#include <unistd.h> //write

// TODO replace strlen par ft_strlen

//Here we check if the file sent do possess the right
//.cub extension

static int	is_right_extension(char *file)
{
	int	len;

	len = strlen(file) - 1;
    printf("len = %d\n", len);
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	parsing(int argc, char *argv[])
{
	if (argc != 2)
    {
        write(2,"invalid argc\n", 13);
        return (1); // todo define arg error
    }
	if (is_right_extension(argv[1]))
    {
         write(2,"invalid extension\n", 18);
        return (2);
    }
	// is map composed of only 6 possible chars
	// 0 for empty spaces
	// 1 for a wall
	// N,S,E,W for the player start pos + orientation at spawn
	// is map closed/surrounded by wall?
	// map content has to be the last
	// is the infos above? (check excalidraw/notion)

	write(1, "parsing successful\n", 19);
	return (RETURN_SUCCESS);
}