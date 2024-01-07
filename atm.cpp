#include <iostream>
#include <ios>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <string>


using namespace std;

const short int FAST_CASH = 1;
const short int WITHDRAW = 2;
const short int DEPOSIT = 3;
const short int CHECK_BALANCE = 4;
const short int GET_CARD_BACK = 5;
const char FILLER = '-';
const short int COL_WIDTH = 20;

// Struct wasn't neccessary since all the info is balance but I wanted to use pointer ( -> ) :)
struct bankAccount {
    string accountNumber;
    string name;
    double balance;
    struct bankAccount *next;
};

bool runClientMode();
bool runBankerMode();

// ---- [ Menu Options for Customer ] -----
void fastCash(bankAccount*);
void withdraw(bankAccount*);
void deposit(bankAccount*);
void checkBalance(const bankAccount*);

// ---- [ Menu Options for Banker ] -----
void displayUserMenu();
void displayListOfCs(bankAccount*, double = 0, string = " ");
void filterCs(bankAccount *head, bool);
void addBankAccountInterface(bankAccount *);
void sortInterface(bankAccount*);
void deleteAccountInterface(bankAccount *);

///  ---- [ HERLPER FUNCTIONS ] ----
void addBankAcount(bankAccount*, string, string, double);
void sortBalance(bankAccount*);
bool deleteAccount(bankAccount*, string);
void sortName(bankAccount*);
// Compare names for sorting
bool nameComparer(string, string);
// Gets formatted account number
string getAccountNumber();
void sortAccountNumber(bankAccount*);
// Clear the buffer to avoid unwanted behavior
void clearBuffer();
// free all allocated space with 'new'
void freeMem(bankAccount*);
// Easier to test, just fills the single linked list with dummy data
void fillListWithDummyData(bankAccount *);
// Transforms string to lowercase
string toLowerString(const string);
// Get bank account
bankAccount* getBankAccount(string);
// Initialize the balance of the bank account to random (1 - 1001)
void initializeAccountBalance(bankAccount*);
// Check if pin is valid
bool checkPin();
// Check if receipt is wanted
void checkIfReceiptWanted(bool*);
// Get a valid entry for the given options
int checkEntry(const int, const int);
/* 
   Checking the validity of the entry should be done in graphical interface (keypad) 
   assuming the program is running on the client side and manual input is also acceptable (keyboard)
   the validation of the entry will be checked in case of not proper input 
*/
double getValidAmount();

int main()
{    
    int entry;
    cout << "1 --> customer\n2 --> banker\n";
    entry = checkEntry(1, 2);
    if(entry == 1){
        runClientMode();
    }else runBankerMode();
    return 0;
}

void initializeAccountBalance(bankAccount *p)
{
    srand((unsigned int)time(NULL));
    p->balance = rand() % 1000 + 1;
}

bool checkPin(){
    short int tries = 0;
    string pin;
    while(tries < 3)
    {
        cout << "Enter personal identification number pin: ";
        try
        {
            cin >> pin;
            if(pin.length() != 4 ||
                !isdigit(pin[0]) ||
                !isdigit(pin[1]) ||
                !isdigit(pin[2]) ||
                !isdigit(pin[3]) 
            )
            {
                throw "Invalid PIN, try again . . .";
            }
        }
        catch (const char *e) 
        {  
            cerr << e << '\n';
            tries++;
            continue;  
        }  
        return true;
    }
    cout << "Sorry you can't continue, contact your bank for assistance!" << endl;
    return false;
}

void checkIfReceiptWanted(bool *isReceiptWanted){
    system("clear"); 
    int entry;
    cout << "Would you like a receipt at the end? \n 1 --> YES  \t 2 <-- NO \n";
    entry = checkEntry(1, 2);
    *isReceiptWanted = (entry == 1 ? true : false);
}

int checkEntry(const int minEntries, const int maxEntries){
    int entry;
    while(true)
    {
        cout<< "Enter your choice: ";
        try
        {
            cin >> entry;
            if(entry < minEntries || entry > maxEntries) throw "Invalid entry, try again . . .";
        }
        catch(const char *e)
        {
            cerr << e << '\n';
            clearBuffer();
            continue;
        }
        system("clear");
        break;
    }
    return entry;
}

void displayUserMenu(){
    cout << "CHOOSE FROM THE FOLLOWING:\n";
    cout << " 1 --> Fast Cash \t Withdraw <-- 2 \n 3 --> Deposit \t\t Check Balance <-- 4 \n 5 --> Get Card Back \n";
}

void fastCash(bankAccount *p)
{
    int entry;
    int amountToWithdraw;
    while(true){
        cout << "Press:\n1 --> $20.00\t\t$40.00  <-- 2\n3 --> $80.00\t\t$100.00 <-- 4\n0 --> Cancel\n";
        entry = checkEntry(0, 4);
        switch (entry)
        {
            case 0:
                amountToWithdraw = 0;
                break;
            case 1:
                amountToWithdraw = 20;
                break;
            case 2:
                amountToWithdraw = 40;
                break;
            case 3:
                amountToWithdraw = 80;
                break;
            case 4:
                amountToWithdraw = 100;
                break;
                
        }
        if(amountToWithdraw > p -> balance)
        {
            cout << "Sorry not enough balance\n";
            continue;
        } 
        if(amountToWithdraw != 0)
        {
            cout << "Take your cash...\n\n";
            p -> balance -= amountToWithdraw;
        }
        checkBalance(p);
        break;
    }
}

void withdraw(bankAccount *p){
    double amountToWithdraw;
    system("clear");
    while(true){
        cout << "Enter amount (enter 0 to cancel): ";
        amountToWithdraw = getValidAmount();
        if(amountToWithdraw > p -> balance)
        {
            cout << "Sorry not enough balance\n";
            continue;
        } 

        if(amountToWithdraw != 0) 
        {
            p -> balance -= amountToWithdraw;
            cout << "Take your cash...\n\n";
        }
        checkBalance(p);
        break;
    }
}

void deposit(bankAccount *p){
    system("clear");
    cout << "Enter amount (enter 0 to cancel): ";
    p -> balance += getValidAmount();
    checkBalance(p);
}

void checkBalance(const bankAccount *p)
{
    system("clear");
    cout <<"Your balance is: $"<< p -> balance << "\n\n";
}

double getValidAmount()
{
    double validAmount;
    while(true)
    {
        try
        {
            cin >> validAmount;
            if(cin.fail()) throw "Invalid entry, try again...";
        }
        catch (const char* e)
        {
            cout << e << endl;
            clearBuffer();
            continue;
        }
        
        break;
    }
    return validAmount;
}

bool runClientMode()
{
    bankAccount myBankAccount;
    bankAccount *p_myBankAccount = &myBankAccount;
    bool isReceiptWanted;
    bool *p_isReceiptWanted = &isReceiptWanted;
    bool isInteracting = true;
    int entry;
    system("clear");
    
    // cout config
    cout << setprecision(2) << fixed;

    // Initialize the bank account balance
    initializeAccountBalance(p_myBankAccount);

    // If pin is entered incorrectly 3 times end program
    if(!checkPin()) return false;

    // Check if customer wants receipt
    checkIfReceiptWanted(p_isReceiptWanted);

    // Interaction Loop
    while(isInteracting)
    {
        displayUserMenu();
        entry = checkEntry(1, 5);
        system("clear");

        switch(entry) {
            case FAST_CASH:
                fastCash(p_myBankAccount);
                break;
            case WITHDRAW:
                withdraw(p_myBankAccount);
                break;
            case DEPOSIT:
                deposit(p_myBankAccount);
                break;
            case CHECK_BALANCE:
                checkBalance(p_myBankAccount);
                break;
            case GET_CARD_BACK:
                isInteracting = false;
                continue;             
        }

        cout << "1 --> Another Transaction\t\tGet Card Back <-- 2\n";
        entry = checkEntry(1, 2);
        if(entry == 1){
            system("clear");
        } else isInteracting = false;
    }
    if (isReceiptWanted) cout << "Take your receipt...\n\n";
    cout << "THANK FOR USING OUR VIRTUAL BANK SYSTEM\nGOODBYE. . . \n";
    return true;
}

void displayBankerMenu(){
    cout << "CHOOSE FROM THE FOLLOWING:\n";
    cout << " 1 --> Display all customers \n" <<
            " 2 --> Display customer w/ balance greater than a value\n" <<
            " 3 --> Search \n" <<
            " 4 --> Sort \n" <<
            " 5 --> Delete an account \n" <<
            " 6 --> Add a new account \n" <<
            " 7 --> Exit \n";
}

bool runBankerMode()
{
    bankAccount *_headList = new bankAccount;
    _headList -> accountNumber = "0000000";
    _headList -> balance = 0;
    _headList -> name = "head";
    _headList -> next = nullptr;

    int entry;
    bool isInteracting = true;

    fillListWithDummyData(_headList);
    while (isInteracting)
    {
        system("clear");
        displayBankerMenu();
        entry = checkEntry(1, 7);
        switch(entry){
            case 1:
                system("clear");
                displayListOfCs(_headList);
                cout << "Enter 1 to continue: ";
                cin.get();
                clearBuffer();
                system("clear");
                break;
            case 2:
                system("clear");
                filterCs(_headList, false);
                break;
            case 3:
                system("clear");
                filterCs(_headList, true);
                break;
            case 4:
                system("clear");
                sortInterface(_headList);
                break;
            case 5:
                system("clear");
                deleteAccountInterface(_headList);
                cout << "Enter 1 to continue: ";
                cin.get();
                clearBuffer();
                system("clear");
                break;
            case 6:
                system("clear");
                addBankAccountInterface(_headList);
                cout << "Customer Added to the database…" << endl;
                cout << "Enter 1 to continue: ";
                cin.get();
                clearBuffer();
                system("clear");
                break;
            case 7:
                system("clear");
                isInteracting = false;
                break;
        }
        
    }
    freeMem(_headList);
    system("clear");
    cout<<"GOODBYE...\n";
    return true;
}

void sortInterface(bankAccount *head){
    char c_entry;
    cout << "a --> \tsort by name\nb --> \tsort by account number\nc --> \tsort by balance\nx --> \treturn main menu\n";
    cout << "Your option here: ";
    while(true)
    {
        try
        {
            cin >> c_entry;
            if (c_entry != 'a' && c_entry != 'b' && c_entry != 'c' && c_entry != 'x') throw "Invalid entry, try again...";
        }
        catch (const char* e)
        {
            cout << e << endl;
            clearBuffer();
            continue;
        }
        clearBuffer();
        break;
    }
    switch(c_entry){
        case 'a':
            sortName(head);
            break;
        case 'b':
            sortAccountNumber(head);
            break;
        case 'c':
            sortBalance(head);
            break;
        case 'x':
            break;
        
    }
    system("clear");
}

void sortBalance(bankAccount *head){
    if(head -> next == nullptr) return;
    // first value to compare
    bankAccount *current = head -> next;
    // this is the node before the first value to compare
    bankAccount *beforeCurrent = head;
    // index to traverse linked list
    bankAccount *index;
    // this is the node before the second value to compare
    bankAccount *nodeBeforeSmallest;
    // trigger for any changes required
    bool changes;
    // safe the smallest value
    double smallest;
    // while we are in the linked list
    while(current){
        // start comparison at the same node of current since we are comparing the one ahead
        index = current;
        // Initializing to the current for comparison
        nodeBeforeSmallest = current;
        // reset trigger
        changes = false;
        // reset smallest value
        smallest = current -> balance;
        // while there is another node in the list
        while(index -> next){
            // if the following node is smaller than safed node, safe this previos address and set new smaller value
            if(index -> next -> balance < smallest){
                changes = true;
                smallest = index -> next -> balance;
                nodeBeforeSmallest = index;
            }
            // continue traversing linked list
            index = index -> next;
        }
        // if any changes are necessary
        if (changes)
        {            
            // since current is not where is suposed to be the previous node to current points to the right node
            beforeCurrent -> next = nodeBeforeSmallest -> next;
            // if current and nodeBeforeSmallest are the same it means they are next to each other
            // due to the nature of my algorithm some changes need to be made
            if(current != nodeBeforeSmallest){                    
                    // switch pointing addresses
                    index = current -> next;
                    current -> next = nodeBeforeSmallest -> next -> next;
                    nodeBeforeSmallest -> next -> next = index;
                    nodeBeforeSmallest -> next = current;
            } else {
                    // if they are adjacent switch addresses a little different
                    index = current -> next;
                    current -> next = current -> next -> next; 
                    index -> next = current;
            }
            // adjust so the next node is the actual next in our new linked list
            current = beforeCurrent -> next;            
        }
        // keep going
        current = current -> next;
        beforeCurrent = beforeCurrent -> next;
    }
}

void sortName(bankAccount *head){
    if(head -> next == nullptr) return;
    // first value to compare
    bankAccount *current = head -> next;
    // this is the node before the first value to compare
    bankAccount *beforeCurrent = head;
    // index to traverse linked list
    bankAccount *index;
    // this is the node before the second value to compare
    bankAccount *nodeBeforeSmallest;
    // trigger for any changes required
    bool changes;
    // safe the smallest value
    string smallest;
    // while we are in the linked list
    while(current){
        // start comparison at the same node of current since we are comparing the one ahead
        index = current;
        // Initializing to the current for comparison
        nodeBeforeSmallest = current;
        // reset trigger
        changes = false;
        // reset smallest value
        smallest = current -> name;
        // while there is another node in the list
        while(index -> next){
            // if the following node is smaller than safed node, safe this previos address and set new smaller value
            if(nameComparer(index -> next -> name , smallest)){
                changes = true;
                smallest = index -> next -> name;
                nodeBeforeSmallest = index;
            }
            // continue traversing linked list
            index = index -> next;
        }
        // if any changes are necessary
        if (changes)
        {
            // since current is not where is suposed to be the previous node to current points to the right node
            beforeCurrent -> next = nodeBeforeSmallest -> next;
            // if current and nodeBeforeSmallest are the same it means they are next to each other
            // due to the nature of my algorithm some changes need to be made
            if(current != nodeBeforeSmallest){
                    // switch pointing addresses
                    index = current -> next;
                    current -> next = nodeBeforeSmallest -> next -> next;
                    nodeBeforeSmallest -> next -> next = index;
                    nodeBeforeSmallest -> next = current;
            } else {
                    // if they are adjacent switch addresses a little different
                    index = current -> next;
                    current -> next = current -> next -> next; 
                    index -> next = current;
            }
            // adjust so the next node is the actual next in our new linked list
            current = beforeCurrent -> next;
        }
        // keep going
        current = current -> next;
        beforeCurrent = beforeCurrent -> next;
    }
}

bool nameComparer(string name, string comparedTo){
    if (tolower(name[0]) < tolower(comparedTo[0])) return true;
    else if(tolower(name[0]) > tolower(comparedTo[0]) || name == comparedTo) return false;

    name = toLowerString(name);
    comparedTo = toLowerString(comparedTo);
    for(int i = 0; i < name.length(); i++){
        if(i == comparedTo.length()) return false;
        if (name[i] < comparedTo[i]) return true;
        else if(name[i] > comparedTo[i]) return false;
    }
    return false;
}

void sortAccountNumber(bankAccount *head){
    if(head -> next == nullptr) return;
    // first value to compare
    bankAccount *current = head -> next;
    // this is the node before the first value to compare
    bankAccount *beforeCurrent = head;
    // index to traverse linked list
    bankAccount *index;
    // this is the node before the second value to compare
    bankAccount *nodeBeforeSmallest;
    // trigger for any changes required
    bool changes;
    // safe the smallest value
    int accountNumber;
    // while we are in the linked list
    while(current){
        // start comparison at the same node of current since we are comparing the one ahead
        index = current;
        // Initializing to the current for comparison
        nodeBeforeSmallest = current;
        // reset trigger
        changes = false;
        // reset smallest value
        accountNumber = stoi(current -> accountNumber);
        // while there is another node in the list
        while(index -> next){
            // if the following node is smaller than safed node, safe this previos address and set new smaller value
            if(stoi(index -> next -> accountNumber) < accountNumber){
                changes = true;
                accountNumber = stoi(index -> next -> accountNumber);
                nodeBeforeSmallest = index;
            }
            // continue traversing linked list
            index = index -> next;
        }
        // if any changes are necessary
        if (changes)
        {
            // since current is not where is suposed to be the previous node to current points to the right node
            beforeCurrent -> next = nodeBeforeSmallest -> next;
            // if current and nodeBeforeSmallest are the same it means they are next to each other
            // due to the nature of my algorithm some changes need to be made
            if(current != nodeBeforeSmallest){                                        
                    // switch pointing addresses
                    index = current -> next;
                    current -> next = nodeBeforeSmallest -> next -> next;                    
                    nodeBeforeSmallest -> next -> next = index;
                    nodeBeforeSmallest -> next = current;
            } else {
                    // if they are adjacent switch addresses a little different
                    index = current -> next;
                    current -> next = current -> next -> next; 
                    index -> next = current;
            }
            // adjust so the next node is the actual next in our new linked list
            current = beforeCurrent -> next;
        }
        // keep going
        current = current -> next;
        beforeCurrent = beforeCurrent -> next;
    }
}

void addBankAccountInterface(bankAccount *head)
{
    string bankAccountNumber;
    string name;
    double balance;

    // get Account Number with format check
    bankAccountNumber = getAccountNumber();
    
    // get Name with format check
    while(true)
    {
        cout << "Enter name: ";
        try
        {
            getline(cin, name);
            if(name.find(' ') == string::npos)
            {
                throw "Invalid Name, use format \"Name Lastname\", try again...";
            }
        }
        catch (const char *e) 
        {  
            cerr << e << '\n';
            continue;  
        } 
        break;
    }
 
    cout << "Opening Balance: ";
    balance = getValidAmount();
    system("clear");
    addBankAcount(head, bankAccountNumber, name, balance);
}

void filterCs(bankAccount *head, bool search){
    if (search){
        string q;
        cout << "Enter you search: ";
        clearBuffer();
        getline(cin, q);
        q = toLowerString(q);
        system("clear");
        displayListOfCs(head, 0, q);
    }
    else{
        double balance;
        cout << "Enter minimum balance: ";
        balance = getValidAmount();
        system("clear");
        displayListOfCs(head, balance);
    }
    cout << "Enter 1 to continue: ";
    cin.get();
    clearBuffer();
    system("clear");
}

void addBankAcount(bankAccount *p, string accountNumber, string name, double balance)
{
    bankAccount *newBankAccount = new bankAccount;
    newBankAccount -> accountNumber = accountNumber;
    newBankAccount -> name = name;
    newBankAccount -> balance = balance;
    if (p->next){
        newBankAccount -> next = p->next;
        p -> next = newBankAccount;
    }
    else {
        p->next = newBankAccount;
        newBankAccount -> next = nullptr;
    }
}

void displayListOfCs(bankAccount *head, double minBalance, string _q)
{
    if (head == nullptr) return;
    if (head -> accountNumber == "0000000"){
        cout << setfill('*') << setw(COL_WIDTH *3) << '*' << endl;
        cout << left << setfill(' ') << setw(COL_WIDTH) << "Account#" << setw(COL_WIDTH) 
        << "Name" << setw(COL_WIDTH) << right << "Balance"<< endl;
        cout << setfill(FILLER) << setw(COL_WIDTH *3) << FILLER << endl;
    }
    else if(head -> balance > minBalance && toLowerString(head -> name).find(_q) != string::npos){
        cout<< fixed << setprecision(2) << left << setfill(' ') << setw(COL_WIDTH) << head -> accountNumber << setw(COL_WIDTH) 
        << head -> name << setw(COL_WIDTH) << right << head -> balance << endl;
        cout << setfill(FILLER) << setw(COL_WIDTH *3) << FILLER << endl;
    }

    if ( head -> next != nullptr )
    {
        displayListOfCs(head->next, minBalance, _q);
    }
    else{
        cout << setfill('*') << setw(COL_WIDTH *3) << '*' << endl;
    }
}

void deleteAccountInterface(bankAccount *head){
    displayListOfCs(head);
    string accountNumber;
    accountNumber = getAccountNumber();
    if (deleteAccount(head, accountNumber)) cout << "Account successfully deleted." << endl;
    else cout<< "Couldn't find account with that number.";
}

bool deleteAccount(bankAccount *head, string accountNumber){
    bankAccount *index = head;
    bankAccount *deletionTarget;
    while(index -> next){
        if (index -> next -> accountNumber == accountNumber){
            deletionTarget = index -> next;
            index -> next = index -> next -> next;
            delete(deletionTarget);
            return true;
        }
        index = index -> next;
    }
    return false;
}

void freeMem(bankAccount *head){
    if(head->next) freeMem(head -> next);
    delete(head);
}

string getAccountNumber(){
    string bankAccountNumber;
    while(true)
    {
        cout << "Enter account number: ";
        try
        {
            cin >> bankAccountNumber;
            if(bankAccountNumber.length() != 7 ||
                bankAccountNumber == "0000000" ||
                !isdigit(bankAccountNumber[0]) ||
                !isdigit(bankAccountNumber[1]) ||
                !isdigit(bankAccountNumber[2]) ||
                !isdigit(bankAccountNumber[3]) ||
                !isdigit(bankAccountNumber[4]) ||
                !isdigit(bankAccountNumber[5]) ||
                !isdigit(bankAccountNumber[6]) 
            )
            {
                throw "Invalid Account Number, try again . . .";
            }
        }
        catch (const char *e) 
        {  
            cerr << e << '\n';
            continue;  
        } 
        clearBuffer();
        return bankAccountNumber;
    }
}

string toLowerString(const string s)
{
    string temp = s;
    for (auto& x : temp) { 
        x = tolower(x); 
    } 
    return temp;
}

void fillListWithDummyData(bankAccount *head)
{
    addBankAcount(head, "1200457" ,"John Smith", 1245.32);
    addBankAcount(head, "1257441" ,"Safia Walter", 15.23);
    addBankAcount(head, "8542212" ,"Kevin Broke", 0.21);
    addBankAcount(head, "6565741" ,"Todd Rich", 55656.28);
    addBankAcount(head, "1215478" ,"Laura Happy", 887.66);
}

void clearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
