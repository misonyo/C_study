/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <string.h>
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static void file_write(void)
{
	FILE *pf;
	char ch[]={"abcdefghijklmn"};
	pf=fopen("./test.txt","w+");
	if(pf != NULL)
	{
		printf("open file successful!\n");
	}
	else
	{
		printf("open file failed");
	}
	fwrite(ch,1,strlen(ch),pf);	/* 1.是需要向文件中写入的内容在内存中的首地址指针,2.待写入内容的每个元素的字节数,3.要写多少个元素,4.文件指针,5.返回实际写入的数据项个数*/
	fclose(pf);
}
static void file_write2(void)
{
	FILE *pf;
	char ch[]={0,1,2,3,4,5,6,7,8,9};
	pf=fopen("./test.txt","w+");
	if(pf != NULL)
	{
		printf("open file successful!\n");
	}
	else
	{
		printf("open file failed");
	}
	fwrite(ch,1,sizeof(ch),pf);
	fwrite("\n",1,1,pf);
	fwrite(ch,1,sizeof(ch),pf);
	fclose(pf);
}
static void file_read(void)
{
	FILE *pf;
	char buffer[512];
	size_t len;
	pf=fopen("./test.txt","r");
	if(pf != NULL)
	{
		printf("open file successful!\n");
	}
	else
	{
		printf("open file failed");
	}

	len=fread(buffer,1,512,pf);
	if(len > 0)
	{
		buffer[len] = '\0';
	}
	printf("%d,%s",(int)len,buffer);
	fclose(pf);
}
static void file_read2(void)
{
	FILE *pf;
	char buffer[512];
	size_t len,i;
	pf=fopen("./test.txt","r");
	if(pf != NULL)
	{
		printf("open file successful!\n");
	}
	else
	{
		printf("open file failed");
	}

	len=fread(buffer,1,512,pf);
	if(len > 0)
	{
		buffer[len] = '\0';
	}
	for(i=0;i<len;i++)
	{
		printf("%d,",buffer[i]);
	}
	fclose(pf);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void file_main(void)
{
	file_write();
	//file_read();
	//file_write2();
	//file_read2();
}
