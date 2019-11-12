#include <stdio.h>
//#include <string.h>

#define MAX 81
#define WORD_MAX 20
#define SPACE '\x20'

const int L_START = 'A';
const int L_FINISH = 'Z';

// получить правую границу слова
//   char *buf - строка
//   int len - длина строки
//   int start - начальный индекс строки 
int get_right_idx(char *buf, int len, int start);

// получить количесвто слов
//   char *buf - строка
//   int len - длина строки
int get_count(char *buf, int len);

// проверка, что это строка из английских букв
//   char *buf - строка
//   int start - начальный индекс слова
//   int finish - конечный индекс слова
int is_alphabet(char *buf, int start, int finish);

// Дана непустая последовательность слов, разделенных одним или несколькими пробелами. 
// Признак конца текста – точка. Распечатать этот текст, удалив из него лишние пробелы 
// (каждую группу из нескольких пробелов заменить одним пробелом).

char src[MAX]; // входная строка    
char words[WORD_MAX][MAX]; // массив слов

int main (void)
{           
    printf("Enter source string = ");

    if (!fgets(src, MAX, stdin))
    {
        perror ("fgets");
		return 1;
    }

    int len = 0; // длина строки    

    //определяем, есть ли символ точка
    while(src[len] && src[len] != '.')
        len++;
    
    if (src[len] != '.')
    {
        printf("No symbol . in source string!\n");
		return 2;
    }
    
    src[len] = '\0'; // обрезаем строку вместе с символом "."

    printf("Source string = %s \n", src);

    int source = 0, dest = 0; // начальный и конечный индекс

    // пропуск начальных побелов
    while(src[source] && src[source] == SPACE) 
        source++; 

    while(src[source])
    {
        //если имеет смысл копировать символы, делаем это
        if (dest != source)
            src[dest] = src[source];

        //увеличиваем индексы
        dest++;
        source++;
        
        //если мы нашли пробел
        if (SPACE == src[source]) 
        {
            //добавляем его
            src[dest++] = src[source++];

            //пропускаем пробелы
            while(src[source] && src[source] == SPACE)
                source++;
        }
    }
    if (dest && src[dest-1] == SPACE) //если последним символом остался пробел, удалим
        dest--;
    
    src[dest] = '.'; //ставим точку
    src[++dest] = '\0';  //обрезаем строку

    printf("Result string = %s=\n", src);

    //подсчитаем количество слов
    int cnt = get_count(src, dest);
    printf("Words count = %d\n", cnt);

    //определим, является ли первое слово алфавитным
    int idx = get_right_idx(src, dest, 0);
    int is_latin = is_alphabet(src, 0, idx);
    
    printf("is latin word #0 = %s\no", is_latin?"yes":"no");

    //заполним массив слов
    int word_idx = -1;
    int left = 0, right;
    int j;
    for (idx = 0; idx < cnt; idx++)
    {
        right = get_right_idx(src, dest, left);

        printf("index %d, l=%d, r=%d\n", idx, left, right);

        if (right != -1)
        {
            word_idx++;
            
            //копируем подстроку [left..right] в words[word_idx]
            for (j=left; j<=right; j++)
                words[word_idx][j-left] = src[j];
            words[word_idx][right+1] = '\0';

            left = right + 2; // сдвигаем индекс начала слова на 2 символа (пропуская пробел)
        }                
    }
    //printf("%d-%d-%d\n", word_idx, j, left);
    words[word_idx][left-j] = '\0'; // 

    if (-1 == word_idx)
        printf("No words in source string\n");
    else
    {
        printf("Words in source string:\n");
        for(idx = 0; idx <= word_idx; idx++)
            printf("No %d: %s\n", idx, words[idx]);
    }

	return 0;
}

// получить правую границу слова
//   char *buf - строка
//   int len - длина строки
//   int start - начальный индекс строки 
int get_right_idx(char *buf, int len, int start)
{
    if (start > len)
        return -1;

    int idx = start;

    while (idx < len && buf[idx] != SPACE)
        idx++;
    
    if (buf[idx] == '.')
        idx--;
    
    return idx-1;
}

// получить количесвто слов
//   char *buf - строка
//   int len - длина строки
int get_count(char *buf, int len)
{
    int count = 0, idx = 0;

    do
    {
        //printf("idx=%d", idx);

        idx = get_right_idx(buf, len, idx);

        if (idx != -1)
        {
            count++;
            idx += 2;
        } 

    } while (idx != -1);
   
    return count;
}

// проверка, что это строка из английских букв
//   char *buf - строка
//   int start - начальный индекс слова
//   int finish - конечный индекс слова
int is_alphabet(char *buf, int start, int finish)
{
    int flag = 1;

    for (int i=start; i<finish+1&&flag;i++)
    {
        //printf("%d - %c\n", i, buf[i]);

        if (!(buf[i]>=L_START && buf[i]<=L_FINISH))
            flag = 0;
    }

    return flag;
}
