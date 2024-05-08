#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct user{
	char name[25];
	char username[30];
	char password[30];
	int phone[10];
	char address[200];
};

void takepassword(char pass[30])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        pass[i++] = ch;
        printf("*");
        
    }
}

/*//todo: needs modifications
int validate(){
	int attempt=0;
	char password[30];
    try:
	printf("Enter password:");
	scanf("%s",password);
	if(strcmp(password,users.password)==0)
		return 1;
	else if(attempt<=2){
		printf("Wrong password, Try again!");
		attempt++;
		goto try;
	}
	else{
		printf("Exceeded Limit!");
		return 0;
	}
 }
 */
 
void newuser(){
//todo: check if user exit
	struct user users;
	char p1[30],p2[30];
	printf("Enter name:");
	scanf("%[^\n]%*c",users.name);
	printf("\nEnter a username:");
	scanf("%s",users.username);
try:	
	printf("Enter Password:");
	scanf("%s",p1);
	printf("Confirm Password:");
	takepassword(users.password);
	if(strcmp(p1,users.password)!=0){
		printf("Passwords not same! Try again!");
		goto try;
	}
	
	printf("Enter Phone Number:");
	scanf("%d",users.phone);
	printf("Enter your address:");
	scanf("%[^\n]%*c",users.address);
}



void main(){
	struct user users;
	char username[30];
	int choice,end=0;
	while (end!=1){
		printf("\n\n\t\tWelcome to our Food Ordering System\n");
        	printf("\n1. Sign-up\n2. Login\n3.Forget password\n4. Exit\n");
        	printf("Please enter your choice\n");

        	scanf("%d", &choice);
	
        	switch (choice){
        	case 1:
            		newuser();
            		break;
        	/*case 2:
            		printf("Enter your username:");
            		scanf("%s",username);
            		if(validate()==1){
            			printf("Access granted!");
            		}
			else{
				printf("Try again! or do forget password!");
			}
            		break;*/
        	case 3:
        		//todo: forget()
        	case 4:
            		end=1;
        	default:
           		 printf("\n Please enter a valid choice\n");
            		break;
        	}
    }
}
