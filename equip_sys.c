#include<stdio.h>
#include<string.h>
#include<direct.h>	//计算时间用
#include<stdlib.h>
#include<malloc.h>	//定义动态数组
#include"time.h"	//计算时间有用
#include"myinput.c"	//个人习惯用的输入操作
#include"myfile.c"	//个人习惯用的文件操作
struct date
 { 
	int year;
	int month;
	int day ;
 };
 struct equipment
 {
	 char ID_Number[16];		//设备编号
	 int equip_Type;			//设备类型:1-笔记本，2-台式机，3-平板电脑，4-投影仪
								//		   5-扫描仪，6-打印机，7-照相机，  8-摄影机
	 char equip_Version[16];	//设备型号（版本）
	 struct date purchase_Date;	//购买日期
	 float price;				//购买单价
	 char manager[16];				//管理员
	 int status;				//设备状态 1-良好，2-需维修，3-待报废
}equipment[99];
int sn = 0;				//sn用来记录设备数
/*清除缓冲区内存*/
void clear()
{
	char ch;
	while((ch = getchar()) != EOF && ch != '\n');
}
int main()
{ 
	int i,j,come;
	FILE *myf;
	void load_file(char *s);		//初始化设备信息
	void load_manual();
	
	void print();			//打印设备信息
	void del();			//删除设备信息
	void search(char way[]);		//查询设备信息
	void insert();		//插入记录
	void start();
	printf("\n************************************************设备管理系统**********************************************\n");
	printf("\n说明:\n\t此设备系统作模拟使用，因此设备数设计为少于99人，且此系统尚有诸多不足之处。\n\t此系统运行时在D盘下建立文件夹：equip_sys作为存储位置。\n");
	printf("\n****** D:\\equip_sys\\equipment_info.txt 作为预存文件，用来存放表格信息;\n");
	printf("\n--------------------------------------------------\n\n");
	if((myf = fopen("D:\\equip_sys\\equipment_info.txt","r")) == NULL)
	{
		printf("\t->鉴定您是第一次使用本系统，现指引您进行初始化：\n\n");
		if(_mkdir("D:\\equip_sys") == 0)
		{
			printf("\t->文件夹：D:\\equip_sys 已建立\n\n");
		}
		if((myf = fopen("D:\\equip_sys\\equipment_info.txt","w")) != NULL)
		{
			printf("\t->文件 D:\\equip_sys\\equipment_info.txt 已建立\n\n");
		}
		printf("\t->进行数据初始化：\n\n\t\t数据录入方式：1.文件录入\t2.手动录入\t3.暂不录入\n\n");
		come = getsInt("请选择:");
		if(come == 1)
		{
			printf("请将要录入的文件放入 D:\\equip_sys 文件夹下，并命名为load.txt(按任意键继续)");
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
		printf("-----------欢迎再次进入设备系统！----------\n\n\n");
		printf("\t->系统为您进行预加载，载入上次保留的记录.");
		load_file("D:\\equip_sys\\equipment_info.txt");
		if(sn == 0) 
		{
			printf("\n\n设备记录为空。\n\n");
			printf("\t->进行数据初始化：\n\n\t\t数据录入方式：1.文件录入\t2.手动录入\t3.暂不录入\n\n");
			come = getsInt("请选择:");
			if(come == 1)
			{
				printf("请将要录入的文件放入 D:\\equip_sys 文件夹下，并命名为load.txt(按任意键继续)");
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
void start()			//系统入口
{
	int i,j = -1;
	char c;

	void load_file(char *s);		//初始化设备信息
	void load_manual();
	void print();			//打印设备信息	
	void search(char way[16]);		//查询设备信息
	void insert();		//插入记录	
	void save();		//保存表格信息
	printf("\n\n************************菜单栏************************\n\n");
	printf("\n\t1.显示表格信息\t\t2.插入记录到表中\n\n");
	printf("\t3.删除表中记录\t\t4.查找记录\n\n");
	printf("\t5.查询各类统计信息\t6.将表格信息保存到文件中\n\n");
	printf("\t7.恢复文件到表格\t8.修改记录\n\n");
	printf("\t9.保存并退出\n\n");
	i = getsInt("请选择指令：");
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
			c = getsChar("是否继续添加？是输入y,否输入n\n:");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("请输入[y/n]:") == 'y')
					j = -1;
				else
					j = 1;
			}
		}
		start();
	}
	else if(i == 3)
	{
		search("删除");
		start();
	}
	else if(i == 4)
	{
		search("查询");
		start();
	}
	else if(i == 5)
	{
		search("统计");
		start();
	}
	else if(i == 6)
	{
		save();
		start();
	}
	else if(i == 7)
	{
		printf("\n\t正在载入预存文件  D:\\equip_sys\\equipment_info.txt......\n");
		load_file("D:\\equip_sys\\equipment_info.txt");
		start();
	}
	else if(i == 8)
	{
		search("修改");
		start();
	}
	else if(i == 9)
	{
		save();
	}
	else if(i == 10)
	{
		printf("\t->制作者：franceyang.jlu.edu.cn\n");
		start();
	}
	else 
	{
		printf("指令错误，无此指令\n");
		start();
	}

}

void load_file(char *s)			//加载文件到表格
{
	int i = 0,j = 2;
	char tmp[16] = {'\0'};
	FILE *fp;
	if((fp = fopen(s,"r")) == NULL){
		printf("载入文件失败\n");
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
	printf("\n\t->载入文件完成，共载入记录 %d 条\n",i);
	sn = i;
	fclose(fp);
}
/*将int 型数据转化为 char[] (string)型 小于10 的前面加零 本来想自动生成编号后来弃用*/
struct str1 intTostr(int a)
{
	struct str1 st;
	if(a < 10)
		sprintf(st.c,"0%d",a);
	else
		sprintf(st.c,"%d",a);
	return st;
}
void load_manual(){				//手动录入信息，开始时候
	int j = -1;
	char c;
	void insert();
	while(j == -1)
		{
			insert();
			c = getsChar("是否继续添加？是输入y,否输入n\n");
			if(c == 'y')
				j = -1;
			else if(c == 'n')
				j = 1;
			else 
			{
				if(getsChar("请输入[y/n]:") == 'y')
					j = -1;
				else
					j = 1;
			}
		}
	
}
/*修改第 k 个数组的值*/
void change(int k)
{

			int i,j,is_ok = 0,input = 0;
			struct   tm* ptm;
			long     ts;
			int      y,m,d,h,n,s;
			int num;
			char tempStr[64];
			void show(int i);
			printf("您将要修改的设备记录如下：\n\n");
			show(k);
			printf("\n\n1-编号\t2-设备类型\t3-型号\t4-购买日期\t5-购入价格\t6-管理员\t7-设备状态\n\n");
			printf("请输入要修改的属性:");
			scanf("%d",&num);
			clear();
			ts  =   time(NULL); 
			ptm =   localtime(&ts); 
			y   =   ptm-> tm_year+1900;     //年 
			m   =   ptm-> tm_mon+1;         //月
			d   =   ptm-> tm_mday;          //日
			h   =   ptm-> tm_hour;          //时
			n   =   ptm-> tm_min;           //分
			s   =   ptm-> tm_sec;           //秒
			i = k;
		
			
	if(num >= 1 && num <=7)
	{
		if(num == 1)
		{
			while(input == 0)
			{
				printf("请输入设备编号:");
				scanf("%s",tempStr);
				for(j = 0;j < sn;j++)
				{
					if(j != k && strcmp(tempStr,equipment[j].ID_Number) == 0)
					{
						printf("编号已被使用！！！\n");
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
			printf("设备类型：1-笔记本，2-台式机，3-平板电脑，4-投影仪, 5-扫描仪，6-打印机，7-照相机，  8-摄影机\n");
			printf("请输入设备类型:");
			scanf("%d",&equipment[i].equip_Type);
			while(equipment[i].equip_Type > 8 || equipment[i].equip_Type < 1)
			{
				printf("类型错误，请重新输入设备类型:");
				scanf("%d",&equipment[i].equip_Type);
			}
		}
		else if(num == 3)
		{
			printf("请输入设备型号(如华为G610):");
			scanf("%s",equipment[i].equip_Version);	
		}
		else if(num == 4)
		{
			while(is_ok != 1)
			{
				if(is_ok == 0)
					printf("请输入购买日期（年、月、日用空格隔开，<10 数字前不加0,如2018 1 3）:");
				
				else
					printf("您输入的购买日期有误（年、月、日用空格隔开，<10 数字前不加0,如2018 1 3），请重新输入：");
				scanf("%d %d %d",&equipment[i].purchase_Date.year,&equipment[i].purchase_Date.month,&equipment[i].purchase_Date.day);
				if(equipment[i].purchase_Date.month < 1 || equipment[i].purchase_Date.month >12)
				{
					printf("您输入的月份不合理，月份只能介于 1 - 12 之间。\n");
					is_ok = -1;
				}
				else
				{
					if(equipment[i].purchase_Date.day < 1 || equipment[i].purchase_Date.day >31)
					{
						printf("您输入的日期不合理，日期只能介于 1 - 31 之间。\n");
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
			printf("请输入设备价格(单价为元):");
			scanf("%f",&equipment[i].price);
			clear();
			while(equipment[i].price < 0 )
			{
				printf("您输入的价格不合理，价格只能输入大于 0 的数字，请重新输入：");
				scanf("%d",&equipment[i].price);
				clear();
			}

		}
		else if(num == 6)
		{
			printf("请输入设备管理员:");
			scanf("%s",equipment[i].manager);
		}
		else if(num == 7)
		{
			printf("请输入设备状态（ 1-良好，2-需维修，3-待报废）:");
			scanf("%d",&equipment[i].status);
			clear();
			while(equipment[i].status > 3 || equipment[i].status < 1)
			{
				printf("状态错误，请重新输入设备状态:");
				scanf("%d",&equipment[i].status);
				clear();
			}
		}

	}
	else
	{
		printf("指令错误\n");
	}

}
/*删除第 K 个数组的值*/
void del(int k)			//	删除表格中的信息
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
	printf("\n删除记录成功.\n");
}
/*格式化展示第 K 个数组的值*/
void show(int i)
{
		printf("%-8s\t",equipment[i].ID_Number);
		//printf("%s%s\t",equipment[i].familyname,equipment[i].givenname);
		switch(equipment[i].equip_Type)
		{
			case 1: printf("%-16s","笔记本");break;
			case 2: printf("%-16s","台式机");break;
			case 3: printf("%-16s","平板电脑");break;
			case 4: printf("%-16s","扫描仪");break;
			case 5: printf("%-16s","投影仪");break;
			case 6: printf("%-16s","打印机");break;
			case 7: printf("%-16s","照相机");break;
			case 8: printf("%-16s","摄相机");break;		
		}
		printf("%-8s",equipment[i].equip_Version);
		printf("\t%d-%d-%d\t",equipment[i].purchase_Date.year,equipment[i].purchase_Date.month,equipment[i].purchase_Date.day); 
        printf("\t%8.2f",equipment[i].price);
        printf("\t%-8s",equipment[i].manager);
        switch(equipment[i].status)
		{
			case 1:printf("良好\t");break;
			case 2:printf("需维修\t");break;
			case 3:printf("待报废\t");break;
		}
		printf("\n");

}
/*打印所有数组的值*/
void print()				//打印表格信息
{
	int i;
	printf("\n\t\t\t\t\t共有设备数：%d，情况如下:\t\t\t\n\n",sn);
	printf("设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
	for(i=0;i<sn;i++)
	{
		show(i);
	}
}
/*核心函数，查询，删除，修改，统计均依靠它*/
void search(char way[16])		//查找表格记录
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
	if(strcmp(way,"统计") == 0)
	{
		printf("\t\t1-全表统计...2-关键字统计\n\n");
		printf("请输入统计方式：");
		scanf("%d",&count_way);
		clear();
		if(count_way == 1)
		{
			for(i = 0;i < sn;i++)
			{
				all_money += equipment[i].price;
			}
			printf("实验室共含有 设备台数为： %d 。价值 %10.2f 元。\n",sn,all_money); 
		}
	}
	if(strcmp(way,"统计") != 0 || count_way == 2)
	{
		printf("%s依据：\n\t\t1.编号\n\t\t2.设备类型\n\t\t3.型号\n\t\t4.购买日期\n\t\t5.购入价格\n\t\t6.管理员\n\t\t7.设备状态\n",way);
		b = getsInt("请输入方式：");

		if(b == 1)
		{
			printf("请输入设备的编号:");
			scanf("%s",a);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n您输入的编号：%s 不存在。\n",a);
			else 
				printf("\n查寻结果： %d 条。\n",m);
		}
		else if(b == 2)
		{
			printf("设备类型：1-笔记本，2-台式机，3-平板电脑，4-投影仪, 5-扫描仪，6-打印机，7-照相机，  8-摄影机\n");
			printf("请输入设备类型:");
			scanf("%d",&type);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n您输入的类型：%d 不存在。\n",type);
			else 
				printf("\n查寻结果： %d 条。\n",m);
		}
		else if(b == 3)
		{
			printf("请输入设备的型号:");
			scanf("%s",a);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n您输入的型号：%s 不存在。\n",a);
			else 
				printf("\n查寻结果： %d 条。\n",m);
		}
		else if(b == 4)
		{
			printf("请输入年、月、日（忽略请在对应位置输入0,如2012 0 0为查找2012年购入的机器，月份、日期忽略）:");
			scanf("%d %d %d",&y,&mon,&d);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n您输入的时期：%d-%d-%d 不存在。\n",y,mon,d);
			else 
				printf("\n查寻结果： %d 条。\n",m);
		}
		else if(b == 5)
		{
			printf("输入金额(运算符[只有<,=,>]+空格+数值的形式，如， < 1000 表示小于1000元的设备):");
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
			if(m == 0) printf("无符合要求的记录.\n");
			else
			{
				printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
				for(i = 1;i <= m;i++)
				{
					printf(" %-4d\t",i);
					show(numArr[i]);
				}
				printf("\n共有记录 %d 条。\n",m);
			}
			
		}
		else if(b == 6)
		{
			printf("请输入管理员:");
			scanf("%s",a);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n您输入的包含管理员：%s 的记录不存在。\n",a);
			else 
				printf("\n查寻结果： %d 条。\n",m);	

		}
		else if(b == 7)
		{
			printf("设备状态： 1-良好，2-需维修，3-待报废 \n");
			printf("请输入设备状态:");
			scanf("%d",&type);
			printf("序号\t设备编号  \t设备类型\t设备型号\t购买日期（年 月 日）\t购入价格 \t管理员 \t设备状态\n");
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
				printf("\n处于设备状态：%d 的设备不存在。\n",type);
			else 
				printf("\n查寻结果： %d 条。\n",m);

		}
		else printf("\n无此命令\n");
	}
	if(strcmp(way,"删除") == 0 && numArr[1] != -1)
	{
		if(numArr[2] == -1)
		{
			printf("\n\n查询结果唯一，已经删除!\n");
			del(numArr[1]);
		}
		else
		{
			printf("\n\n查询结果不唯一，请选择记录前面的序号进行删除：");
			scanf("%d",&type);
			if(type >= 1 && type <= m)
			{
				del(numArr[type]);
				printf("\n上述第 %d 条记录已经成功删除！\n\n",type);
			}
		}
	}
	if(strcmp(way,"修改") == 0 && numArr[1] != -1)
	{
		if(numArr[2] == -1)
		{
			printf("查询结果唯一。");
			type = 1;
		}
		else
		{
			printf("\n\n查询结果不唯一，请选择记录前面的序号进行修改：");
			scanf("%d",&type);
			while(type < 1 && type > m)
			{
				printf("序号不在范围肉，请重新输入：");
				scanf("%d",&type);
			}
		}
		change(numArr[type]);
		printf("\n上述第 %d 条记录已经成功修改！\n\n",type);
	}
	if(strcmp(way,"统计") == 0 && count_way == 2)
	{
		if(m != 0)
		{
			for(i = 1;i <= m;i++)
			{
				all_money += equipment[numArr[i]].price;
			}
		}
		printf("\n\n符合条件的设备有 %d 台，共价值 %10.2f 元。\n",m,all_money);
	}
}

void insert()			// 向表格中插入数据
{ 
			int i,j,is_ok = 0,input = 0;
			struct   tm* ptm;
			long     ts;
			int      y,m,d,h,n,s;
			ts  =   time(NULL); 
			ptm =   localtime(&ts); 
			y   =   ptm-> tm_year+1900;     //年 
			m   =   ptm-> tm_mon+1;         //月
			d   =   ptm-> tm_mday;          //日
			h   =   ptm-> tm_hour;          //时
			n   =   ptm-> tm_min;           //分
			s   =   ptm-> tm_sec;           //秒
			i = sn;
			printf("\n正在添加设备信息，第 %d 个设备的信息：\n\n",(i+1));
			while(input == 0)
			{
				printf("请输入设备编号:");
				scanf("%s",equipment[sn].ID_Number);
				for(j = 0;j < sn;j++)
				{
					if(strcmp(equipment[sn].ID_Number,equipment[j].ID_Number) == 0)
					{
						printf("编号已被使用！！！");
						input = 1;
						break;
					}
				}
				if(input == 1) input = 0;
				else		   input = 2;
			}
			printf("设备类型：1-笔记本，2-台式机，3-平板电脑，4-投影仪, 5-扫描仪，6-打印机，7-照相机，  8-摄影机\n");
			printf("请输入设备类型:");
			scanf("%d",&equipment[sn].equip_Type);
			printf("请输入设备型号(如华为G610):");
			scanf("%s",equipment[sn].equip_Version);
			printf("请输入设备价格(单价为元):");
			scanf("%f",&equipment[i].price);
			while(equipment[i].price < 0 )
			{
				printf("您输入的价格不合理，价格只能输入大于 0 的数字，请重新输入：");
				scanf("%d",&equipment[i].price);
				printf("\n");
			}
			printf("请输入设备管理员:");
			scanf("%s",equipment[i].manager);
			printf("请输入设备状态（ 1-良好，2-需维修，3-待报废）:");
			scanf("%d",&equipment[i].status);
			while(is_ok != 1)
			{
				if(is_ok == 0)
					printf("请输入购买日期（年、月、日用空格隔开，<10 数字前不加0,如2018 1 3）:");
				
				else
					printf("您输入的购买日期有误（年、月、日用空格隔开，<10 数字前不加0,如2018 1 3），请重新输入：");
				scanf("%d %d %d",&equipment[sn].purchase_Date.year,&equipment[sn].purchase_Date.month,&equipment[sn].purchase_Date.day);
				if(equipment[i].purchase_Date.month < 1 || equipment[i].purchase_Date.month >12)
				{
					printf("您输入的月份不合理，月份只能介于 1 - 12 之间。\n");
					is_ok = -1;
				}
				else
				{
					if(equipment[i].purchase_Date.day < 1 || equipment[i].purchase_Date.day >31)
					{
						printf("您输入的日期不合理，日期只能介于 1 - 31 之间。\n");
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
			printf("\n\n添加设备成功......\n\n");
}
void save()				//将表格信息存入文档：D:\\equip_sys\\equipment_info.txt
{
	int i,j;
	FILE *fp;
	if((fp = fopen("D:\\equip_sys\\equipment_info.txt","w")) == NULL)
	{
		printf("打开文件 D:\\equip_sys\\equipment_info.txt 失败\n");
	}
	fprintf(fp,"设备编号  设备类型 设备型号 购买日期（年 月 日） 购入价格 管理员 设备状态\n");
	for(i = 0;i < sn;i++)
	{
		fprintf(fp,"%s %d %s %d %d %d %5.2f %s %d\n",equipment[i].ID_Number,equipment[i].equip_Type,equipment[i].equip_Version,
			equipment[i].purchase_Date.year,equipment[i].purchase_Date.month,equipment[i].purchase_Date.day,equipment[i].price,
			equipment[i].manager,equipment[i].status);
	}
	fprintf(fp,"\n\n");
	fclose(fp);
	printf("\n\t->保存表格信息成功。\n");
}


