
/*********************个人文件操作定义函数***********************/

//具体每个函数写写思路
/*******到m行*****/
int fgotoline(FILE *fp,int m){				//到达并定位到第m行行首，成功则返回 1; 否则 返回 -1，意味着该文件行数不足 m 行;
	int i,j = 1;							//j用来记录返回值
	char c;
	rewind(fp);								//回归文件首行首地址
	for(i = 1; i<m;i++){					//逐行后移
		while((c=fgetc(fp)) != EOF){		
			if(c == '\n') 
				break;
		}
		if(c == EOF) {						//若已经文件结束，则结束循环,并回退到文件首行首地址
			rewind(fp);
			j = -1;
			break;
		}
	}
	return j;								//返回J的值
}
/*********到字符a处*********/
int fgotochar(FILE *fp,char a){				//***从该位置出发直到行尾，直到找到该字符，并定位到该字符处，返回1;
	int k = 1;								//****若行尾仍未找到字符a，则返回 -1，定位到原位置;k记录位置
	char c;
	while((c = fgetc(fp)) != EOF){
		k++;
		if(c == a) return 1;
		if(c == '\n') {
			fseek(fp,-k,1);					//回退k
			return (-1);
		}
	}
	return (-1);
}
/***到字符串处******/
int fgotostr(FILE *fp,char *s){			//***从该位置出发直到行尾，直到找到该字符串，并定位到该字符串处，返回1;
	char c[400];						//****若未找到字符串s，则返回 -1，定位到原位置;m和n记录位置
	char k;
	char *j;
	int m = 1,n;
	n = sizeof(c[0]);
	while((k = fgetc(fp)) != EOF){		//判断从自己位置起该行有多少元素，记为m
		if(k == '\n') break;
		m++;
	}
	fseek(fp,-m*n,1);					//回退到原位置
	fgets(c,(m+1)*n,fp);				//获取从自己位置起该行的所有元素，放到c中
	j = strstr(c,s);					//判断c中是否有s,返回值记到j，
	if(j == NULL){						//c中没有s
		fseek(fp,-m*n,1);				//回退到原位置
		return -1;
	}
	else {								//c中有s
		fseek(fp,(-m+(j-c))*n,1);		//回退到字符串s的位置
		return 1;
	}
}
/**获取数字****/
int fgetnum(FILE *fp){
	char c[8] = {'\0'},m;
	char *s = c;
	int i = 0,num;
	while((m = fgetc(fp)) != EOF)
	{
		if(m != ' ' && m != '\n')
		{
		c[i] = m;
		i++;
		}
		else break;
	}
	num = atoi(s);
	return (num);
}
double fgetfloat(FILE *fp){
	char c[8] = {'\0'},m;
	char *s = c;
	int i = 0;
	double num;
	while((m = fgetc(fp)) != EOF)
	{
		if(m != ' ' && m != '\n')
		{
		c[i] = m;
		i++;
		}
		else break;
	}
	num = atof(s);
	return (num);
}
/**获取字符串**/
struct str1 fgetstr(FILE *fp){
	struct str1 mystr = {'0'};
	char m;
	char *s = mystr.c;
	int i = 0,j;
	while((m = fgetc(fp)) != EOF)
	{
		
		if(m != ' ' && m != '\n')
		{
		mystr.c[i] = m;
		i++;
		}
		else if(m == '\n')
		{
			mystr.c[0] = '\n';
			break;
		}
		else break;
	}
	return (mystr);
}

