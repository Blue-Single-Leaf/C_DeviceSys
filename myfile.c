
/*********************�����ļ��������庯��***********************/

//����ÿ������дд˼·
/*******��m��*****/
int fgotoline(FILE *fp,int m){				//���ﲢ��λ����m�����ף��ɹ��򷵻� 1; ���� ���� -1����ζ�Ÿ��ļ��������� m ��;
	int i,j = 1;							//j������¼����ֵ
	char c;
	rewind(fp);								//�ع��ļ������׵�ַ
	for(i = 1; i<m;i++){					//���к���
		while((c=fgetc(fp)) != EOF){		
			if(c == '\n') 
				break;
		}
		if(c == EOF) {						//���Ѿ��ļ������������ѭ��,�����˵��ļ������׵�ַ
			rewind(fp);
			j = -1;
			break;
		}
	}
	return j;								//����J��ֵ
}
/*********���ַ�a��*********/
int fgotochar(FILE *fp,char a){				//***�Ӹ�λ�ó���ֱ����β��ֱ���ҵ����ַ�������λ�����ַ���������1;
	int k = 1;								//****����β��δ�ҵ��ַ�a���򷵻� -1����λ��ԭλ��;k��¼λ��
	char c;
	while((c = fgetc(fp)) != EOF){
		k++;
		if(c == a) return 1;
		if(c == '\n') {
			fseek(fp,-k,1);					//����k
			return (-1);
		}
	}
	return (-1);
}
/***���ַ�����******/
int fgotostr(FILE *fp,char *s){			//***�Ӹ�λ�ó���ֱ����β��ֱ���ҵ����ַ���������λ�����ַ�����������1;
	char c[400];						//****��δ�ҵ��ַ���s���򷵻� -1����λ��ԭλ��;m��n��¼λ��
	char k;
	char *j;
	int m = 1,n;
	n = sizeof(c[0]);
	while((k = fgetc(fp)) != EOF){		//�жϴ��Լ�λ��������ж���Ԫ�أ���Ϊm
		if(k == '\n') break;
		m++;
	}
	fseek(fp,-m*n,1);					//���˵�ԭλ��
	fgets(c,(m+1)*n,fp);				//��ȡ���Լ�λ������е�����Ԫ�أ��ŵ�c��
	j = strstr(c,s);					//�ж�c���Ƿ���s,����ֵ�ǵ�j��
	if(j == NULL){						//c��û��s
		fseek(fp,-m*n,1);				//���˵�ԭλ��
		return -1;
	}
	else {								//c����s
		fseek(fp,(-m+(j-c))*n,1);		//���˵��ַ���s��λ��
		return 1;
	}
}
/**��ȡ����****/
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
/**��ȡ�ַ���**/
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

