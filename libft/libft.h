/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micchen <micchen@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:38:19 by micchen           #+#    #+#             */
/*   Updated: 2023/10/30 22:27:44 by micchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
int			ft_putstr(char *str);
int			ft_putnbr(int n);
int			ft_puthex(unsigned long n, int min);
int			lenhex(unsigned int n);
int			printhexa(unsigned int n, int min);
int			ft_putchar(int c);
int			countnbr(int n);
int			putunbr(unsigned int n);
int			ft_putptr(unsigned long long *ptr);
int			ft_printf(const char *str, ...);
int			countunbr(unsigned int n);

char		*ft_substr(const char *s, unsigned int debut, size_t n);
char		*ft_strchr(const char *s, int x);
char		*ft_strrchr(const char *s, int x);
char		*ft_strnstr(const char *big, const char *little, size_t l);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(const char *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dsize);

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isprint(int i);
int			ft_isalpha(int i);
int			ft_isdigit(int i);
int			ft_isascii(int i);
int			ft_isalnum(int i);
int			ft_strncmp(const char *s1, const char *s2, size_t l);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *str);

void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		*ft_calloc(size_t count, size_t s);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
