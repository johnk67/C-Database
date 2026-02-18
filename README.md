OEM Parts LLC Inventory Management System User Manual

This program manages an auto parts inventory. The user can provide a binary file containing the inventory data, and the program will organize and manage all the provided parts.

You can build the project using the 'make' command followed by one of the following:

    'all' - compiles all files in the project
    'run' - compiles all files in the project and executes ./bin/inventory inventory_data/little_endian_sample.bin
    'test' - compiles all files in the project and executes ./bin/inventory < tests/test.txt inventory_data/little_endian_sample.bin
    'clean' - removes all build artifacts (leaves inventory_data and documents intact)

If you would like to run the program with a different inventory file than little_endian_sample.bin, you can run the command "./bin/inventory <inventory_data_file>".

When the program executes, it'll read in the provided binary file and store all the individual parts into a hash table. Then, you will be prompted for a command. You can enter "help" to see the full list of commands available:

    'list' - List all the available functions or show details on a specific function.

    'add' - Add a part to the store. After entering the command, the program will prompt you for a part name, description, ID, price, and quantity. Part names and IDs must be unique. The part name and description is limited to 64 characters, and if the provided value is over, it'll be truncated to the 64th character. The price must be entered in cents. The part ID, price, and quantity must all be positive integers under the maximum value for an unsigned int, 4,294,967,295. (i.e. 'Wheel', 'Stainless steel wheel', 1022, 10000, 40)

    'list' - List all the parts in the inventory. The program will then ask whether you want to view the list in alphabetical order by name or numerical order by ID.

    'search' - Search for a part by name or ID. The program will print out the part's details. After search returns a result, the following actions are available: delete, modify, exit.

    'delete' - Delete the retrieved part from the inventory. Once the search function returns a part, you can enter this command to delete the part.

    'modify' - Modify the retrieved part's quantity, price, or description. Once the search function returns a part, you can enter this command to modify it. The program will ask if you want to modify the quantity, price, or description. Once you select a field, the program will prompt you for the new value. The price must be entered in cents. The part ID, price, and quantity must all be positive integers under the maximum value for an unsigned int, 4,294,967,295.

    'exit' - Exit the current function or save the current inventory in little_endian_saved.bin and exit the program.

The inventory data file must be in the following format:

First, the store address (64 byte padded) is written as a header to the file:

```raw
 0                   1                   2                   3  
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                  STORE ADDRESS [64 BYTES NULL PADDED]         +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

Afterwards, each part will follow this pattern, for as many parts that are in the file:

```raw
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                     PART NAME [64 BYTES NULL PADDED]          +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+               PART DESCRIPTION [64 BYTES NULL PADDED]         +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    PART_ID [4 BYTES UNSIGNED]                 |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    PRICE [4 BYTES UNSIGNED]                   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                   QUANTITY [4 BYTES UNSIGNED]                 |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                 (REPEAT ITEMS AS NECESSARY...)                +
|                                                               |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
- Price field is in cents
- Note: All values are assumed to be in host-endian (Little-endian for most modern computers).

The data structure containing the parts is a hash table of linked lists. The hash function is simply the modulus of the part ID and the table size. If a collision occurs during insertion, the new part will be inserted to the end of the linked list located at the hash node.

When you exit the program, it'll automatically write the current inventory to little_endian_saved_bin in the same format as shown above.