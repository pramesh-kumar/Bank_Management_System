#include <iostream>
#include <fstream>
#include <string>
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

bool readAccount(ifstream &inputFile, Account &account) {
    string line;
    if (!getline(inputFile, line) || line.empty()) return false;

    stringstream ss(line);
    string balanceStr;
    getline(ss, account.userId,       DELIMITER);
    getline(ss, account.fullName,     DELIMITER);
    getline(ss, account.fatherName,   DELIMITER);
    getline(ss, account.address,      DELIMITER);
    getline(ss, account.pin,          DELIMITER);
    getline(ss, account.password,     DELIMITER);
    getline(ss, account.phoneNumber,  DELIMITER);
    getline(ss, balanceStr,           DELIMITER);
    account.balance = stof(balanceStr);
    return true;
}

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

bool findAccount(const string &userId, Account &account) {
    ifstream inputFile(DB_FILE);
    if (!inputFile) return false;
    Account current;
    while (readAccount(inputFile, current))
        if (current.userId == userId) { account = current; return true; }
    return false;
}

void rewriteDB(const string &targetUserId, const Account *replacement) {
    ifstream sourceFile(DB_FILE);
    ofstream tempFile(TEMP_FILE);
    Account current;
    while (readAccount(sourceFile, current)) {
        if (current.userId == targetUserId) { if (replacement) writeAccount(tempFile, *replacement); }
        else writeAccount(tempFile, current);
    }
    sourceFile.close();
    tempFile.close();
    remove(DB_FILE.c_str());
    rename(TEMP_FILE.c_str(), DB_FILE.c_str());
}

int passedCount = 0;
int failedCount = 0;

void check(bool condition, const string &testDescription) {
    if (condition) { cout << "  [PASS] " << testDescription << "\n"; passedCount++; }
    else           { cout << "  [FAIL] " << testDescription << "\n"; failedCount++; }
}

void resetDatabase() {
    remove("bank.txt");
    remove("bill.txt");
}

Account buildTestAccount(const string &userId, const string &fullName, float balance) {
    return {userId, fullName, "Test Father", "Test City", "12345", "testpass", "9999999999", balance};
}

void testCreateAndFind() {
    cout << "\n[TEST] Create & Find\n";
    resetDatabase();

    Account newAccount = buildTestAccount("U1", "Alice Smith", 1000.0f);
    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, newAccount);
    outputFile.close();

    Account foundAccount;
    check(findAccount("U1", foundAccount),      "find existing account");
    check(foundAccount.balance == 1000.0f,      "balance is correct");
    check(foundAccount.fullName == "Alice Smith","full name with space stored correctly");
    check(!findAccount("NONE", foundAccount),   "missing account returns false");
}

void testDeposit() {
    cout << "\n[TEST] Deposit\n";
    resetDatabase();

    Account account = buildTestAccount("U2", "Bob Jones", 500.0f);
    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, account);
    outputFile.close();

    account.balance += 200.0f;
    rewriteDB("U2", &account);

    Account updatedAccount;
    findAccount("U2", updatedAccount);
    check(updatedAccount.balance == 700.0f, "balance updated after deposit");
}

void testWithdraw() {
    cout << "\n[TEST] Withdraw\n";
    resetDatabase();

    Account account = buildTestAccount("U3", "Carol White", 300.0f);
    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, account);
    outputFile.close();

    account.balance -= 100.0f;
    rewriteDB("U3", &account);

    Account updatedAccount;
    findAccount("U3", updatedAccount);
    check(updatedAccount.balance == 200.0f, "balance reduced after withdraw");
    check(updatedAccount.balance < 500.0f,  "overdraft blocked");
}

void testTransfer() {
    cout << "\n[TEST] Transfer\n";
    resetDatabase();

    Account senderAccount   = buildTestAccount("U4", "Dave Brown", 1000.0f);
    Account receiverAccount = buildTestAccount("U5", "Eve Davis",   200.0f);

    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, senderAccount);
    writeAccount(outputFile, receiverAccount);
    outputFile.close();

    float transferAmount = 300.0f;
    senderAccount.balance   -= transferAmount;
    receiverAccount.balance += transferAmount;
    rewriteDB("U4", &senderAccount);
    rewriteDB("U5", &receiverAccount);

    Account updatedSender, updatedReceiver;
    findAccount("U4", updatedSender);
    findAccount("U5", updatedReceiver);
    check(updatedSender.balance   == 700.0f, "sender balance reduced");
    check(updatedReceiver.balance == 500.0f, "receiver balance increased");
}

void testDelete() {
    cout << "\n[TEST] Delete\n";
    resetDatabase();

    Account account = buildTestAccount("U6", "Frank Miller", 100.0f);
    ofstream outputFile(DB_FILE, ios::app);
    writeAccount(outputFile, account);
    outputFile.close();

    rewriteDB("U6", nullptr);

    Account deletedAccount;
    check(!findAccount("U6", deletedAccount), "deleted account not found");
}

int main() {
    cout << "===== Unit Tests =====\n";

    testCreateAndFind();
    testDeposit();
    testWithdraw();
    testTransfer();
    testDelete();

    cout << "\n======================\n";
    cout << "  Passed: " << passedCount << "\n";
    cout << "  Failed: " << failedCount << "\n";
    cout << "======================\n";

    return (failedCount == 0) ? 0 : 1;
}
