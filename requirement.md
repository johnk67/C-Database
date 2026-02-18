# Project 2: Inventory Management System

### Introduction

Welcome to OEM parts LLC where we only offer original equipment manufacturer (OEM) replacement car and truck parts direct to our customers, because you deserve the very best! We are not a shade tree knock-off parts retailer.

Over the last few years we have experienced issues of not having an accurate inventory on hand, which leads to confusion and disappointed customers. We manage hundreds of thousands of parts. The first part in solving this problem will be to create a standalone inventory system. We want stand-alone since we currently only manage one location, but may open other locations in the future.

### Intent

The goal of this program is to develop a simple auto parts inventory management system that manages a single store but has the capability of potentially managing additional stores in the event of future growth.

This is a five-day self-paced individual project. You are to do all work on your own, but can reach out to instructors and mentors for guidance.

### Requirements

**User interface shall:**
- Be responsive to user input.  Meaning that a response shall be provided to the user within one second.
- Be from the command line (no GUI).

**User prompts for input shall be:**
- Clear 
- Concise
- Easy to understand what is being asked. 

**Baseline directory tree shall have the minimum file structure relative to project root:**

```
.
├── bin/                    (Compiled executable directory)
│   └── inventory           (Executable file)
├── docs/                   (Project documents directory)
├── include/                (Header file directory)
├── README.md               (User Manual README.md)
├── inventory_data/         (Data file directory)
├── src/                    (Source file directory)
├── tests/                  (Unit testing files/scripts)
└── .gitignore              (git specific file)
```

The `.gitignore` file shall be configured to prevent uploading of data and other non-relevant files.

*This is a baseline directory struture. The user can add directories as needed for thier project. Directories and file names shall be named accordinging and their placement shall be logical and consistent.*

*Similarly, the testing directory structure and file naming is up to the programmer's discretion, although it shall be logical and scalable.*

**Program shall:**

- Run with `./bin/inventory <inventory_data_file>` (if taking in multiple files, specify a directory instead with `-d <directory_path>`)
- Implement make or CMake to build the project the following targets:
    * `all` - builds the complete project
    * `run` - ensure project is built and launch server
    * `test` - ensure project is built and run tests
    * `clean` - removes all build artifacts (leave inventory_data and documents intact)
- Implement all data structures as *abstract data types* such that they accept `void *` as their data type
- Read the full inventory file on program load that is managed in memory (or directory containing files)
- File operations shall have safeguards to prevent partial reading/writing.
- ensure the time complexity of the sorting algorithms utilized must be at most O(n*log n) in worst case.
- Implement `help` so that the user can get help on the entire program or help on a specific function.
- Compile without errors or warnings with `-Wall -Wextra` at minimum.
- Securely handle user input
- Appropriately handle memory without leaks
- Run on Ubuntu 20.04 LTS with no external dependencies.
- Provide an optional way to save and shutdown
- Be compliant with the [BARR-C Embedded Guide](https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf).

**Required Data structures:**

- A hash table shall be implemented for quick lookup of items. It shall utilize [chaining](https://www.geeksforgeeks.org/separate-chaining-collision-handling-technique-in-hashing/) to handle hash collisions.

**Mandatory File structure format:**

- Inventory file contains:
    - Store Address - address where part is located
	- Part name
    - Part description
    - Part ID
	- Price
    - Quantity on hand

Although this program is designed to operate a single store, the store address field is implemented in the event that this store expands to other store locations.

Each inventory record shall be written to the inventory file sequentially in the following format. First, the store address (64 byte padded) is written as a header to the file:

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
- Note: Sample binary files are in this directory for you to use as reference, one for little endian and one for big endian. Below is a markdown table of the sample inventory contents in a human readable format:

| Part Name        | Description                         | Part ID | Price | Quantity |
|------------------|-------------------------------------|---------|-------|----------|
| Transmission     | Automatic transmission for sedan    | 1001    | 1200  | 15       |
| Battery          | 12V car battery                     | 1002    | 150   | 30       |
| Engine           | V6 engine block                     | 1003    | 2500  | 10       |
| Tires            | All-season radial tires             | 1004    | 100   | 50       |
| Lug Nut          | Standard lug nut set                | 1005    | 5     | 200      |
| Muffler          | Stainless steel muffler             | 1006    | 120   | 25       |
| Spark Plug       | High performance spark plug         | 1007    | 10    | 100      |
| Brake Pad        | Front brake pads for sedan          | 1008    | 50    | 40       |
| Air Filter       | Engine air filter                   | 1009    | 15    | 60       |
| Oil Filter       | Synthetic oil filter                | 1010    | 12    | 70       |
| Alternator       | 12V electrical alternator           | 1011    | 200   | 15       |
| Radiator         | Cooling radiator for compact cars   | 1012    | 130   | 20       |
| Fuel Pump        | High-efficiency fuel pump           | 1013    | 180   | 25       |
| Water Pump       | Engine water pump                   | 1014    | 110   | 30       |
| Shock Absorber   | Rear shock absorbers                | 1015    | 85    | 35       |
| Exhaust Pipe     | Stainless steel exhaust pipe        | 1016    | 90    | 20       |
| Windshield Wiper | 22-inch windshield wiper blade      | 1017    | 8     | 150      |
| Headlight Bulb   | LED headlight bulb                  | 1018    | 20    | 50       |
| Tail Light       | Rear tail light assembly            | 1019    | 75    | 30       |
| Car Seat         | Adjustable car seat for sedan       | 1020    | 250   | 10       |
| Steering Wheel   | Leather steering wheel              | 1021    | 100   | 20       |

- Note: Truncated for brevity


### Program Workflow

Program must provide an intuitive menu driven interface. Sub-menus may be used if needed. Also, `help` must be available for a users to get help at any time about program or help on a specific menu-item/function. 

The program shall, at a minimum, provide the ability to perform the following:

- **Add a part** to the store ensuring to obtain all relevant part information. The store address shall be configured in such as way that once a store address is entered (or obtained), then it uses that address for all subsequent part entries. Part names and IDs must be unique.
- **List all parts**
- **Search for a part by Name**
- After search returns a result, the following actions must be available:
    - **Delete a part**
    - **Modify a part** - Quantity, price, or description

All prices shall be displayed with a dollar sign and cents. Examples:  $4.93 $2.00...

## Deliverables

1. Working program that meets the above requirements
2. Utilizes `make` or `cmake` to build project.

## Turn-In Instructions

Your final work should be committed to branch called "develop". When you are ready for turn-in:

1. Create a "merge request" to merge "develop" into "main"
2. Select your instructor or mentor in the "reviewers" drop-down menu
3. Select the merge option: "Delete source branch when merge is accepted"

## Extra Credit

| Extra Credit Items | Point Value | Points Awarded |
| --- | --- | --- |
| Use a signal handler to shutdown gracefully when SIGINT is sent | 1 |  |
| Reads/Writes data to the inventory file(s) in big-endian | 1 |  |
|Add the ability to manage multiple stores. To implement this feature, save the inventory data in a file named by a three digit store ID (i.e. 123), then create a prompt with a list of current stores allow input to select the store to load. Ensure to save the current inventory status before switching stores unless you provide the ability to load multiple stores simultaneously. The directory containing the inventory files should be specified with `-d <directory_path>` | 2 |  |
|Dependent on the previous optional feature of managing multiple stores, provide the ability to move items between stores. This will take a desired quantity from one store and add it to another store. If that item doesn't exist in the target store then that item will be added to the target store with the quantity moved. Implementation will require a menu addition to move items.|2 |  |
|Implement Continuous Integration/Continuous Development (CI/CD) - A `.gitlab-ci.yml` file shall be provided that will perform linting, compilation, memory leak detection (valgrind), and run unit tests. | 2 | |
| A reference manual for maintainers containing documentation for every function, it's parameters, and return values. This should be automatically generated (ex: via `doxygen`) | 1 | | 
