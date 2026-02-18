#include "../include/inventory_item.h"

inventory_item create_item(char name[], char description[], int part_id, int price, int quantity, char store_address[])
{
    inventory_item * p_item = malloc(sizeof(inventory_item));
    strcpy(p_item->name, name);
    strcpy(p_item->description, description);
    p_item->id = part_id;
    p_item->price = price;
    p_item->quantity = quantity;
    strcpy(p_item->store_address, store_address);

    return * p_item;
}

// Display inventory item details.
void details(inventory_item * p_item)
{
    printf("\nPart Name = %s\nDescription = %s\nID = %u\nPrice = $%.2f\nQuantity = %u\nStore Address = %s\n\n", p_item->name, p_item->description, p_item->id, p_item->price / 100.0, p_item->quantity, p_item->store_address);
}

// Set the store address.
void set_addr(inventory_item * p_item, char addr[])
{
    strcpy(p_item->store_address, addr);
}

// Modify the part quantity.
void modify_quantity(inventory_item * p_item, int amt)
{
    p_item->quantity = amt;
}

// Modify the part price.
void modify_price(inventory_item * p_item, int amt)
{
    p_item->price = amt;
}

// Modify the part description.
void modify_description(inventory_item * p_item, char str[])
{
    strcpy(p_item->description, str);
}
