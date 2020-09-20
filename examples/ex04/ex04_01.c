#include <stdio.h> 

// Упражнение 4.1
// Написать функцию конкатенации строк (аналог функции strcat)

// Функция добавляет копию строки srcptr в конец строки destptr.
// Нулевой символ конца строки destptr заменяется первым символом строки srcptr, 
// и новый нуль-символ добавляется в конец уже новой строки, сформированной объединением 
// символов двух строк в строке destptr.
char *my_strcat(char *destptr, const char *srcptr);

int main(void)
{
    char str1[80], str2[80];

    printf("Enter first string > ");
    scanf("%s", str1);

    printf("Enter second string > ");
    scanf("%s", str2);

    /*str1 =*/ 
    my_strcat(str1, str2);

    printf("Result of concat is = %s\n", str1);

    return 0;
}


// Функция конкатенации строк (аналог функции strcat)
char *my_strcat(char *destptr, const char *srcptr)
{
    char *p = destptr;
    
    while (*p++);
    p--;

    while (*srcptr) *p++ = *srcptr++;

    *p = '\0';

    return destptr;
}