#include <iostream>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

class atm
{
private:
        int userid;
        int pin;
        int balance,debit=0;
        string name;
public:

        //Getting user information.
        void getdata()
        {
            cout<<endl<<"---> Welcome To A.T.M Services <---"<<endl;
            cout<<"Enter your Credentials"<<endl;
            cout<<"Enter your name"<<endl;
            cin>>name;
            cout<<"Enter your User ID"<<endl;
            cin>>userid;
            cout<<"Enter your Pin"<<endl;
            cin>>pin;
            cout<<endl<<"How much amount you want to deposit"<<endl;
            cin>>balance;

        }

        void new_user();
        void existing_user();
        void balance_inquiry();
        void cash_withdrawal();
        void fund_transfer();
        void pin_change();
        void DTH_recharge();
        void LPG_recharge();
        void electricity_bill();
        void telephone_bill();

        //Different services provides to the user.
        void choices()
        {
            int ch=1;
        while(1)
        {
                cout<<endl<<"\nSelect the service\n"<<endl;
                cout<<"1.Balance Inquiry"<<endl;
                cout<<"2.Cash Withdrawal"<<endl;
                cout<<"3.Pin Change"<<endl;
                cout<<"4.Fund Transfer"<<endl;
                cout<<"5.Bill Payments"<<endl;
                cout<<"6.Exit"<<endl;
                cout<<endl<<"Enter service you want to use\t";
                cin>>ch;

                switch(ch)
                {
                case 1:
                        this->balance_inquiry();
                        break;

                case 2:
                        this->cash_withdrawal();
                        break;

                case 3:
                        this->pin_change();
                        break;

                case 4:
                        this->fund_transfer();
                        break;

                case 5:
                        this->bill_payments();
                        break;

                case 6:
                        exit(0);
                        break;

                default: cout<<endl<<"Wrong choice entered"<<endl;
            }
        }
    }


    //Function for different bill payments.
    void bill_payments()
        {
            int ch=1;
            while(ch!=5)
            {
                cout<<endl<<"\nSelect the service\n"<<endl;
                cout<<"1.DTH Recharge"<<endl;
                cout<<"2.Telephone Bill"<<endl;
                cout<<"3.LPG recharge"<<endl;
                cout<<"4.Electricity Bill"<<endl;
                cout<<"5.Exit"<<endl;
                cout<<endl<<"Enter service you want to use\t";
                cin>>ch;

                switch(ch)
                {
                case 1:
                        this->DTH_recharge();
                        break;

                case 2:
                        this->telephone_bill();
                        break;

                case 3:
                        this->LPG_recharge();
                        break;

                case 4:
                        this->electricity_bill();
                        break;

                case 5:
                        break;

                default: cout<<endl<<"Please! Select right option"<<endl;
            }
        }
        cout<<endl<<"Press any key to continue ";
    }
};

//Function for New users.
void atm :: new_user()
{
    fstream file;
    file.open("input.txt",ios::app);
    this->getdata();
    //Writing all information of user into the file.
    file.write((char*)this,sizeof(*this));
    file.close();
    this->choices();
}

//Function for Existing users.
void atm :: existing_user()
{
    atm user;
    int userid1;
    int pin1;
    string name1;

    cout<<endl<<"Enter your credential"<<endl;
    cout<<"Enter your name"<<endl;
    cin>>name;
    cout<<"Enter your User ID"<<endl;
    cin>>userid1;
    cout<<"Enter your Pin"<<endl;
    cin>>pin1;

    ifstream file;
    file.open("input.txt",ios::in);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(userid1==this->userid && pin1==this->pin)
        {
            cout<<"Your account is opening"<<endl<<"Please wait!!!"<<endl;
            this->choices();
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for Balance Inquiry.
void atm :: balance_inquiry()
{
    int pin3;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;


            ifstream file;
            file.open("input.txt",ios::in | ios::binary);
            file.seekg(0);
            file.read((char*)this,sizeof(*this));
            cout<<endl<<this->pin<<endl;
            //reading appropriate user information from the file.
            while(!file.eof())
            {
                if(this->pin==pin3)
                {
                    cout<<endl<<"User name:\t"<<this->name<<endl;;
                    cout<<"User bank ID:\t"<<this->userid<<endl;
                    cout<<"User Remaining :\t"<<this->balance<<endl;
                    cout<<"User debited amount:\t"<<this->debit<<endl;
                    break;
                }

                else
                {
                    file.read((char*)this,sizeof(*this));
                }

            }
            if(file.eof())
            {
                cout<<"Sorry Can't find your account"<<endl;
            }
            file.close();
}

//Function for Cash Withdrawal.
void atm :: cash_withdrawal()
{
    int b,pin3;
    cout<<endl<<"Enter the amount in multiple of 100";
    cout<<endl<<"Enter the amount of withdrawal:\t";
    cin>>b;

    if(b%100==0)
    {
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b){
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"Cash proceed... Please Wait!"<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
        if(file.eof())
        {
        cout<<"Sorry Can't find your account"<<endl;
        }
        file.close();
    }

    }
    else
    {
        cout<<endl<<"Please enter the correct amount\n";
        this->cash_withdrawal();
    }
}

//Function for Pin Change.
void atm :: pin_change()
{
    int pin3;
    cout<<endl<<"Enter your old pin:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);
    //Reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            cout<<endl<<"Enter your new pin:\t";
            cin>>pin3;
            this->pin=pin3;
            cout<<endl<<"Your New pin is changed "<<this->pin<<endl;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for Fund Transfer.
void atm :: fund_transfer()
{
    string bank_name,account_holder;
    int b,pin3,account_no;
    cout<<endl<<"Enter the Bank name of receiver:\t";
    cin>>bank_name;
    cout<<endl<<"Enter the name of receiver:\t";
    cin>>account_holder;
    cout<<endl<<"Enter the account number of receiver:\t";
    cin>>account_no;
    cout<<endl<<"Enter the amount for transfer:\t";
    cin>>b;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b){
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"The "<<b<<" is transfered to the "<<account_holder<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for DTH Recharge.
void atm :: DTH_recharge()
{
    int b,pin3,DTHid;
    cout<<endl<<"Enter Customer DTH id:\t";
    cin>>DTHid;
    cout<<endl<<"Enter the amount of DTH recharge:\t";
    cin>>b;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b){
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"Your DTH has been recharged"<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for LPG recharge.
void atm :: LPG_recharge()
{
    int b,pin3,LPGid;
    cout<<endl<<"Enter Customer LPG-book id:\t";
    cin>>LPGid;
    cout<<endl<<"Enter the amount of LPG recharge:\t";
    cin>>b;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b)
            {
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"Your LPG has been recharged"<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for Electricity Bill.
void atm :: electricity_bill()
{
    int b,pin3,meterid;
    cout<<endl<<"Enter Customer electricity meter id:\t";
    cin>>meterid;
    cout<<endl<<"Enter the amount of Electricity Bill:\t";
    cin>>b;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b)
            {
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"Your Electricity Bill has been paid."<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}

//Function for Telephone Bill.
void atm :: telephone_bill()
{
    int b,pin3,teleno;
    cout<<endl<<"Enter Customer Telephone number:\t";
    cin>>teleno;
    cout<<endl<<"Enter the amount of Telephone Bill:\t";
    cin>>b;
    cout<<endl<<"Enter your pin again:\t";
    cin>>pin3;

    fstream file;
    file.open("input.txt", ios::in | ios::out | ios::binary);

    //reading the file.
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(pin3==this->pin)
        {
            if(this->balance >= b)
            {
            this->balance=this->balance - b;
            this->debit=this->debit + b;
            cout<<endl<<"Your Telephone Bill has been paid."<<endl;
            cout<<endl<<"Remaining amount\t"<<this->balance;
            file.seekp(file.tellp() - sizeof(*this));
            //writing updated values into the file.
            file.write((char*)this,sizeof(*this));
            break;
            }
            else{
                cout<<endl<<"Insufficient Balance"<<endl;
                break;
            }
        }
        else
        {
            file.read((char*)this,sizeof(*this));
        }
    }
    if(file.eof())
    {
        cout<<"Sorry Can't find your account"<<endl;
    }
    file.close();
}


int main()
{
    atm user;
    int choice=1;

    while(choice!=3)
    {
        cout<<endl<<"1.New User"<<endl;
        cout<<"2.Existing User"<<endl;
        cout<<"3.Exit"<<endl;
        cin>>choice;

        switch(choice)
        {
            case 1:
                    user.new_user();
                    break;

            case 2:
                    user.existing_user();
                    break;

            case 3:
                    exit(0);
                    break;

            default:    cout<<endl<<"Wrong choice entered";
        }
    }
}
