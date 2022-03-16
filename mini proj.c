#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h> 
#define N sizeof(struct Account)
#define M sizeof(struct Money)
 struct Account //Account information 
{
	 char name[10]; //Account nickname 
	 char password[18]; //password 
	 struct Account *next; //Pointer field 
};
typedef struct Account Acc;
typedef Acc *Accp;
 
 struct Money //Money 
{
	float money;
	 char time[10];//time
	 char date[10];//date 
	struct Money *next;
};
typedef struct Money mon;
typedef mon *monp;
 
 //Function declaration area 
 void HideCursor(); //Hide the cursor
 void toxy(int x, int y); //Move the cursor to the X, Y coordinates
 void color(short x); //Set the color
 void menu(); //Menu 
 Accp ff(); //Read the contents of the file  
 void signin(); //Log in or register 
 void login(); // Register account 
 void logon(); // Account login   
 void amend_password(); //Modify password
 void add_money(); //Deposit 
 void find_money(); //Query 
 void get_money(); //Withdraw money
 void transfer_money(); //transfer
 void save_account(Accp p); //Save the content pointed to by p into the file
 void save_money(monp p); //Save the content pointed to by p into the file 
 float Sum(); //Find the balance 
 void over(); //Exit the system  
 void list(); //Bill details 
monp ss();
 
 
 char _name[20],_password[18]; //Global variables remember the current login account 
 
void color(short x)
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
} 
 
 void HideCursor() //Hide the cursor
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
 
 void toxy(int x, int y) //Move the cursor to the X, Y coordinates
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos); 
}
 
 Accp ff() //Output the contents of the file with the account to the linked list
{
	 FILE *fp; //File pointer 
	int n=0;
	Accp head=NULL;
	Accp p2,p;
	 fp=fopen("account","a+"); //Open the file in read-only mode 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		 while(!feof(fp)) //Judging whether the file position mark has moved to the end of the file 
		{
		   n++;
		   	 p=(Accp)malloc(N); //Apply a space from the memory 
		    fread(p,N,1,fp); //Assign the contents of the file pointed to by fp to p 
		   if(n==1)
		   {
		      head=p;
		      p2=p;
		    }
		     else //Create a linked list 
		    {
		    	p2->next=p;
		    	p2=p;
			}
	    }
	    p2->next=NULL;
	}
         fclose(fp); //Close the file 
         return head; //return head pointer 
}
 
 void menu() //Menu 
{
	 system("cls"); //Clear the screen  
	do{
		 color(14); //Look at the comfortable color
		char t;
		toxy(50,5);
		 printf("Automatic teller machine simulation system");
		toxy(50,6);
		 printf("The current account is: %s",_name);
		toxy(48,8);
		 printf("| 1. Withdraw money |");
		toxy(48,10);
		 printf("| 2. Transfer |");
		toxy(48,12);
		 printf("| 3. Balance |");
		toxy(48,14);
		 printf("| 4. Details |");
		toxy(48,16);
		 printf("| 5. Deposit |");
		toxy(48,18);
		 printf("| 6. Modify password |"); 
		toxy(48,20);
		 printf("| 7. Exit the system |");
		 t=getch(); //Using the non-echo function, enter t, you don’t need to manually press the enter key 
		switch(t)
		{
			case '1':get_money();break; 
			case '2':transfer_money();break;
			case '3':find_money();break;
			case '4':list();break; 
			case '5':add_money();break;
			case '6':amend_password();break;
			case '7':over();break;
			default :;break;
		}
         }while(1); //Always true 
}
 
 void signin() //Log in or register 
{
	system("cls");
	color(12); 
	 HideCursor(); //Hide the cursor
	char t;
	toxy(50,5);
	 printf("Automatic teller machine simulation system");
	toxy(44,8);
	printf("----------------------------");
	toxy(45,10);
	printf("Please enter (1: login; 2: register.)");
	toxy(44,12);
	printf("----------------------------");
	while(1)
	{
		t=getch();
		switch(t)
		{
			case '1':logon();break;
			case '2':login();break;
			default :break;
		}
	}
}
 
 void logon() // Account login 
{ 
	 system("cls"); //Clear the screen 
	 color(10); //Set the color 
	Accp p,head;    
	 head=ff(); //Call the function, the return value is the pointer of the head node 
    do{
	    p=head;
	    char t,c,k;
	    int i=0;;
		toxy(50,5);
		 printf("Automatic teller machine simulation system");
		toxy(45,6);
		printf("***************************");
		toxy(45,8);
		 printf("Login status");
		toxy(45,10);
		 printf("* Please enter your account number:");
		gets(_name);
		toxy(45,12);
		 printf("* Please enter your password:");
		 for(;;) //Here is the operation of inputting the password without echo 
		{
			 k=getch(); //Enter k 
			 if(k=='\r') //If the input k is a carriage return, then jump out of the loop 
			{
				break;
			}
			 else if(k=='\b') //If input k is the delete key 
			{
				 if(i>0) //If the password has not been completely deleted 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else //If the input k is neither the delete key nor the enter key 
			{
				 _password[i]=k; //Assign the value of k to _password[i]; 
				 printf("*"); //output * to protect user privacy 
				 i++; //Add 1 to the number of password digits 
			}
		}
		_password[i]='\0';
		 while(p!=NULL&&strcmp(p->name,_name)!=0) //Traverse the linked list to find the account of the currently entered account 
		{
			p=p->next;
		}
		 if(p!=NULL) //If p is not empty 
		{
	    	 if(strcmp(p->password,_password)==0) //If the entered password is correct 
			{
				toxy(48,16);
				 printf("Logging in...");
				 Sleep(500); //Pause for 0.5 seconds
				system("cls");
				color(10);
				toxy(48,10);
				 printf("Login successful!");
				 break; //out of the loop
			}
			 else //If the entered password is wrong
			{ 
				toxy(48,16);
				 printf("Logging in...");
				Sleep(500);
				system("cls");
				color(10);
				toxy(46,8);
				printf("-------------------------");
				toxy(46,9);
				printf("|                       |");
				toxy(46,10);
				 printf("| Wrong password! Do you want to continue? |");
				toxy(46,12);
				 printf("| 1. Yes 2. No |");
				toxy(46,13);
				printf("|                       |");
				toxy(46,14);
				printf("-------------------------");
				while(1)
				{
					 t=getch(); //Enter t    
					if(t=='1')          
					{
						 system("cls"); //Clear the screen 
						color(10); 
						break;
					}
					 else if(t=='2') //If the input t is n, enter the start interface 
					{
						signin();break;
					}
				}
			} 
	   }
	    else //If p is empty, the account number entered is incorrect 
	   {
	   	    toxy(48,16);
	   	     printf("Logging in...");
	   	    Sleep(500);
	   	    system("cls");
	   	    color(10);
	   	    toxy(46,8);
	   	    printf("-------------------------");
	   	    toxy(46,9);
	   	    printf("|                       |");
	   		toxy(46,10);
			 printf("| Account error! Do you want to continue? |");
			toxy(46,11);
			printf("|                       |");
			toxy(46,12);
			 printf("| 1. Yes 2. No |"); 
			toxy(46,13);
			printf("|                       |");
			toxy(46,14);
			printf("-------------------------");
			 while(1) //Endless loop to prevent other button interference 
			{
				c=getch();
				if(c=='1')
				{  
					system("cls");
					color(10);
					break;
				}
				else if(c=='2')
				{
					signin();break;
				}
			}
	   }
         }while(1); //Always true 
       Sleep(500); //Pause for 0.5 seconds 
       menu(); //The account and password are correct, enter the main menu 
}
 
 void login() //register account 
{
	
	system("cls");
	color(10); 
	Accp p1;
	 p1=(Accp)malloc(N); //Apply a space from the memory 
	do{
		color(10);
		char name[20],password[18],againpassword[18],c,k;
		int i=0;; 
		toxy(50,5);
		 printf("Automatic teller machine simulation system");
		toxy(45,6);
		printf("**************************");
		toxy(45,8);
		 printf("Registering");
		toxy(45,10);
		 printf("* Please enter the account number:");
		gets(name);
		toxy(45,12);
		 printf("* Please enter the password:");
		 for(;;) //Here is the operation of inputting the password without echo 
		{
			 k=getch(); //Enter k 
			 if(k=='\r') //If the input k is a carriage return, then jump out of the loop 
			{
				break;
			}
			 else if(k=='\b') //If input k is the delete key 
			{
				 if(i>0) //If the password has not been completely deleted 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else //If the input k is neither the delete key nor the enter key 
			{
				 password[i]=k; //Assign the value of k to _password[i]; 
				 printf("*"); //output * to protect user privacy 
				 i++; //Add 1 to the number of password digits 
			}
		}
		password[i]='\0';
		i=0;
		toxy(45,14);
		 printf("* Please confirm your password:");
		 for(;;) //Here is the operation of inputting the password without echo 
		{
			 k=getch(); //Enter k 
			if(k=='\r') //If the input k is a carriage return, then jump out of the loop 
			{
				break;
			}
			 else if(k=='\b') //If input k is the delete key 
			{
				 if(i>0) //If the password has not been completely deleted 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else //If the input k is neither the delete key nor the enter key 
			{
				 againpassword[i]=k; //Assign the value of k to _password[i]; 
				 printf("*"); //output * to protect user privacy 
				 i++; //Add 1 to the number of password digits 
			}
		}
		againpassword[i]='\0';
		 if(strcmp(password,againpassword)==0) //If the two passwords entered are correct 
		{
			strcpy(p1->name,name);
			strcpy(p1->password,password);
			toxy(48,16);
			 printf("Registering...");
			Sleep(500);
			system("cls");
			color(12);
			toxy(48,10);
			 printf("Registered successfully!");
			 Sleep(500); //Pause for 0.5 seconds 
			 break; //out of the loop 
		}
		 else //If the two passwords entered are different 
		{
			toxy(48,16);
			 printf("Registering...");
			Sleep(500);
			system("cls");
			color(12);
			toxy(46,8);
			printf("-----------------------------");
			toxy(46,9);
			printf("|                           |");
			toxy(46,10);
			 printf("| Registration failed! Do you want to continue registration? |");
			toxy(46,11);
			printf("|                           |");
			toxy(46,12);
			 printf("| 1. Yes 2. No |"); 
			toxy(46,13);
			printf("|                           |");
			toxy(46,14);
			printf("-----------------------------");
			while(1)
			{
				c=getch();
				if(c=='1')
				{
					system("cls");
					color(12);
					break;
				}
				else if(c=='2')
				{
					signin();
					break;
				}
			}
		}
	 }while(1); //Always true 
	 save_account(p1); //Call the function to store the content pointed to by p1 in the file 
	toxy(48,12);
	 printf("Automatically logging in for you...");
	Sleep(500);
	 menu(); //Enter the main menu after successful registration 
}
 
 
 /*change Password 
 The method is stupid, here is the account information stored in the file first
 Output in a linked list, traverse the linked list, find the account currently logged in, modify the p->password of the node,
 Then save the modified linked list to the file. It should be noted that the content in the file needs to be saved after the modification.
 Empty*/ 
 void amend_password() //Modify password 
{ 
	 system("cls"); //Clear the screen 
	 color(14); //Look at the comfortable color 
	HideCursor();  
	 Accp p,head; //Hide the cursor, look more comfortable 
	head=ff();
	FILE *fp;
    do
    {
    	color(14);
    	     HideCursor(); //Hide the cursor and look comfortable 
    	p=head;
    	char password[18],newpassword[18],t,k;
    	int i=0;
    	     toxy(50,5); //Move the cursor to the position with coordinates (50,5) 
		 printf("Automatic teller machine simulation system");
		toxy(50,8);
		 printf("Modify Password");
		toxy(48,10);
		 printf("Please enter the old password:");
		 for(;;) //Here is the operation of inputting the password without echo 
		{
			 k=getch(); //Enter k 
			 if(k=='\r') //If the input k is a carriage return, then jump out of the loop 
			{
				break;
			}
			 else if(k=='\b') //If input k is the delete key 
			{
				 if(i>0) //If the password has not been completely deleted 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else //If the input k is neither the delete key nor the enter key 
			{
				 password[i]=k; //Assign the value of k to _password[i]; 
				 printf("*"); //output * to protect user privacy 
				 i++; //Add 1 to the number of password digits 
			}
		}
		password[i]='\0';
		i=0;
		toxy(48,12);
		 printf("Please enter a new password:");
		 for(;;) //Here is the operation of inputting the password without echo 
		{
			 k=getch(); //Enter k 
			 if(k=='\r') //If the input k is a carriage return, then jump out of the loop 
			{
				break;
			}
			 else if(k=='\b') //If input k is the delete key 
			{
				 if(i>0) //If the password has not been completely deleted 
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
			}
			 else //If the input k is neither the delete key nor the enter key 
			{
				 newpassword[i]=k; //Assign the value of k to _password[i]; 
				 printf("*"); //output * to protect user privacy 
				 i++; //Add 1 to the number of password digits 
			}
		}
		newpassword[i]='\0';
		 while(p!=NULL&&strcmp(p->name,_name)!=0)//traverse the linked list to find the account of the current login account 
		{
			p=p->next;
		}
		 if(p!=NULL) //If p is not empty 
		{
			if(strcmp(p->password,password)==0) //If the old password is entered correctly 
			{
				 strcpy(p->password,newpassword); //Change the old password to the new password 
				 break; //out of the loop 
			}
			 else //If the old password is entered incorrectly 
			{
				system("cls");
				color(12);
				toxy(46,8);
				printf("--------------------------");
				toxy(46,9);
				printf("|                        |");
				toxy(46,10);
				 printf("| Wrong password! Do you want to continue? |");
				toxy(46,11);
				printf("|                        |");
				toxy(46,12);
				 printf("| 1. Yes 2. No |");
				toxy(46,13);
				printf("|                        |");
				toxy(46,14);
				printf("--------------------------");
				while(1)
				{
					 t=getch(); //Enter t 
					if(t=='1')
					{
						system("cls");
						color(12);
						break;
					}
					else if(t=='2')
					  menu();
				}
			}
		}
	 }while(1); //Always true 
	 p=head->next; //make p point to the second node 
	 fp=fopen("account","w"); //First empty the original file content and then write the modified information to the file 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	 if(fwrite(head,N,1,fp)!=1) //Write the data pointed to by head to the file pointed to by fp 
	{
		printf("file write error\n");
	}
	 fclose(fp); //Close the file 
	 fp=fopen("account","a"); // Open the account file by appending 
	 while(p!=NULL) //Execute the loop body if p is not empty 
	{
		 if(fwrite(p,N,1,fp)!=1) //Write a data structure of size N pointed to by p to the file pointed to by fp 
	    {
		printf("file write error\n");
	    }
	     p=p->next; //make p point to the next node 
	}
	 fclose(fp); //Close the file 
	toxy(48,14);
	 printf("Modified successfully! Jumping...");
	 Sleep(500); //Pause for 0.5 seconds 
}
 
 
 void save_account(Accp p1) //Store the content pointed to by p1 to the file 
{
	 FILE *fp; //File pointer 
	 fp=fopen("account","a"); //Open the file by appending 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	 if(fwrite(p1,N,1,fp)!=1) //Write a data structure of size N pointed to by p1 into the file pointed to by fp 
	{
		printf("file write error\n");
	}
	 fclose(fp); //Close the file 
}
 
 void add_money() //Deposit 
{
	do
	{
		 system("cls"); //Clear the screen 
		color(11);
		monp p;
		char t; 
		char time[10],date[10];
		 p=(monp)malloc(M); //Apply a space from the memory 
		toxy(48,8);
		 printf("Please enter the amount you need to deposit:");
		scanf("%f",&p->money);
		 getchar(); //absorb the enter key 
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);   
		toxy(48,10);
		 printf("Operating, please wait...");
		Sleep(500);
		save_money(p);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf("| Saved successfully! Do you want to continue? |");
		toxy(46,12);
		 printf("| 1. Yes 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu();
			}
		}
	}while(1);
}
 
 void find_money() //Check balance 
{
	system("cls");
	color(13);
	float sum=0;
	sum=Sum();
	toxy(46,12);
	 printf("The balance is:%f",sum);
	toxy(46,16);
	 printf("Press any key to return to the main menu");
	getch();
	menu(); 
}
 
 void get_money() //Withdraw money 
{
	do
	{
		system("cls");
		color(11);
		monp p;
		float money,sum;
		char t;
		char time[10],date[10];
		toxy(46,12);
		 printf("Please enter the amount you want to withdraw:");
		scanf("%f",&money); 
		 getchar();//Absorb the enter key 
		sum=Sum();
		 if(money>sum) //If the amount to be taken is greater than the balance 
		{
			toxy(46,14);
			 printf("Insufficient balance, please re-enter!");
			Sleep(500);
			 continue; //End this cycle 
		}
		 p=(monp)malloc(M); //Apply a space from the memory 
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);  
		p->money=-money;
		save_money(p);      
		toxy(46,14);
		 printf("Operating, please wait...");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf("| Withdrawal is successful! Do you want to continue? |");
		toxy(46,12);
		 printf("| 1. Yes 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu();break;
			}
		}
	}while(1);
	
}
 
 void list() //Detail 
{
	system("cls");
	color(10);
	monp head,p;
	int i=10;
	head=ss();
	p=head;
	toxy(50,5);
	 printf("Automatic teller machine simulation system");
	toxy(54,6);
	 printf("Bill Details");
	toxy(30,7);
	printf("-------------------------------------------------------------");
	toxy(31,8);
	 printf("Amount of time, date");
	toxy(30,9);
	printf("-------------------------------------------------------------");
	while(p!=NULL)
	{
		toxy(30,i);
		if(p->money>=0)
		{
			printf("+%f                %-24s%s",p->money,p->time,p->date);
		}
		else
		{
			printf("%f                %-24s%s",p->money,p->time,p->date);
		}
		p=p->next;
		i++;
	}
	toxy(50,i);
	printf("Please press any key to return to the main menu");
	getch();
	menu();
}
 
 void transfer_money() //transfer 
{
	do
	{
		system("cls");
		color(10);
		FILE *fp1;
		monp p,head,p1;
		float money,sum=0;
		char name[20],t;
		char time[10],date[10];
		toxy(46,12);
		 printf("Please enter the account number you want to transfer:");
		gets(name);
		toxy(46,14);
		 printf("Please enter the amount you want to transfer:");
		scanf("%f",&money);
		 getchar(); //absorb the enter key 
		sum=Sum();
		 if(money>sum) //If the amount to be transferred is greater than the balance 
		{
			toxy(46,16);
			 printf("Insufficient balance!");
			Sleep(500);
			 continue; //End this cycle 
		 } 
		 fp1=fopen(name,"rb"); //Open the binary file named name in read-only mode  
		 if(fp1==NULL) //If the file does not exist 
		{
			toxy(46,16);
			 printf("Account does not exist!");
			fclose(fp1);
			Sleep(500);
			continue;
		}
		 fp1=fopen(name,"ab"); //Open the binary file named name by appending  
		 p=(monp)malloc(M); //Apply a space from the memory 
		p->money=-money;
		_tzset(); 
        _strtime(time);      
        strcpy(p->time,time);
        _strdate(date);
		strcpy(p->date,date);  
		save_money(p);
		p1=(monp)malloc(M);
		p1->money=money;
		strcpy(p1->time,time);
		strcpy(p1->date,date);
		 if(fwrite(p1,M,1,fp1)!=1) //store a node of size M pointed to by p1 into the file pointed to by fp1 
		{
			 printf("Transfer failed, please try again!");
			continue;
		}
		fclose(fp1);
		toxy(46,18);
		 printf("Operating, please wait...");
		Sleep(500);
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		 printf("| The transfer is successful! Do you want to continue? |");
		toxy(46,12);
		 printf("| 1. Yes 2. No |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			}
			else if(t=='2')
			{
				menu(); 
			}
		}
 
	}while(1);
}
 
float Sum()
{
	monp head=NULL,p;
	float sum=0;
	head=ss();
	p=head;
	while(p!=NULL)
	{
		 sum+=p->money; //sum 
		p=p->next;
	}
	if(head==NULL)
		sum=0;
	return sum;
}
 
 monp ss() //Find the balance 
{
	 FILE *fp; //File pointer 
	monp p,head=NULL,p2,pre=NULL;
	int n=0;
	//float sum=0;
	 fp=fopen(_name,"ab+"); //Open the binary file named _name in read-only mode 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	else
	{
		 while(!feof(fp)) //Determine whether the mark is moved to the end of the file 
		{
			n++;
			 p=(monp)malloc(M); //Apply a space from the memory 
			 fread(p,M,1,fp); // assign a section of size M in the file pointed to by fp to p 
			if(n==1)
			{
				head=p;
				p2=p;
			}
			 else //Create a linked list 
			{
				pre=p2;
				p2->next=p;
				p2=p;
			}
			p2->next=NULL;
		}
	}
	 fclose(fp); //Close the file 
	if(pre!=NULL)
		pre->next=NULL;
	 return(head); //Return the sum value 
}
 
 void save_money(monp p) //Save the content pointed to by p into the file 
{
	 FILE *fp; //File pointer 
	 fp=fopen(_name,"ab"); //Open the binary file named _name by appending 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	 if(fwrite(p,M,1,fp)!=1) //Store the content of size M pointed to by p into the file pointed to by fp 
	{
		printf("write error");
	}
	 fclose(fp); //Close the file  
}
 
 void over() //Exit the software 
{
	char t;
	toxy(48,11);
	printf("-----------------------");
	toxy(48,12);
	 printf("| Are you sure you want to exit? |");
	toxy(48,14);
	 printf("| 1. Confirm 2. Cancel |");
	toxy(48,15);
	printf("-----------------------");
	while(1)
	{
		 t=getch(); //Enter t
		switch(t)
		{
			case '1':
			system("cls");
		    color(6);
			toxy(48,10);
			 printf("Exiting safely...");
			 Sleep(1000); //Pause for 1 second 
			system("cls");
			color(8);
			toxy(48,10);
			 printf("The software has been safely exited");
			toxy(48,12);
			 printf("Thank you for using!");
			toxy(48,14);
			printf("by-by^_^");
			 exit(0); break; //terminate the program 
			case '2':
			 menu(); break; //Call the function and enter the menu 
			default :break;
		}
	}
}
 
 main() // Concise and clear main function~~~ 
{
	 signin(); //Call function 
}