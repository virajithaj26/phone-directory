#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct node {
   char name[30];
   char pno[11];
   struct node *next;
} *first = NULL, *last = NULL;


struct calllog {
   char name[30];
   char pno[11];
   char time[20];
   struct calllog *next;
} *top = NULL;


struct reminder {
   char name[30];
   char pno[11];
   char message[100];
   struct reminder *next;
} *front = NULL, *rear = NULL;


int valtime(char *time) {
   int hour, minute;
   if (strlen(time) != 5 || time[2] != ':') return 0;
   for (int i = 0; i < 5; i++) {
       if (i == 2) continue;
       if (!isdigit(time[i])) return 0;
   }
   sscanf(time, "%d:%d", &hour, &minute);
   if (hour < 0 || hour > 23 || minute < 0 || minute > 59) return 0;
   return 1;
}


void push(char *name, char *pno, char *time) {
   struct calllog *newlog = (struct calllog *)malloc(sizeof(struct calllog));
   strcpy(newlog->name, name);
   strcpy(newlog->pno, pno);
   strcpy(newlog->time, time);
   newlog->next = top;
   top = newlog;
}


void deletelog() {
   if (top == NULL) {
       printf("No call logs available.\n");
       return;
   }
   struct calllog *temp = top;
   top = top->next;
   printf("Deleted call log: %s %s %s\n", temp->name, temp->pno, temp->time);
   free(temp);
}                                  


struct node *search(char *name) {
   struct node *temp;
   if (first == NULL) {
       printf("List is Empty\n");
       return NULL;
   }
   temp = first;
   while (temp != NULL) {
       if (strcmp(name, temp->name) == 0) {
           printf("Name: %s Phone Number: %s\n", temp->name, temp->pno);
           return temp;
       }
       temp = temp->next;
   }
   printf("Contact not found.\n");
   return NULL;
}


void displaylogs() {
   if (top == NULL) {
       printf("No call logs available.\n");
       return;
   }
   struct calllog *temp = top;
   printf("Call Logs:\n");
   while (temp != NULL) {
       printf("%s %s %s\n", temp->name, temp->pno, temp->time);
       temp = temp->next;
   }
}


int traversal(char name[11]) {
   struct node *temp1;
   temp1 = first;
   while (temp1 != NULL) {
       if (strcmp(name, temp1->pno) == 0) {
           return 1;
       }
       temp1 = temp1->next;
   }
   return 0;
}
int validno(char *pno){
    for (int i = 0; i < strlen(pno); i++) {
        if (isdigit(pno[i])==0) {
            return 0; 
        }
    }
    return 1;
}
void create() {
   struct node *nn;
   char name[30], pno[11];
   printf("Enter name:\n");
   scanf("%s", name);


   printf("Enter Phone Number:\n");
   scanf("%s", pno);
   if (traversal(pno) == 1) {
       printf("Duplicates not allowed\n");
       return;
   }
 if (validno(pno)==0) {
        printf("Invalid Phone Number. Phone number must contain only digits.\n");
        return;
 }

   if (strlen(pno) != 10) {
       printf("Invalid Phone Number\n");
       return;
   }
   nn = (struct node *)malloc(sizeof(struct node));
   strcpy(nn->name, name);
   strcpy(nn->pno, pno);
   nn->next = NULL;
   if (first == NULL) {
       first = nn;
       last = nn;
   } else {
       last->next = nn;
       last = nn;
   }
   printf("Contact Saved\n");
}


void modify() {
   int choice;
   struct node *p;
   char x[30], y[30], name[30];
   printf("Enter name you want to modify:\n");
   scanf("%s", x);
   p = search(x);
   if (p == NULL) {
       printf("Please try again.\n");
       return;
   }
   printf("Enter 0 for modifying name and 1 for modifying number\n");
   scanf("%d", &choice);
   if (choice == 0) {
       printf("Enter the modified name:\n");
       scanf("%s", name);
       strcpy(p->name, name);
       printf("Contact name is modified.\n");
   }
   if (choice == 1) {
       printf("Enter the modified phone number:\n");
       scanf("%s", y);
       if (strlen(y) != 10) {
           printf("Invalid Phone Number\n");
           return;
       }
       strcpy(p->pno, y);
       printf("Contact number is modified.\n");
   }
}


void sort() {
   struct node *a, *b;
   char temp[30], t[100];
   if (first == NULL) {
       printf("List is empty.\n");
       return;
   }
   for (a = first; a != NULL; a = a->next) {
       for (b = a->next; b != NULL; b = b->next) {
           if (strcmp(b->name, a->name) < 0) {
               strcpy(temp, a->name);
               strcpy(t, a->pno);
               strcpy(a->name, b->name);
               strcpy(a->pno, b->pno);
               strcpy(b->name, temp);
               strcpy(b->pno, t);
           }
       }
   }
}


void display() {
   struct node *temp;
   if (first == NULL) {
       printf("Phone Book is Empty\n");
       return;
   }
   sort();
   temp = first;
   printf("\n%-30s %-11s\n", "Name", "Phone Number");
   printf("--------------------------------------------------\n");
   while (temp != NULL) {
       printf("%-30s %-11s\n", temp->name, temp->pno);
       temp = temp->next;
   }
}


void deletion() {
   struct node *temp, *temp1;
   char name[30];
   printf("Enter the name you want to delete:\n");
   scanf("%s", name);
   temp = search(name);
   if (temp == NULL) return;
   temp1 = first;
   if (temp == first) {
       first = temp->next;
       free(temp);
       printf("Contact Deleted\n");
       return;
   }
   if (temp == last) {
       while (temp1->next != temp) {
           temp1 = temp1->next;
       }
       temp1->next = NULL;
       last = temp1;
       free(temp);
       printf("Contact Deleted\n");
       return;
   }
   while (temp1->next != temp) {
       temp1 = temp1->next;
   }
   temp1->next = temp->next;
   free(temp);
   printf("Contact Deleted\n");
}


void makecall() {
   char name[30], pno[11], time[20];
   struct node *contact;
   printf("Enter the name you want to call:\n");
   scanf("%s", name);
   contact = search(name);
   if (contact == NULL) {
      
       return;
   }
   strcpy(pno, contact->pno);
   do {
       printf("Enter current time (HH:MM format):\n");
       scanf("%s", time);
       if (!valtime(time)) {
           printf("Invalid time format. Please enter again.\n");
       }
   } while (!valtime(time));
   push(contact->name, pno, time);
   printf("Call made to %s at %s\n", contact->name, time);
}


void enqueuereminder(char *name, char *pno, char *message) {
   struct reminder *nr = (struct reminder *)malloc(sizeof(struct reminder));
   strcpy(nr->name, name);
   strcpy(nr->pno, pno);
   strcpy(nr->message, message);
   nr->next = NULL;
   if (rear == NULL) {
       front = rear = nr;
   } else {
       rear->next = nr;
       rear = nr;
   }
   printf("Reminder added for %s\n", name);
}


void dequeuereminder() {
   if (front == NULL) {
       printf("No reminders available.\n");
       return;
   }
   struct reminder *temp = front;
   front = front->next;
   if (front == NULL) {
       rear = NULL;
   }
   printf("Removed reminder for %s\n", temp->name);
   free(temp);
}


void displayreminders() {
   if (front == NULL) {
       printf("No reminders available.\n");
       return;
   }
   struct reminder *temp = front;
   printf("\nReminders:\n");
   printf("%-30s %-11s %-80s\n", "Name", "Phone Number", "Message");
   printf("-------------------------------------------------------------------------------------------------------\n");
   while (temp != NULL) {
       printf("%-30s %-11s %-80s\n", temp->name, temp->pno, temp->message);
       temp = temp->next;
   }
}


void printmenu() {
   printf("\n");
   printf("***************************************\n");
   printf("*          PHONE MENU                 *\n");
   printf("***************************************\n");
   printf("* 1. Create a contact                 *\n");
   printf("* 2. Display Contacts                 *\n");
   printf("* 3. Search a Contact                 *\n");
   printf("* 4. Modify Contact                   *\n");
   printf("* 5. Delete Contact                   *\n");
   printf("* 6. Make Call                        *\n");
   printf("* 7. Delete Call Log                  *\n");
   printf("* 8. Display Call Logs                *\n");
   printf("* 9. Add Reminder                     *\n");
   printf("* 10. Display Reminders               *\n");
   printf("* 11. Remove Reminder                 *\n");
   printf("* 0. Exit                             *\n");
   printf("***************************************\n");
   printf("\n");
   printf("Enter choice: ");
}


int main() {
   int choice;
   char name[30], pno[11], message[100];


   while (1) {
       printmenu();
       scanf("%d", &choice);


       switch (choice) {
           case 1:
               create();
               break;
           case 2:
               display();
               break;
           case 3:
                  printf("Enter the name\n");
                  scanf("%s",name);
               search(name);
               break;
           case 4:
               modify();
               break;
           case 5:
               deletion();
               break;
           case 6:
               makecall();
               break;
           case 7:
               deletelog();
               break;
           case 8:
               displaylogs();
               break;
           case 9: {
               struct node *contact;
               printf("Enter name:\n");
               scanf("%s", name);
               contact = search(name);
               if (contact == NULL) break;
               strcpy(pno, contact->pno);
               printf("Enter message:\n");
               scanf(" %[^\n]s", message);  // To read a full line with spaces
               enqueuereminder(name, pno, message);
               break;
           }
           case 10:
               displayreminders();
               break;
           case 11:
               dequeuereminder();
               break;
           case 0:
               exit(0);
           default:
               printf("Invalid choice, please try again.\n");
       }
   }


   return 0;
}
