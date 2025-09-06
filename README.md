# Store Inventory System
 > Authors: [Bryan Wong](https://github.com/byranne), [Jonathan Wu](https://github.com/jwu458), [Ryan Yan](https://github.com/kitty1737), [Josh Mena](https://github.com/Jmena023)

## Project Description
Store Inventory System is a program for managing a store. First, the user needs to log in. From then on, program can be divided into two parts - the customer and admin side. Customers are able to search for items and add them to their cart. After they checkout their chart, the store's inventory is updated. Admins are able to add, remove, and edit existing product information. Inventory data is stored in local .json files, allowing inventory changes to be permanent. This program is important because it helps us to practice managing an online store which could be a potential side gig. 

## Languages and Technologies
This project will be a terminal program solely implemented in C++. We will use GitHub to host our repository. We used a popular, external library called [nlohmann/json](https://github.com/nlohmann/json), so that we could work with `.json` files in our program. Finally, we used GoogleTest and Valgrind to test our code. 

## Features

- **Admin**
  - Add new products
  - Restock products
  - Edit existing products' information
  - Print inventory/product info
  - Low Stock warning

- **Customer**
  - Search for items
  - View product info
  - Dynamic checkout cart

**Input**  
The input of the project will mainly be user commands typed into the terminal. The project loads product information from .json files. A json file containing some product information is already provided, but a user could theoretically generate his own and use it on our program.

**Output**  
The output of the project is displayed in the terminal. Product information is saved to .json files when a customer checks out or when a admin changes product information. When user and product information is altered, their data in the corresponding data files will also be altered, ensuring that changes are persistent.

## User Interface Specification

### Navigation Diagram
![image](https://github.com/user-attachments/assets/881bb9a1-eff9-429c-bd2e-9e4fabb16462)



### Screen Layouts
![image](https://github.com/user-attachments/assets/99005aad-b8fc-46c2-a416-74386471cb10)
![image](https://github.com/user-attachments/assets/0b5e3928-82f0-4dfa-bfb7-1e101529738a)

Screen starts giving users 3 options: register store, login, or customer. 
**Customer**
- able to search items
- view best sellers
- view cart

**Store Manager**
- able to add
- able to remove
- update inventory
- view product info
- view best sellers
- view warnings

## Class Diagram
![CS100 Project drawio](https://github.com/user-attachments/assets/e01b5f36-544f-4dc5-b5c3-684b249511dd)

### Changes made following SOLID principles:
1. We decided to split the inventory class into two seperate classes following the single responsiblity principle. The inventory class before was reponsible for too many things, so we created a FileManager class, which handles file related actions, and InventoryManager, which handles all filtering, adding, and removing actions. This helps us to code better because by breaking up the class that had too many reponsiblities it made our code easier to test, maintain, and understand.

2. Making the class function for a login interface follows the open/closed principle. This is because it allows users to create new passwords and logins without changing existing code. It also splits the main interface because it handles only the login part splitting the work load in main following the single responsibly.

We used a main product class and drew several subclasses off of it as a way of implementing Open-Closed principle. This allows us to generally not have to change long if-statements whenever we want to add a new product type. 

![CS100 Project (1) drawio (2)](https://github.com/user-attachments/assets/e9dd5587-5fc1-4be1-ace5-b14c809e7bb8)
 
 ## Screenshots
<table> <tr> <td><img width="240" alt="Screenshot 1" src="https://github.com/user-attachments/assets/e1d37e5e-d609-4f28-8f65-7087aeb9396b" /></td> <td><img width="306" alt="Screenshot 2" src="https://github.com/user-attachments/assets/1c00130d-9876-4e70-9acf-297ba331dd02" /></td> <td><img width="279" alt="Screenshot 3" src="https://github.com/user-attachments/assets/e7d6ade3-072a-4267-91b7-1e64727b8028" /></td> </tr> <tr> <td><img width="312" alt="Screenshot 4" src="https://github.com/user-attachments/assets/13e69f33-cfea-4d52-9207-6d1d7ba38b81" /></td> <td><img width="247" alt="Screenshot 5" src="https://github.com/user-attachments/assets/960341a1-06e6-4a62-958a-2d28901257d8" /></td> <td><img width="322" alt="Screenshot 6" src="https://github.com/user-attachments/assets/06fb426c-f1e6-45f6-bf93-621a37a60873" /></td> </tr> <tr> <td><img width="244" alt="Screenshot 7" src="https://github.com/user-attachments/assets/5693cebb-8c7a-4169-9ae8-fafd87ed8435" /></td> <td><img width="250" alt="Screenshot 8" src="https://github.com/user-attachments/assets/de2f3afa-c804-48ec-9c40-9ea6f966dcbc" /></td> <td><img width="262" alt="Screenshot 9" src="https://github.com/user-attachments/assets/da034a29-0c7c-4840-85da-9837acefb73d" /></td> </tr> <tr> <td colspan="3" align="center"> <img width="341" alt="Screenshot 10" src="https://github.com/user-attachments/assets/18c60c2b-c90c-46cf-b555-23371d560703" /> </td> </tr> </table>

## Installation
### Requirements

- C++ compiler(C++11 or later)
- CMake (version 3.10 or later)

### Steps
1. Clone or download the repository:
   ```bash
   git clone --recursive https://github.com/cs100/final-project-project-group-6.git
   cd final-project-project-group-6
   ```

2. To compile:
   ```bash
   cmake .
   make
   ```

3. Run tests:
   ```bash
   ./bin/test
   ```

4. Run the program:
   ```bash
   ./bin/testLogin
   ```
---

## Usage

As described above, run the main program through "./bin/testLogin" in terminal.

After starting the program, you'll be prompted to log in or register.

You can create new logins for customer by following the prompts on the UI.

The default login for admin is set to:

Username : Admin

Password : 123ABC!@

### Admin Mode
- View product info
- Edit product info (Change details like price)
- Delete product
- Add or restock products
- low-stock warnings (Display items low on stock)

### Customer Mode
- Search and browse products
- View products by its category
- View detailed product info
- Add/remove items from a dynamic shopping cart
- Checkout based on purchase history

The entire interface operates through **terminal input**. Follow the on-screen instructions to navigate through the system.

 ## Testing
We used GoogleTest, a C++ testing framework developed by Google, to write unit tests for our code. This submodule is installed using the recursive flag when cloning the repo. Our unit tests covered the three main vital classes of our program - product, Inventory, and the Cart class. We made sure to use a combination of both ASSERT AND EXPECT in our unit tests with appropriate usage. In many of our functions for our Inventory and Cart classes, we threw exceptions for invalid calls, demonstrating offensive programming. We made sure to test these functions using the EXPECT_THROW test. The code for the tests can be found in test/test.cpp, and the executable created by cmake is can be found at /bin/test. 

We also used Valgrind to check for any memory leaks in our program. We made sure that our destructor for our Inventory was robust, and as a result, we were able to achieve MEMCHECK-CLEAN.


Finally, we tested our program heavily to be able to accept the correct inputs. Here are some examples of the cases we tested and fixed our code to handle - 
1. Admins cannot set the price of a product to a double with 2+ precision points (like 2.449 and 8.1112). This is because obviously there is no such thing as half a cent.
2. Product IDs are only set to ints when an integer is entered. Previously, an input of something like 2.22 was accepted by our program as 2 (obviously fixed).
3. All productIDs inputted by the user are checked to make sure they are valid references before any work is done. 

 
