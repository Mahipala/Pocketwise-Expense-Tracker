/* PocketWise expense tracker: Singly linked-list based C program.
 * Compile: gcc expense_tracker.c -o expense_tracker
 * Run: ./expense_tracker (Windows: expense_tracker.exe)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LEN 80
#define CAT_LEN 24

typedef struct Expense {
    int id;
    char title[TITLE_LEN];
    char category[CAT_LEN];
    double amount;
    char date[16];
    struct Expense *next;
} Expense;

Expense *head = NULL;
int nextId = 1;

void trimNewline(char *s){ s[strcspn(s,"\n")]=0; }
void addExpense(void){
    Expense *node=(Expense*)malloc(sizeof(Expense));
    if(!node){puts("Memory allocation failed.");return;}
    node->id=nextId++;
    printf("Expense title: ");fgets(node->title,sizeof node->title,stdin);trimNewline(node->title);
    printf("Category (Food/Travel/Bills/etc): ");fgets(node->category,sizeof node->category,stdin);trimNewline(node->category);
    printf("Amount (INR): ");if(scanf("%lf",&node->amount)!=1||node->amount<=0){puts("Invalid amount.");while(getchar()!='\n');free(node);return;}while(getchar()!='\n');
    printf("Date (YYYY-MM-DD): ");fgets(node->date,sizeof node->date,stdin);trimNewline(node->date);
    node->next=head;head=node;printf("Expense saved (ID %d).\n",node->id);
}
void showExpenses(void){
    if(!head){puts("\nNo expenses recorded yet.");return;}
    printf("\n%-5s %-24s %-14s %-12s %-12s\n","ID","TITLE","CATEGORY","AMOUNT","DATE");
    printf("---------------------------------------------------------------------\n");
    for(Expense *p=head;p;p=p->next)printf("%-5d %-24.24s %-14.14s ₹%-11.2f %-12s\n",p->id,p->title,p->category,p->amount,p->date);
}
void totalExpenses(void){double total=0;int count=0;for(Expense *p=head;p;p=p->next){total+=p->amount;count++;}printf("\nTotal spend: ₹%.2f | Entries: %d | Average: ₹%.2f\n",total,count,count?total/count:0.0);}
void searchExpense(void){char query[TITLE_LEN];int found=0;printf("Search title/category: ");fgets(query,sizeof query,stdin);trimNewline(query);printf("\nSearch results:\n");for(Expense *p=head;p;p=p->next){if(strstr(p->title,query)||strstr(p->category,query)){printf("ID %d | %s | %s | ₹%.2f | %s\n",p->id,p->title,p->category,p->amount,p->date);found=1;}}if(!found)puts("No matches found.");}
void deleteExpense(void){int id;printf("Enter expense ID to delete: ");if(scanf("%d",&id)!=1){puts("Invalid ID.");while(getchar()!='\n');return;}while(getchar()!='\n');Expense **link=&head;while(*link&&(*link)->id!=id)link=&(*link)->next;if(!*link){puts("Expense ID not found.");return;}Expense *del=*link;*link=del->next;free(del);puts("Expense removed.");}
void freeAll(void){while(head){Expense *tmp=head;head=head->next;free(tmp);}}
int main(void){int choice;puts("======================================\n PocketWise Expense Tracker (C)\n Data Structure: Singly Linked List\n======================================");do{printf("\n1. Add expense\n2. View all expenses\n3. Total / average summary\n4. Search by title/category\n5. Delete expense by ID\n0. Exit\nChoose: ");if(scanf("%d",&choice)!=1){puts("Invalid input.");break;}while(getchar()!='\n');switch(choice){case 1:addExpense();break;case 2:showExpenses();break;case 3:totalExpenses();break;case 4:searchExpense();break;case 5:deleteExpense();break;case 0:puts("Goodbye!");break;default:puts("Choose a listed option.");}}while(choice!=0);freeAll();return 0;}
