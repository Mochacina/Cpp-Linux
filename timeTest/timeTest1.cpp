#define _CRT_SECURE_NO_WARNINGS // Ȥ�� localtime_s�� ���
#include <stdio.h>
#include <time.h>

int main() {
    time_t timer;
    struct tm* t;
    timer = time(NULL); // 1970�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� ��
    t = localtime(&timer); // �������� ���� ����ü�� �ֱ�
    
    printf("���н� Ÿ�� (Unix Time): %lld ��\n\n", timer); 
    printf("���� ��: %d\n", t->tm_year + 1900);
    printf("���� ��: %d\n", t->tm_mon + 1);
    printf("���� ��: %d\n", t->tm_mday);
    printf("���� ��: %d\n", t->tm_hour);
    printf("���� ��: %d\n", t->tm_min);
    printf("���� ��: %d\n", t->tm_sec);
    printf("���� ����: %d\n", t->tm_wday); // ��=0, ��=1, ȭ=2, ��=3, ��=4, ��=5, ��=6
    printf("���� �� ��° ��: %d\n", t->tm_yday); // 1�� 1���� 0, 1�� 2���� 1
    printf("����Ÿ�� ���� ����: %d\n", t->tm_isdst); // �ǽ� ���̸� ���, �̽ǽø� 0, �ǽ� ������ ������ ����
    
    return 0;
}