#include  "parsing.h"
#include <stdio.h> //for printf TORM

// TODO replace strlen with ft_strlen

//Here we check if the file sent do possess the right
//.cub extension

static int	is_right_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
    printf("len = %d\n", len);
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	parsing(int argc, char *argv[], t_settings *set)
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
    if (open_and_parse_file(argv[1], set))
    {
        write(2, "problem during read file\n", 25);
        return (3); //TODO may have to do more specific error type here in near future
    }
	write(1, "parsing successful\n", 19);
	return (RETURN_SUCCESS);
}