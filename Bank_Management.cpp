#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

class bank
{
private:
    string id, pass, name, fname, address, phone, pin;
    float balance;

public:
    void menu();
    void bank_management();
    void atm_management();
    void new_user();
    void already_user();
    void deposit();
    // void withdraw();
    // void  transfer();
    // void payment();
    // void search();
    // void edit();
    // void del();
    // void show_records();
    // void show_payment();
    // void user_balance();
    // void withdraw_atm();
    // void check_detail();
};

void bank::menu()
{
p:
    // system("cls");
    int choice;
    char ch;
    string pin, pass, email;

    cout << "\n\n\t\t\tControl Panel";

    cout << "\n\n 1.Bank Management";
    cout << "\n 2.ATM Management";
    cout << "\n 3.Exit";

    cout << "\n\n Enter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        bank_management();
        break;
    case 2:
        atm_management();
        break;
    case 3:
        exit(0);
    default:
        cout << "\n\n Invalid choice....Please Try Again";
    }
    getch();
    goto p;
}

void bank::bank_management()
{
p:
    int choice;
    cout << "\n\n\t\t\tBank Management System";
    cout << "\n\n 1.New User";
    cout << "\n 2.Already User ";
    cout << "\n 3.Deposit Option";
    cout << "\n 4.Withdraw Option";
    cout << "\n 5.Transfer Option";
    cout << "\n 6.Payment Option";
    cout << "\n 7.Search User Record";
    cout << "\n 8.Edit User Record";
    cout << "\n 9.Delete User Record";
    cout << "\n 10.Show All Records";
    cout << "\n 11. Payment All Records";
    cout << "\n 12.Go Back";

    cout << "\n\n Enter Your Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        new_user();
        break;
    case 2:
        already_user();
        break;
    case 3:
        deposit();
        break;
    case 4:
        // withdraw();
        break;
    case 5:
        // transfer();
        break;
    case 6:
        // payment();
        break;
    case 7:
        // search();
        break;
    case 8:
        // edit();
        break;
    case 9:
        // del();
        break;
    case 10:
        // show_records();
        break;
    case 11:
        // show_payment();
        break;
    case 12:
        menu();
    default:
        cout << "\n\n Invalid value....Please Try Again";
    }

    getch();
    goto p;
}

void bank::atm_management()
{
p:

    int choice;
    cout << "\n\n\t\t\tATM Management System";

    cout << "\n\n 1.User Login & Check Balance";
    cout << "\n 2.Withdraw Amount ";
    cout << "\n 3.Account Details";
    cout << "\n 4.Go Back";

    cout << "\n\n Enter Your Choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        // user_balance();
        break;
    case 2:
        // withdraw_atm();
        break;
    case 3:
        // check_detail();
        break;
    case 4:
        menu();
    default:
        cout << "\n\n Invalid value....Please Try Again";
    }
    getch();
    goto p;
}

void bank::already_user()
{
    // write your code here
}
void bank::new_user()
{
p:
    fstream file;
    int p;
    float b;
    string n, f, pa, a, ph, i;
    cout << "\n\n\t\t\tAdd New User";
    cout << "\n\nUser ID : ";
    cin >> id;
    cout << "\n\nEnter your Name : ";
    cin >> name;
    cout << "\n\nFather Name : ";
    cin >> fname;
    cout << "\n\nAddress : ";
    cin >> address;
    cout << "\n\nPin Code (5 digit) : ";
    cin >> pin;
    cout << "\n\nPassword : ";
    cin >> pass;
    cout << "\n\nPhone Number : ";
    cin >> phone;
    cin.ignore();
    cout << "\n\nCurrent Balance : ";
    cin >> balance;

    file.open("bank.txt", ios::in);

    if (!file)
    {

        file.open("bank.txt", ios::app | ios::out);
        file << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
        file.close();
    }
    else
    {
        file >> i >> n >> f >> a >> p >> pa >> ph >> b;
        while (!file.eof())
        {
            if (i == id)
            {
                cout << "\n\nUser ID Already Exist... ";
                getch();
                goto p;
            }
            file >> i >> n >> f >> a >> p >> pa >> ph >> b;
        }
        file.close();
        file.open("bank.txt", ios::app | ios::out);
        file << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << endl;
        file.close();
    }
    cout << "\n\nNew User Account Created Successfully.....";
}

void bank::deposit()
{
    fstream file, file1;
    string t_id;
    float dep;
    bool found = false;
    bank bk;

    cout << "\n\n\t\t\t Deposit Amount option";
    file.open("bank.txt", ios::in | ios::out);

    if (!file)
    {
        cout << "\n\nFile Opening Error...";
    }
    else
    {
        cout << "\n\nEnter User ID :";
        cin >> t_id;

        file1.open("temp.txt", ios::app | ios::out);

        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id)
            {
                cout << "\n\nEnter Amount For Deposit : ";
                cin >> dep;
                balance = balance + dep;
                file1 << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance;
                cout << "\n\nYour current amount is " << balance << endl
                     << "Sucessfully Deposit...";
                found = true;
            }
            else
            {
                file1 << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance;
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        remove("bank.txt");
        rename("temp.txt", "bank.txt");

        file.close();
        file1.close();

        if (found == false)
        {
            cout << "User not found";
        }
    }
}
int main()
{
    bank obj;
    obj.menu();
}