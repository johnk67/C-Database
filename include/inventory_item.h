#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Inventory item structure contains part details.
struct inventory_item
{
    char name[64];
    char description[64];
    unsigned int id;
    unsigned int price;
    unsigned int quantity;
    char store_address[64];
};
typedef struct inventory_item inventory_item;

inventory_item create_item(char name[], char description[], int part_id, int price, int quantity, char store_address[]);
void details(inventory_item * p_item);
void set_addr(inventory_item * p_item, char addr[]);
void modify_quantity(inventory_item * p_item, int amt);
void modify_price(inventory_item * p_item, int amt);
void modify_description(inventory_item * p_item, char str[]);


#endif
