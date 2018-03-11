/*************************个人输入函数开发*************************/

/*********

基本函数：get+类型（）               ->后边类型首字母大写，返回设类型值
		  gets+类型(char *s)         ->先输出char *s的内容，再返回类型值
特殊：getStr()与getsStr(char *s)	 ->借用结构体，使用时在后边加上.c	如：char * string1 = getsStr("please Enter a string").c;

*********/
//返回整型值函数
int getInt(){
	int a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
int getsInt(char *c){
	int a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//返回short型值函数
short getShort(){
	short a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
short getsShort(char *c){
	short a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//返回长整型值函数
long getLong(){
	long a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
long getsLong(char *c){
	long a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//返回double型值函数
double getDouble(){
	double a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
double getsDouble(char *c){
	double a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//返回float型值函数
float getFloat(){
	float a;			//the value you should input and then return;
	scanf("%d",&a);
	return (a);
}
float getsFloat(char *c){
	float a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%d",&a);
	return (a);
}
//返回字符型值函数
char getChar(){
	char a;			//the value you should input and then return;
	scanf("%c",&a);
	return (a);
}
char getsChar(char *c){
	char a;			//the value you should input and then return;
	printf("%s",c);
	scanf("%c",&a);
	return (a);
}
//返回字符串型值函数
struct str {
	char c[100];
};
struct str1 {
	char c[16];
};
struct	str getStr(){
	struct str a;
	gets(a.c);			//the value you should input and then return;
	return a;
}
struct	str getsStr(char *c){
	struct str a;
	printf("%s",c);
	gets(a.c);				//the value you should input and then return;
	return a;
}