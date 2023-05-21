#ifndef SYS_H
# define SYS_H

# include "minirt.h"

void	x_free_1d_alloc(void **alloc);
void	x_free_2d_alloc(void ***alloc);
int		x_open(const char *path, int oflag);
int		x_close(int fd);

#endif //SYS_H
