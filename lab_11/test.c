#include <stdio.h>
#include <limits.h>
#include "process.h"

/**
 * @brief my_strcmp Функция сравнения строк s1 и s2.
 * @param s1 [in] - указатель на первую строку
 * @param s2 [in] - указатель на вторую строку
 * @return Возвращает -1, если строки не равны, иначе - 0.
 */
int my_strcmp(const char *s1, const char *s2)
{
    int len_1 = my_strlen(s1);
    int len_2 = my_strlen(s2);
    if (len_1 != len_2)
        return -1;
    for (int i = 0; i < len_1; i++)
        if (s1[i] != s2[i])
            return -1;
    return 0;
}

/**
 * @brief test_strcmp Функция тестирования сравнения строк.
 */
void test_strcmp(void)
{
    printf("Tests for my_strcmp:\n");
    {
        char *s1 = "\0";
        char *s2 = "\0";
        char *s3 = "a";
        printf("Correct work with empty strings: %s\n", (my_strcmp(s1, s2) == 0) ? "YES" : "NO");
        printf("Correct work with empty strings: %s\n", (my_strcmp(s1, s3) == -1) ? "YES" : "NO");
    }
    {
        char *s1 = "a";
        char *s2 = "a";
        char *s3 = "aa";
        printf("Correct work with non-empty strings: %s\n", (my_strcmp(s1, s2) == 0) ? "YES" : "NO");
        printf("Correct work with non-empty strings: %s\n", (my_strcmp(s1, s3) == -1) ? "YES" : "NO");
        printf("Correct work with non-empty strings: %s\n\n", (my_strcmp(s3, s1) == -1) ? "YES" : "NO");
    }
}

/**
 * @brief test_strlen Функция тестирования определения длины строки
 */
void test_strlen(void)
{
    printf("Tests for my_strlen:\n");
    {
        char *s1 = "\0";
        char *s2 = "a";
        char *s3 = "ab";
        char *s4 = "abc";
        printf("Correct work with empty string: %s\n", (my_strlen(s1) == 0) ? "YES" : "NO");
        printf("Correct work with 1-letter string: %s\n", (my_strlen(s2) == 1) ? "YES" : "NO");
        printf("Correct work with 2-letter string: %s\n", (my_strlen(s3) == 2) ? "YES" : "NO");
        printf("Correct work with 3-letter string: %s\n\n", (my_strlen(s4) == 3) ? "YES" : "NO");
    }
}

/**
 * @brief test_strcpy Функция тестирования копирования памяти.
 */
void test_memcpy(void)
{
    printf("Tests for  my_strcpy:\n");
    {
        char s1[2];
        s1[0] = '\0';
        char *s2 = "";
        my_memcpy(s1, s2, 0);
        printf("Correct work with empty strings: %s\n", (my_strcmp(s1, "\0") == 0) ? "YES" : "NO");
    }
    {
        char s1[2] = { 'a', '\0' };
        char *s2 = "";
        my_memcpy(s1, s2, 0);
        printf("Correct work with empty string: %s\n", (my_strcmp(s1, "a") == 0) ? "YES" : "NO");
    }
    {
        char s1[2];
        s1[0] = '\0';
        char *s2 = "a";
        my_memcpy(s1, s2, 2);
        printf("Correct work with empty string and 1-letter string: %s\n", (my_strcmp(s1, "a") == 0) ? "YES" : "NO");
    }
    {
        char s1[3];
        s1[0] = '\0';
        char *s2 = "ab";
        my_memcpy(s1, s2, 3);
        printf("Correct work with empty string and 2-letter string: %s\n", (my_strcmp(s1, "ab") == 0) ? "YES" : "NO");
    }
    {
        char s1[4];
        s1[0] = 'a';
        s1[1] = '\0';
        char *s2 = "ab";
        my_memcpy(s1 + 1, s2, 3);
        printf("Correct work with non-empty string and 2-letter string: %s\n\n", (my_strcmp(s1, "aab") == 0) ? "YES" : "NO");
    }
}

/**
 * @brief test_my_itoa функция тестирования перевода числа в указанную систему счисления и конвертирование полученного числа в строку.
 */
void test_my_itoa(void)
{
    printf("Tests for turning decimal number to octal (in string format):\n");
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "0";
        int num = 0;
        my_itoa(num, res, 8);
        printf("Correct work with 0: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "1";
        int num = 1;
        my_itoa(num, res, 8);
        printf("Correct work with 1: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "16";
        int num = 14;
        my_itoa(num, res, 8);
        printf("Correct work with 14: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "400";
        int num = 256;
        my_itoa(num, res, 8);
        printf("Correct work with 256: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "17777777777";
        long long int num = 2147483647;
        my_itoa(num, res, 8);
        printf("Correct work with INT_MAX: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "12365402763010431625";
        long long int num = 188781952858469269;
        my_itoa(num, res, 8);
        printf("Correct work with limit: %s\n\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    printf("Tests for turning decimal number to decimal (in string format):\n");
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "0";
        int num = 0;
        my_itoa(num, res, 10);
        printf("Correct work with 0: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "1";
        int num = 1;
        my_itoa(num, res, 10);
        printf("Correct work with 1: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "14";
        int num = 14;
        my_itoa(num, res, 10);
        printf("Correct work with 14: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "256";
        int num = 256;
        my_itoa(num, res, 10);
        printf("Correct work with 256: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "2147483647";
        long long int num = 2147483647;
        my_itoa(num, res, 10);
        printf("Correct work with INT_MAX: %s\n\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    printf("Tests for turning decimal number to binary (in string format):\n");
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "0";
        int num = 0;
        my_itoa(num, res, 2);
        printf("Correct work with 0: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "1";
        int num = 1;
        my_itoa(num, res, 2);
        printf("Correct work with 1: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "1110";
        int num = 14;
        my_itoa(num, res, 2);
        printf("Correct work with 14: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "100000000";
        int num = 256;
        my_itoa(num, res, 2);
        printf("Correct work with 256: %s\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
    {
        char res[MAX_NUM_LEN + 1];
        char *check = "10110111011101011011";
        long long int num = 751451;
        my_itoa(num, res, 2);
        printf("Correct work with 751451: %s\n\n", (my_strcmp(check, res) == 0) ? "YES" : "NO");
    }
}

/**
 * @brief test_my_snprintf Функция тестирования snprintf().
 */
void test_my_snprintf(void)
{
    printf("Tests for my_snprintf:\n");
    {
        // Проверка правильной обработки односимвольной строки и двух цифр: восьмеричной и десятичной
        char a[20];
        char b[20];
        char str[10] = "a";
        unsigned long long int o_num = 1;
        int d_num = 0;
        int rc1 = my_snprintf(a, 20, "%s%llo%i", str, o_num, d_num);
        int rc2 = snprintf(b, 20, "%s%llo%i", str, o_num, d_num);
        printf("Correct work with '%%s%%llo%%i': %s\n", (my_strcmp(a, b) == 0 && (rc1 == rc2)) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки трехсимвольной строки и двух цифр: восьмеричной и десятичной
        char a[20];
        char b[20];
        char str[10] = "abc";
        unsigned long long int o_num = 1;
        int d_num = 0;
        int rc1 = my_snprintf(a, 20, "%s%llo%i", str, o_num, d_num);
        int rc2 = snprintf(b, 20, "%s%llo%i", str, o_num, d_num);
        printf("Correct work with '%%s%%llo%%i': %s\n", (my_strcmp(a, b) == 0 && (rc1 == rc2)) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки односимвольной строки и двух цифр: восьмеричной и десятичной (другой порядок спецификаторов)
        char a[20];
        char b[20];
        char str[10] = "a";
        unsigned long long int o_num = 1;
        int d_num = 0;
        int rc1 = my_snprintf(a, 20, "%llo%s%i", o_num, str, d_num);
        int rc2 = snprintf(b, 20, "%llo%s%i", o_num, str, d_num);
        printf("Correct work with '%%llo%%s%%i': %s\n", (my_strcmp(a, b) == 0 && (rc1 == rc2)) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки трехсимвольной строки и двух чисел: восьмеричного и десятичного (другой порядок спецификаторов)
        char a[20];
        char b[20];
        char str[10] = "abc";
        unsigned long long int o_num = 51;
        int d_num = 0;
        int rc1 = my_snprintf(a, 20, "%i%llo%s", d_num, o_num, str);
        int rc2 = snprintf(b, 20, "%i%llo%s", d_num, o_num, str);
        printf("Correct work with '%%i%%llo%%s': %s\n", (my_strcmp(a, b) == 0 && (rc1 == rc2)) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки отрицательного числа в десятичной системе
        char a[20];
        char b[20];
        char str[10] = "a";
        unsigned long int o_num = 1;
        int d_num = -1;
        int rc1 = my_snprintf(a, 20, "%llo%i%s", o_num, d_num, str);
        int rc2 = snprintf(b, 20, "%llo%i%s", o_num, d_num, str);
        printf("Correct work with '%%llo%%i%%s', int num < 0: %s\n", (rc1 == -10 && rc2 == -1) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки отрицательного числа в десятичной системе
        char a[20];
        char b[20];
        char str[10] = "a";
        unsigned long long int o_num = 1;
        int d_num = -156;
		const char *p = "%llo%i%s";
        int rc1 = my_snprintf(a, 20, p, o_num, d_num, str);
        int rc2 = snprintf(b, 20, p, o_num, d_num, str);
        printf("Correct work with '%%llo%%i%%s', int num < 0: %s\n", (my_strcmp(a, b) == 0 && rc1 == 6 && rc2 == 6) ? "YES" : "NO");
    }
    {
        // // Проверка правильной обработки отрицательного числа в восьмеричной системе системе
        char a[20];
        //char b[20];
        char str[10] = "a";
        long long int o_num = -1;
        int d_num = 0;
		const char *p = "%llo%i%s";
        int rc1 = my_snprintf(a, 20, p, o_num, d_num, str);
        //int rc2 = snprintf(b, 20, "%llo%i%s", o_num, d_num, str);
        //printf("%d %s\n", rc2, b);
        printf("Correct work with '%%llo%%i%%s', oct num < 0: %s\n", (rc1 == SN_ERROR) ? "YES" : "NO");
    }
    {
        // Проверка правильности обработки двух срок
        char a[20];
        char b[20];
        char str[11] = "My name is";
        char str_2[7] = "[name]";
        printf("Correct work with '%%s%%s': %s\n", (my_snprintf(a, 20, "%s %s!", str, str_2) == snprintf(b, 20, "%s %s!", str, str_2) && my_strcmp(a, b) == 0) ? "YES" : "NO");
    }
    {
        // Размер предоставляемого буфера меньше, чем необходимое количество байт для записи
        char a[5];
        char str[11] = "My name is";
		const char *p = "%s!";
        int rc1 = my_snprintf(a, 5, p, str);
        int rc2 = snprintf(a, 5, p, str);
        printf("Correct work with '%%s', len(argument) > sizeof(buf): %s\n", (rc1 == SN_ERROR && rc2 == -1) ? "YES" : "NO");
    }
    {
        // Размер предоставляемого буфера меньше, чем необходимое количество байт для записи (не хватает места для символа конца строки)
        char a[9];
        char str[11] = "name";
		const char *p = "!%s%s";
        int rc1 = my_snprintf(a, 9, p, str, str);
        int rc2 = snprintf(a, 8, p, str, str); // snprintf не проверяет, хватает ли памяти под \0 (?)
        printf("Correct work with '%%s', len(argument) > sizeof(buf): %s\n", (rc1 == SN_ERROR && rc2 == -1) ? "YES" : "NO");
    }
    {
        // Проверка правильной обработки неккоретного спецификатора
        char a[9];
        char str[11] = "name";
        int rc = my_snprintf(a, 9, "!%d%s", str, str);
        printf("Correct work with invalid specificator: %s\n", (rc == SN_ERROR) ? "YES" : "NO");
    }
    {
        // Память под строку выделена, но размер переданного буфера нулевой
        char a[9];
        char str[11] = "name";
		const char *p = "!%s%s";
        int rc1 = my_snprintf(a, 0, p, str, str);
        int rc2 = snprintf(a, 0, p, str, str); // на windows функция не соответствует стандарту (возвращает -1)
        printf("Correct work with n = 0 and buf != NULL: %s\n", (rc1 == 9 && rc2 == -1) ? "YES" : "NO");
    }
    {
        // Память под строку не выделена, но размер переданного буфера не нулевой
        char *a = NULL;
        char str[11] = "name";
        int rc1 = my_snprintf(a, 10, "!%s%s", str, str);
        //int rc2 = snprintf(a, 10, "!%s%s", str, str); // при этом вызове функции появляются ошиби по памяти
        printf("Correct work with n = 0 and buf != NULL: %s\n", (rc1 == SN_ERROR) ? "YES" : "NO");
    }
    {
        // Память под строку не выделена и размер переданного буфера равен 0, функция должна вернуть необходимое количество байт для записи(не считая \0)
        char *a = NULL;
        char str[11] = "name";
		const char *p = "%s";
        int rc1 = my_snprintf(a, 0, p, str);
        int rc2 = snprintf(a, 0, p, str);
        printf("Correct work with n = 0 and buf = NULL: %s\n", (rc1 == rc2) ? "YES" : "NO");
    }
    printf("\nNew tests:\n");
    {
        // максимальные и минимальные значения для знакового типа
        char str[30];
        char str2[30];
        int max = INT_MAX;
        int min = INT_MIN;
        int rc1 = my_snprintf(str, sizeof(str), "%i", max);
        int rc2 = snprintf(str2, sizeof(str2), "%i", max);
        printf("Correct work with INT_MAX: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");

        // если переводить INT_MIN в положительное число, то возникает переполнение
        // можно в функции snprintf записывать переданный результат в переменную типа long int,
        // однако в моем случае INT_MIN совпадает с LONG_MIN и все равно происходит переполнение

        rc1 = my_snprintf(str, sizeof(str), "%i", min + 1);
        rc2 = snprintf(str2, sizeof(str2), "%i", min + 1);
        printf("Correct work with INT_MIN + 1: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
    {
        // передача нуля и отрицательного числа в знаковый тип
        char str[100];
        char str2[100];
        int max = 0;
        int min = -1;
        int rc1 = my_snprintf(str, sizeof(str), "%i", max);
        int rc2 = snprintf(str2, sizeof(str2), "%i", max);
        printf("Correct work with 0: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");

        rc1 = my_snprintf(str, sizeof(str), "%i", min);
        //printf("%d %s\n", rc1, str);
        rc2 = snprintf(str2, sizeof(str2), "%i", min);
        //printf("%d %s\n", rc2,  str2);
        printf("Correct work with -1: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
    {
        // передача нуля и максимального значения для беззнакового типа
        char str[500];
        char str2[500];
        unsigned long long int min = 0;
        unsigned long long int max = ULLONG_MAX;
        int rc1;
        int rc2;
        rc1 = my_snprintf(str, sizeof(str), "%llo", max);
        rc2 = snprintf(str2, sizeof(str2), "%llo", max);
        printf("Correct work with ULLONG_MAX: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");

        rc1 = my_snprintf(str, sizeof(str), "%llo", min);
        //printf("%d %s\n", rc1, str);
        rc2 = snprintf(str2, sizeof(str2), "%llo", min);
        //printf("%d %s\n", rc2,  str2);
        printf("Correct work with 0: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
    {
        // передача отрицательного значения в беззнаковый тип
        char str[100];
        char str2[100];
        unsigned long long int a = -10;
        int rc1 = my_snprintf(str, sizeof(str), "%llo", a);
        int rc2 = snprintf(str2, sizeof(str2), "%llo", a);
        printf("Correct work with -10 for %%llo: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
    {
        // передача значения, превышающего допустимое, для знакового типа
        char str[100];
        char str2[100];
        unsigned int max = UINT_MAX;
        int rc1 = my_snprintf(str, sizeof(str), "%i", max);
        int rc2 = snprintf(str2, sizeof(str2), "%i", max);
        printf("Correct work with UINT_MAX for %%i: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
    {
        // передача буфера достаточной длины
        char str[100] = "";
        char str2[100] = "";
        int year = 1999;
        char *test1 = "Nika";
        int rc1;
        rc1 = my_snprintf(str, sizeof(str), "My name is %s. I was born in %i", test1, year);
        snprintf(str2, sizeof(str2), "My name is %s. I was born in %i", test1, year);
        printf("Correct work with 'My name is %%s. I was born in %%i': %s\n", (my_strcmp(str, str2) == 0 && rc1 == 35) ? "YES" : "NO");
    }
    {
        // передача буфера нулевой длины
        char str[1] = "";
        char str2[1] = "";
        char *str_literal_1 = "My name is ";
        char *str_literal_2 = ". I was born in ";
        int year = 1999;
        char *test1 = "Nika";
        int rc1;
		const char *p = "%s%s%s%i";
        rc1 = my_snprintf(str, 0, p, str_literal_1, test1, str_literal_2, year);
        snprintf(str2, 0, p, str_literal_1, test1, str_literal_2, year);
        printf("Correct work with 'My name is %%s. I was born in %%i' and 0 in length of buff: %s\n", (my_strcmp(str, str2) == 0 && rc1 == 35) ? "YES" : "NO");
    }
    {
        // передача буфера недостаточной длины, для записи строки, переданной через %s
        char str[14] = "";
        char str2[14] = "My name is Ni";
        char *str_literal_1 = "My name is ";
        char *str_literal_2 = ". I was born in ";
        int year = 1999;
        char *test1 = "Nika";
        int rc1;
		const char *p = "%s%s%s%i";
        rc1 = my_snprintf(str, 14, p, str_literal_1, test1, str_literal_2, year);
        printf("Correct work with 'My name is %%s. I was born in %%i' and length of buff not enough for string: %s\n", (my_strcmp(str, str2) == 0 && rc1 == -10) ? "YES" : "NO");
    }
    {
        // передача буфера недостаточной длины, для записи числа, переданного через %i
        char str[34] = "";
        char str2[34] = "My name is Nika. I was born in 19";
        char *str_literal_1 = "My name is ";
        char *str_literal_2 = ". I was born in ";
        int year = 1999;
        char *test1 = "Nika";
        int rc1;
		const char *p = "%s%s%s%i";
        rc1 = my_snprintf(str, 34, p, str_literal_1, test1, str_literal_2, year);
        printf("Correct work with 'My name is %%s. I was born in %%i' and length of buff not enough for number: %s\n", (my_strcmp(str, str2) == 0 && rc1 == -10) ? "YES" : "NO");
    }
    {
        // передача в буфер пустой строки через %s
        char str[50];
        char str2[50];
        char *str_literal_1 = "My name is ";
        char *str_literal_2 = ". I was born in ";
        int year = 1999;
        char *test1 = "";
        int rc1, rc2;
        rc1 = my_snprintf(str, 50, "%s%s%s%i", str_literal_1, test1, str_literal_2, year);
        rc2 = snprintf(str2, 50, "%s%s%s%i", str_literal_1, test1, str_literal_2, year);
        printf("Correct work with 'My name is %%s. I was born in %%i' and string is null: %s\n", (my_strcmp(str, str2) == 0 && rc1 == rc2) ? "YES" : "NO");
    }
}

int main(void)
{
    test_strlen();
    test_strcmp();
    test_memcpy();
    test_my_itoa();
    test_my_snprintf();
    return 0;
}
