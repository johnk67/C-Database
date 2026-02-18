# Inventory Management System Student Rubric

Specific Implementation Standards
| Requirement | Point Value | Score | Comments |
| -- | --- | --- | --- |
| Functional and Interactive Terminal | 10 | | |
| Create Items | 6 | | |
| List Items: in alphabetical order | 4 | | |
| List Items: in part ID order | 4 | | |
| Search Items: by name or part ID | 6 | | |
| Update Items: quantity, price, description | 6 | | |
| Delete Items | 4 | | |
| Properly Read Inventory State File | 6 | | |
| Properly Write Inventory State File | 6 | | |
| Properly uses Abstract Data Types | 4 | | |
| Properly hashes and stores items | 4 | | |
| Subtotal | 60 | | |

General Implementation Standards
| Requirement | Point Value | Score | Comments | 
| --- | --- | --- | --- |
| Memory management | 10 | | |
| Follows styleguide(s) | 5 | | |
| Follows required directory structure | 2 | | |
| builds without warnings | 3 | | |
| Discretionary points | 10 | | |
| Documentation on all functions, enums, structures, and defines | 5 | | |
| User Manual / README (to include compilation steps) | 3 | | |
| Design Document | 2 | | |
| Subtotal | 40 | | |


| Base Score | Points Possible |
| --- | --- |
| __ | 100

| Extra Credit Items | Point Value | Score |
| --- | --- | --- |
| Use a signal handler to shutdown gracefully when SIGINT is sent | 1 | |
| Reads/Writes data to the inventory file(s) in big-endian | 1 | |
|Add the ability to manage multiple stores. To implement this feature, save the inventory data in a file named by a three digit store ID (i.e. 123), then create a prompt with a list of current stores allow input to select the store to load. Ensure to save the current inventory status before switching stores unless you provide the ability to load multiple stores simultaneously.| 2 | |
|Dependent on the previous optional feature of managing multiple stores, provide the ability to move items between stores. This will take a desired quantity from one store and add it to another store. If that item doesn't exist in the target store then that item will be added to the target store with the quantity moved. Implementation will require a menu addition to move items.| 2 | |
|Implement Continuous Integration/Continuous Development (CI/CD) - A `.gitlab-ci.yml` file shall be provided that will perform linting, compilation, memory leak detection (valgrind), and run unit tests. | 2 | |
| A reference manual for maintainers containing documentation for every function, it's parameters, and return values. | 1 | |
| Subtotal | 9 | __ |
 
**FINAL SCORE:** ____

**FINAL COMMENTS:** ____
