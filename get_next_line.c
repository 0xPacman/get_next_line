#include "get_next_line.h"

char *ft_line_reader(int fd)
{
	char *buff;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ssize_t size = read(fd, buff, BUFFER_SIZE);
	printf("the buffer:%s\nthe size:%zu",buff,size);
}

int main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	ft_line_reader(fd);
}
