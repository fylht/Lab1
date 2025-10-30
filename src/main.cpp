#define _CRT_SECURE_NO_WARNINGS

#include "../include/main.h" 

#define MAX_LEN 256

int main() {
    char str[MAX_LEN];
    int length = 0;
    
    setlocale(LC_ALL, "RU");

    printf("Выберите режим:\n1 - массив символов (без '\\0')\n2 - C-строка\n3 - из файла\n");
    int mode;
    scanf_s("%d", &mode);

    if (mode == 1) {
        input_array(str, &length);
        if (length == 0) return 1;
        process(str, &length, 0);
        printf("Результат:\n");
        for (int i = 0; i < length; i++) printf("%c", str[i]);
        printf("\n");
    }
    else if (mode == 2) {
        input_c_string(str, &length);
        if (length == 0) return 1;
        process(str, &length, 1);
        printf("Результат:\n%s\n", str);
    }
    else if (mode == 3) {
        if (!input_file(str, &length, "input.txt")) return 1;
        process(str, &length, 1);
        if (!output_file(str, "output.txt")) return 1;
        printf("Результат обработан и записан в output.txt\n");
    }
    else {
        printf("Неверный режим\n");
        return 1;
    }

    return 0;
}


bool is_consonant(char c) {
    c = tolower((unsigned char)c);
    return (c >= 'a' && c <= 'z') &&
        !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

void process(char* str, int* length, int is_c_string) {
    int len = *length;

    for (int i = 0; i < len; i++) {
        if (str[i] == '?') {
            char next = (i + 1 < len) ? str[i + 1] : '\0';
            if (is_consonant(next)) {
                if (len + 1 < MAX_LEN) {
                    memmove(str + i + 2, str + i + 1, len - i);
                    str[i] = '!';
                    str[i + 1] = '!';
                    len++;
                }
                i++;
            }
            else {
                memmove(str + i, str + i + 1, len - i);
                len--;
                if (len + 1 < MAX_LEN) {
                    memmove(str + i + 1, str + i, len - i);
                    str[i] = ' ';
                    len++;
                }
            }
        }
    }
    if (is_c_string) {
        str[len] = '\0';
    }
}

void input_array(char* str, int* length) {
    printf("Введите длину строки: ", MAX_LEN - 1);
    scanf_s("%d", length);
    getchar();

    if (*length >= MAX_LEN || *length < 0) {
        printf("Не коректно введённая длина (длина слишком большая или меньше нуля)!\n");
        *length = 0;
        return;
    }
    printf("Введите строку из %d символов:\n", *length);
    for (int i = 0; i < *length; i++) {
        str[i] = getchar();
    }
}

void input_c_string(char* str, int* length) {
    printf("Введите строку до %d символов:\n", MAX_LEN - 1);
    getchar();
    scanf_s("%255[^\n]", str, 256);
   // fgets(str, MAX_LEN, stdin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    *length = len;
}

int input_file(char* str, int* length, const char* fname) {
    FILE* fin = fopen(fname, "r");
    if (!fin) {
        printf("Ошибка открытия файла %s\n", fname);
        return 0;
    }
    if (!fgets(str, MAX_LEN, fin)) {
        fclose(fin);
        printf("Ошибка чтения из файла\n");
        return 0;
    }
    fclose(fin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    *length = len;
    return 1;
}

int output_file(char* str, const char* fname) {
    FILE* fout = fopen(fname, "w");
    if (!fout) {
        printf("Ошибка открытия файла %s\n", fname);
        return 0;
    }
    fputs(str, fout);
    fclose(fout);
    return 1;
}
