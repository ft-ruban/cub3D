#ifndef UTILS_H
# define UTILS_H
#include <stdlib.h> //size_t

# include <fcntl.h> //GNL (TOCHECKBCS OLD)
# include <stdlib.h> //GNL (TOCHECKBCS OLD)
# include <unistd.h> //GNL (TOCHECKBCS OLD)
# include <stdio.h> //GNL
# include "cub3D.h"

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

// ft_atoi.c
int	ft_atoi(const char *nptr);

// ft_isnum.c
int	ft_isnum(int c);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
size_t	ft_strlen(const char *s);

//get_next_line.c
char	*get_next_line(int fd);
void	*ft_calloc(size_t element_count, size_t element_size);
char	*ft_strchr(const char *s, int c);
# endif