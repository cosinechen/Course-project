#include<iostream>
#include<string.h>
#include<fstream>  //open file and read file's libary

using namespace std;

		
	char symboltable[10000][200];	

	int StringToHexNumber(string Number)
	{
		int ans=0,i;
		for(i=0;i<Number.length();i++)
			{
			ans=ans*16+(Number[i]-48);
			}
		
				return ans;	
	}

	int StringToNumber(string Number)
	{
		int ans=0,i;
		for(i=0;i<Number.length();i++)
			{
			ans=ans*10+(Number[i]-48);
			}
		
						return ans;	
	}

	
	  
		  
	void PrintObjectCode(string instruction,string operand)
	{
		if(instruction[0]=='J'&&instruction[1]=='S'&&instruction[2]=='U'&&instruction[3]=='B')
			printf("48");
		else if(instruction[0]=='W'&&instruction[1]=='O'&&instruction[2]=='R'&&instruction[3]=='D')
			printf("%06x",StringToNumber(operand));	
		else if(instruction[0]=='C'&&instruction[1]=='O'&&instruction[2]=='M'&&instruction[3]=='P')
			printf("28");
		else if(instruction[0]=='R'&&instruction[1]=='S'&&instruction[2]=='U'&&instruction[3]=='B')
			printf("4C0000");
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='C'&&instruction[3]=='H')
			printf("54");							
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='C'&&instruction[3]=='H')
			printf("50");			
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='L')
			printf("14");
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='X')
			printf("10");
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='A')
			printf("00");
		else if(instruction[0]=='J'&&instruction[1]=='E'&&instruction[2]=='Q')
			printf("30");
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='A'&&instruction[3]!='R')
			printf("0C");
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='L')
			printf("08");
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='X')
			printf("04");
		else if(instruction[0]=='T'&&instruction[1]=='I'&&instruction[2]=='X')
			printf("2C");
		else if(instruction[0]=='J'&&instruction[1]=='L'&&instruction[2]=='T')
			printf("38");
		else if(instruction[0]=='T'&&instruction[1]=='D')
			printf("E0");
		else if(instruction[0]=='R'&&instruction[1]=='D')
			printf("D8");
		else if(instruction[0]=='W'&&instruction[1]=='D')
			printf("DC");
		else if(instruction[0]=='J')
			printf("3C");
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D')
			printf("18");
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D'&&instruction[3]=='F')
			printf("58");
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D'&&instruction[3]=='R')
			printf("90");
		else if(instruction[0]=='B'&&instruction[1]=='Y'&&instruction[2]=='T'&&instruction[3]=='E')
			{
				int word=2;
				while(operand[0]=='X'||operand[0]=='x'&&operand[1]=='\'')
				{	
					if(operand[word]=='\'')
					break;
					printf("%c",operand[word]);
					word++;
				}
				if(operand[2]=='E'&&operand[3]=='O'&&operand[4]=='F')
				{
					printf("454F46");
				}
			}	
				
		for(int i = 0;i<10000;i++)
		{
			if(operand==symboltable[i]&&instruction[0]!='E'&&instruction[1]!='N'&&instruction[2]!='D')
			{
				printf("%x",i);
				break;
			}
			if(operand=="BUFFER,X")
			{
				for(int i = 0;i<10000;i++)
				{
					if(symboltable[i][0]=='B'&&symboltable[i][1]=='U'&&symboltable[i][2]=='F'&&symboltable[i][3]=='F'&&symboltable[i][4]=='E'&&symboltable[i][5]=='R')
					printf("%x",i+8*16*16*16);
				}
				break;
			}			
		}
		printf("\n");
	}	  
		  
		  
	int IfOpcodeIsByte(string symbol)
	{
		int i = 2,length=0;
		while(symbol[0]=='C'||symbol[0]=='c'&&symbol[1]=='\'')
		{
			if(symbol[i]!='\'')
			{length++;i++;}
			else
			break;
		}
		if(symbol[0]=='X'||symbol[0]=='x'&&symbol[1]=='\'')
		{
		length=1;
		}
		return length;
		  }	  
	
	
	bool optablefind(string instruction)	
	{
		if(instruction[0]=='J'&&instruction[1]=='S'&&instruction[2]=='U'&&instruction[3]=='B')
			return true;
		else if(instruction[0]=='C'&&instruction[1]=='O'&&instruction[2]=='M'&&instruction[3]=='P')
			return true;
		else if(instruction[0]=='R'&&instruction[1]=='S'&&instruction[2]=='U'&&instruction[3]=='B')
			return true;
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='C'&&instruction[3]=='H')
			return true;			
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='C'&&instruction[3]=='H')
			return true;			
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='L')
			return true;
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='X')
			return true;
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='A')
			return true;
		else if(instruction[0]=='J'&&instruction[1]=='E'&&instruction[2]=='Q')
			return true;
		else if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='A')
			return true;
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='L')
			return true;
		else if(instruction[0]=='L'&&instruction[1]=='D'&&instruction[2]=='X')
			return true;
		else if(instruction[0]=='T'&&instruction[1]=='I'&&instruction[2]=='X')
			return true;
		else if(instruction[0]=='J'&&instruction[1]=='L'&&instruction[2]=='T')
			return true;
		else if(instruction[0]=='T'&&instruction[1]=='D')
			return true;
		else if(instruction[0]=='R'&&instruction[1]=='D')
			return true;
		else if(instruction[0]=='W'&&instruction[1]=='D')
			return true;
		else if(instruction[0]=='J')
			return true;
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D')
			return true;
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D'&&instruction[3]=='F')
			return true;
		else if(instruction[0]=='A'&&instruction[1]=='D'&&instruction[2]=='D'&&instruction[3]=='R')
			return true;
		else
			return false;		
		}
		  
	int CountLoc(int Loc,string instruction,string operand)
	{
			if(instruction[0]=='S'&&instruction[1]=='T'&&instruction[2]=='A'&&instruction[3]=='R'&&instruction[4]=='T')
				Loc=Loc;	
			else if(optablefind(instruction))
				Loc+=3;
			else if(instruction[0]=='W'&&instruction[1]=='O'&&instruction[2]=='R'&&instruction[3]=='D')
				Loc+=3;	
			else if(instruction[0]=='R'&&instruction[1]=='E'&&instruction[2]=='S'&&instruction[3]=='W')		
				Loc+=3*StringToNumber(operand);
			else if(instruction[0]=='R'&&instruction[1]=='E'&&instruction[2]=='S'&&instruction[3]=='B')		
				Loc+=StringToNumber(operand);
			else if(instruction[0]=='B'&&instruction[1]=='Y'&&instruction[2]=='T'&&instruction[3]=='E')	
				Loc+=IfOpcodeIsByte(operand);
		return Loc;
	}


	
	
	int main(){
	
		char buffer[900];
		char  label[100][300];
		char  opcode[100][300];
		char  symbol[100][300];
		char *delimiter= "\t";
  		char * token;
  		int order,linelength=0;
		
		 
		fstream file;
		file.open("Figure2.1.txt",ios::in); //開啟檔案並讀取 
		if(!file)
			cout<<"the file can't open.\n";
		else
			do{
				file.getline(buffer,sizeof(buffer));//讀入一行 放進buffer 
				order=1;
				token= strtok(buffer,delimiter);   //切字串 
  					while (token){
  						
						if(order==1)
  						strcpy(label[linelength],token);
  					 	if(order==2)
  						strcpy(opcode[linelength],token);
  						if(order==3)
  						strcpy(symbol[linelength],token);
    					
						token = strtok (NULL, delimiter);
    					order++;
					}
						linelength++;
			}while(!file.eof());
			file.close();
		
			
		cout<<"Line\tLoc\tSource statement\t\tObject code\n"<<endl;
		int line=5,loc=0,objectcode,LOCCTR[10000];
		
		if(opcode[0][0]=='S'&&opcode[0][1]=='T'&&opcode[0][2]=='A'&&opcode[0][3]=='R'&&opcode[0][4]=='T')
		{
			loc=StringToHexNumber(symbol[0]);
		}
		

		
		for(line=5;line<=255;line+=5)
		{
			if(line!=5&&label[line/5-1][0]>=65&&label[line/5-1][0]<91)//把我的symtable 處理好 
			{
				strcpy(symboltable[loc],label[line/5-1]);
			}
			
		/*if(symboltable[loc][0]>=65&&symboltable[loc][0]<91)//把我的symtable show出來 
			{
				printf("%s,%x\n",symboltable[loc],loc);
			}*/ 
			LOCCTR[line/5-1]=loc;
			loc=CountLoc(loc,opcode[line/5-1],symbol[line/5-1]);
			

		}
		
		for(line=5;line<=255;line+=5)
		{
			if(label[line/5-1][0]=='.')
			printf("%d\t\t%s\t%s\n",line,label[(line-5)/5],opcode[(line-5)/5]);
			else if(opcode[line/5-1][0]=='E'&&opcode[line/5-1][1]=='N'&&opcode[line/5-1][2]=='D')
			printf("%d\t\t%s\t%s\t%s\t\t",line,label[(line-5)/5],opcode[(line-5)/5],symbol[(line-5)/5]);
			else if(opcode[line/5-1][2]=='C'&&opcode[line/5-1][3]=='H')
			printf("%d\t%x\t%s\t%s\t%s\t",line,LOCCTR[line/5-1],label[(line-5)/5],opcode[(line-5)/5],symbol[(line-5)/5]);			
			else			
			printf("%d\t%x\t%s\t%s\t%s\t\t",line,LOCCTR[line/5-1],label[(line-5)/5],opcode[(line-5)/5],symbol[(line-5)/5]);
			
			if(label[line/5-1][0]!='.')	
			PrintObjectCode(opcode[(line-5)/5],symbol[(line-5)/5]);		
		}
	}	
