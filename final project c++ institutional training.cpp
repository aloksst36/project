#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class Database{
string name;
string user_name;
double password;
public:
void get()
{
    cout<<"enter the value in the database:-\n";
    cout<<"name:-\n";
    cin>>name;;
    cout<<"username:-\n";
    cin>>user_name;
    cout<<"password:-\n";
    cin>>password;
    }
    string user()
    {
        return user_name;
    }
    string nam()
    {
        return name;
    }
    double pass()
    {
        return password;
    }
void put()
{
    ifstream f2;
    f2.open("database.txt",ios::in);
    cout<<"details of the entered user is:-\n";
    cout<<"name:-"<<name<<endl<<"username:-\n"<<user_name<<endl;
    f2.close();
}
};
Database d;
fstream f1;
void finduser(string user)
{
    f1.open("database.txt",ios::in);
        f1.read((char*)(&d),sizeof(d));
        if(d.user()==user)
        {
            d.put();
            }
  f1.close();
}
void insertdata()
{
    cout<<"enter the details of the user you want to insert:-\n";
    f1.open("database.txt",ios::out|ios::app|ios::binary);
    d.get();
    f1.write((char*)(&d),sizeof(d));
    cout<<"the data is inserted successfully!!\n";
    f1.close();
}
void update()
{
    f1.open("database.txt",ios::binary| ios::in|ios::out);
        double n;
        cout<<"Enter password to search\n";
        cin>>n;
        f1.read((char*)&d,sizeof(d));

            if(d.pass()==n)
            {
                d.put();
                cout<<"Enter value to update"<<endl;
                f1.seekp(-sizeof(d),ios::cur);
                d.get();
                f1.write((char*)&d,sizeof(d));
                cout<<"The data is updated successfully!!\n";
            }
             else
                cout<<"\nRecord not found";
    f1.close();
}
void del()
{
    f1.open("database.txt",ios::binary| ios::in);
    fstream f2("temp.txt",ios::binary|ios::out);
    f1.seekg(0);
    if(!f1|| !f2)
        cout<<"Error in opening file";
    else
    {
        double r;
        cout<<"Enter password to delete\n";
        cin>>r;
        while(f1.read((char*)&d,sizeof(d)))
        {
            if(d.pass()!=r)
            {
                f2.write((char*)&d,sizeof(d));
            }

        }
        f1.close();
        f2.close();
        cout<<"The data is deleted successfully!!\n";
        remove("database.txt");
        rename("temp.txt","database.txt");


    }
}
int main()
{
    char condition;
f1.open("database.txt",ios::out);
do{
cout<<"enter the function you want to perform:-\n 1.GetData \n 2.DisplayData\n 3.InsertData\n 4.UpdateData\n 5.DeleteData\n6:FindUser\n";
 int choice;
 cin>>choice;
 switch(choice)
 {
 case 1:
    d.get();
     f1.write((char*)(&d),sizeof(d));
    break;
 case 2:
     f1.open("database.txt",ios::out);
    d.put();
    f1.read((char*)(&d),sizeof(d));
    break;
 case 3:
    insertdata();
    break;
 case 4:
    update();
    break;
 case 5:
    del();
    break;
 case 6:
     string user;
  cout<<"enter the user name whom you want to search:-\n";
  cin>>user;
  finduser(user);
  break;
     }
     cout<<"Do you want to continue:- y or n \n";
  cin>>condition;
}while(condition=='y' || condition=='Y');
     f1.close();
    return 0;
}
