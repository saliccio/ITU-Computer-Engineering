#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NO_OF_PRODUCTS 5
#define NO_OF_CUSTOMERS 3

typedef struct Product {
    pthread_mutex_t mutex;

    int product_ID;
    double product_Price;
    int product_Quantity;
} Product;

typedef struct Customer {
    int customer_ID;
    double customer_Balance;
    
    int ordered_Items[NO_OF_PRODUCTS];

    int purchased_Items[NO_OF_PRODUCTS];
} Customer;

typedef struct OrderData {
    int product_ID;
    int quantity;
} OrderData;

void order_product(int, int, int);
void order_products(int, OrderData*, int);

Customer customer_Arr[NO_OF_CUSTOMERS];
Product product_Arr[NO_OF_PRODUCTS];

void order_products(int customer_ID, OrderData* order_Arr, int product_Count) {
    for (int i = 0; i < product_Count; i++) {
        Product* product_Ptr = &product_Arr[order_Arr[i].product_ID];
        customer_Arr[customer_ID].ordered_Items[product_Ptr->product_ID] += order_Arr[i].quantity;
        if (customer_Arr[customer_ID].customer_Balance < order_Arr[i].quantity * product_Ptr->product_Price) {
            printf("Customer%d(%d,%d) fail! Insufficient funds.\n", customer_ID + 1, product_Ptr->product_ID + 1, order_Arr[i].quantity);
        } else if (product_Ptr->product_Quantity < order_Arr[i].quantity) {
            printf("Customer%d(%d,%d) fail! Only %d left in stock.\n", customer_ID + 1, product_Ptr->product_ID + 1, order_Arr[i].quantity, product_Ptr->product_Quantity);
        } else {
            order_product(customer_ID, order_Arr[i].product_ID, order_Arr[i].quantity);
        }
    }
}

void order_product(int customer_ID, int product_ID, int quantity) {
    Product* product_Ptr = &product_Arr[product_ID];
    pthread_mutex_lock(&product_Ptr->mutex);
    Customer* customer_Ptr = &customer_Arr[customer_ID];

    int product_Quantity = product_Ptr->product_Quantity;
    double product_Price = product_Ptr->product_Price;
    if (quantity > product_Quantity) {
        printf("Customer%d(%d,%d) fail! Only %d left in stock.\n", customer_ID + 1, product_ID + 1, quantity, product_Quantity);
    } else if (quantity * product_Price > customer_Ptr->customer_Balance) {
        printf("Customer%d(%d,%d) fail! Insufficient funds.\n", customer_ID + 1, product_ID + 1, quantity);
    } else {
        /*printf("Customer %d:\nInitial Products:\nProduct ID\tQuantity\tPrice\n", customer_ID + 1);
        for(int i = 0; i < NO_OF_PRODUCTS; i++) {
            printf("%d\t\t%d\t\t%f\n", i + 1, product_Ptr->product_Quantity, product_Ptr->product_Price);
        }
        printf("Bought %d of product %d for $%f\n\n", quantity, product_ID + 1, quantity * product_Price);*/

        customer_Ptr->customer_Balance -= quantity * product_Price;
        customer_Ptr->purchased_Items[product_ID] += quantity;
        product_Ptr->product_Quantity -= quantity;

        /*printf("Updated Products:\nProduct ID\tQuantity\tPrice\n");
        for(int i = 0; i < NO_OF_PRODUCTS; i++) {
            printf("%d\t\t%d\t\t%f\n", i + 1, product_Ptr->product_Quantity, product_Ptr->product_Price);
        }*/
    }
    pthread_mutex_unlock(&product_Ptr->mutex);
}

void give_random_order(int customer_ID) {
    int scenario = rand() % 10;
    int ordered_Product_Count = scenario == 0 ? 1 : 2 + (rand() % 5);
    if (scenario == 0) {
        int random_Product_ID = rand() % NO_OF_PRODUCTS;
        int random_Quantity = 1 + rand() % 5;
        order_product(customer_ID, random_Product_ID, random_Quantity);
    } else {
        OrderData* order_Data = malloc(sizeof(order_Data) * ordered_Product_Count);
        for (int j = 0; j < ordered_Product_Count; j++) {
            order_Data[j].product_ID = rand() % NO_OF_PRODUCTS;
            order_Data[j].quantity = 1 + rand() % 5;
        }
        order_products(customer_ID, order_Data, ordered_Product_Count);
        free(order_Data);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    double customer_Start_Balances[NO_OF_CUSTOMERS];
    for (int i = 0; i < NO_OF_CUSTOMERS; i++) {  // Initialize customers
        double balance = 1.0 + ((double)rand() / (double)RAND_MAX) * 199.0;
        customer_Start_Balances[i] = balance;
        customer_Arr[i].customer_Balance = balance;
        customer_Arr[i].customer_ID = i;
    }

    printf("Product ID\tQuantity\tPrice\n");
    for (int i = 0; i < NO_OF_PRODUCTS; i++) {  // Initialize products
        pthread_mutex_init(&product_Arr[i].mutex, NULL);
        product_Arr[i].product_ID = i;
        product_Arr[i].product_Price = 1.0 + ((double)rand() / (double)RAND_MAX) * 199.0;
        product_Arr[i].product_Quantity = 1 + (rand() % 10);
        printf("%d\t\t%d\t\t%.2f\n", i + 1, product_Arr[i].product_Quantity, product_Arr[i].product_Price);
    }

    pthread_t customer_Threads[NO_OF_CUSTOMERS];
    for (int i = 0; i < NO_OF_CUSTOMERS; i++) {
        pthread_create(&customer_Threads[i], NULL, (void*)give_random_order, (void*) i);
    }

    for (int i = 0; i < NO_OF_CUSTOMERS; i++) {
        pthread_join(customer_Threads[i], NULL);
    }

    for (int i = 0; i < NO_OF_CUSTOMERS; i++) {
        printf("Customer%d----------\nInitial balance: $%.2f\nUpdated balance: $%.2f\nOrdered products:\nID\tQuantity\n", i + 1, customer_Start_Balances[i], customer_Arr[i].customer_Balance);
        for (int j = 0; j < NO_OF_PRODUCTS; j++) {
            int customer_Order_Count = customer_Arr[i].ordered_Items[j];
            if (customer_Order_Count > 0) {
                printf("%d\t\t%d\n", j + 1, customer_Order_Count);
            }
        }
        printf("Purchased products:\nID\tQuantity\n");
        for (int j = 0; j < NO_OF_PRODUCTS; j++) {
            int customer_Purchase_Count = customer_Arr[i].purchased_Items[j];
            if (customer_Purchase_Count > 0) {
                printf("%d\t\t%d\n", j + 1, customer_Purchase_Count);
            }
        }
    }

    return 0;
}