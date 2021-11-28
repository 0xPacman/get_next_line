#include "get_next_line.h"

int     ft_to_check(const char *s, char c)
{
        unsigned int    i;

        i = 0;
        if (!s)
                return (-42);
        while (s[i])
        {
                if (s[i] == c)
                        return (i);
                i++;
        }
        return (-42);
}

char    *ft_to_print(char *to_save)
{
        int             i;
        char    *str;

        i = 0;
        if (!to_save[i])
                return (NULL);
        while (to_save[i] && to_save[i] != '\n')
                i++;
        if(to_save[i] == '\n')
                i++;
        str = (char *)malloc(sizeof(char) * i + 1);
        if (!str)
                return (NULL);
        ft_strlcpy(str,to_save,i+1);
        return (str);
}

char    *ft_to_save(char *to_save)
{
        char    *str;
        int             start;
        int             i;

        start = 0;
        while (to_save[start] && to_save[start] != '\n')
                start++;
        if (to_save[start] == '\n')
                start++;
        if (!to_save[start])
        {
                free(to_save);
                return (NULL);
        }
        str = (char *)malloc(sizeof(char) * (ft_strlen(to_save) - start + 1));
        if (!str)
                return (NULL);
        i = 0;
        while (to_save[start])
        {
                str[i] = to_save[start];
                i++;
                start++;
        }
        str[i] = '\0';
        free(to_save);
        return (str);
}

char    *ft_to_read(char *to_save, int fd)
{
        ssize_t         sz;
        char            *buff;

        buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
        if (!buff)
                return (NULL);
        sz = 1;
        while (ft_to_check(to_save, '\n') == -42 && sz > 0 )
        {
                sz = read(fd, buff, BUFFER_SIZE);
                if (sz == -1)
                {
                        free(buff);
                        return (NULL);
                }
                buff[sz] = '\0';
                to_save = ft_strjoin(to_save, buff);
        }
        free(buff);
        return (to_save);
}

char    *get_next_line(int fd)
{
        static char     *to_save;
        char            *to_print;

        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        to_save = ft_to_read(to_save, fd);
        //      printf("-%s\n",to_save);
        if (!to_save)
                return (NULL);
        to_print = ft_to_print(to_save);
        to_save = ft_to_save(to_save);
        return (to_print);
}
/*
#include <stdio.h>
int main()
{
        int fd;
        char *str;
        fd = open("test.txt", O_RDWR);
        printf("%s",get_next_line(fd));
        printf("%s",get_next_line(fd));
        printf("%s",get_next_line(fd));
}

*/
