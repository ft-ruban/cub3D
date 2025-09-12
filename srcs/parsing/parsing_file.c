/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:27:19 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/12 14:48:08 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>    //open
#include <stdio.h>    //printf
#include <sys/stat.h> //open

// here we open a given file by checking in
// the scene description folder (TODO may have to do a DEFINE here)
// if no readable file with the right name found send a invalid FD(DEFINE TOO)
// otherwise send the related fd of our file

static int	open_file_give_fd(char *file)
{
	char	*path;
	int		fd;

	path = ft_strjoin("scene_descriptions/", file);
	if (!path)
		return (OPEN_FAILED);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

// here we collect all the info in the file scene descriptions
// by reading the 2 first char, if no match found get next line
// until we successfully get the first 
// informations before getting to the map parsing

// TODO PENSER A CLOSE LE FD!!!
// TODO IDEE AVEC BUFF

int	open_file_collect_elements(char *file, t_settings *set, int *fd)
{
	*fd = open_file_give_fd(file);
	if (*fd == OPEN_FAILED)
		return (error_handler(set, INV_FAIL, "parsing_file.c:34 ", MSG_4));
	set->buff = malloc(2);
	if (!set->buff)
	{
		close(*fd);
		return (error_handler(set, MAL_ERR_BUFF, "parsing.c:37", MSG_5));
	}
	set->buff[1] = '\0';
	if (collect_elements(*fd, set))
	{
		close(*fd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
