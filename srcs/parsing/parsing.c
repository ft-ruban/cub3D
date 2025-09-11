#include  "parsing.h"
#include <stdio.h> //for printf TORM

//Here we check if the file sent do possess the right
//.cub extension

static int	is_right_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	parsing(int argc, char *argv[], t_settings *set)
{
	if (argc != 2)
    {
        set->error_type = PARSING_NBR_ARGC;
        return (RETURN_FAILURE);
    }
	if (is_right_extension(argv[1]))
    {
        set->error_type = PARSING_FILE_EXTENSION;
        return (RETURN_FAILURE);
    }
    if (open_file_collect_elements(argv[1], set))
    {
        print_struct_set(set);
        write(2, "problem during read file\n", 25); //torm at some point
        return (RETURN_FAILURE); //TODO may have to do more specific error type here in near future
    }
    //TODO next step would be to parse the map. Or is that for later? need to talk about it
    //to know the course of action, in any case need to close fd at some point! also if we need
    //to use the fd later on then would be better to save it in our set struct.
	write(1, "parsing successful\n", 19); //TORM
	return (RETURN_SUCCESS);
}
