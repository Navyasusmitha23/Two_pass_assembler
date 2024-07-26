#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>

using namespace std;

int main()
{
	char opcode[10],label[10],operand[10],mne[10],code[10],name[10],loc[10]; 
	int locctr,start,length;
	
	ofstream fout1,fout2,fout3,fout4;
	ifstream fin1,fin2,fin3,fin4;
	fout3.open("symtab.txt");
	fout4.open("output.txt");
	
	fin1.open("input1.txt");
	fin1>>label>>opcode>>operand;
		
	if(strcmp(opcode,"START")==0)
	{
		start=atoi(operand);
		start=4096;
		strcpy(name,label);
		locctr=start;
		fout4<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
		fin1>>label>>opcode>>operand;
	}
	
	else
		locctr=0;
		
			
		while(strcmp(opcode,"END")!=0)
		{
			sprintf(loc,"%X",locctr);
			fout4<<loc<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
			if(strcmp(label,"**")!=0)
			{
				sprintf(loc,"%X",locctr);
				fout3<<label<<"\t"<<loc<<endl;
			}
				
				
			fin2.open("optab.txt");	
			fin2>>code>>mne;

			while(strcmp(code,"END")!=0)
			{
				if(strcmp(opcode,code)==0)
				{
					locctr=locctr+3;
				}
				fin2>>code>>mne;
			}
			fin2.close();
			
			if(strcmp(opcode,"WORD")==0)
				locctr=locctr+3;
				
			else if(strcmp(opcode,"RESW")==0)
				locctr=locctr+3*atoi(operand);
				
			else if(strcmp(opcode,"RESB")==0)
				locctr=locctr+atoi(operand);
				
			else if(strcmp(opcode,"BYTE")==0)
				locctr=locctr+strlen(operand);
				fin1>>label>>opcode>>operand;
	
		}
			
			sprintf(loc,"%X",locctr);
			fout4<<loc<<"\t"<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
			
			length=locctr-start;			
			sprintf(loc,"%X",length);
			strcpy(label,"length");
			fout3<<label<<"\t"<<loc<<endl;
			fin1.close();
			fout3.close();
			fout4.close();
}
