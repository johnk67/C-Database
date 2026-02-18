#include "../include/helper_functions.h"

// Print out help information based on the user's input. Return 1 if the command exists and 0 if not.
int print_help(char input[])
{
    int ret = 0;
    char command_details[7][1024] =
    {
        "\n\'help\'\nList all the available functions or show details on a specific function.\n",
        "\n\'add\'\nAdd a part to the store. After entering the command, the program will prompt you for a part name, description, ID, price, and quantity. Part names and IDs must be unique. The price must be entered in cents. The part ID, price, and quantity must all be positive integers under the maximum value for an unsigned int, 4,294,967,295. (i.e. \'Wheel\', \'Stainless steel wheel\', 1022, 100, 40)\n",
        "\n\'list\'\nList all the parts in the inventory in alphabetical order by name or numerical order by ID.\n",
        "\n\'search\'\nSearch for a part by name or ID. The program will print out the part's details. After search returns a result, the following actions are available: delete, modify, exit.\n",
        "\n\'delete\'\nDelete the retrieved part from the inventory. Once the search function returns a part, you can enter this command to delete the part.\n",
        "\n\'modify\'\nModify the retrieved part's quantity, price, or description. Once the search function returns a part, you can enter this command to modify it. The program will ask if you want to modify the quantity, price, or description. Once you select a field, the program will prompt you for the new value. The price must be entered in cents. The part ID, price, and quantity must all be positive integers under the maximum value for an unsigned int, 4,294,967,295.\n",
        "\n\'exit\'\nExit the current function or save the current inventory in little_endian_saved.bin and exit the program.\n"
    };

    // Print out help information for the entire program.
    if (!strcmp(input, "\n"))
    {
        printf("%s\n", "\nThe following functions are available:\n"
                        "\tadd - add a part\n"
                        "\tlist - list all parts\n"
                        "\tsearch - search for a part\n"
                        "\tdelete - delete a part\n"
                        "\tmodify - modify a part\n"
                        "\texit - exit the program\n"
                        "Use \'help\' to get help on a specific function.\n");
        ret = 1;
    }
    // Remove trailing newline character.
    input[strcspn(input, "\n")] = 0;

    // Print out help information for corresponding function.
    if (!strcmp(input, "help"))
    {
        printf("%s\n", command_details[0]);
        ret = 1;
    }
    else if (!strcmp(input, "add"))
    {
        printf("%s\n", command_details[1]);
        ret = 1;
    }
    else if (!strcmp(input, "list"))
    {
        printf("%s\n", command_details[2]);
        ret = 1;
    }
    else if (!strcmp(input, "search"))
    {
        printf("%s\n", command_details[3]);
        ret = 1;
    }
    else if (!strcmp(input, "delete"))
    {
        printf("%s\n", command_details[4]);
        ret = 1;
    }
    else if (!strcmp(input, "modify"))
    {
        printf("%s\n", command_details[5]);
        ret = 1;
    }
    else if (!strcmp(input, "exit"))
    {
        printf("%s\n", command_details[6]);
        ret = 1;
    }

    return ret;
}

// Check if the string is a valid unsigned integer. Return the number if the string is a valid number and 0 if not.
long check_uint(char str[])
{
    long ret = 0;
    long num;
    char * input = str;

    // Convert input string to a long integer.
    num = strtol(input, &input, 10);

    // Check for any non-numeric characters.
    if ('\0' == * input && 10 >= strlen(input))
    {
        // Check if number is between 0 and INT_MAX.
        if (0 <= num && UINT_MAX >= num)
        {
            ret = num;
        }
    }

    return ret;
}

// Clear the input buffer.
void clear_buffer(char * p_input[])
{
    // Check if newline is in part_name.
    if(!strchr(* p_input, '\n'))
    {
        // Clear up to newline.
        scanf("%*[^\n]");
        scanf("%*c");
    }
    // Remove trailing newline character.
    p_input[strcspn(* p_input, "\n")] = 0;
}