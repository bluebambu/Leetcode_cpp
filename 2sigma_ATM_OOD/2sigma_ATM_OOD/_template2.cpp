// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i < n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// ¿ª»§£¬µÇÂ½£¬ÊäÃÜÂëÊä´íÎå´ÎÍÌ¿¨£¬´æ¿îÈ¡¿î£¬´òÓ¡ÊÕ¾Ý£¬Ã»´òÓ¡Ö½·¢ÏûÏ¢¸ø·ÖÐÐ¾­Àí
// cash withdraw: get cash first, then emit card;   by-default amout: 50, 100, 500, ....;  
//					transaction fee 1.5; 
// balance inquiry:  Go back to menu when finishing
// cash transfer:  own bank/other bank;   target acc number;   amount;   report; 


// 3. ATM 重点说一下这题。有这样几个class要你implement
// class AccountStore
// class CardHandler
// class CashDispenser
// class CashIntake

// 	然后ATM class里面有写好的menu function，就是用户输入一个选项，然后switch case到这个选项。但是你要implement 到这个case之后的操作。比如
// case LOGIN:
// 	//TODO: implement function to support user login

// 	ATM有几个member
// 	AccountStore _accountstore; // store the account created at this ATM
// 	CardHandler _cardhanlder; // handles card read return
// 	CashDispenser _cashdispenser; // hanldes cash dispense
// 	CashIntake _cashintake; //

class Screen{
public:
	void display(const string &){}
}; 

class Keypad {
public:
	string getInput(){}
}; 

class CardHandler {
public:
}; 

class CashDispenser {
public:
}; 

class DipositSlot {
public:
}; 

class BankDatabase {
public:
	bool authenticateUsr(DebitCardInfo*, string&){}
}; 

class Account  {
public:
}; 

class DebitCardInfo{

};

class Transaction{
protected:
	Screen* _screen; 
	Keypad* _keypad; 
	BankDatabase* _bankDatabase; 
	Account* curAcc; 
	
public:
	Transaction(Screen* x, Keypad* y, BankDatabase* z, Account* ac) :_screen(x), _keypad(y), _bankDatabase(z), curAcc(ac){}
	virtual void execute();
};

class InquiryTrans :public Transaction{
public:
	InquiryTrans(Screen* x, Keypad* y, BankDatabase* z, Account* ac) :Transaction(x, y, z, ac) {}
	void execute(){
		_screen->display("Your account info is"); 
		string info = _bankDatabase->getAccountInfo(ac); 
		_screen->display(info); 
		_screen->display("press any key to exit"); 
		_keypad->getInput(); 
		return; 
	}
};

class DepositTrans :public Transaction{
protected:
	DipositSlot* _depositSlot; 
public:
	DepositTrans(Screen* x, Keypad* y, BankDatabase* z, Account* ac, DipositSlot* ds) :Transaction(x, y, z, ac), _depositSlot(ds) {}
	void execute(){
		_screen->display("please insert ur cash into dispenser"); 
		int realAmount = _depositSlot->receiveCash(); 
		// amount can be "CANCELLED!!"
		bool correctness = false; 
		_screen->display("your deposit amount is " + to_string(realAmount) + ", is it correct?"); 
		int status = stoi(_keypad->getInput()); 
		if (status == 1){
			bool bankStatus = _bankDatabase->confirmDeposit(ac, realAmount); 
			if (bankStatus == true){
				_screen->display("Completed transaction!"); 
				return; 
			}
			else{
				_screen->display("Failed to sync data with bank DB! Please contact service people! "); 
				_depositSlot->popCashBack(); 
			}
		}
		else{
			_screen->display("Mismatched number! Please re-input the number"); 
			_depositSlot->popCashBack(); 
		}
	}
};

class WithdrawTrans :public Transaction{
protected:
	CashDispenser* _cashDispenser; 
public:
	WithdrawTrans(Screen* x, Keypad* y, BankDatabase* z, Account* ac, CashDispenser* cd) :Transaction(x, y, z, ac), _cashDispenser(cd) {}
	void execute(){
		_screen->display("Please input amount you want to withdraw"); 
		unsigned amount = stoi(_keypad->getInput()); 
		// here amount command can be "Canceled!!" , so pay attention to this. 
		int bankStatus = _bankDatabase->confirmWithdraw(amount); 
		if (bankStatus == 0){
			_screen->display("Failed to sync data with bank DB. Please contact service guys"); 
			return; 
		}
		else if (bankStatus == 2){
			_screen->display("amount exceed your account balance. Please input another amount"); 
		}
		else{
			_screen->display("Completed transaction. Please take your cash"); 
			// here the cash dispenser might have not enought money!!!!! 
			_cashDispenser->dispense(amount); 
		}
	}
};

class ATM{
	Screen* _screen; 
	Keypad* _keypad; 
	CardHandler* _cardHdlr; 
	CashDispenser* _cashDispenser; 
	DipositSlot* _depositSlot; 
	BankDatabase* _bankDatabase; 
	
	bool isVerified; 
	bool isSuspicious; 
	int	pin_tried_times; 
	Account* curAcc; 

	const int MAX_TRIALS = 5; 

	enum{ INQUIRY ,DEPOSIT ,WITHDRAW ,EXIT }; 

public:
	ATM() :_screen(new Screen), _keypad(new Keypad), isVerified(false), isSuspicious(false), pin_tried_times(0) {}

	void run(){
		while (true){
			_screen->display("Please insert your card"); 
			DebitCardInfo *debit = _cardHdlr->receiveCard(); 

			while (!isVerified){
				if (_bankDatabase->checkSuspicious(debit)){
					_screen->display("Suspicious user, try again tomorrow"); 
					isSuspicious = true; 
					break;
				}

				isVerified = authenticateUsr(debit, pin_tried_times); 
				if (pin_tried_times > MAX_TRIALS){
					isSuspicious = true; 
					break; 
				}
			}
			
			if (isSuspicious){
				_screen->display("Exceeds max trials. Plese try again tomorrow. "); 
				_bankDatabase->registerSuspiciousAccount(debit); 
				break; 
			}
			
			curAcc = _bankDatabase->getAccount(debit); 
			bool isContinued = true; 
			while (isContinued){
				startTransactions(curAcc);
				_screen->display("Do you want to continue to operate? "); 
				isContinued = stoi(_keypad->getInput()); 
			}

			_screen->display("Operation completed. Thanks for using ATM.");
			isSuspicious = false; 
			isVerified = false; 
			pin_tried_times = 0; 
		}
	}

	bool authenticateUsr(DebitCardInfo* tmpInfo, int& pin_tried_times){
		_screen->display("Please input your PIN"); 
		string pin = _keypad->getInput(); 
		++pin_tried_times; 
		return _bankDatabase->authenticateUsr(tmpInfo, pin); 
	}

	void startTransactions(Account* curAcc){
		while (true){
			int transactOption = transactionMenu();
			Transaction* curTransaction;
			switch (transactOption) {
			case INQUIRY:
			case WITHDRAW:
			case DEPOSIT:
				curTransaction = genTrans(transactOption);
				curTransaction->execute(); 
				break;
			case EXIT:
				return; // exit
			default:
				_screen->display("Invalid input. Re-input please");
				break;
			}
		}
	}

	int transactionMenu(){
		_screen->display("1. Inquiry. 2.Deposit. 3.Withdraw. 4. Exit\n Please input your choice: "); 
		int choice = stoi(_keypad->getInput()); 
		return choice; 
	}

	Transaction* genTrans(int option){
		switch (option) {
		case INQUIRY: return new InquiryTrans(_screen, _keypad, _bankDatabase, curAcc);
		case WITHDRAW: return new WithdrawTrans(_screen, _keypad, _bankDatabase, curAcc, _cashDispenser);
		case DEPOSIT: return new DepositTrans(_screen, _keypad, _bankDatabase, curAcc, _depositSlot);
		}
	}
};




int main(){
	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

