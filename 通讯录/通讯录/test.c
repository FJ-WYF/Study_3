#include "contacts.h"
void menu()
{
	printf("*******************************************\n");
	printf("*******1.�����ϵ��     2.ɾ����ϵ��*******\n");
	printf("*******3.������ϵ��     4.�޸���ϵ��*******\n");
	printf("*******5.�鿴ͨѶ¼     6.������ϵ��*******\n");
	printf("***************** 0.�˳� ******************\n");
}
int main()
{
	int input = 0;
	contacts x;//����ͨѶ¼�ṹ�����x
	Init_contacts(&x);//��ʼ��ͨѶ¼
	do {
		menu();
		printf("��ѡ��: >");
		scanf("%d", &input);
		switch (input)
		{
		case �����ϵ��:
			contacts_add(&x);
			break;
		case ɾ����ϵ��:
			contacts_delete(&x);
			break;
		case ������ϵ��:
			contacts_search(&x);
			break;
		case �޸���ϵ��:
			contacts_modify(&x);
			break;
		case �鿴ͨѶ¼:
			contacts_show(&x);
			break;
		case ������ϵ��:
			contacts_sort(&x);
			break;
		case �˳�:
			//����ͨѶ¼�����ٶ�̬���ٵ��ڴ�
			Savecontact(&x);
			Destroy(&x);
			printf("�˳�.");
			break;
		default:
			printf("����������֣�\n");
			break;
		}
	} while (input);
	return 0;
}