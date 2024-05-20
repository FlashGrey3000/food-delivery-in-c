#include <stdio.h>
#include <string.h>

typedef struct{//user defined struct
	char rest_name[50];
	char food_name[50];
	int quantity;
	int price;
	int total;
}cart;

void add_cart(cart *row[],int i, char rest_name, char food_name,float price){
	int quantity;
	printf("Enter quantity : ");
	scanf("%d",quantity);
	strcpy(row[i].rest_name,rest_name);
	strcpy(row[i].food_name,food_name);
	row[i].quantity=quantity;
	row[i].price=price;
	row[i].total=quantity*price;
}

void remove_cart(cart *row[], char food_name){
	for (int i=0;i<sizeof(row);i++){
		if(strcmp(row[i].food_name,food_name)==0){
			for (int j=i;j<sizeof(row);j++){
				strcpy(row[j].rest_name,row[j+1].rest_name);
				strcpy(row[j].food_name,row[j+1].food_name);
				row[j].quantity=row[j+1].quantity;
				row[j].price=row[j+1].price;
				row[j].total=row[j+1].total;
			}
		}
	}
}

void print_cart(cart *row){
	for(int i=0;i<sizeof(row);i++){
		printf("%d ",i);
		printf("%s ",row[i].rest_name);
		printf("%s ",row[i].food_name);
		printf("%d ",row[i].quantity);
		printf("%d ",row[i].price);
		printf("%d \n",row[i].total);
	}
}
	
int main() {
	char rest[]=abc;//selected restaurent.
	cart row[100];
	while(1){
	int choice;
	//let give 2 options, 1.add to cart 2.remove from cart.
	printf("0.Exit.\n1.add to cart.\n2.remove from cart.\n3.Print cart.\nEnter your option : ");
	scanf("%d",choice);
	switch(choice){
		case 0:
			break;
		case 1:
			while (1){
				int price,i=0;
				char food[50];
				printf("Enter q to exit. \nEnter food : ");
				scanf("%s",food);
				if(food=='q'||food=='Q')
					break;
				else{
				printf("Enter price : ");
				scanf("%d", price);
				add_cart(row,i,rest,food,price);
				i++;
				}
			}
			break;
		case 2:
			char food[50];
			printf("Enter food to remove : ");
			scanf("%s",food);
			remove_cart(row, food);
			break;
		case 3:
			print_cart(row);
			break;
	}
	}
}
