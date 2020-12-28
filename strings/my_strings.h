#ifndef MY_STRINGS_H
#define MY_STRINGS_H

#ifndef NULL
#define NULL ((void *)0)
#endif

int _strlen(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_strndup(char *str, int n);

#endif /* MY_STRINGS_H */
