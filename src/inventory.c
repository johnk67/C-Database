// This program develops a simple auto parts inventory management system that
// manages a single store but has the capability of potentially managing
// additional stores in the event of future growth.

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "../include/hash_table.h"
#include "../include/linked_list.h"
#include "../include/inventory_item.h"
#include "../include/helper_functions.h"

int main(int argc, char * argv[])
{
    // Declare constants.
    const int TABLE_SIZE = 100;
    const int MAX_LENGTH = 64;

    // Initialize variables.
    FILE * p_in;
    FILE * p_out;
    int loc = 0;
    char input[MAX_LENGTH];
    char part_name[MAX_LENGTH];
    char part_description[MAX_LENGTH];
    unsigned int part_id;
    unsigned int part_quantity;
    long part_price;
    char store_addr[MAX_LENGTH];
    hash_table * p_inventory = create_table(TABLE_SIZE);
    inventory_item * p_new_items = malloc(sizeof(inventory_item));
    inventory_item * p_part = malloc(sizeof(inventory_item));

    // Check if inventory data file is passed as a command line  argument.
    if (1 == argc)
    {
        perror("Pass inventory data file as a command line argument.\n");
    }

    // Open binary inventory data file to read.
    p_in = fopen(argv[1], "rb");
    if (NULL == p_in)
    {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    // Store the first 64 bytes of the file as the store address.
    if (64 > fread(store_addr, sizeof(char), 64, p_in))
    {
        perror("File has no header.");
        exit(EXIT_FAILURE);
    }

    // Read in file to an array of inventory_item structs.
    while (fread(&p_new_items[loc], sizeof(inventory_item) - 64, 1, p_in))
    {
        // Set the store address to the address at the file header.
        set_addr(&p_new_items[loc], store_addr);
        // Convert the price to cents.
        modify_price(&p_new_items[loc], (&p_new_items[loc])->price * 100);
        // Insert part into hash table.
        insert(p_inventory, &p_new_items[loc]);
        loc += sizeof(inventory_item);
    }

    // Close file.
    fclose(p_in);

    printf("\nWelcome to OEM parts LLC's inventory management system. How many I help you today?\n");
    // Prompt user for a command.
    printf("Enter a command (Enter 'help' to see all commands): ");
    fgets(input, MAX_LENGTH, stdin);
    // Check if newline is in input.
    if(!strchr(input, '\n'))
    {
        // Clear up to newline.
        scanf("%*[^\n]");
        scanf("%*c");
    }
    // Remove trailing newline character.
    input[strcspn(input, "\n")] = 0;

    // Continue prompting user for commands until "exit" is entered.
    while (strcmp(input, "exit"))
    {
        // "help" displays help information on the entire program or a specific function.
        if (!strcmp(input, "help"))
        {       
            while (1)
            {
                // Prompt user for a specific command.
                printf("Enter a specific command or press \'enter\' to get help on the entire program: ");
                fgets(input, MAX_LENGTH, stdin);

                // Print out help information based on user's input. 
                if (!print_help(input))
                {
                    printf("Command does not exist.\n");
                }
                else
                {
                    break;
                }
            }
        }

        // "list" prints out all the part names in the inventory.
        else if (!strcmp(input, "list"))
        {
            while (1)
            {
                // Ask user if list should be printed in alphabetical order or in part ID order.
                printf("Sort by \'name\' or \'id\': ");
                fgets(input, MAX_LENGTH, stdin);
                // Check if newline is in input.
                if(!strchr(input, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                input[strcspn(input, "\n")] = 0;

                // Print out help information based on user's input. 
                if (!strcmp(input, "name"))
                {
                    list_by_name(p_inventory);
                    break;
                }
                else if (!strcmp(input, "id"))
                {
                    list_by_id(p_inventory);
                    break;
                }
            }
        }

        // "add" adds a new part to the inventory.
        else if (!strcmp(input, "add"))
        {
            while (1)
            {
                // Prompt user for a part name.
                printf("Enter new part name: ");
                fgets(part_name, MAX_LENGTH, stdin);
                // Check if newline is in part_name.
                if(!strchr(part_name, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                part_name[strcspn(part_name, "\n")] = 0;

                // Check if part name is already in use.
                if (64 < strlen(part_name))
                {
                    printf("Part name is limited to 64 characters.\n");
                }
                else if (search_by_name(p_inventory, part_name))
                {
                    printf("Part name already in use.\n");
                }
                else
                {
                    break;
                }
            }

            // Prompt user for a part description.
            printf("Enter new part description: ");
            fgets(part_description, MAX_LENGTH, stdin);
            // Check if newline is in part_description.
            if(!strchr(part_description, '\n'))
            {
                // Clear up to newline.
                scanf("%*[^\n]");
                scanf("%*c");
            }
            // Remove trailing newline character.
            part_description[strcspn(part_description, "\n")] = 0;

            while (1)
            {
                // Prompt user for the part id.
                printf("Enter new part ID: ");
                fgets(input, MAX_LENGTH, stdin);
                // Check if newline is in input.
                if(!strchr(input, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                input[strcspn(input, "\n")] = 0;

                // Check if input is a valid unsigned integer.
                part_id = check_uint(input);
                if (part_id)
                {
                    // Check if part ID is already in use.
                    if (!search_by_id(p_inventory, part_id))
                    {
                        break;
                    }
                    printf("Part ID already in use.\n");
                }
                else
                {
                    printf("Enter a positive integer under %u.\n", UINT_MAX);
                }
                
            }

            while (1)
            {
                // Prompt user for the part price.
                printf("Enter new part price in cents: ");
                fgets(input, MAX_LENGTH, stdin);
                // Check if newline is in input.
                if(!strchr(input, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                input[strcspn(input, "\n")] = 0;

                // Check if input is a valid unsigned integer.
                part_price = check_uint(input);
                if (part_price)
                {
                    break;
                }
                printf("Enter a positive integer under %u.\n", UINT_MAX);
            }


            while (1)
            {
                // Prompt user for the part quantity.
                printf("Enter new part quantity: ");
                fgets(input, MAX_LENGTH, stdin);
                // Check if newline is in input.
                if(!strchr(input, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                input[strcspn(input, "\n")] = 0;

                // Check if input is a valid unsigned integer.
                part_quantity = check_uint(input);
                if (part_quantity)
                {
                    break;
                }
                printf("Enter a positive integer under %u.\n", UINT_MAX);
            }

            p_new_items[loc] = create_item(part_name, part_description, part_id, part_price, part_quantity, store_addr);
            insert(p_inventory, &p_new_items[loc]);
            loc += sizeof(inventory_item);
            printf("Added %s to the inventory.\n\n", part_name);
        }

        // "search" returns the details of a part given its name.
        else if (!strcmp(input, "search"))
        {
            // Prompt user for the part name.
            printf("Enter a part name or ID: ");
            fgets(input, MAX_LENGTH, stdin);
            // Check if newline is in input.
            if(!strchr(input, '\n'))
            {
                // Clear up to newline.
                scanf("%*[^\n]");
                scanf("%*c");
            }
            // Remove trailing newline character.
            input[strcspn(input, "\n")] = 0;

            cllist * part_node = malloc(sizeof(cllist));

            // Check if input is a valid unsigned integer.
            part_id = check_uint(input);

            // Get part if the input is an ID
            if (part_id)
            {
                part_node = (cllist *) search_by_id(p_inventory, part_id);
            }
            // Get part if the input is a name.
            else
            {
                strcpy(part_name, input);
                part_node = (cllist *) search_by_name(p_inventory, part_name);
            }

            if (part_node)
            {
                p_part = (inventory_item *) part_node->data;

                // Print out the part details.
                details(p_part);
            }

            while (1)
            {
                // Break out of the loop is part does not exist.
                if (!part_node)
                {
                    printf("\nPart not found.\n\n");
                    break;
                }

                // Ask user if they want to modify or delete the part.
                printf("Enter 'delete', 'modify', or 'exit': ");
                fgets(input, MAX_LENGTH, stdin);
                // Check if newline is in input.
                if(!strchr(input, '\n'))
                {
                    // Clear up to newline.
                    scanf("%*[^\n]");
                    scanf("%*c");
                }
                // Remove trailing newline character.
                input[strcspn(input, "\n")] = 0;

                if (!strcmp(input, "exit"))
                {
                    break;
                }
                
                // Delete the part from the inventory.
                else if (!strcmp(input, "delete"))
                {
                    if (part_id)
                    {
                        delete_by_id(p_inventory, part_id);
                        printf("Part %d removed from inventory.\n\n", part_id);
                    }
                    else
                    {
                        delete_by_name(p_inventory, part_name);
                        printf("%s removed from inventory.\n\n", part_name);
                    }
                    break;
                }

                // Modify the part.
                else if (!strcmp(input, "modify"))
                {
                    while (1)
                    {
                        // Prompt the user for what they want to modify.
                        printf("Enter 'quantity', 'price', 'description', or 'exit': ");
                        fgets(input, MAX_LENGTH, stdin);
                        // Check if newline is in input.
                        if(!strchr(input, '\n'))
                        {
                            // Clear up to newline.
                            scanf("%*[^\n]");
                            scanf("%*c");
                        }
                        // Remove trailing newline character.
                        input[strcspn(input, "\n")] = 0;

                        if (!strcmp(input, "exit"))
                        {
                            break;
                        }

                        // Modify the part quantity.
                        else if (!strcmp(input, "quantity"))
                        {
                            while (1)
                            {
                                // Prompt the user for the new quantity.
                                printf("Enter the new quantity: ");
                                fgets(input, MAX_LENGTH, stdin);
                                // Check if newline is in input.
                                if(!strchr(input, '\n'))
                                {
                                    // Clear up to newline.
                                    scanf("%*[^\n]");
                                    scanf("%*c");
                                }
                                // Remove trailing newline character.
                                input[strcspn(input, "\n")] = 0;

                                // Check if input is a valid unsigned integer.
                                part_quantity = check_uint(input);
                                if (part_quantity)
                                {
                                    break;
                                }
                                printf("Enter a positive integer under %u.\n", UINT_MAX);
                            }

                            // Change the part's quantity field.
                            printf("\n%s quantity changed from %d to %d.\n\n", p_part->name, p_part->quantity, part_quantity);
                            modify_quantity(p_part, part_quantity);
                            break;
                        }

                        // Modify the part price.
                        else if (!strcmp(input, "price"))
                        {
                            while (1)
                            {
                                // Prompt the user for the new price.
                                printf("Enter the new price in cents: ");
                                fgets(input, MAX_LENGTH, stdin);
                                // Check if newline is in input.
                                if(!strchr(input, '\n'))
                                {
                                    // Clear up to newline.
                                    scanf("%*[^\n]");
                                    scanf("%*c");
                                }
                                // Remove trailing newline character.
                                input[strcspn(input, "\n")] = 0;

                                // Check if input is a valid unsigned integer.
                                part_price = check_uint(input);
                                if (part_price)
                                {
                                    break;
                                }
                                printf("Enter a positive integer under %u.\n", UINT_MAX);
                            }

                            // Change the part's price field.
                            printf("\n%s price changed to from $%.2f to $%.2f.\n\n", p_part->name, p_part->price / 100.0, part_price / 100.0);
                            modify_price(p_part, part_price);
                            break;
                        }

                        // Modify the part description.
                        else if (!strcmp(input, "description"))
                        {
                            // Prompt the user for the new description.
                            printf("Enter the new description: ");
                            fgets(part_description, MAX_LENGTH, stdin);
                            // Check if newline is in part_description.
                            if(!strchr(part_description, '\n'))
                            {
                                // Clear up to newline.
                                scanf("%*[^\n]");
                                scanf("%*c");
                            }
                            // Remove trailing newline character.
                            part_description[strcspn(part_description, "\n")] = 0;

                            // Change the part's description field.
                            printf("\n%s description changed from \"%s\" to \"%s\".\n\n", p_part->name, p_part->description, part_description);
                            modify_description(p_part, part_description);
                            break;
                        }

                        printf("Invalid command. Try again.\n\n");
                    }
                }

                else
                {
                    printf("Invalid command. Try again.\n\n");
                }
            }
        }
        
        else
        {
            printf("Invalid command. Try again.\n\n");
        }

        // Reprompt user for command.
        printf("Enter a command: ");
        fgets(input, MAX_LENGTH, stdin);
        // Check if newline is in input.
        if(!strchr(input, '\n'))
        {
            // Clear up to newline.
            scanf("%*[^\n]");
            scanf("%*c");
        }
        // Remove trailing newline character.
        input[strcspn(input, "\n")] = 0;
    }

    // Open binary inventory data file to write.
    p_out = fopen("inventory_data/little_endian_saved.bin", "wb");
    if (NULL == p_out)
    {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    // Store the first 64 bytes of the file as the store address.
    fwrite(store_addr, sizeof(char), 64, p_out);

    // Iterate through the inventory hash table.
    for (int i = 0; i < p_inventory->size; i++)
    {
        if (p_inventory->nodes[i])
        {
            cllist * list = (cllist *) p_inventory->nodes[i]->value;
            cllist * temp = list;
            do
            {
                // Convert the price to cents.
                modify_price((inventory_item *) temp->data, ((inventory_item *) temp->data)->price / 100);
                // Write part to the output file.
                fwrite((inventory_item *) temp->data, sizeof(inventory_item) - 64, 1, p_out);
                temp = temp->next;
            } while (temp != list);
        }
    }

    // Clear memory.
    fclose(p_out);
    free(p_new_items);
    free(p_part);
    delete_all(p_inventory);
}

/*** end of file ***/
