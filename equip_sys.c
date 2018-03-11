#include<stdio.h>
#include<string.h>
#include<direct.h>	//����ʱ����
#include<stdlib.h>
#include<malloc.h>	//���嶯̬����
#include"time.h"	//����ʱ������
#include"myinput.c"	//����ϰ���õ��������
#include"myfile.c"	//����ϰ���õ��ļ�����
struct date
 { 
	int year;
	int month;
	int day ;
 };
 struct equipment
 {
	 char ID_Number[16];		//�豸���
	 int equip_Type;			//�豸����:1-�ʼǱ���2-̨ʽ����3-ƽ����ԣ�4-ͶӰ��
								//		   5-ɨ���ǣ�6-��ӡ����7-�������  8-��Ӱ��
	 char equip_Version[16];	//�豸�ͺţ��汾��
	 struct date purchase_Date;	//��������
	 float price;				//���򵥼�
	 char manager[16];				//����Ա
	 int status;				//�豸״̬ 1-���ã�2-��ά�ޣ�3-������
}equipment[99];
int sn = 0;				//sn������¼�豸��
/*����������ڴ�*/
void clear()
{
	char ch;
	while((ch = getchar()) != EOF && ch != '\n');
}
int main()
{ 
	int i,j,come;
	FILE *myf;
	void load_file(char *s);		//��ʼ���豸��Ϣ
	void load_manual();
	
	void print();			//��ӡ�豸��Ϣ
	void del();			//ɾ���豸��Ϣ
	void search(char way[]);		//��ѯ�豸��Ϣ
	void insert();		//�����¼
	void start();
	printf("\n************************************************�豸����ϵͳ**********************************************\n");
	printf("\n˵��:\n\t���豸ϵͳ��ģ��ʹ�ã�����豸�����Ϊ����99�ˣ��Ҵ�ϵͳ������಻��֮����\n\t��ϵͳ����ʱ��D���½����ļ��У�equip_sys��Ϊ�洢λ�á�\n");
	printf("\n****** D:\\equip_sys\\equipment_info.txt ��ΪԤ���ļ���������ű����Ϣ;\n");
	printf("\n--------------------------------------------------\n\n");
	if((myf = fopen("D:\\equip_sys\\equipment_info.txt","r")) == NULL)
	{
		printf("\t->�������ǵ�һ��ʹ�ñ�ϵͳ����ָ�������г�ʼ����\n\n");
		if(_mkdir("D:\\equip_sys") == 0)
		{
			printf("\t->�ļ��У�D:\\equip_sys �ѽ���\n\n");
		}
		if((myf = fopen("D:\\equip_sys\\equipment_info.txt","w")) != NULL)
		{
			printf("\t->�ļ� D:\\equip_sys\\equipment_info.txt �ѽ���\n\n");
		}
		printf("\t->�������ݳ�ʼ����\n\n\t\t����¼�뷽ʽ��1.�ļ�¼��\t2.�ֶ�¼��\t3.�ݲ�¼��\n\n");
		come = getsInt("��ѡ��:");
		if(come == 1)
		{
			printf("�뽫Ҫ¼����ļ����� D:\\equip_sys �ļ����£�������Ϊload.txt(�����������)");
			getchar();
			getchar();
			load_file("D:\\equip_sys\\load.txt");
		}
		else if(come == 2)
		{
			load_manual();
		}
	}
	else
	{
		printf("-----------��ӭ�ٴν����豸ϵͳ��----------\n\n\n");
		printf("\t->ϵͳΪ������Ԥ���أ������ϴα����ļ�¼.");
		load_file("D:\\equip_sys\\equipment_info.txt");
		if(sn == 0) 
		{
			printf("\n\n�豸��¼Ϊ�ա�\n\n");
			printf("\t->�������ݳ�ʼ����\n\n\t\t����¼�뷽ʽ��1.�ļ�¼��\t2.�ֶ�¼��\t3.�ݲ�¼��\n\n");
			come = getsInt("��ѡ��:");
			if(come == 1)
			{
				printf("�뽫Ҫ¼����ļ����� D:\\equip_sys �ļ����£�������Ϊload.txt(�����������)");
				getchar();
				getchar();
				load_file("D:\\equip_sys\\load.txt");
			}
			else if(come == 2)
			{
				load_manual();
			}
		}
		
		
	}
	start();
	return 0;
}
void start()			//ϵͳ���
{
	int i,j = -1;
	char c;

	void load_file(char *s);		//��ʼ���豸��Ϣ
	void load_manual();
	void print();			//��ӡ�豸��Ϣ	
	void search(char way[16]);		//��ѯ�豸��Ϣ
	void insert();		//�����¼	
	void save();		//��������Ϣ
	printf("\n\n************************�˵���************************\n\n");
	printf("\n\t1.��ʾ�����Ϣ\t\t2.�����¼������\n\n");
	printf("\t3.ɾ�����м�¼\t\t4.���Ҽ�¼\n\n");
	printf("\t5.��ѯ����ͳ����Ϣ\t6.�������Ϣ���浽�ļ���\n\n");
	printf("\t7.�ָ��ļ������\t8.�޸ļ�¼\n\n");
	printf("\t9.���沢�˳�\n\n");
	i = getsInt("��ѡ��ָ�");
	if(i == 1)
	{
		print();
		start();
	}
	else if(i == 2)
	{
		while(j == -1)
		{
			insert();
			c = getsChar("�Ƿ������ӣ�������y,������n\n:");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("������[y/n]:") == 'y')
					j = -1;
				else
					j = 1;
			}
		}
		start();
	}
	else if(i == 3)
	{
		search("ɾ��");
		start();
	}
	else if(i == 4)
	{
		search("��ѯ");
		start();
	}
	else if(i == 5)
	{
		search("ͳ��");
		start();
	}
	else if(i == 6)
	{
		save();
		start();
	}
	else if(i == 7)
	{
		printf("\n\t��������Ԥ���ļ�  D:\\equip_sys\\equipment_info.txt......\n");
		load_file("D:\\equip_sys\\equipment_info.txt");
		start();
	}
	else if(i == 8)
	{
		search("�޸�");
		start();
	}
	else if(i == 9)
	{
		save();
	}
	else if(i == 10)
	{
		printf("\t->�����ߣ�franceyang.jlu.edu.cn\n");
		start();
	}
	else 
	{
		printf("ָ������޴�ָ��\n");
		start();
	}

}

void load_file(char *s)			//�����ļ������
{
	int i = 0,j = 2;
	char tmp[16] = {'\0'};
	FILE *fp;
	if((fp = fopen(s,"r")) == NULL){
		printf("�����ļ�ʧ��\n");
		return;
	}
	while(1)
	{
		if(fgotoline(fp,j) == -1) break;
		strcpy(tmp,fgetstr(fp).c);
		if(tmp[0] == '\n') break;
		strcpy(equipment[i].ID_Number,tmp);
		equipment[i].equip_Type = fgetnum(fp);
		strcpy(equipment[i].equip_Version,fgetstr(fp).c);
		equipment[i].purchase_Date.year = fgetnum(fp);
		equipment[i].purchase_Date.month = fgetnum(fp);
		equipment[i].purchase_Date.day = fgetnum(fp);
		equipment[i].price = fgetfloat(fp);
		strcpy(equipment[i].manager,fgetstr(fp).c);
		equipment[i].status = fgetnum(fp);
		i++;
		j++;
	}
	printf("\n\t->�����ļ���ɣ��������¼ %d ��\n",i);
	sn = i;
	fclose(fp);
}
/*��int ������ת��Ϊ char[] (string)�� С��10 ��ǰ����� �������Զ����ɱ�ź�������*/
struct str1 intTostr(int a)
{
	struct str1 st;
	if(a < 10)
		sprintf(st.c,"0%d",a);
	else
		sprintf(st.c,"%d",a);
	return st;
}
void load_manual(){				//�ֶ�¼����Ϣ����ʼʱ��
	int j = -1;
	char c;
	void insert();
	while(j == -1)
		{
			insert();
			c = getsChar("�Ƿ������ӣ�������y,������n\n");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("������[y/n]:") == 'y')
					j = -1;
				else
					j = 1;
			}
		}
	
}
/*�޸ĵ� k �������ֵ*/
void change(int k)
{

			int i,j,is_ok = 0,input = 0;
			struct   tm* ptm;
			long     ts;
			int      y,m,d,h,n,s;
			int num;
			char tempStr[64];
			void show(int i);
			printf("����Ҫ�޸ĵ��豸��¼���£�\n\n");
			show(k);
			printf("\n\n1-���\t2-�豸����\t3-�ͺ�\t4-��������\t5-����۸�\t6-����Ա\t7-�豸״̬\n\n");
			printf("������Ҫ�޸ĵ�����:");
			scanf("%d",&num);
			clear();
			ts  =   time(NULL); 
			ptm =   localtime(&ts); 
			y   =   ptm-> tm_year+1900;     //�� 
			m   =   ptm-> tm_mon+1;         //��
			d   =   ptm-> tm_mday;          //��
			h   =   ptm-> tm_hour;          //ʱ
			n   =   ptm-> tm_min;           //��
			s   =   ptm-> tm_sec;           //��
			i = k;
		
			
	if(num >= 1 && num <=7)
	{
		if(num == 1)
		{
			while(input == 0)
			{
				printf("�������豸���:");
				scanf("%s",tempStr);
				for(j = 0;j < sn;j++)
				{
					if(j != k && strcmp(tempStr,equipment[j].ID_Number) == 0)
					{
						printf("����ѱ�ʹ�ã�����\n");
						input = 1;
						break;
					}
				}
				if(input == 1) input = 0;
				else		   input = 2;
			}
		}
		else if(num == 2)
		{
			printf("�豸���ͣ�1-�ʼǱ���2-̨ʽ����3-ƽ����ԣ�4-ͶӰ��, 5-ɨ���ǣ�6-��ӡ����7-�������  8-��Ӱ��\n");
			printf("�������豸����:");
			scanf("%d",&equipment[i].equip_Type);
			while(equipment[i].equip_Type > 8 || equipment[i].equip_Type < 1)
			{
				printf("���ʹ��������������豸����:");
				scanf("%d",&equipment[i].equip_Type);
			}
		}
		else if(num == 3)
		{
			printf("�������豸�ͺ�(�绪ΪG610):");
			scanf("%s",equipment[i].equip_Version);	
		}
		else if(num == 4)
		{
			while(is_ok != 1)
			{
				if(is_ok == 0)
					printf("�����빺�����ڣ��ꡢ�¡����ÿո������<10 ����ǰ����0,��2018 1 3��:");
				
				else
					printf("������Ĺ������������ꡢ�¡����ÿո������<10 ����ǰ����0,��2018 1 3�������������룺");
				scanf("%d %d %d",&equipment[i].purchase_Date.year,&equipment[i].purchase_Date.month,&equipment[i].purchase_Date.day);
				if(equipment[i].purchase_Date.month < 1 || equipment[i].purchase_Date.month >12)
				{
					printf("��������·ݲ������·�ֻ�ܽ��� 1 - 12 ֮�䡣\n");
					is_ok = -1;
				}
				else
				{
					if(equipment[i].purchase_Date.day < 1 || equipment[i].purchase_Date.day >31)
					{
						printf("����������ڲ���������ֻ�ܽ��� 1 - 31 ֮�䡣\n");
						is_ok = -1;
					}
					else
					{

						if((equipment[i].purchase_Date.year - y) <0)
						{
							is_ok = 1;
						}
						else if((equipment[i].purchase_Date.year - y) == 0)
						{
							if((equipment[i].purchase_Date.month - m) < 0)
							{
								is_ok = 1;
							}
							else if((equipment[i].purchase_Date.month - m) == 0)
							{
								if((equipment[i].purchase_Date.day - d) <= 0)
								{
									is_ok = 1;
								}
								else
								{
									is_ok = -1;
								}
							}
							else
							{
								is_ok = -1;
							}
						}
						else
						{
							is_ok = -1;
						}
					}
				}
			}

		}
		else if(num == 5)
		{
			printf("�������豸�۸�(����ΪԪ):");
			scanf("%f",&equipment[i].price);
			clear();
			while(equipment[i].price < 0 )
			{
				printf("������ļ۸񲻺����۸�ֻ��������� 0 �����֣����������룺");
				scanf("%d",&equipment[i].price);
				clear();
			}

		}
		else if(num == 6)
		{
			printf("�������豸����Ա:");
			scanf("%s",equipment[i].manager);
		}
		else if(num == 7)
		{
			printf("�������豸״̬�� 1-���ã�2-��ά�ޣ�3-�����ϣ�:");
			scanf("%d",&equipment[i].status);
			clear();
			while(equipment[i].status > 3 || equipment[i].status < 1)
			{
				printf("״̬���������������豸״̬:");
				scanf("%d",&equipment[i].status);
				clear();
			}
		}

	}
	else
	{
		printf("ָ�����\n");
	}

}
/*ɾ���� K �������ֵ*/
void del(int k)			//	ɾ������е���Ϣ
{
	int j;
	for(j = k;j<sn;j++)
	{
		strcpy(equipment[j].ID_Number,equipment[j+1].ID_Number);
		equipment[j].equip_Type = equipment[j+1].equip_Type;
		strcpy(equipment[j].equip_Version,equipment[j+1].equip_Version);
		equipment[j].purchase_Date.year = equipment[j+1].purchase_Date.year;
		equipment[j].purchase_Date.month = equipment[j+1].purchase_Date.month;
		equipment[j].purchase_Date.day = equipment[j+1].purchase_Date.day;
		strcpy(equipment[j].manager,equipment[j+1].manager);
		equipment[j].price = equipment[j+1].price;
		equipment[j].status = equipment[j+1].status;
	}
	sn -= 1;
	printf("\nɾ����¼�ɹ�.\n");
}
/*��ʽ��չʾ�� K �������ֵ*/
void show(int i)
{
		printf("%-8s\t",equipment[i].ID_Number);
		//printf("%s%s\t",equipment[i].familyname,equipment[i].givenname);
		switch(equipment[i].equip_Type)
		{
			case 1: printf("%-16s","�ʼǱ�");break;
			case 2: printf("%-16s","̨ʽ��");break;
			case 3: printf("%-16s","ƽ�����");break;
			case 4: printf("%-16s","ɨ����");break;
			case 5: printf("%-16s","ͶӰ��");break;
			case 6: printf("%-16s","��ӡ��");break;
			case 7: printf("%-16s","�����");break;
			case 8: printf("%-16s","�����");break;		
		}
		printf("%-8s",equipment[i].equip_Version);
		printf("\t%d-%d-%d\t",equipment[i].purchase_Date.year,equipment[i].purchase_Date.month,equipment[i].purchase_Date.day); 
        printf("\t%8.2f",equipment[i].price);
        printf("\t%-8s",equipment[i].manager);
        switch(equipment[i].status)
		{
			case 1:printf("����\t");break;
			case 2:printf("��ά��\t");break;
			case 3:printf("������\t");break;
		}
		printf("\n");

}
/*��ӡ���������ֵ*/
void print()				//��ӡ�����Ϣ
{
	int i;
	printf("\n\t\t\t\t\t�����豸����%d���������:\t\t\t\n\n",sn);
	printf("�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
	for(i=0;i<sn;i++)
	{
		show(i);
	}
}
/*���ĺ�������ѯ��ɾ�����޸ģ�ͳ�ƾ�������*/
void search(char way[16])		//���ұ���¼
{	
	char a[16];
	int b;
	int y,mon,d;
	char c[16];
	float money;
	char compare;
	int numArr[99];
	int type;
	int i,j,k = -1,m;
	float all_money = 0;
	int count_way;
	void show(int i);
	for(i = 0;i < 99;i++)
		numArr[i] = -1;
	if(strcmp(way,"ͳ��") == 0)
	{
		printf("\t\t1-ȫ��ͳ��...2-�ؼ���ͳ��\n\n");
		printf("������ͳ�Ʒ�ʽ��");
		scanf("%d",&count_way);
		clear();
		if(count_way == 1)
		{
			for(i = 0;i < sn;i++)
			{
				all_money += equipment[i].price;
			}
			printf("ʵ���ҹ����� �豸̨��Ϊ�� %d ����ֵ %10.2f Ԫ��\n",sn,all_money); 
		}
	}
	if(strcmp(way,"ͳ��") != 0 || count_way == 2)
	{
		printf("%s���ݣ�\n\t\t1.���\n\t\t2.�豸����\n\t\t3.�ͺ�\n\t\t4.��������\n\t\t5.����۸�\n\t\t6.����Ա\n\t\t7.�豸״̬\n",way);
		b = getsInt("�����뷽ʽ��");

		if(b == 1)
		{
			printf("�������豸�ı��:");
			scanf("%s",a);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(strstr(equipment[i].ID_Number,a) != NULL)
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
					
				}
			}
			if(k == -1)
				printf("\n������ı�ţ�%s �����ڡ�\n",a);
			else 
				printf("\n��Ѱ����� %d ����\n",m);
		}
		else if(b == 2)
		{
			printf("�豸���ͣ�1-�ʼǱ���2-̨ʽ����3-ƽ����ԣ�4-ͶӰ��, 5-ɨ���ǣ�6-��ӡ����7-�������  8-��Ӱ��\n");
			printf("�������豸����:");
			scanf("%d",&type);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(equipment[i].equip_Type == type)
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
				}
			}
			if(k == -1)
				printf("\n����������ͣ�%d �����ڡ�\n",type);
			else 
				printf("\n��Ѱ����� %d ����\n",m);
		}
		else if(b == 3)
		{
			printf("�������豸���ͺ�:");
			scanf("%s",a);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(strstr(equipment[i].equip_Version,a) != NULL)
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
				}
			}
			if(k == -1)
				printf("\n��������ͺţ�%s �����ڡ�\n",a);
			else 
				printf("\n��Ѱ����� %d ����\n",m);
		}
		else if(b == 4)
		{
			printf("�������ꡢ�¡��գ��������ڶ�Ӧλ������0,��2012 0 0Ϊ����2012�깺��Ļ������·ݡ����ں��ԣ�:");
			scanf("%d %d %d",&y,&mon,&d);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(((y == 0) || (equipment[i].purchase_Date.year == y)) && ((mon == 0) || (equipment[i].purchase_Date.month == mon)) && ((d == 0) || (equipment[i].purchase_Date.day == d)))
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
				}
			}
			if(k == -1)
				printf("\n�������ʱ�ڣ�%d-%d-%d �����ڡ�\n",y,mon,d);
			else 
				printf("\n��Ѱ����� %d ����\n",m);
		}
		else if(b == 5)
		{
			printf("������(�����[ֻ��<,=,>]+�ո�+��ֵ����ʽ���磬 < 1000 ��ʾС��1000Ԫ���豸):");
			getchar();
			compare = getchar();
			scanf("%f",&money);
			getchar();
			printf("compare = %c,money = %f\n",compare,money);
			if(compare == '>')
			{	
				for(i = 0,m = 0;i < sn;i++)
				{
					if(equipment[i].price > money)
					{
						m++;
						numArr[m] = i;
					}
				}
			}
			else if(compare == '=' )
			{
				for(i = 0,m = 0;i < sn;i++)
				{
					if(equipment[i].price == money)
					{
						m++;
						numArr[m] = i;
					}
				}
			}
			else if(compare == '<')
			{
				for(i = 0,m = 0;i < sn;i++)
				{
					if(equipment[i].price < money)
					{
						m++;
						numArr[m] = i;
					}
				}
			}
			else
			{

			}
			if(m == 0) printf("�޷���Ҫ��ļ�¼.\n");
			else
			{
				printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
				for(i = 1;i <= m;i++)
				{
					printf(" %-4d\t",i);
					show(numArr[i]);
				}
				printf("\n���м�¼ %d ����\n",m);
			}
			
		}
		else if(b == 6)
		{
			printf("���������Ա:");
			scanf("%s",a);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(strcmp(equipment[i].manager,a) == 0)
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
				}
			}
			if(k == -1)
				printf("\n������İ�������Ա��%s �ļ�¼�����ڡ�\n",a);
			else 
				printf("\n��Ѱ����� %d ����\n",m);	

		}
		else if(b == 7)
		{
			printf("�豸״̬�� 1-���ã�2-��ά�ޣ�3-������ \n");
			printf("�������豸״̬:");
			scanf("%d",&type);
			printf("���\t�豸���  \t�豸����\t�豸�ͺ�\t�������ڣ��� �� �գ�\t����۸� \t����Ա \t�豸״̬\n");
			for(i = 0,m = 0;i < sn;i++)
			{
				if(equipment[i].status == type)
				{
					k = i;
					printf(" %-4d\t",m+1);
					show(i);
					m++;
					numArr[m] = i;
				}
			}
			if(k == -1)
				printf("\n�����豸״̬��%d ���豸�����ڡ�\n",type);
			else 
				printf("\n��Ѱ����� %d ����\n",m);

		}
		else printf("\n�޴�����\n");
	}
	if(strcmp(way,"ɾ��") == 0 && numArr[1] != -1)
	{
		if(numArr[2] == -1)
		{
			printf("\n\n��ѯ���Ψһ���Ѿ�ɾ��!\n");
			del(numArr[1]);
		}
		else
		{
			printf("\n\n��ѯ�����Ψһ����ѡ���¼ǰ�����Ž���ɾ����");
			scanf("%d",&type);
			if(type >= 1 && type <= m)
			{
				del(numArr[type]);
				printf("\n������ %d ����¼�Ѿ��ɹ�ɾ����\n\n",type);
			}
		}
	}
	if(strcmp(way,"�޸�") == 0 && numArr[1] != -1)
	{
		if(numArr[2] == -1)
		{
			printf("��ѯ���Ψһ��");
			type = 1;
		}
		else
		{
			printf("\n\n��ѯ�����Ψһ����ѡ���¼ǰ�����Ž����޸ģ�");
			scanf("%d",&type);
			while(type < 1 && type > m)
			{
				printf("��Ų��ڷ�Χ�⣬���������룺");
				scanf("%d",&type);
			}
		}
		change(numArr[type]);
		printf("\n������ %d ����¼�Ѿ��ɹ��޸ģ�\n\n",type);
	}
	if(strcmp(way,"ͳ��") == 0 && count_way == 2)
	{
		if(m != 0)
		{
			for(i = 1;i <= m;i++)
			{
				all_money += equipment[numArr[i]].price;
			}
		}
		printf("\n\n�����������豸�� %d ̨������ֵ %10.2f Ԫ��\n",m,all_money);
	}
}

void insert()			// �����в�������
{ 
			int i,j,is_ok = 0,input = 0;
			struct   tm* ptm;
			long     ts;
			int      y,m,d,h,n,s;
			ts  =   time(NULL); 
			ptm =   localtime(&ts); 
			y   =   ptm-> tm_year+1900;     //�� 
			m   =   ptm-> tm_mon+1;         //��
			d   =   ptm-> tm_mday;          //��
			h   =   ptm-> tm_hour;          //ʱ
			n   =   ptm-> tm_min;           //��
			s   =   ptm-> tm_sec;           //��
			i = sn;
			printf("\n��������豸��Ϣ���� %d ���豸����Ϣ��\n\n",(i+1));
			while(input == 0)
			{
				printf("�������豸���:");
				scanf("%s",equipment[sn].ID_Number);
				for(j = 0;j < sn;j++)
				{
					if(strcmp(equipment[sn].ID_Number,equipment[j].ID_Number) == 0)
					{
						printf("����ѱ�ʹ�ã�����");
						input = 1;
						break;
					}
				}
				if(input == 1) input = 0;
				else		   input = 2;
			}
			printf("�豸���ͣ�1-�ʼǱ���2-̨ʽ����3-ƽ����ԣ�4-ͶӰ��, 5-ɨ���ǣ�6-��ӡ����7-�������  8-��Ӱ��\n");
			printf("�������豸����:");
			scanf("%d",&equipment[sn].equip_Type);
			printf("�������豸�ͺ�(�绪ΪG610):");
			scanf("%s",equipment[sn].equip_Version);
			printf("�������豸�۸�(����ΪԪ):");
			scanf("%f",&equipment[i].price);
			while(equipment[i].price < 0 )
			{
				printf("������ļ۸񲻺����۸�ֻ��������� 0 �����֣����������룺");
				scanf("%d",&equipment[i].price);
				printf("\n");
			}
			printf("�������豸����Ա:");
			scanf("%s",equipment[i].manager);
			printf("�������豸״̬�� 1-���ã�2-��ά�ޣ�3-�����ϣ�:");
			scanf("%d",&equipment[i].status);
			while(is_ok != 1)
			{
				if(is_ok == 0)
					printf("�����빺�����ڣ��ꡢ�¡����ÿո������<10 ����ǰ����0,��2018 1 3��:");
				
				else
					printf("������Ĺ������������ꡢ�¡����ÿո������<10 ����ǰ����0,��2018 1 3�������������룺");
				scanf("%d %d %d",&equipment[sn].purchase_Date.year,&equipment[sn].purchase_Date.month,&equipment[sn].purchase_Date.day);
				if(equipment[i].purchase_Date.month < 1 || equipment[i].purchase_Date.month >12)
				{
					printf("��������·ݲ������·�ֻ�ܽ��� 1 - 12 ֮�䡣\n");
					is_ok = -1;
				}
				else
				{
					if(equipment[i].purchase_Date.day < 1 || equipment[i].purchase_Date.day >31)
					{
						printf("����������ڲ���������ֻ�ܽ��� 1 - 31 ֮�䡣\n");
						is_ok = -1;
					}
					else
					{

						if((equipment[i].purchase_Date.year - y) <0)
						{
							is_ok = 1;
						}
						else if((equipment[i].purchase_Date.year - y) == 0)
						{
							if((equipment[i].purchase_Date.month - m) < 0)
							{
								is_ok = 1;
							}
							else if((equipment[i].purchase_Date.month - m) == 0)
							{
								if((equipment[i].purchase_Date.day - d) <= 0)
								{
									is_ok = 1;
								}
								else
								{
									is_ok = -1;
								}
							}
							else
							{
								is_ok = -1;
							}
						}
						else
						{
							is_ok = -1;
						}
					}
				}
			}
			is_ok = 0;
			input = 0;
			sn++;
			printf("\n\n����豸�ɹ�......\n\n");
}
void save()				//�������Ϣ�����ĵ���D:\\equip_sys\\equipment_info.txt
{
	int i,j;
	FILE *fp;
	if((fp = fopen("D:\\equip_sys\\equipment_info.txt","w")) == NULL)
	{
		printf("���ļ� D:\\equip_sys\\equipment_info.txt ʧ��\n");
	}
	fprintf(fp,"�豸���  �豸���� �豸�ͺ� �������ڣ��� �� �գ� ����۸� ����Ա �豸״̬\n");
	for(i = 0;i < sn;i++)
	{
		fprintf(fp,"%s %d %s %d %d %d %5.2f %s %d\n",equipment[i].ID_Number,equipment[i].equip_Type,equipment[i].equip_Version,
			equipment[i].purchase_Date.year,equipment[i].purchase_Date.month,equipment[i].purchase_Date.day,equipment[i].price,
			equipment[i].manager,equipment[i].status);
	}
	fprintf(fp,"\n\n");
	fclose(fp);
	printf("\n\t->��������Ϣ�ɹ���\n");
}


