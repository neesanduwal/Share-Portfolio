
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user{
	char fullname[50];
	char password[50];
	char email[50];
	char username[50];
};

void takeinput(char ch[50]){
	fgets(ch,50,stdin);
	ch[strlen(ch)-1]=0;//removes \n and simply adds 0
	
}
char generateUsername(char email[50],char username[50]){
	int i;
	for(i=0;i<strlen(email);i++){
		if(email[i]=='@')break;
		else username[i]=email[i];//breaks the loop and creates username as before 
		
	}
}
void takepassword(char pwd[50]){
	int i;
	char ch;
	while(1){
		ch=getch();
		if(ch==ENTER || ch==TAB){
			pwd[i]='\0';
			break;
		}else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			pwd[i++]=ch;
			printf("* \b");
		}
	}
}

void gotoxy(int ,int );
void menu();
void add();
void view();
void search();
void sell();
void selldisplay();
void deleterec();
void broker();

struct stock
{
    char script[20];
    float bp;
    float sp;
    int unit;
    int sell;
    float pl;
    float total;
};

float tax=0.005;
float bc=0.00004;

int main()
{	
struct user user;
	char password2[50];
//	system("color 1f");
	FILE *fp;
	int opt,usrFound=0;
	printf("\n\t\t\t----------Welcome to authentication system-------------");
	printf("\n\nPlease choose your operation");
	printf("\n1.Signup");
	printf("\n2.Login");
	printf("\n3.Exit");
	
	printf("\n\n\nEnter Your choice:");
	scanf("%d",&opt);
	fgetc(stdin);
	
	switch(opt){
		case 1:
			system("cls");
			printf("\nEnter Name:\t");
			takeinput(user.fullname);
			printf("Enter Email:\t");
			takeinput(user.email);
			printf("Enter password:\t");
			takepassword(user.password);
			printf("\nConfirm your Password:\t");
			takepassword(password2);
			
			if(!strcmp(user.password,password2)){
				
				generateUsername(user.email,user.username);
				fp=fopen("User.dat","a+");
				fwrite(&user,sizeof(struct user),1,fp);//stores info in the file.
				if(fwrite !=0) printf("\n\nUser registration success\nUsername: %s",user.username);
				
				else
				printf("Error");
				fclose(fp);
				
			}
			else{
				printf("\nPassword dosent match");
				
				
			}
			break;
			
			case 2:;
				char username[50],pword[50];
				struct user usr;
				
				
				printf("\nEnter your Username:\t");
				takeinput(username);
				printf("\nEnter your password:\t");
				takepassword(pword);
				
				system("cls");
				
				fp=fopen("user.dat","r");
				while(fread(&usr,sizeof(struct user),1,fp)){
					if(!strcmp(usr.username,username)){
						if(!strcmp(usr.password,pword)){
							printf("\n\t\t\t\tWelcome %s",usr.fullname);
							printf("\n\n|Full Name:\t%s",usr.fullname);
							printf("\n|Email:\t%s",usr.email);
							menu();
						}
						else{
							printf("Invalid Password!!");
						}
					}
					usrFound=1;
				}
				if(!usrFound){
		printf("\n\nUser not registered");
	}
		fclose(fp);
		break;
		
		case 3:
		printf("Program ended.");
		return 0;

	}
	return 0;
	
    
}



void menu()
{
    int choice;
    system("cls");
    
    gotoxy(10,3);
    printf("<--:MENU:-->");
    gotoxy(10,5);
    printf("Enter appropriate number to perform following task.");
    gotoxy(10,7);
    printf("1 : Add a new Stock Transaction.");
    gotoxy(10,8);
    printf("2 : View your Portfolio.");
    gotoxy(10,9);
    printf("3 : Search Stock.");
    gotoxy(10,10);
    printf("4 : Sell Stock.");
    gotoxy(10,11);
    printf("5 : View your Sell Record.");
    gotoxy(10,12);
    printf("6 : Delete.");
    gotoxy(10,13);
    printf("7 : Broker Details.");
	gotoxy(10,14);
    printf("8 : Exit.");
    gotoxy(10,15);
    printf("Enter your choice.");
    scanf("%d",&choice);
    
    switch(choice)
    {
	    case 1:
	        add();
	        break;
	
	    case 2:
	        view();
	        break;
	
	    case 3:
	        search();
	        break;
	
	    case 4:
	        sell();
	        break;
	
	    case 5:
	        selldisplay();
	        break;
	        
	    case 6:
		    deleterec();
		    break;
	
	    case 7:
	        broker();
	        break;
	    
	    case 8:
	        exit(1);
	        break;
	
	    default:
	        gotoxy(10,17);
	        printf("Invalid Choice.");
    }
}



void add()
{
    FILE *fp;
    struct stock st;
    char another ='y';
    
    system("cls");

    fp = fopen("record.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    
    while(another == 'y')
    {
        gotoxy(10,3);
        printf("<--:ADD STOCK:-->");
        gotoxy(10,5);
        printf("Enter details of Stock.");
        gotoxy(10,7);
        printf("Enter Script : ");
        gets(st.script);
        gotoxy(10,8);
        printf("Enter Buying Price : ");
        scanf("%f",&st.bp);
        gotoxy(10,9);
        printf("Enter Unit : ");
        scanf("%d",&st.unit);
        fflush(stdin);
        st.total=(st.bp*st.unit)+(st.bp*st.unit)*bc;
        gotoxy(10,10);
        fwrite(&st,sizeof(st),1,fp);
        gotoxy(10,15);
        printf("Want to add of another record? Then press 'y' else 'n'.");
        fflush(stdin);
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,18);
    printf("Press any key to continue.");
    getch();
    menu();
}
void view()
{
    FILE *fp;
    int i=1,j;
    struct stock st;
    system("cls");
    gotoxy(10,3);
    printf("<--:YOUR PORTFOLIO:-->");
    gotoxy(10,5);
    printf("S.No   Script       Buying Price   Unit  Total      ");
    gotoxy(10,6);
    printf("--------------------------------------------------------------------");
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error opening file.");
        exit(1);
    }
    j=8;
    
    while(fread(&st,sizeof(st),1,fp) == 1){
        gotoxy(10,j);
        printf("%-7d %-12s %-14.2f %-5d %-12.2f",i,st.script,st.bp,st.unit,st.total);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to continue.");
    getch();
    menu();
}
void selldisplay()
{
    FILE *fp;
    int i=1,j;
    struct stock st;
    system("cls");
    
    gotoxy(10,3);
    printf("<--:YOUR SELL RECORD:-->");
    gotoxy(10,5);
    printf("S.No   Script       Buying Price	Selling Price   Unit	Profit/Loss      ");
    gotoxy(10,6);
    printf("--------------------------------------------------------------------------");
    fp = fopen("sellrecord.txt","rb+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Error opening file.");
        exit(1);
    }
    j=8;
    
    while(fread(&st,sizeof(st),1,fp) == 1){
        gotoxy(10,j);
        printf("%-7d %-13s %-18.2f %-13.2f %-7d %.2f",i,st.script,st.bp,st.sp,st.sell,st.pl);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Press any key to continue.");
    getch();
    menu();
}



void search()
{
    FILE *fp;
    struct stock st;
    char stname[20];
    system("cls");
    
    gotoxy(10,3);
    printf("<--:SEARCH STOCK:-->");
    gotoxy(10,5);
    printf("Enter Script of Stock : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    
    while(fread(&st,sizeof(st),1,fp ) == 1){
        if(strcmp(stname,st.script) == 0){
            gotoxy(10,8);
            printf("Script : %s",st.script);
            gotoxy(10,9);
            printf("Buying Price : %.2f",st.bp);
            gotoxy(10,10);
            printf("Units : %d",st.unit);
            gotoxy(10,11);
            printf("Total : %.2f",st.total);
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Press any key to continue.");
    getch();
    menu();
}
void sell()
{

	FILE *fp, *fs;
	int sell;
	float pl;
    struct stock st;
    char stname[20];
    system("cls");
    gotoxy(10,3);
    printf("<--:SELL STOCK:-->");
    gotoxy(10,5);
    printf("Enter Script of Stock you want to sell : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }

    fs = fopen("sellrecord.txt","ab+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    
    while(fread(&st,sizeof(st),1,fp ) == 1){
        if(strcmp(stname,st.script) == 0){
            gotoxy(10,8);
            printf("Script : %s",st.script);
            gotoxy(10,9);
            printf("Buying Price : %.2f",st.bp);
            gotoxy(10,10);
            printf("Units : %d",st.unit);
            gotoxy(10,11);
            printf("Total : %.2f",st.total);
            gotoxy(10,13);
            printf("Enter Selling price :");
    		scanf("%f", &st.sp);
    		gotoxy(10,14);
            printf("Enter number of units you want to sell :");
    		scanf("%d", &st.sell);
    		gotoxy(10,16);
    		printf("Your new stock balance : ");
    		gotoxy(10,17);
            printf("Script : %s",st.script);
            gotoxy(10,18);
            printf("Buying Price : %.2f",st.bp);
            gotoxy(10,19);
            st.unit = st.unit - st.sell;
            printf("Units : %d",st.unit);
            st.total=(st.bp*(st.unit))+(st.bp*(st.unit))*bc;
            gotoxy(10,20);
            printf("Total : %.2f",st.total);
            st.pl = ((st.sell * st.sp) - (st.sell * st.sp) * tax - (st.sell * st.bp));
            if(st.pl >= 0){
            	gotoxy(10,21);
				printf("Profit = %f",st.pl);
			}
			else{
				gotoxy(10,21);
				printf("Loss = %f", -1 * st.pl);
			}
			
			fwrite(&st,sizeof(st),1,fs);
			
            fseek(fp ,-sizeof(st),SEEK_CUR);
        	fwrite(&st,sizeof(st),1,fp);
           	break;
           	
           	
        }
    } 
    fclose(fp);
    fclose(fs);
    gotoxy(10,25);
    printf("Press any key to continue.");
    getch();
    menu();	
}
void deleterec()
{
   char stname[20];
   FILE *fp,*ft;
   struct stock st;
   system("cls");
   
   gotoxy(10,3);
   printf("<--:DELETE STOCK:-->");
   gotoxy(10,5);
   printf("Enter script of stock to delete  : ");
   fflush(stdin);
   gets(stname);
   fp = fopen("record.txt","rb+");
   if(fp == NULL){
       gotoxy(10,6);
       printf("Error opening file");
       exit(1);
   }
   ft = fopen("temp.txt","wb+");
   if(ft == NULL){
       gotoxy(10,6);
       printf("Error opening file");
       exit(1);
   }
   
   while(fread(&st,sizeof(st),1,fp) == 1){
       if(strcmp(stname,st.script)!=0)
           fwrite(&st,sizeof(st),1,ft);
   }
   fclose(fp);
   fclose(ft);
   remove("record.txt");
   rename("temp.txt","record.txt");
   gotoxy(10,10);
   printf("Press any key to continue.");
   getch();
   menu();
}



void broker(){
	int Number;
	system("cls");
	printf("Enter Your Broker's B.N. (1-59): ");
	scanf("%d", &Number);
	
	switch (Number)
	{
		case 1:
			printf("\n\tBroker Name: Kumari Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4418036");
			printf("\n\n\tAddress: Dillibazar, Kathmandu");
			break;
		
		case 2:
			printf("\n\tBroker Name: Kumari Securities Pvt. Limited");
			printf("\n\n\tPhone No: 061-537511");
			printf("\n\n\tAddress: New Road, Pokhara");
			break;
			
		case 3:
			printf("\n\tBroker Name: Arun Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4239567");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 4:
			printf("\n\tBroker Name: Opal Securities Investment Pvt. Limited");
			printf("\n\n\tPhone No: 01-4423509");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 5:
			printf("\n\tBroker Name: Market Securities Exchange Company Pvt. Limited");
			printf("\n\n\tPhone No: 01-4248973");
			printf("\n\n\tAddress: KichhaPokhari, Kathmandu");
			break;
			
		case 6:
			printf("\n\tBroker Name: Agrawal Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4424406");
			printf("\n\n\tAddress: Dillibazar, Kathmandu");
			break;
			
		case 7:
			printf("\n\tBroker Name: J.F. Securities Company Pvt. Limited");
			printf("\n\n\tPhone No: 01-4256099");
			printf("\n\n\tAddress: Dharmapath, Kathmandu");
			break;
			
		case 8:
			printf("\n\tBroker Name: Ashutosh Brokerage & Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4220276");
			printf("\n\n\tAddress: Kichha Pokhari, Kathmandu");
			break;
			
		case 10:
			printf("\n\tBroker Name: Pragyan Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4413392");
			printf("\n\n\tAddress: Kamaladi, Kathmandu");
			break;
			
		case 11:
			printf("\n\tBroker Name: Malla & Malla Stock Broking Company Pvt. Limited");
			printf("\n\n\tPhone No: 01-4425750, 4431607");
			printf("\n\n\tAddress: Hattisar, Kathmandu");
			break;
			
		case 13:
			printf("\n\tBroker Name: Thrive Brokerage House Pvt. Limited");
			printf("\n\n\tPhone No: 01-4425750, 4431607");
			printf("\n\n\tAddress: Naxal, Kathmandu");
			break;
			
		case 14:
			printf("\n\tBroker Name: Nepal Stock House Pvt. Limited");
			printf("\n\n\tPhone No: 01-4265888");
			printf("\n\n\tAddress: Anamnagar, Kathmandu");
			break;
			
		case 16:
			printf("\n\tBroker Name: Primo Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4168214");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 17:
			printf("\n\tBroker Name: ABC Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4230787");
			printf("\n\n\tAddress: Indrachowk, Kathmandu");
			break;
			
		case 18:
			printf("\n\tBroker Name: Sagarmatha Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4439315");
			printf("\n\n\tAddress: Dillibazar, Kathmandu");
			break;
			
		case 19:
			printf("\n\tBroker Name: Nepal Investment & Securities Trading Pvt. Limited");
			printf("\n\n\tPhone No: 01-4495450");
			printf("\n\n\tAddress: Bhimsengola, Kathmandu");
			break;
			
		case 20:
			printf("\n\tBroker Name: Sipla Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4255782");
			printf("\n\n\tAddress: NewRoad, Kathmandu");
			break;
			
		case 21:
			printf("\n\tBroker Name: Midas Stock Broking Company Pvt. Limited");
			printf("\n\n\tPhone No: 01-4240089");
			printf("\n\n\tAddress: Kamaladi Chowk, Kathmandu");
			break;
			
		case 22:
			printf("\n\tBroker Name: Siprabi Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-5530701");
			printf("\n\n\tAddress: Pulchowk, Lalitpur");
			break;
			
		case 25:
			printf("\n\tBroker Name: Sweta Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4444791");
			printf("\n\n\tAddress: Putalisadak,Kathmandu");
			break;
			
		case 26:
			printf("\n\tBroker Name: Asian Securities Pvt. Limited");
			printf("\n\n\tPhone No: 01-4424351");
			printf("\n\n\tAddress: Putalisadak-32, Kathmandu");
			break;
			
		case 28:
			printf("\n\tBroker Name: Shree Krishna Securities Limited");
			printf("\n\n\tPhone No: 01-4441226");
			printf("\n\n\tAddress: Dillibazar, Kathmandu");
			break;
			
		case 29:
			printf("\n\tBroker Name: Trishul Securities And Investment Limited");
			printf("\n\n\tPhone No: 01-4440709");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 32:
			printf("\n\tBroker Name: Premier Securities Company Limited");
			printf("\n\n\tPhone No: 01-4231339");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 33:
			printf("\n\tBroker Name: Dakshinkali Investment Securities Pvt.Limited");
			printf("\n\n\tPhone No: 01-4168640");
			printf("\n\n\tAddress: Kamaladi, Kathmandu");
			break;
			
		case 34:
			printf("\n\tBroker Name: Vision Securities Pvt.Limited");
			printf("\n\n\tPhone No: 01-4770425/452, 01-4770408");
			printf("\n\n\tAddress: Anamnagar, Kathmandu");
			break;
			
		case 35:
			printf("\n\tBroker Name: Kohinoor Investment and Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4442857");
			printf("\n\n\tAddress: Kamalpokhari, Kathmandu");
			break;
			
		case 36:
			printf("\n\tBroker Name: Secured Securities Limited");
			printf("\n\n\tPhone No: 01-4262861");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 37:
			printf("\n\tBroker Name: Swarnalaxmi Securities Pvt.Limited	");
			printf("\n\n\tPhone No: 01-4417178");
			printf("\n\n\tAddress: Kamalpokhari, Kathmandu");
			break;
			
		case 38:
			printf("\n\tBroker Name: Dipshika Dhitopatra Karobar Co. Pvt.Limited");
			printf("\n\n\tPhone No: 01-4102532");
			printf("\n\n\tAddress: Anamnagar, Kathmandu");
			break;
			
		case 39:
			printf("\n\tBroker Name: Sumeru Securities Pvt.Limited");
			printf("\n\n\tPhone No: 01-4444740");
			printf("\n\n\tAddress: Hattisar, Kathmandu");
			break;
			
		case 40:
			printf("\n\tBroker Name: Creative Securities Pvt.Limited");
			printf("\n\n\tPhone No: 01-4419572");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 41:
			printf("\n\tBroker Name: Linch Stock Market Limited");
			printf("\n\n\tPhone No: 01-4784567");
			printf("\n\n\tAddress: New Baneshwor, Kathmandu");
			break;
			
		case 42:
			printf("\n\tBroker Name: Sani Securities Company Limited");
			printf("\n\n\tPhone No: 01-4166005");
			printf("\n\n\tAddress: Jamal, Kathmandu");
			break;
			
		case 43:
			printf("\n\tBroker Name: South Asian Bulls Pvt.Limited");
			printf("\n\n\tPhone No: 01-4284785");
			printf("\n\n\tAddress: Kuleshwor, Kathmandu");
			break;
			
		case 44:
			printf("\n\tBroker Name: Dynamic Money Managers Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4414522");
			printf("\n\n\tAddress: Kamalpokhari, Kathmandu");
			break;
			
		case 45:
			printf("\n\tBroker Name: Imperial Securities Co. Pvt. Ltd.");
			printf("\n\n\tPhone No: 01-5706004, 5705187, 5705344");
			printf("\n\n\tAddress: Anamnagar, Kathmandu");
			break;
			
		case 46:
			printf("\n\tBroker Name: Kalika Securities Pvt.Limited");
			printf("\n\n\tPhone No: 01-4430601");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 47:
			printf("\n\tBroker Name: Neev Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4168601");
			printf("\n\n\tAddress: Kamaladi, Kathmandu");
			break;
			
		case 48:
			printf("\n\tBroker Name: Trishakti Securities Public Limited");
			printf("\n\n\tPhone No: 01-4232132");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 49:
			printf("\n\tBroker Name: Online Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4168298");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 50:
			printf("\n\tBroker Name: Crystal Kanchenjunga Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4011072");
			printf("\n\n\tAddress: New Plaza, Kathmandu");
			break;
			
		case 51:
			printf("\n\tBroker Name: Oxford Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4278113");
			printf("\n\n\tAddress: Kalimati, Kathmandu");
			break;
		
		case 52:
			printf("\n\tBroker Name: Sundhara Securities Limited");
			printf("\n\n\tPhone No: 01-4263583");
			printf("\n\n\tAddress: Sundhara, Kathmandu");
			break;
			
		case 53:
			printf("\n\tBroker Name: Investment Management Nepal Pvt. Ltd.");
			printf("\n\n\tPhone No: 01-4256589");
			printf("\n\n\tAddress: Tripureshwor,Kathmandu");
			break;
			
		case 54:
			printf("\n\tBroker Name: Sewa Securities Pvt. Ltd.");
			printf("\n\n\tPhone No: 01-4256642");
			printf("\n\n\tAddress: Tripureshwor, Kathmandu");
			break;
			
		case 55:
			printf("\n\tBroker Name: Bhrikuti Stock Broking Co. Pvt. Ltd.");
			printf("\n\n\tPhone No: 01-4223466");
			printf("\n\n\tAddress: Newroad, Kathmandu");
			break;
			
		case 56:
			printf("\n\tBroker Name: Shree Hari Securities Pvt. Ltd");
			printf("\n\n\tPhone No: 01-4437562");
			printf("\n\n\tAddress: Kamaladi, Kathmandu");
			break;
			
		case 57:
			printf("\n\tBroker Name: Araya Tara Investment And Securities Pvt. Ltd.");
			printf("\n\n\tPhone No: 01-5706297, 01-5705596");
			printf("\n\n\tAddress: Anamnagar, Kathmandu");
			break;
			
		case 58:
			printf("\n\tBroker Name: Naasa Securities Co. Ltd.");
			printf("\n\n\tPhone No: 01-4440384");
			printf("\n\n\tAddress: Naxal, Kathmandu");
			break;
			
		case 59:
			printf("\n\tBroker Name: Deevyaa Securities & Stock House Pvt. Ltd	");
			printf("\n\n\tPhone No:01-4421488");
			printf("\n\n\tAddress: Putalisadak, Kathmandu");
			break;
			
		case 9:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 12:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 15:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 23:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 24:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 27:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 30:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		case 31:
			printf("\n\tThere is no Company Registered in this Number.");
			break;
			
		default:
			printf("\n\tPlease choose the number ranging from '1 to 59'\n\t\t\tThank You!");
			
		
	}
	getch();
	menu();
}



void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}




