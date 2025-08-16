Bil Buddy
 Bil Spliting Application
Problem 
Statement
 The "Bill Buddy" app is a group expense
 management tool designed to simplify bill
 splitting. Users can create accounts, form
 groups for specific trips or events, add expenses,
 and track who paid for what. The app calculates
 how much each participant owes and allows
 users to settle balances directly, ensuring clear
 and organized expense tracking.
C++ Libraries used
 <iostream>
 <string>
 <vector>
 <fstream>
OOC Concepts 
used
 Encapsulation
 Data and functions related to
 a specific entity are bundled
 together. For example, the
 UserAccount class
 encapsulates user-related
 functionality like account
 creation and login.
 Polymorphism
 Inheritance
 Using runtime polymorphism
 with base classes for
 different item types (e.g.,
 BaseItem, FoodItem,
 DrinkItem).
 Although inheritance is not
 used directly in this example,
 it can be considered for
 future extensions, where
 different types of users (e.g.,
 admin users)
 Abstraction
 Complex functionalities like adding
 an expense, creating a group, or
 settling expenses are abstracted
 into high-level methods. The user
 interacts with these methods
 without worrying about the 
underlying complexity 
OOC Concepts 
used
 Composition 
Composing the BillSplitter
 class with Item and
 Participant objects.
 Overloading
 Exception Handling
 Overloading functions and
 operators to handle various
 input types and simplify
 operations
 The code uses a try-catch
 block to handle potential
 exceptions during the login
 process .
Tasks performed 
1. Creating account
 2. Login 
3. Create group
 4. Switch group 
5. Add expenses 
6. View group expenses 
7. Settling expenses 
8. Display total owed









conclusion
 The "Bill Buddy" project successfully demonstrates the application of key Object
Oriented Concepts (OOC) to solve the problem of splitting bills among a group. The
 app's design, using C++ libraries, emphasizes encapsulation, polymorphism,
 inheritance, abstraction, composition, and exception handling. By encapsulating
 user-related functionality and employing polymorphism for various item types, the
 application simplifies complex processes like managing group expenses. The ability
 to create accounts, add expenses, and settle balances efficiently demonstrates the
 project’s practical functionality, showing how OOC principles can be effectively
 implemented in a real-world scenario. 
Thank you
