#include<bits/stdc++.h>
using namespace std;

class User{
    private:
        int id;
        string name;
    public:
        User(int id,string name){
            this->id=id;
            this->name=name;
        }

        int getId(){
            return id;
        }
        string getName(){
            return name;
        }
};

class Expense{
    private:
        int expenseId;
        string description;
        double amount;
        string paidBy;
        vector<string> participants;
    public:
        Expense(int expenseId,string description,double amount,string paidBy,vector<string>& participants){
            this->expenseId=expenseId;
            this->description=description;
            this->amount=amount;
            this->paidBy=paidBy;
            this->participants=participants;
        }
        int getexpenseId(){
            return expenseId;
        }
        string getDescription(){
            return description;
        }
        double getAmount(){
            return amount;
        }
        string getPaidBy(){
            return paidBy;
        }
        vector<string>& getParticipants(){
            return participants;
        }
};

class ExpenseViewer{
    public:
        void displayExpenseList(vector<Expense>& expenseList){
            if(expenseList.empty()){
                cout<<"No Current Expenses\n";
                return;
            }
            for(Expense& exp:expenseList){
                cout<<"Expense ID: "<<exp.getexpenseId()<<endl;
                cout<<"Description: "<<exp.getDescription()<<endl;
                cout<<"Total Amount: "<<exp.getAmount()<<endl;
                cout<<"Paid By: "<<exp.getPaidBy()<<endl;
                cout<<"\n*************************************\n";
            }
        }
};
class ExpenseManager{
    private:
        vector<User> users;
        vector<Expense> expenseList;
        unordered_map<string,unordered_map<string,double>> balances;

    public:
        void addUser(int id,string name){
            users.push_back(User(id,name));
        }
        void addExpense(int expid,string desc,double amt,string paidby,vector<string> participants){

            if(participants.empty() || amt==0){
                return;
            }
            expenseList.push_back(Expense(expid,desc,amt,paidby,participants));
            double share=amt/participants.size();
            for(auto mem:participants){
                if(mem==paidby) continue;
                balances[mem][paidby]+=share;
            }

            ofstream file("expenses.txt",ios::app);
            file<<expid<<","<<desc<<","<<amt<<","<<paidby;
            for(auto mem:participants){
                file<<","<<mem;
            }
            file<<endl;
            file.close();
        }
        void showBalance(){
            if(balances.empty()){
                cout<<"All Settled! \n";
                return;
            }
            for(auto debtor:balances){
                for(auto creditor:debtor.second){
                    cout<< debtor.first<<" HAS TO PAY Rs."<< creditor.second<<" TO "<< creditor.first<<endl;
                }
            }
        }
        vector<Expense>& getExpenses(){
            return expenseList;
        }
        void viewExpenses(ExpenseViewer& viewer){
            viewer.displayExpenseList(expenseList);
        }
};

int main(){
    ExpenseManager manager;
    ExpenseViewer viewer;

    int choice;
    while(true){
        cout<<"\n 1. Add User \n 2. Add Expense \n 3. Show Expense \n 4. Show Balance \n 5. Exit\n";
        cout<<"ENTER CHOICE: \n";
        cin>>choice;

        if(choice==1){
            int id;
            string name;
            cout<<"Enter User ID: ";cin>>id;
            cout<<"Enter Name: ";cin>>name;

            manager.addUser(id,name);
            cout<<"User Added Succesfully.\n";
        }
        else if(choice==2){
            int expid;
            double amt;
            string desc,paidBy;
            int n;

            cout<<"Expense ID: ";
            cin>>expid;
            cout<<"Description: ";
            cin.ignore();
            getline(cin,desc);
            cout<<"Total Amount: ";
            cin>>amt;
            cout<<"Paid By: ";
            cin>>paidBy;
            cout<<"Number of Participants: ";
            cin>>n;

            vector<string> participants;
            for(int i=0;i<n;i++){
                string name;
                cout<<"Participant "<<i+1<<": ";
                cin>>name;
                participants.push_back(name);
            }
            manager.addExpense(expid,desc,amt,paidBy,participants);
            cout<<"Expense Added Successfully\n";

        }
        else if(choice==3){
            manager.viewExpenses(viewer);
        }
        else if(choice==4){
            manager.showBalance();
        }
        else if(choice==5){
            cout<<"Exiting Program...";
            break;
        }
    }

    return 0;
}

