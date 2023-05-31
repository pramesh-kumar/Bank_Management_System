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
    void withdraw();
    void transfer();
    void payment();
    void search();
    void edit();
    void del();
    void show_records();
    void show_payment();
    void user_balance();
    void withdraw_atm();
    void check_detail();
};

void bank::menu()
{
p:
    system("clear");
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
        system("clear");
        bank_management();

    case 2:
        atm_management();
        break;
    case 3:
        exit(0);
    default:
        cout << "\n\nInvalid value....Please Try Again";
    }
    getch();
    goto p;
}
void bank::bank_management()
{
p:
    system("clear");
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
    cout << "\n 11.Payment All Records";
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
        withdraw();
        break;
    case 5:
        transfer();
        break;
    case 6:
        payment();
        break;
    case 7:
        search();
        break;
    case 8:
        edit();
        break;
    case 9:
        del();
        break;
    case 10:
        show_records();
        break;
    case 11:
        show_payment();
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

    system("clear");
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
        user_balance();
        break;
    case 2:
        withdraw_atm();
        break;
    case 3:
        check_detail();
        break;
    case 4:
        menu();
    default:
        cout << "\n\n Invalid value....Please Try Again";
    }
    getch();
    goto p;
}

void bank::new_user()
{
p:
    system("clear");
    fstream file;
    int p;
    float b;
    string n, f, pa, a, ph, i;
    cout << "\n\n\t\t\t Add New User";
    cout << "\n\n User ID : ";
    cin >> id;
    cout << "\n\n Name : ";
    cin >> name;
    cout << "\n\n Father Name : ";
    cin >> fname;
    cout << "\n\n Address : ";
    cin >> address;
    cout << "\n\n Pin Code (5 digit) : ";
    cin >> pin;
    cout << "\n\n Enter Password : ";
    cin >> pass;
    cout << "\n\n Phone Number : ";
    cin >> phone;
    cout << "\n\n Current Balance : ";
    cin >> balance;

    file.open("bank.txt", ios::in);

    if (!file)
    {
        file.open("bank.txt", ios::app | ios::out);
        file << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
        file.close();
    }
    else
    {
        file >> i >> n >> f >> a >> p >> pa >> ph >> b;
        while (!file.eof())
        {
            if (i == id)
            {
                cout << "\n\n User ID Already Exist... ";
                getch();
                goto p;
            }
            file >> i >> n >> f >> a >> p >> pa >> ph >> b;
        }
        file.close();

        file.open("bank.txt", ios::app | ios::out);
        file << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
        file.close();
    }
    cout << "\n\n  New User Account Created Successfully.....";
}

void bank::already_user()
{
    system("clear");
    fstream file;
    string t_id;
    bool found = false;
    cout << "\n\n Already User Account";
    file.open("bank.txt", ios::in);

    if (!file)
    {
        cout << "\n\nFile Opening Error...";
    }
    else
    {

        cout << "\n\n User ID :";
        cin >> t_id;
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id)
            {
                system("clear");
                cout << "\n\nAlready User Account";
                cout << "\n\nUser ID : " << id << "   "
                     << "Pin code : " << pin << " Password : " << pass;
                found = true;
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file.close();
        if (!found)
        {
            cout << "\n\n User ID Not Found...";
        }
    }
}

void bank::deposit()
{
    fstream file, file1;
    string t_id;
    float dep;
    bool found = false;

    system("clear");
    cout << "\n\n\t\t\t Deposit Amount option";
    file.open("bank.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\n User ID :";
        cin >> t_id;

        file1.open("temp.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id)
            {
                cout << "\n\nAmount For Deposit : ";
                cin >> dep;
                balance = balance + dep;

                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
                cout << "\n\nYour current balance is " << balance << endl;
                cout << "\n\nYour Amount " << dep << endl
                     << "Sucessfully Deposit...";
                found = true;
            }
            else
            {
                // write into file1
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }

            // reading from file

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }

        if (found == false)
        {
            cout << "\n\n User ID Not Found...";
        }
        file1.close();
        file.close();
        remove("bank.txt");
        rename("temp.txt", "bank.txt");
    }
}

void bank::withdraw()
{
    fstream file, file1;
    string t_id;
    float with;
    bool found = false;
    system("clear");
    cout << "\n\n\t\t\tWithdraw Amount option";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\nFile Opening Error...";
    }
    else
    {
        cout << "\n\nUser ID :";
        cin >> t_id;
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id)
            {
                cout << "\n\nAmount For Withdraw : ";
                cin >> with;
                if (with <= balance)
                {
                    balance -= with;
                    file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";

                    cout << "\n\nYour Amount " << with << "\n"
                         << "Sucessfully Withdraw...";
                }
                else
                {
                    file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
                    cout << "\n\nYour Current Balance " << balance << " Insufficient to withdraw.";
                }
                found = true;
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        if (found == false)
        {
            cout << "\n\n User ID Not Found...";
        }
        file1.close();
        file.close();

        remove("bank.txt");
        rename("bank1.txt", "bank.txt");
    }
}

void bank::transfer()
{

    fstream file, file1;

    string s_id, r_id;
    float amount;
    int found = 0;
    cout << "\n\n\t\t\tPayment Transfer Option";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\nSender User ID For Transaction : ";
        cin >> s_id;
        cout << "\n\nReceiver User ID For Transaction : ";
        cin >> r_id;
        cout << "\n\nEnter Transfer Amount : ";
        cin >> amount;
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (s_id == id && amount <= balance)
            {
                found++;
            }
            else if (r_id == id)
            {
                found++;
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file1.close();
    }
    file.close();

    if (found == 2)
    {
        file.open("bank.txt", ios::in);
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (s_id == id)
            {
                balance -= amount;
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }
            else if (r_id == id)
            {
                balance += amount;
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file1.close();
        file.close();
        remove("bank.txt");
        rename("bank1.txt", "bank.txt");
        cout << "\n\nTransaction Sucessfully";
    }
    else
    {
        cout << "\n\nBoth Transaction User ID's & Balance May Invalid....";
    }
}

void bank::payment()
{

    system("clear");

    string t_id;
    int found = 0;
    float amount;
    string b_name;

    fstream file, file1;
    cout << "\n\nBill Payment Option";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\nFile Opening Error..";
    }
    else
    {
        cout << "\n\n User ID: ";
        cin >> t_id;
        cout << "\n\n Bill Name : ";
        cin >> b_name;
        cout << "\n\n Bill Amount : ";
        cin >> amount;
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id && amount <= balance)
            {
                balance -= amount;
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
                found++;
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }

        file.close();
        file1.close();
        remove("bank.txt");
        rename("bank1.txt", "bank.txt");

        if (found == 1)
        {
            file.open("bill.txt", ios::app | ios::out);
            file << " " << t_id << " " << b_name << " " << amount << " "
                 << "\n";
            file.close();

            cout << "\n\n"
                 << b_name << " Bill Pay successfully..";
        }
        else
        {
            cout << "\n\n User ID Or Amount Invalid...";
        }
    }
}

void bank::search()
{

    system("clear");
    fstream file;
    string t_id;
    bool found = false;

    cout << "\n\n Search User Record";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\n User ID : ";
        cin >> t_id;

        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id)
            {
                // system("clear");

                cout << "\n\n\t\tUser Record    ";

                cout << "\n\n\t\tUser ID: " << id << "\n"
                     << "\t\tName : " << name << "\n"
                     << "\t\tFather's Name: " << fname << "\n"
                     << "\t\tAddress: " << address << "\n"
                     << "\t\tPin: " << pin << "\n"
                     << "\t\tPassword: " << pass << "\n"
                     << "\t\tPhone No: " << phone << "\n"
                     << "\t\tCurrent Balance: " << balance << "\n";

                found = true;

                // TO hold the output data.
                getch();
            }

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file.close();

        if (found == false)
        {
            cout << "\n\nUser ID Can't Found...";
        }
    }
}
void bank::edit()
{
    system("clear");

    fstream file, file1;
    string t_id, n, f, a, p, ph;
    int found = 0, pi;

    cout << "\n\nEdit User Record";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\nUser ID : ";
        cin >> t_id;
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {

            if (t_id == id)
            {
                cout << "\n\nEnter Name : ";
                cin >> n;
                cout << "\n\nFather Name : ";
                cin >> f;
                cout << "\n\nAddress : ";
                cin >> a;
                cout << "\n\nPin Code (5 digit) : ";
                cin >> pi;
                cout << "\n\nPassword : ";
                cin >> p;
                cout << "\n\nPhone Number : ";
                cin >> ph;

                file1 << " " << id << " " << n << " " << f << " " << a << " " << pi << " " << p << " " << ph << " " << balance << "\n";
                cout << "\n\nRecord  Edited Successfully...  ";
                found++;
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }

        file1.close();
        file.close();
        remove("bank.txt");
        rename("bank1.txt", "bank.txt");

        if (found == 0)
        {
            cout << "\n\n User ID Can't Found...";
        }
    }
}

void bank::del()
{
    system("clear");
    fstream file, file1;
    string t_id;
    int found = 0;

    cout << "\n\nDelete  User Record";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {

        cout << "\n\nUser ID : ";
        cin >> t_id;
        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {

            if (t_id == id)
            {
                cout << "\n\n Record  Deleted Successfully...  ";
                found++;
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        if (found == 0)
        {
            cout << "\n\n User ID Can't Found...";
        }
        file.close();
        file1.close();
        remove("bank.txt");
        rename("bank1.txt", "bank.txt");
    }
}

void bank::show_records()
{

    system("clear");
    fstream file;
    int found = 0;
    cout << "\n\n\t\t\t Show  All User's Records";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\nFile Opening Error...";
    }
    else
    {

        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            cout << "\n\n\n User ID : " << id;
            cout << "\n Name: " << name;
            cout << "\n Father Name: " << fname;
            cout << "\n Address: " << address;
            cout << "\n Pin :" << pin;
            cout << "\n Password : " << pass;
            cout << "\n Phone No : " << phone;
            cout << "\n Current Balance : " << balance;
            cout << "\n\n========================";
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
            // time interval
            sleep(2);
            // getch();
            found++;
        }
        file.close();
        if (found == 0)
        {
            cout << "\n\n Data Base is Empty ";
        }
    }
}

void bank::user_balance()
{
    system("clear");
    fstream file;
    int found = 0;
    string t_id, t_pin = "", t_pass = "";
    char ch;
    char ch2;
    cout << "\n\n\t\t User Login & Check Balance";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\n User ID : ";
        cin >> t_id;
        cout << "\n\nPin Code : ";

        ch = getch();
        for (int i = 1; i <= 5; i++)
        {
            ch = getch();
            t_pin += ch;
            cout << "*";
        }

        cout << "\n\nPassword : ";

        ch2 = getch();
        while (ch2 != '\n')
        {
            cout << "*";
            t_pass += ch2;
            ch2 = getch();
        }

        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id && t_pin == pin && t_pass == pass)
            {
                cout << "\n\n\t\tYour current balance is : " << balance;
                found++;
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file.close();
        if (found == 0)
        {
            cout << "\n\n User either ID, Pin or Password Invalid...";
        }
    }
}

void bank::show_payment()
{
    system("clear");
    float amount;

    fstream file;
    int found = 0;
    cout << "\n\n\t\t\t Show  All Bill's Records";
    file.open("bill.txt", ios::in);
    if (!file)
    {
        cout << "\n\nFile Opening Error...";
    }
    else
    {

        file >> id >> name >> amount;
        while (!file.eof())
        {
            cout << "\n\n\n User ID : " << id;
            cout << "\n Bill Name: " << name;
            cout << "\n Amount: " << amount;

            cout << "\n\n========================";
            file >> id >> name >> amount;
            found++;
            // to hold the screen
            getch();
        }
        file.close();
        if (found == 0)
        {
            cout << "\n\n Data Base is Empty ";
        }
    }
}

void bank::withdraw_atm()
{
    fstream file, file1;
    string t_id, t_pass, t_pin;
    float with;
    char ch, ch2;
    int found = 0;
    system("clear");
    cout << "\n\n\t\t\tWithdraw Amount option";
    file.open("bank.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File Opening Error...";
    }
    else
    {
        cout << "\n\n\t\tUser ID :";
        cin >> t_id;
        cout << "\n\t\tPin code : ";

        ch = getch();
        for (int i = 1; i <= 5; i++)
        {
            ch = getch();
            t_pin += ch;
            cout << "*";
        }

        cout << "\n\t\tPassword : ";

        ch2 = getch();
        while (ch2 != '\n')
        {
            cout << "*";
            t_pass += ch2;
            ch2 = getch();
        }

        file1.open("bank1.txt", ios::app | ios::out);
        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;

        while (!file.eof())
        {
            if (t_id == id && t_pin == pin && t_pass == pass)
            {
                cout << "\n\n Amount For Withdraw : ";
                cin >> with;
                if (with <= balance)
                {
                    balance -= with;
                    file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";

                    cout << "\n\nYour Amount " << with << " Sucessfully Withdraw..." << endl;
                    cout << "\n\nYour Current Balance :" << balance << endl;
                    getch();
                }
                else
                {
                    file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
                    cout << "\n\nYour Current Balance is " << balance << " Insufficient to withdraw.";
                }
                found++;
            }
            else
            {
                file1 << " " << id << " " << name << " " << fname << " " << address << " " << pin << " " << pass << " " << phone << " " << balance << "\n";
            }
            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file.close();
        file1.close();
        remove("bank.txt");
        rename("bank1.txt", "bank.txt");
        if (found == 0)
        {
            cout << "\n\n User ID Not Found...";
        }
    }
}

void bank::check_detail()
{

    fstream file;
    string t_id, t_pass, t_pin;
    int found = 0;
    char ch, ch2;

    system("clear");
    cout << "\n\n\t\t\t Check Details option";
    file.open("bank.txt", ios::in);
    if (!file)
    {

        cout << "\n\n File Opening Error...";
    }
    else
    {

        cout << "\n\n\t\tUser ID :";
        cin >> t_id;
        cout << "\n\t\tPin code : ";

        ch = getch();
        for (int i = 1; i <= 5; i++)
        {
            ch = getch();
            t_pin += ch;
            cout << "*";
        }

        cout << "\n\t\tPassword : ";

        ch2 = getch();
        while (ch2 != '\n')
        {
            cout << "*";
            t_pass += ch2;
            ch2 = getch();
        }

        file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        while (!file.eof())
        {
            if (t_id == id && t_pin == pin && t_pass == pass)
            {
                cout << "\n\n\n User ID : " << id;
                cout << "\n Name: " << name;
                cout << "\n Father Name: " << fname;
                cout << "\n Address: " << address;
                cout << "\n Pin :" << pin;
                cout << "\n Password : " << pass;
                cout << "\n Phone No : " << phone;
                cout << "\n Current Balance : " << balance;
                found++;
                // to hold the screen i used getch()
                // when any key pressed screen will start moving
                getch();
            }

            file >> id >> name >> fname >> address >> pin >> pass >> phone >> balance;
        }
        file.close();

        if (found == 0)
        {
            cout << "\n\n User ID Not Found...";
        }
    }
}

int main()
{
    bank obj;
    obj.menu();
}