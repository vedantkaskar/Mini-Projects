#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Structure for storing user data
struct User
{
    int userId;
    string name;
    string email;
    string password; // Added password for each user
};

// Structure for storing expense data
struct Expense
{
    string description;
    double amount;
    int payerId;              // User ID of the person who paid
    vector<int> participants; // User IDs of the participants
};

// Structure for storing group data
struct Group
{
    string groupName;
    vector<Expense> expenses; // Expenses associated with the group
};

// Class for managing user accounts
class UserAccount
{
    vector<User> users;

public:
    void createAccount()
    {
        string name, email, password;
        cout << "\nEnter your name: ";
        cin >> name;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter a password: ";
        cin >> password;

        if (name.empty() || email.empty() || password.empty())
        {
            cout << "Name, email, and password cannot be empty. Please try again." << endl;
            return;
        }

        int userId = users.size() + 1;
        User newUser = {userId, name, email, password};
        users.push_back(newUser);

        cout << "Account created! User ID: " << userId << endl;
    }

    int login()
    {
        string email, password;
        cout << "Enter your email to login: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;

        for (int i = 0; i < users.size(); i++)
        {
            try // Try-catch block for password checking
            {
                if (users[i].email == email && users[i].password == password)
                {
                    cout << "Welcome, " << users[i].name << "!" << endl;
                    return i;
                }
            }
            catch (const std::exception &e)
            {
                cout << "Login failed. Incorrect email or password." << endl;
                return -1; // Returning -1 in case of an error
            }
        }
        cout << "Login failed. Incorrect email or password." << endl;
        return -1;
    }

    vector<User> &getUsers()
    {
        return users;
    }
};

// Class for managing groups and expenses
class ExpenseManager
{
    vector<Group> groups;
    int currentGroupIndex;

public:
    ExpenseManager()
    {
        currentGroupIndex = -1;
    }

    void createGroup()
    {
        string groupName;
        cout << "Enter group name: ";
        cin >> groupName;

        Group newGroup;
        newGroup.groupName = groupName;
        groups.push_back(newGroup);
        currentGroupIndex = groups.size() - 1;

        cout << "Group '" << groupName << "' created and activated." << endl;
    }

    void switchGroup()
    {
        cout << "Available Groups: " << endl;
        for (int i = 0; i < groups.size(); ++i)
        {
            cout << i + 1 << ". " << groups[i].groupName << endl;
        }
        int choice;
        cout << "Select a group number to switch to: ";
        cin >> choice;

        if (choice > 0 && choice <= groups.size())
        {
            currentGroupIndex = choice - 1;
            cout << "Switched to group: " << groups[currentGroupIndex].groupName << endl;
        }
        else
        {
            cout << "Invalid group selection." << endl;
        }
    }

    void addExpense(vector<User> &users)
    {
        if (currentGroupIndex == -1)
        {
            cout << "No active group. Please create or switch to a group." << endl;
            return;
        }

        string description;
        double amount;
        int numParticipants;
        vector<int> participants;

        cout << "Enter expense description: ";
        cin >> description;

        if (description.empty())
        {
            cout << "Description cannot be empty. Please try again." << endl;
            return;
        }

        cout << "Enter amount: ";
        cin >> amount;
        if (cin.fail() || amount <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid amount. Please enter a positive value." << endl;
            return;
        }

        cout << "Enter number of participants: ";
        cin >> numParticipants;
        if (cin.fail() || numParticipants <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid number of participants. Please enter a positive value." << endl;
            return;
        }

        // Input participant IDs
        for (int i = 0; i < numParticipants; i++)
        {
            int userId;
            cout << "Enter participant User ID: ";
            cin >> userId;

            if (userId > 0 && userId <= users.size())
            {
                participants.push_back(userId);
            }
            else
            {
                cout << "Invalid User ID: " << userId << ". Please enter a valid ID." << endl;
                --i;
            }
        }

        int payerId;
        cout << "Enter the User ID of the payer: ";
        cin >> payerId;

        if (payerId > 0 && payerId <= users.size())
        {
            Expense newExpense = {description, amount, payerId, participants};
            groups[currentGroupIndex].expenses.push_back(newExpense);

            ofstream outFile(groups[currentGroupIndex].groupName + ".txt", ios::app);
            if (outFile)
            {
                outFile << "Description: " << description << ", Amount: " << amount
                        << ", Payer ID: " << payerId << "\nParticipants: ";
                for (int i = 0; i < participants.size(); ++i)
                {
                    outFile << participants[i] << " ";
                }
                outFile << "\n\n";
                outFile.close();
                cout << "Expense added: " << description << " of amount " << amount << endl;
            }
            else
            {
                cout << "Error opening file for writing." << endl;
            }
        }
        else
        {
            cout << "Invalid User ID for the payer." << endl;
        }
    }

    void viewGroupExpenses()
    {
        if (currentGroupIndex == -1)
        {
            cout << "No active group. Please create or switch to a group." << endl;
            return;
        }

        cout << "Expenses for group: " << groups[currentGroupIndex].groupName << endl;

        ifstream inFile(groups[currentGroupIndex].groupName + ".txt");
        if (inFile)
        {
            string line;
            while (getline(inFile, line))
            {
                cout << line << endl;
            }
            inFile.close();
        }
        else
        {
            cout << "Error opening file for reading. No expenses recorded yet." << endl;
        }
    }

    void settleExpenses(vector<User> &users)
    {
        if (currentGroupIndex == -1)
        {
            cout << "No active group. Please create or switch to a group." << endl;
            return;
        }

        int payerId, payeeId;
        double amount;

        cout << "Enter the User ID of the payer: ";
        cin >> payerId;

        cout << "Enter the User ID of the payee: ";
        cin >> payeeId;

        if (payerId > 0 && payerId <= users.size() && payeeId > 0 && payeeId <= users.size())
        {
            cout << "Enter the amount to settle: ";
            cin >> amount;

            if (amount <= 0)
            {
                cout << "Invalid amount. Settlement must be a positive value." << endl;
                return;
            }

            cout << users[payeeId - 1].name << " has settled "
                 << amount << " with " << users[payerId - 1].name << endl;
        }
        else
        {
            cout << "Invalid User IDs provided for settlement." << endl;
        }
    }

    void displayTotalOwed(vector<User> &users)
    {
        if (currentGroupIndex == -1)
        {
            cout << "No active group. Please create or switch to a group." << endl;
            return;
        }

        cout << "Total amounts owed between participants in group: " << groups[currentGroupIndex].groupName << endl;
        vector<vector<double> > amountsOwed(users.size(), vector<double>(users.size(), 0.0));

        for (int i = 0; i < groups[currentGroupIndex].expenses.size(); ++i)
        {
            const Expense &expense = groups[currentGroupIndex].expenses[i];
            double splitAmount = expense.amount / expense.participants.size();
            for (int j = 0; j < expense.participants.size(); ++j)
            {
                int participantId = expense.participants[j];
                if (participantId != expense.payerId)
                {
                    amountsOwed[participantId - 1][expense.payerId - 1] += splitAmount;
                }
            }
        }

        for (int i = 0; i < users.size(); ++i)
        {
            for (int j = 0; j < users.size(); ++j)
            {
                if (amountsOwed[i][j] > 0)
                {
                    cout << users[i].name << " owes " << amountsOwed[i][j] << " to " << users[j].name << endl;
                }
            }
        }
    }
};

// Main function to demonstrate usage
int main()
{
    UserAccount userAccount;
    ExpenseManager expenseManager;

    int choice;
    int loggedInUserIndex = -1;

    do
    {
        cout << "\n====================================================================================================================\n";
        cout << "                                                Bill Buddy                \n";
        cout << "====================================================================================================================\n";
        cout << "                        1. Create Account               2. Login\n";
        cout << "                        3. Create Group                 4. Switch Group\n";
        cout << "                        5. Add Expense                  6. View Group Expenses\n";
        cout << "                        7. Settle Expenses              8. Display Total Owed\n";
        cout << "                        0. Exit\n";
        cout << "--------------------------------------------------------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "--------------------------------------------------------------------------------------------------------------------\n";

        switch (choice)
        {
        case 1:
            userAccount.createAccount();
            break;
        case 2:
            loggedInUserIndex = userAccount.login();
            break;
        case 3:
            if (loggedInUserIndex != -1)
            {
                expenseManager.createGroup();
            }
            else
            {
                cout << "Please login first." << endl;
            }
            break;
        case 4:
            expenseManager.switchGroup();
            break;
        case 5:
            if (loggedInUserIndex != -1)
            {
                expenseManager.addExpense(userAccount.getUsers());
            }
            else
            {
                cout << "Please login first." << endl;
            }
            break;
        case 6:
            expenseManager.viewGroupExpenses();
            break;
        case 7:
            expenseManager.settleExpenses(userAccount.getUsers());
            break;
        case 8:
            expenseManager.displayTotalOwed(userAccount.getUsers());
            break;
        case 0:
            cout << "Thank you for using Bill Buddy. Bye Buddy!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
