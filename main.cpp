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

class SplitLogic{
    public:
        virtual unordered_map<string,double>split(double amt,vector<string>& participants)=0;

};

class EqualSplitLogic: public SplitLogic{
    public:
        unordered_map<string,double> split(double amt,vector<string>& participants){
            unordered_map<string,double> result;
            double eachshare=amt/participants.size();
            
            for(auto member:participants){
                result[member]=eachshare;
            }
            return result;
        }
};

class BalanceData{
    private:
        unordered_map<string,unordered_map<string,double>> balances;
    public:
        void updateBalance(string payee,unordered_map<string,double>& splitdata){
            for(auto& data:splitdata){
                string user=data.first;
                double amt=data.second;

                if(user==payee) continue;

                balances[user][payee]+=amt;
            }
        }

        void showBalance(){
            for(auto debtor:balances){
                for(auto creditor:debtor.second){
                    cout<< debtor.first<<" HAS TO PAY Rs."<< creditor.second<<" TO "<< creditor.first<<endl;
                }
            }
        }

};
class ExpenseManager{
    private:
        vector<User> users;
        vector<Expense> expenseList;
        BalanceData balances;

    public:
        void addUser(User& user){
            users.push_back(user);
        }
        void addExpense(Expense& exp,SplitLogic* logic){
            auto splits=logic->split(exp.getAmount(),exp.getParticipants());

            balances.updateBalance(exp.getPaidBy(),splits);
            expenseList.push_back(exp);
        }
        void showBalance(){
            balances.showBalance();
        }
        vector<Expense>& getExpenses(){
            return expenseList;
        }
        void viewExpenses(ExpenseViewer& viewer){
            viewer.displayExpenseList(expenseList);
        }
};

int main(){
    return 0;
}