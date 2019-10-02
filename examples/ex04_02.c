#include <stdio.h>

// Упражнение 4.2
// Написать функцию сравнения строк (аналог функции strcmp)

//   Аргументы:
//     char *string1 - первая строка
//     char *string2 - вторая строка
//   Результат
//     0 - если строки равны
//     1 - если первая строка больше
//     2 - если вторая строка больше
//     Сравнение идет до первого нсовпадающего символа
int my_strcmp(char *string1, char *string2);

int main(void)
{
    char str1[80], str2[80];

    printf("Enter first string > ");
    scanf("%s", str1);

    printf("Enter second string > ");
    scanf("%s", str2);

    int res = my_strcmp(str1, str2);

    printf("Result of comparision is = %d\n", res);

    return 0;
}

// функция сравнения двух строк
int my_strcmp(char *string1, char *string2)
{
    while (*string1 && *string2 && *string1++==*string2++);

    if (*string1==*string2)
        return 0;
    else
        if (*string1 > *string2)
            return  1;
        else
            return -1;
}
