# 42_libs

## string
```c
/* is */
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_ispunct(char c);

bool		is_chr_in_str(char chr, const char *str);
bool		is_str1chrs_in_str2(const char *str1, const char *str2);

int		ft_toupper(int c);
int		ft_tolower(int c);


/* str */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp_ns(const char *s1, const char *s2, size_t n);
int		ft_strcmp_ns(const char *s1, const char *s2);
bool	        is_same_str(const char *str1, const char *str2);

size_t		ft_strlen(const char *s);
size_t		ft_strlen_ns(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat_ns(char *dst, const char *src, size_t dstsize);
size_t		get_arr_size(char **array);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ft_strdup_ns(const char *s1);
char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);
char		**ft_split_empty(char const *s, char c);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));


/* mem */
void		ft_bzero(void *s, size_t n);
int             ft_memcmp(const void *s1, const void *s2, size_t n);
void            *ft_memset(void *s, int c, size_t n);
void		*ft_memset_ns(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
```
## std
```c
char		*ft_itoa(int n);
int	        ft_atoi(const char *str, bool *is_success);
long long	ft_strtoll(char *num, bool *is_success);
void		*ft_calloc(size_t count, size_t size);
```


## put
```c
ssize_t		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
```

## list
```c
/* list */
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

size_t		ft_lstsize(t_list *lst);


/* list bidirectional */
t_list_bdi	*ft_lstnew_bdi(void *content);
t_list_bdi	*ft_lstpop_bdi(t_list_bdi **lst);
t_list_bdi	*ft_lstlast_bdi(t_list_bdi *lst);

void		ft_lstadd_front_bdi(t_list_bdi **lst, t_list_bdi *new);
void		ft_lstadd_back_bdi(t_list_bdi **lst, t_list_bdi *new);
void		ft_lstdelone_bdi(t_list_bdi **lst, void (*del)(void *));
void		ft_lstclear_bdi(t_list_bdi **lst, void (*del)(void *));
void		ft_lstiter_bdi(t_list_bdi *lst, void (*f)(void *));

size_t		ft_lstsize_bdi(t_list_bdi *lst);
```

## math
```c
size_t		min_size(size_t a, size_t b);
size_t		max_size(size_t a, size_t b);
int		min_int(int a, int b);
int		max_int(int a, int b);
```

## printf
```c
int		ft_printf(const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);
```

