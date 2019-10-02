#include <stdio.h>

// Упражнение 4.3
// Присвоить переменной единицу, если одна строка содержится в конце другой, и ноль в противном случае

// Функция возвращает 1, если string2 находится в конце другой строки
int is_finished_by(char *string1, char *string2);

int main(void)
{
    char str1[80], str2[80];

    printf("Enter first string > ");
    scanf("%s", str1);

    printf("Enter second string > ");
    scanf("%s", str2);

    int res = is_finished_by(str1, str2);

    printf("Result of search is = %d\n", res);

    return 0;
}

// Функция возвращает 1, если string2 находится в конце другой строки
int is_finished_by(char *string1, char *string2)
{
    int count1 = 0, count2 = 0;

    while (*string1++) count1++;
    while (*string2++) count2++;

    printf("count1 = %d", count1);
    printf("count2 = %d", count2);

    if (count1 < count2) 
        return 0;

    for (;count2;count2--)
    {
        if (*string1-- != *string2--)
            return 0;
    }  

    return 1;
}
