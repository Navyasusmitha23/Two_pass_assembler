#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>

using namespace std;

int main()
{
	char ch[2],opcode[10],label[10],operand[10],objcode[10],mne[2],mne1[2],code[10],name[10],loc[10],sym[10],loc1[10],BUF[70]={'\0'},lo[10];	//loc is string 
	char preloc[10],si[2],opcode1[10],stloc[10];
	int locctr,start,length,size=0,a,m=1,k=0,n=0;
	
	ofstream fout4;
	ifstream fin1,fin2,fin3,fin4;		
	
	fin1.open("output.txt");
	fout4.open("objectcode.txt");
	
	fin1>>label>>opcode>>operand;
	
	
	strcpy(stloc,"00");
	strcat(stloc,operand);
	
	fin3.open("symtab.txt");
	fin3>>lo>>loc1;
	
	while(strcmp(lo,"length")!=0)
	{
		fin3>>lo>>loc1;
	}
	
	fout4<<'H'<<'^'<<label<<'^'<<operand<<'^'<<loc1<<endl;
	strcpy(preloc,"00");
	strcat(preloc,operand);											
	
	while(strcmp(opcode,"END")!=0)
	{

		for(int i=0;i<10;i++)
		{
			objcode[i]={'\0'};
		}
		
		if(strcmp(opcode,"BYTE")!=0 && strcmp(opcode,"WORD")!=0 && strcmp(opcode,"RESB")!=0 && strcmp(opcode,"RESW")!=0)
		{
			fin2.open("optab.txt");
			fin2>>code>>mne;
			
			while(strcmp(code,"END")!=0)
			{
				if(strcmp(code,opcode)==0)
				{
					strcpy(mne1,mne);
					break;
				}
				else
				fin2>>code>>mne;
			}
			fin2.close();
			
			fin3.open("symtab.txt");
			fin3>>sym>>loc1;
			
			char check[10];
			int r=0;
			
			for(int i=0;i<10;i++)
			{
				check[i]='\0';
			}
			for(int i=0;i<strlen(operand);i++)
			{
				
				if(operand[i]==',')
				{
					r=1;
					break;	
				}	
				check[i]=operand[i];
			}
			
			if(r==0)
			strcpy(check,operand);
			cout<<"check	"<<check<<"\t"<<operand<<endl;
			
			while(fin3)										
			{
				if(strcmp(check,sym)==0)
				break;
				
				else
				fin3>>sym>>loc1;
			}
			
			strcpy(objcode,mne);
			strcat(objcode,loc1);
			
			for(int i=0;i<10;i++)
			{
				if(operand[i]==',')
				{
					if(objcode[2]==char('0'))
					{
						
						objcode[2]=char('8');
					}
				
					else if(objcode[2]==char('1'))
					{
						objcode[2]=char('9');
					}
				
					else if(objcode[2]==char('2'))
					{
						objcode[2]=char('A');
					}
				
					else if(objcode[2]==char('3'))
					{
						objcode[2]=char('B');
					}
				}
			}
			
			
			fin3.close();
			
		}
		
		else if(strcmp(opcode,"BYTE")==0 || strcmp(opcode,"WORD")==0 || strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0)
		{
			k++;
			
			if(strcmp(opcode,"WORD")==0)
			{
				strcpy(objcode,"00000");
				a=atoi(operand);
				sprintf(lo,"%X",a);
				strcat(objcode,lo);
			}
			
			else if(strcmp(opcode,"BYTE")==0)
			{
				if(operand[0]=='C')
				{
					
					for(int i=2;i<strlen(operand)-1;i++)
					{
						a=int(operand[i]);
						sprintf(lo,"%X",a);
						strcpy(ch,lo);
						strcat(objcode,ch);
					
					}
				
				}
				
				else if(operand[0]=='X')
				{
					for(int i=2;i<strlen(operand)-1;i++)
					{
						objcode[i-2]=operand[i];
					}
				}
			}
			
		}
		strcpy(opcode1,opcode);
		
		strcpy(loc1,loc);
		fin1>>loc>>label>>opcode>>operand;
	
	
		
		if(k==1)
		{
			size=size/2;	
			sprintf(si,"%X",size);
			fout4<<'T'<<'^'<<preloc<<'^'<<si<<BUF<<endl;
			strcpy(BUF,"\0");
			size=0;
		}
		
		
		
		if((strcmp(opcode1,"RESW")==0) || (strcmp(opcode1,"RESB")==0))
		{
			if(n==0)
			{
				size=size/2;	
				sprintf(si,"%X",size);
				fout4<<'T'<<'^'<<preloc<<'^'<<si<<BUF<<endl;
				strcpy(BUF,"\0");
				size=0;
				
			}
			n++;	
		}
		
		else if(strcmp(opcode1,"START")!=0 )
		{
				
			if(size==0)
			{
				
				if(m!=1)
				{
					strcpy(preloc,"00");
					strcpy(preloc,loc1);
				}
				
				m--;
				
			
			}
		
			if(size<=60)
			{
				size=size+strlen(objcode);
				strcat(BUF,"^");
				strcat(BUF,objcode);
				
			}
			
			
			if(size>60 || strcmp(opcode,"END")==0 )
			{
				size=size/2;
				sprintf(si,"%X",size);
				fout4<<'T'<<'^'<<preloc<<'^'<<si<<BUF<<endl;
				strcpy(BUF,"\0");
				size=0;
			}
			
	
		}
	
	}
	
	cout<<"Source code is successfully converted to objcode!"<<endl;
		fout4<<'E'<<'^'<<stloc<<endl;
		fout4.close();
		fin1.close();
}
