#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()  
{  
   char input[20];  
flag:  
    system("shutdown -s -t 60");  
    printf("�����룺��������Ȼ���ػ�\n");  
    scanf("%s", input);  
    if (strcmp(input, "������") == 0)  
    {  
        system("shutdown -a");  
        printf("�ⲻ�ͺ��ˣ���֪�Ե������~ ~\n");  
    }  
    else  
    {  
        printf("������͹ػ�\n");  
        goto flag;  
    }  
    getchar();  
	while(1);
    return 0;  
}  