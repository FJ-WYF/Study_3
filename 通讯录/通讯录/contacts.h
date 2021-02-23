#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define DEFAULT_SZ 3
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 15
#define MAX_ADDRESS 30

enum menu
{
	�˳�,
	�����ϵ��,
	ɾ����ϵ��,
	������ϵ��,
	�޸���ϵ��,
	�鿴ͨѶ¼,
	������ϵ��
};

typedef struct info {
	char name   [MAX_NAME]   ;
	int  age                 ;
	char sex    [MAX_SEX]    ;
	char tele   [MAX_TELE]   ;
	char address[MAX_ADDRESS];
}info;

typedef struct contacts {
	info* x;
	int capacity;//��ǰͨѶ¼���������
	int sz;//��¼��ǰ������ϵ����
}contacts;

void Init_contacts(struct contacts* p);
void contacts_add(struct contacts* p);
void contacts_delete(struct contacts* p);
void contacts_search(struct contacts* p);
void contacts_modify(struct contacts* p);
void contacts_show(const struct contacts* p);
void contacts_sort(struct contacts* p);
void Destroy(struct contacts* p);
void Savecontact(struct contacts* p);
int name_cmp(const void* e1, const void* e2);
int age_cmp(const void* e1, const void* e2);