#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string.h>

#include "../include/main.h"

bool is_consonant(char c);
void process(char* str, int* length, int is_c_string);

TEST_CASE("�������� ������� is_consonant") {
    REQUIRE(is_consonant('b') == true);
    REQUIRE(is_consonant('a') == false);
    REQUIRE(is_consonant('Y') == false); 
    REQUIRE(is_consonant('Z') == true);
    REQUIRE(is_consonant('?') == false);
}

TEST_CASE("�������� ������� process � �������� !! � ��������") {
    char str[256];
    int len;

    SECTION("������� !! ���� ����� ? ���������") {
        strcpy(str, "abc?dxyz");
        len = (int)strlen(str);
        process(str, &len, 1);
        REQUIRE(strcmp(str, "abc!!dxyz") == 0);
        REQUIRE(len == strlen(str));
    }

    SECTION("�������� ? � �������� ������� ���� ����� ? �� ���������") {
        strcpy(str, "test? xyz");
        len = (int)strlen(str);
        process(str, &len, 1);
        REQUIRE(strcmp(str, "test  xyz") == 0);
        REQUIRE(len == strlen(str));
    }

    SECTION("��������� ������") {
        strcpy(str, "?a?b?c?");
        len = (int)strlen(str);
        process(str, &len, 1);
        REQUIRE(strcmp(str, " ?a!!b ?c ") == 0);
    }
}