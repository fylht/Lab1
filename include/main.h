#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

bool is_consonant(char c);
void process(char* str, int* length, int is_c_string);
void input_array(char* str, int* length);
void input_c_string(char* str, int* length);
int input_file(char* str, int* length, const char* fname);
int output_file(char* str, const char* fname);




#endif