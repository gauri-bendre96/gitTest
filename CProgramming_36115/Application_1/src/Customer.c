#include<stdlib.h>
#include<stdio.h>
#include "../include/Customer.h"
Customer_t Customer[3];
Product_t Product[10];

Customer_t C;
int get_id()
{
	FILE * fp = fopen("Customer.db" , "rb+");
	if(fp != NULL)
	{
		fseek(fp , -1*sizeof(Customer_t) ,SEEK_END);
		fread(&C , sizeof(Customer_t) , 1 , fp );
		fclose(fp);
	}
	return ++C.Customer_id;
}

void Register_Customer(Customer_t *ptr)
{
	if(ptr != NULL)
	{
	ptr->Customer_id = get_id();
	printf("Customer-name : ");
	scanf(" %[^\n]s" , ptr->name);
	printf("Customer-Address : ");
	scanf(" %[^\n]s" , ptr->address);
	}

}

void Write_Customer_Record( char *filename  , Customer_t *ptr)
{
	FILE *fp = fopen(filename , "ab+");
	if(fp != NULL)
	{
		fwrite(ptr , sizeof(Customer_t) , 1 , fp );
		fclose(fp);
	}
	else
	{
		printf("File IO Error.\n");
	}
}

void print_customer_record(Customer_t *prt)
{
	printf("%d  %s  %s\n " , prt->Customer_id , prt->name , prt->address);
}


void Read_Customer_Record( char *filename)
{
	Customer_t ptr;
	FILE *fp = fopen(filename , "rb+");
	if(fp != NULL)
	{
		while(fread(&ptr , sizeof(Customer_t) , 1 , fp) != 0)
		{
			print_customer_record(&ptr);
		}
		fclose(fp);
	}
	else
	{
		printf("FILE IO Error.\n");
	}

}

int Compare_Customer_id(int *id)
{
	//int found;
	Customer_t e;
		FILE *fp;
		//int id, found=0;
		fp = fopen("Customer.db", "rb");
		if(fp == NULL)
		{
			//perror("fopen() Failed");
			printf("No register ");
			//return 0;
		}

		//printf("enter emp id to find: ");
		//scanf("%d", &id);

		while( fread(&e, sizeof(Customer_t), 1, fp) != 0 )
		{
			if(e.Customer_id == *id)
			{
				//print_emp(&e);
				//printf("HEllo");
				return 1;
			}
		}
		fclose(fp);
		//if(found == 0)
			//printf("no such emp found.\n");

	/*FILE *fp = fopen("Customer.db" ,"rb");
	if(fp==NULL)
	{
		prinf("NULL");
	}
*/
	//printf("Hello2");
	return 0;
}




void Add_Produt_Category( char * filename1)
{
	int choice;
	char str[100];
	FILE *fp = fopen(filename1, "a");
		if(fp != NULL)
		{
			/*fprintf(fp , "Mobile\n");
			fprintf(fp , "Tablet\n");
			fprintf(fp , "Laptop\n");
			fprintf(fp , "Accessories\n");*/

			do
			{
				printf("Do you want to add product category (1/0) : ");
				scanf("%d" , &choice);
				if(choice ==0)
				{
					break;
				}
				else
				{
					scanf("%s",str);
					//printf("\n");
					//strcat(str , "\n");
					fputs(str,fp);
					fputc('\n', fp);

				}
			}while(choice == 1);

			fclose(fp);
		}
		else
		{
			printf("File IO error.\n");
		}
}



void Read_Record_Categories( char * filename1)
{
	FILE *fp = fopen(filename1, "r");
	char buff[255];
	while(!feof(fp))
	{
		fread(buff , sizeof(buff) , 1 , fp);
		printf("%s" , buff);
	}
}




void Accept_Product_record(Product_t *ptr)
{
	char temp;
	if( ptr != NULL )
		{

		    //ptr->prdt_id = ++ prdt_id;
			printf("Product ID	: ");
			scanf("%d", &ptr->prdt_id);


			printf("Product Name	: ");
			scanf("%c", &temp);
			scanf("%s", ptr->name);

			printf("Product Category : ");
			scanf("%s", &ptr->category);
			printf("Product Rate :   ");
			scanf("%lf", &ptr->rate);
		}

}

void print_product_record(Product_t *prt)
{
	printf("%d  %s  %s  %lf\n " , prt->prdt_id , prt->name , prt->category , prt->rate);
}

void write_product_record( char *filename2, Product_t *ptr)
	{
		FILE *fp = fopen(filename2, "ab");
		if( fp != NULL )
		{
			fwrite(ptr, sizeof( Product_t), 1, fp);
			fclose(fp);
		}
		else
			printf("FILE IO Error\n");
	}


void read_product_record(char *filename2)
{
	Product_t prt;
	//char buffer[256];
		FILE *fp = fopen(filename2 , "rb+");
		if(fp != NULL)
		{
			while(fread(&prt , sizeof(Product_t) , 1 , fp) != 0)
			{
				print_product_record(&prt);
			}
			fclose(fp);
		}
		else
		{
			printf("FILE IO Error.\n");
		}
}



void Delete_Product()
{
	FILE *fs, *fd;
	Product_t e;
	int id, found=0;
	printf("enter product id to delete: ");
	scanf("%d", &id);
	fs = fopen("products.db", "rb");
	if(fs == NULL)
	{
		perror("fopen() failed");
		return;
	}
	fd = fopen("temp.db", "wb");
	if(fd == NULL)
	{
		perror("fopen() failed");
		return;
	}
	while(fread(&e, sizeof(Product_t), 1, fs) != 0)
	{
		if(e.prdt_id == id)
			found = 1;
		else
			fwrite(&e, sizeof(Product_t), 1, fd);
	}
	fclose(fd);
	fclose(fs);
	remove("products.db");
	rename("temp.db", "products.db");

	if(found == 0)
		printf("no such emp found.\n");
}


void find_emp_by_name()
{
	Product_t e;
	FILE *fp;
	char name[50], found=0;
	fp = fopen("products.db", "rb");
	if(fp == NULL)
	{
		perror("fopen() failed");
		return;
	}

	printf("enter product name to find: ");
	scanf("%s",name);

	while( fread(&e, sizeof(Product_t), 1, fp) != 0 )
	{
		if(strcmp(e.name ,name) == 0)
		{
			print_product_record(&e);
			found = 1;
		}
	}

	if(found == 0)
		printf("no such product found.\n");
	fclose(fp);
}


void edit_emp()
{
	Product_t e;
	FILE *fp;
	int id, found=0, n;
	long size = sizeof(Product_t);
	fp = fopen("products.db", "rb+");
	if(fp == NULL)
	{
		perror("fopen() failed");
		return;
	}

	printf("enter product id to find: ");
	scanf("%d", &id);

	while( fread(&e, sizeof(Product_t), 1, fp) != 0 )
	{
		if(e.prdt_id == id)
		{
			print_product_record(&e);
			found = 1;

			// add new details for emp
			Accept_Product_record(&e);
			fseek(fp, -size, SEEK_CUR);
			n = fwrite(&e, sizeof(Product_t), 1, fp);
			printf("product edited: %d\n", n);
		}
	}

	if(found == 0)
		printf("no such product found.\n");
	fclose(fp);
}


void order_item( int *id)
{
	//int id;
	Orders_t q;
	FILE *fd;
	printf("Select the product with product id : ");
	scanf("%d", &q.product_id);
	printf("Enter the Quantity for products : ");
	scanf("%d", &q.quantity);
	q.customer_id = *id;
	q.status = 0;
	q.order_id = 1;
	//char buff[256];
	//printf("Enter todays date:");
	//scanf("%d %d %d", &q.order_date.day , &q.order_date.month, &q.order_date.year);

	fd = fopen("orders.db" , "ab");
	if(fd!=NULL)
	{

		fwrite(&q , sizeof(Orders_t) , 1 , fd);
	}
	fclose(fd);

}

void print_orders_record(Orders_t *prt)
{
	printf("%d  %d  %d %d %d\n " , prt->order_id , prt->customer_id , prt->product_id , prt->quantity ,prt->status);
	printf("Your order has been placed!!");
}

void read_order_item(Orders_t *q)
{
	//printf("Order_id=%d Cus_id=%d",q->order_id,q->customer_id );

		//char buffer[256];
			FILE *fp = fopen("orders.db" , "rb+");
			if(fp != NULL)
			{
				while(fread(&q , sizeof(Orders_t) , 1 , fp) != 0)
				{
					print_orders_record(&q);
				}
				fclose(fp);
			}
			else
			{
				printf("FILE IO Error.\n");
			}

}

