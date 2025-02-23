#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
};

struct Queue {
    struct Node* enq;
    struct Node* qdata; /*sturct enq เป็น node ที่ชี้ node หลังสุดเพื่อ enqueue ส่วน qdata จะชี้ไปยัง node แรกเสมอเพื่อ dequeue*/
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->enq = queue->qdata = NULL;
    return queue;
}

void enqueue(struct Queue* queue,char* data) {
    char* copiedData = strdup(data);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = copiedData;
    newNode->next = NULL;

    if (queue->qdata == NULL) {
        queue->enq = queue->qdata = newNode;
    } else {
        queue->qdata->next = newNode;
        queue->qdata = newNode;
    }
}

char* dequeue(struct Queue* queue) {
    if (queue->enq == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }

    char* data = queue->enq->data;
    struct Node* delete = queue->enq;
    queue->enq = queue->enq->next;

    if (queue->enq == NULL) {
        queue->qdata = NULL;
    }

    free(delete);
    return data;
}

void displayQueue(struct Queue* queue, int displayAll) {
    if (queue->enq != NULL) {
        struct Node* current = queue->enq;
        printf("Queue: ");
        while (current != NULL) {
            printf("%s ", current->data);
            current = current->next;
            if (displayAll != 1) {
                break;
            }
        }
    } else {
        printf("Queue is empty");
    }
}
void bubbleSort(char menu[10][20], int price[10], int n) {
    char sortmenu[20];
    int sortprice;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (price[j] > price[j + 1]) {
                strcpy(sortmenu, menu[j]);
                strcpy(menu[j], menu[j + 1]);
                strcpy(menu[j + 1], sortmenu);
                sortprice = price[j];
                price[j] = price[j + 1];
                price[j + 1] = sortprice;}}
        }
    }

int menu(float money,char* customerName) {
    char menu[10][20] = {"Water", "Coffee", "Cocoa", "Tea", "Latte","Green tea","lemon tea","Bubble milk tea","Sala soda","Coconut water"};
    int f, p, pt, order, price[10] = {10, 25, 30, 25, 30, 25, 20, 30, 20, 30};
    float cash,cashback;
    money=0;
    char sortChoice;
do{
    printf("Do you want to sort the menu by price (y/n): ");
    scanf(" %c", &sortChoice);
    if (sortChoice == 'y' || sortChoice == 'Y') {bubbleSort(menu, price, 10);}
}while(sortChoice != 'y' && sortChoice != 'Y' && sortChoice != 'n' && sortChoice != 'N');
    do {
        do {
            for (int i = 0; i < 10; i++) {
                printf("[%d] %s %d bath\n", i + 1, menu[i], price[i]);
            }
            printf("Press the number of the drink you want: ");
            scanf("%d", &p);
            if (p >= 1 && p <= 10) {
                printf("How many do you want: ");
                scanf("%d", &f);
                pt = f * price[p - 1];
                money = pt + money;

                printf("Total cost: %.2f bath\n", money);
            } else {
                printf("Not on the menu\n");
            }
        } while (p < 1 || p > 10);
        printf("Press 1 if you want to order more (if not press any number): ");
        scanf("%d", &order);
    } while (order == 1);

    do {
        printf("Total cost: %.2f bath\n", money);
        printf("Enter the amount of cash: ");
        scanf("%f", &cash);

        if (cash >= money) {
            cashback = cash - money;
            printf("Cashback: %.2f bath\n", cashback);
            break;
        } else {
            printf("Not enough money\n");
        }
    } while (cash <= money);
    printf("\n-----Thank you-----\n\n");

    FILE *file = fopen("Transaction for QQueue.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    fprintf(file, "Customer: %s\n", customerName);
    fprintf(file, "Total Cost: %.2f bath\n", money);
    fprintf(file, "Cashback: %.2f bath\n", cashback);
    fprintf(file, "-----------------------------\n");
    fclose(file);

    return money;
}
int search(struct Queue* queue, const char* name) {
    struct Node* current = queue->enq;
    int SearchQ = 0;

    while (current != NULL) {
        if (strcmp(current->data, name) == 0) {
            return SearchQ; 
        }
        current = current->next;
        SearchQ++;
    }
            return -1; 
    }

int main() {
    struct Queue* queue = createQueue();

    int choiceformenu = 0, pass, money = 0;
    char input[20];
    printf("\n----------Welcome to QQueue Application----------\n");
    printf("App opening...\n");
    do {
        printf("\n----------Menu----------\n");
        printf("1. Enter queue\n");
        printf("2. Use the service\n");
        printf("3. Cancel queue\n");
        printf("4. Show Current Queue\n");
        printf("5. Show All Queues\n");
        printf("6. Check queue\n");
        printf("7. Quit (only for administrator)\n");
        printf("Enter your choice: ");
        scanf("%d", &choiceformenu);
        switch (choiceformenu) {
            case 1:{
                char* data;
                printf("Enter customer name: ");
                scanf("%s", input);
                enqueue(queue, input);
                displayQueue(queue, 0);
                break;
            }
            case 2:{
                char* data = dequeue(queue);
                if (data != NULL) {
                    printf("\n--------Current Customer : %s--------\n", data);
                    money = menu(money, data);
                    displayQueue(queue, 0);
                }
                break;
            }
            case 3:{
                char* data = dequeue(queue);
                displayQueue(queue, 0);
                break;
            }
            case 4:
                displayQueue(queue, 0);
                break;
            case 5:
                displayQueue(queue, 1);
                break;
            case 6:{
                char searchName[20];
                    printf("Enter the name to search: ");
                    scanf("%s", searchName);
                    int SearchQ = search(queue, searchName);
                if (SearchQ != -1) {
                    printf("Customer %s is in the queue.\n", searchName);} 
                else {printf("Customer %s is not in the queue.\n", searchName);}
                break;
                }
            case 7:
                printf("\nWhat is the password: ");
                scanf("%d", &pass);
                if (pass == 123) {
                    printf("\nPassword Correct\nExiting...\n");
                } else {
                    printf("\nPassword wrong\n");
                }
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");}
    } while (pass != 123);

    return 0;
}
