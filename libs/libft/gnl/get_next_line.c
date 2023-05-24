/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:09:17 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 21:42:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_gnl.h"

static char	*create_newline_frm_save(char *save, bool is_include_nl)
{
	char	*new_line;
	size_t	i;

	if (!save || !save[0])
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (is_include_nl && save[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	ft_strlcpy_gnl(new_line, save, i + 1);
	return (new_line);
}

static char	*delete_newline_in_save(char *save)
{
	char	*new_save;
	size_t	i;
	size_t	j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (ft_free_gnl(&save, NULL));
	new_save = (char *)malloc(sizeof(char) * (ft_strlen_gnl(save) - i + 1));
	if (!new_save)
		return (ft_free_gnl(&save, NULL));
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	ft_free_gnl(&save, NULL);
	if (j == 0)
		ft_free_gnl(&new_save, NULL);
	return (new_save);
}

static char	*read_file_and_save(int fd, char *save)
{
	char	*buf;
	ssize_t	read_bytes;
	size_t	nl_cnt;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free_gnl(&save, NULL));
	read_bytes = 1;
	nl_cnt = 0;
	while (nl_cnt == 0 && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free_gnl(&buf, NULL));
		buf[read_bytes] = '\0';
		nl_cnt = cnt_chr_in_str('\n', buf);
		save = strjoin_and_free_dst(save, buf);
		if (!save)
			break ;
	}
	ft_free_gnl(&buf, NULL);
	return (save);
}

char	*get_next_line(int fd, bool is_include_nl)
{
	char		*gnl_line;
	static char	*save_buf[FOPEN_MAX];

	errno = 0;
	if (fd < 0 || FOPEN_MAX < fd || BUFFER_SIZE <= 0 || INT_MAX < BUFFER_SIZE)
		return (NULL);
	if (cnt_chr_in_str('\n', save_buf[fd]) == 0)
	{
		save_buf[fd] = read_file_and_save(fd, save_buf[fd]);
		if (!save_buf[fd])
			return (NULL);
	}
	gnl_line = create_newline_frm_save(save_buf[fd], is_include_nl);
	save_buf[fd] = delete_newline_in_save(save_buf[fd]);
	if (errno != 0)
		return (ft_free_gnl(&save_buf[fd], &gnl_line));
	return (gnl_line);
}

