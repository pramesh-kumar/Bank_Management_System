#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

const string DB_FILE   = "bank.txt";
const string BILL_FILE = "bill.txt";
const string TEMP_FILE = "temp.txt";
const char   DELIMITER = '|';

struct Account {
    string userId;
    string fullName;
    string fatherName;
    string address;
    string pin;
    string password;
    string phoneNumber;
    float  balance;
};

// Reads one pipe-delimited account line from file
bool readAccount(ifstream &inputFile, Account &account) {
    string line;
    if (!getline(inputFile, line) || line.empty()) return false;

    stringstream ss(line);
    string balanceStr;
    getline(ss, account.userId,      DELIMITER);
    getline(ss, account.fullName,    DELIMITER);
    getline(ss, account.fatherName,  DELIMITER);
    getline(ss, account.address,     DELIMITER);
    getline(ss, account.pin,         DELIMITER);
    getline(ss, account.password,    DELIMITER);
    getline(ss, account.phoneNumber, DELIMITER);
    getline(ss, balanceStr,          DELIMITER);
    account.balance = stof(balanceStr);
    return true;
}

// Writes one account as a pipe-delimited line
void writeAccount(ofstream &outputFile, const Account &account) {
    outputFile << account.userId      << DELIMITER
               << account.fullName    << DELIMITER
               << account.fatherName  << DELIMITER
               << account.address     << DELIMITER
               << account.pin         << DELIMITER
               << account.password    << DELIMITER
               << account.phoneNumber << DELIMITER
               << account.balance     << "\n";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads a line from user with a prompt (handles spaces)
string readLine(const string &prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

bool findAccount(const string &userId, Account &account) {
    ifstream inputFile(DB_FILE);
    if (!inputFile) return false;

    Account current;
    while (readAccount(inputFile, current)) {
        if (current.userId == userId) {
            account = current;
            return true;
        }
    }
    return false;
}

void rewriteDB(const string &targetUserId, const Account *replacement) {
    ifstream sourceFile(DB_FILE);
    ofstream tempFile(TEMP_FILE);

    Account current;
    while (readAccount(sourceFile, current)) {
        if (current.userId == targetUserId) {
            if (replacement) writeAccount(tempFile, *replacement);
        } else {
            writeAccount(tempFile, current);
        }
    }

    sourceFile.close();
    tempFile.close();
    remove(DB_FILE.c_str());
    rename(TEMP_FILE.c_str(), DB_FILE.c_str());
}

void createAccount() {
    Account newAccount;
    cout << "\n--- New Account ---\n";
    cout << "User ID     : "; cin >> newAccount.userId; clearInput();
    newAccount.fullName    = readLine("Full Name   : ");
    newAccount.fatherName  = readLine("Father Name : ");
    newAccount.address     = readLine("Address     : ");
    cout << "PIN (5 dig) : "; cin >> newAccount.pin;
    cout << "Password    : "; cin >> newAccount.password;
    cout << "Phone       : "; cin >> newAccount.phoneNumber;
    cout << "Balance     : "; cin >> newAccount.balance;

    Account existing;
    if (findAccount(newAccount.userId, existing)) {
        cout << "  ! User ID already exists.\n";
        return;
    }

    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, newAccount);
    cout << "  Account created successfully.\n";
}

void depositAmount() {
    string userId;
    float depositAmt;
    cout << "\n--- Deposit ---\n";
    cout << "User ID : "; cin >> userId;
    cout << "Amount  : "; cin >> depositAmt;

    if (depositAmt <= 0) { cout << "  ! Amount must be positive.\n"; return; }

    Account account;
    if (!findAccount(userId, account)) { cout << "  ! Account not found.\n"; return; }

    account.balance += depositAmt;
    rewriteDB(userId, &account);
    cout << "  Deposited. New balance: " << account.balance << "\n";
}

void withdrawAmount() {
    string userId;
    float withdrawAmt;
    cout << "\n--- Withdraw ---\n";
    cout << "User ID : "; cin >> userId;
    cout << "Amount  : "; cin >> withdrawAmt;

    if (withdrawAmt <= 0)              { cout << "  ! Amount must be positive.\n"; return; }

    Account account;
    if (!findAccount(userId, account))     { cout << "  ! Account not found.\n";    return; }
    if (withdrawAmt > account.balance)     { cout << "  ! Insufficient balance.\n"; return; }

    account.balance -= withdrawAmt;
    rewriteDB(userId, &account);
    cout << "  Withdrawn. New balance: " << account.balance << "\n";
}

void transferAmount() {
    string senderUserId, receiverUserId;
    float transferAmt;
    cout << "\n--- Transfer ---\n";
    cout << "Sender ID   : "; cin >> senderUserId;
    cout << "Receiver ID : "; cin >> receiverUserId;
    cout << "Amount      : "; cin >> transferAmt;

    Account senderAccount, receiverAccount;
    if (!findAccount(senderUserId,   senderAccount))   { cout << "  ! Sender not found.\n";     return; }
    if (!findAccount(receiverUserId, receiverAccount)) { cout << "  ! Receiver not found.\n";   return; }
    if (transferAmt > senderAccount.balance)           { cout << "  ! Insufficient balance.\n"; return; }

    senderAccount.balance   -= transferAmt;
    receiverAccount.balance += transferAmt;
    rewriteDB(senderUserId,   &senderAccount);
    rewriteDB(receiverUserId, &receiverAccount);
    cout << "  Transfer successful.\n";
}

void searchAccount() {
    string userId;
    cout << "\n--- Search Account ---\n";
    cout << "User ID : "; cin >> userId;

    Account account;
    if (!findAccount(userId, account)) { cout << "  ! Account not found.\n"; return; }

    cout << "\n  User ID     : " << account.userId      << "\n";
    cout << "  Full Name   : " << account.fullName     << "\n";
    cout << "  Father Name : " << account.fatherName   << "\n";
    cout << "  Address     : " << account.address      << "\n";
    cout << "  Phone       : " << account.phoneNumber  << "\n";
    cout << "  Balance     : " << account.balance      << "\n";
}

void editAccount() {
    string userId;
    cout << "\n--- Edit Account ---\n";
    cout << "User ID : "; cin >> userId;

    Account account;
    if (!findAccount(userId, account)) { cout << "  ! Account not found.\n"; return; }

    clearInput();
    account.fullName   = readLine("New Full Name   : ");
    account.fatherName = readLine("New Father Name : ");
    account.address    = readLine("New Address     : ");
    cout << "New Phone    : "; cin >> account.phoneNumber;
    cout << "New PIN      : "; cin >> account.pin;
    cout << "New Password : "; cin >> account.password;

    rewriteDB(userId, &account);
    cout << "  Account updated.\n";
}

void deleteAccount() {
    string userId;
    cout << "\n--- Delete Account ---\n";
    cout << "User ID : "; cin >> userId;

    Account account;
    if (!findAccount(userId, account)) { cout << "  ! Account not found.\n"; return; }

    rewriteDB(userId, nullptr);
    cout << "  Account deleted.\n";
}

void showAllAccounts() {
    ifstream inputFile(DB_FILE);
    if (!inputFile) { cout << "  No records found.\n"; return; }

    cout << "\n--- All Accounts ---\n";
    Account account;
    int recordCount = 0;
    while (readAccount(inputFile, account)) {
        cout << "  [" << ++recordCount << "]"
             << " ID: "        << account.userId
             << " | Name: "    << account.fullName
             << " | Balance: " << account.balance << "\n";
    }
    if (recordCount == 0) cout << "  No records.\n";
}

void payBill() {
    string userId;
    float billAmount;
    cout << "\n--- Pay Bill ---\n";
    cout << "User ID   : "; cin >> userId;
    clearInput();
    string billName = readLine("Bill Name : ");
    cout << "Amount    : "; cin >> billAmount;

    Account account;
    if (!findAccount(userId, account))  { cout << "  ! Account not found.\n";   return; }
    if (billAmount > account.balance)   { cout << "  ! Insufficient balance.\n"; return; }

    account.balance -= billAmount;
    rewriteDB(userId, &account);

    ofstream billFile(BILL_FILE, ios::app);
    billFile << userId << DELIMITER << billName << DELIMITER << billAmount << "\n";
    cout << "  Bill paid successfully.\n";
}

void showAllBills() {
    ifstream inputFile(BILL_FILE);
    if (!inputFile) { cout << "  No bills found.\n"; return; }

    cout << "\n--- Bill Records ---\n";
    string line;
    int recordCount = 0;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string userId, billName, amountStr;
        getline(ss, userId,    DELIMITER);
        getline(ss, billName,  DELIMITER);
        getline(ss, amountStr, DELIMITER);
        cout << "  [" << ++recordCount << "]"
             << " ID: "       << userId
             << " | Bill: "   << billName
             << " | Amount: " << amountStr << "\n";
    }
    if (recordCount == 0) cout << "  No bill records.\n";
}

bool authenticateUser(Account &account) {
    string userId, enteredPin, enteredPassword;
    cout << "User ID  : "; cin >> userId;
    cout << "PIN      : "; cin >> enteredPin;
    cout << "Password : "; cin >> enteredPassword;

    if (!findAccount(userId, account)) {
        cout << "  ! Account not found.\n";
        return false;
    }
    if (account.pin != enteredPin || account.password != enteredPassword) {
        cout << "  ! Invalid PIN or Password.\n";
        return false;
    }
    return true;
}

void atmCheckBalance() {
    cout << "\n--- ATM: Check Balance ---\n";
    Account account;
    if (authenticateUser(account))
        cout << "  Welcome " << account.fullName << "! Balance: " << account.balance << "\n";
}

void atmWithdrawAmount() {
    cout << "\n--- ATM: Withdraw ---\n";
    Account account;
    if (!authenticateUser(account)) return;

    float withdrawAmt;
    cout << "Amount : "; cin >> withdrawAmt;

    if (withdrawAmt <= 0)              { cout << "  ! Amount must be positive.\n"; return; }
    if (withdrawAmt > account.balance) { cout << "  ! Insufficient balance.\n";    return; }

    account.balance -= withdrawAmt;
    rewriteDB(account.userId, &account);
    cout << "  Withdrawn Rs." << withdrawAmt << ". New balance: " << account.balance << "\n";
}

void bankMenu() {
    int menuChoice;
    do {
        cout << "\n====== Bank Management ======\n";
        cout << " 1. New Account    2. Search Account\n";
        cout << " 3. Deposit        4. Withdraw\n";
        cout << " 5. Transfer       6. Pay Bill\n";
        cout << " 7. Edit Account   8. Delete Account\n";
        cout << " 9. Show All      10. Show Bills\n";
        cout << "11. Back\n";
        cout << " Choice: ";

        if (!(cin >> menuChoice)) { clearInput(); continue; }

        switch (menuChoice) {
            case 1:  createAccount();   break;
            case 2:  searchAccount();   break;
            case 3:  depositAmount();   break;
            case 4:  withdrawAmount();  break;
            case 5:  transferAmount();  break;
            case 6:  payBill();         break;
            case 7:  editAccount();     break;
            case 8:  deleteAccount();   break;
            case 9:  showAllAccounts(); break;
            case 10: showAllBills();    break;
            case 11: break;
            default: cout << "  Invalid choice.\n";
        }
    } while (menuChoice != 11);
}

void atmMenu() {
    int menuChoice;
    do {
        cout << "\n====== ATM ======\n";
        cout << " 1. Check Balance\n";
        cout << " 2. Withdraw\n";
        cout << " 3. Back\n";
        cout << " Choice: ";

        if (!(cin >> menuChoice)) { clearInput(); continue; }

        switch (menuChoice) {
            case 1: atmCheckBalance();   break;
            case 2: atmWithdrawAmount(); break;
            case 3: break;
            default: cout << "  Invalid choice.\n";
        }
    } while (menuChoice != 3);
}

int main() {
    int menuChoice;
    cout << "=== Bank Management System ===\n";
    do {
        cout << "\n 1. Bank Management\n 2. ATM\n 3. Exit\n";
        cout << " Choice: ";

        if (!(cin >> menuChoice)) { clearInput(); continue; }

        switch (menuChoice) {
            case 1: bankMenu(); break;
            case 2: atmMenu();  break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "  Invalid choice.\n";
        }
    } while (menuChoice != 3);

    return 0;
}
