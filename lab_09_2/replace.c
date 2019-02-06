#include "replace.h"
#include "str.h"

/**
 * @brief my_strstr Функция ищет первое вхождение строки str2 в строку str1, возвращает указатель на это первое вхождение или NULL.
 * @param str1 [in] - указатель на первую строку, в которой ведется поиск вхождения
 * @param str2 [in] - указатель на вторую (искомую) строку
 * @return Возвращает указатель на первое вхождение str2 в str1, либо (если вхождения не найдены) возвращает NULL.
 */
char *my_strstr(const char *str1, const char *str2)
{
    if (str2 == NULL || str1 == NULL)
        return NULL;
    const char *cur = str1;
    const char *s1, *s2;
    while (*cur)
    {
        s1 = cur;
        s2 = str2;
        while (*s1 && *s2)
        {
            if (*s1 - *s2)
                break;
            s1++;
            s2++;
        }
        if (*s2 == '\0')
            return (char *)cur;
        cur++;
    }
    return NULL;
}

/**
 * @brief str_replace Функция производит замену каждого вхождения подстроки search в строку source на подстроку replace.
 * @param source [in] - указатель на строку, в которой будут производиться замены
 * @param search [in] - указатель на подстроку, которую нужно заменить
 * @param replace [in] - указатель на подстроку, на которую нужно заменить
 * @return Возвращает указатель на результирующую строку (result), в которой произведены все замены, либо NULL, если исходная строка нулевая или произошла ошибка выделения памяти.
 */
char *str_replace(const char *source, const char *search, const char *replace)
{
    if (source == NULL)
        return NULL; // Если строка, в которой необходимо произвести замены, пустая, то и результирующая строка тоже будет пустой
    char *result = NULL; // Инициализация результирующей строки
    size_t len_source = len(source); // Длина строки, в которой будут производиться замены
    size_t len_search = len(search); // Длина строки, которую нужно заменить
    size_t len_replace = len(replace); // Длина строки, на которую нужно заменить
    size_t diff = len_replace - len_search; // Разница между длиной заменяющей строки и длиной заменяемой строкой
    size_t changes = 0; // Количество замен
    const char *str = source; // Вспомогательный указатель на строку, в которой будут производиться замены
    char *new; // Вспомогательный указатель на строку, сохраняющий результат работы функции my_strstr()

    /*
     * Тело цикла выполняется до тех пор, пока указатель на строку str не будет указывать на '\0'
     * или если функция my_strstr вернула NULL (это значит, что вхождение подстроки search в строку str не было найдено)
    */
    while (*str && (new = my_strstr(str, search)))
    {
        str += new - str + len_search; // Если вхождение нашлось, то указатель str перемещается на позицию символа, следующего после найденного вхождения заменяемой подстроки
        changes += 1; // Количество замен увеличивается на 1
    }
    result = malloc(len_source + changes * diff + 1); // Выделение памяти под результирующую строку
    // Если память удалось выделить успешно
    if (result)
    {
        //  Если заменяемой строки не нашлось в исходной (нечего заменять), то в результирующую строку полностью скопирована исходная строка
        if (changes == 0)
            my_memcpy((void *)result, (void *)source, len_source);
        else
        {
            char *cur_res = result; // Вспомогательный указатель на результирующую строку
            const char *str = source; // Вспомогательный указатель на исходную строку

            // Тело икла выполняется, пока существуют вхождения подстроки search  в строку str
            while ((new = my_strstr(str, search)) != NULL)
            {
                // Если вхождение найдено
                my_memcpy(cur_res, str, new - str); // В результирующую строку скопированы все символы исходной строки до найденного вхождения (не включая символы search)
                my_memcpy(cur_res + (new - str), (void *)replace, len_replace); // В результирующую строку после уже скопированных символов скопированы символы заменяющей строки (replace)
                cur_res += (new - str) + len_replace; // Текущий указатель на исходную строку передвинут на позицию символа, следующего после найденного вхождения
                str += (new - str) + len_search; // Текущий указатель на результирующую строку передвинут на позицию символа, следующего после скопированных символов исходной строки и после всех символов заменяющей строки
            }
            my_memcpy(cur_res, str, len(str)); // Все остальные символы исходной строки, которые находятся за последним вхождением заменяемой подстроки, скопированы в результирующую
        }
        result[len_source + changes * diff] = '\0'; // В результирующую строку на последнее место добавлен признак конца строки
    }
    else
        return NULL;  // Если память не удалось выделить, то возвращается NULL
    return result; // Если функция отработала успешно, то возвращается указатель на результирующую строку
}