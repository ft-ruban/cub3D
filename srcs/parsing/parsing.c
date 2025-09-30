#include "parsing.h"

// Here we check if the file sent do possess the right
//.cub extension by checking the last characters in the
// given string of char

static bool	is_file_cub_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (false);
	return (true);
}

// we check if the user entered 1 param and nothing more.
// we check if the param is a .cub to make sure it is the right extension
// we open file to collect the elements above the map
// TODO we parse the map and save its content inside of a variable(s)
// TODO if in the end parsing can only end up in two ways, turn it into a bool

int	parsing(int argc, char *argv[], t_settings *set)
{
	int	fd;

	if (argc != 2)
		return (error_handler(set, PAR_NBR_ARGC, "parsing.c:28 ", MSG_2));
	if (!is_file_cub_extension(argv[1]))
		return (error_handler(set, PAR_EXTENSION, "parsing.c:30 ", MSG_3));
	if (prepare_collect_elements(argv[1], set, &fd, &set->buff))
		return (RETURN_FAILURE);
	// if (get_and_check_map(argv[1], set, fd))
	// 	return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
