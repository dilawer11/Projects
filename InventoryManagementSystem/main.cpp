#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;
//Structs
struct Product{
	string name;
	int quantity;
	double price;
};
struct invoiceEntry{
	int index;
	int quantity;
};
//Structs End
//Globals
ofstream fout;
ifstream fin;
#define MIN_QUANTITY 10
#define PRODUCT_FILE "products.txt"
vector<string> notifications;
vector<Product> products;
//Globals End
//File Handling Functions
void writeProducts(){
	fout.open(PRODUCT_FILE);
	if(fout.is_open()){
		for(int i=0;i<products.size();i++){
			fout << products[i].name << " " << products[i].quantity << " " << products[i].price << endl;
		}
		fout.close();
	}
}
void readProducts(){
	string temp;
	fin.open(PRODUCT_FILE);
	if(fin.is_open()){
		while(!fin.eof()){
			Product temp;
			fin >> temp.name >> temp.quantity >> temp.price;
			products.push_back(temp);
		}
		products.pop_back();
	}
}
//File Handling Functions End
string getDate(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
	return buffer;
}
void lowQuantityChecker(int index){
	if(products[index].quantity < MIN_QUANTITY){
		notifications.push_back("Product : " + products[index].name + " is below min quantity level");
	}
	return;	
}
int findProductByName(string name){
	for(int i = 0; i < products.size(); i++){
		if(name == products[i].name){
			return i;
		}
	}
	return -1;
}
void addProduct(){
	Product temp;
	cout << "---Add a Product---" << endl;
	cout << "Name : ";
	cin >> temp.name;
	cout << "Price : ";
	cin >> temp.price;
	cout << "Quantity : ";
	cin >> temp.quantity;
	products.push_back(temp);
	return;
}
void deleteProduct(){
	string _name;
	cout << "---Delete a Product---" << endl;
	cout << "Name : ";
	cin >> _name;
	int index = -1;
	bool confirm = false;
	for(int i = 0; i < products.size();i++){
		if(products[i].name==_name){
			index = i;
			break;
		}
	}
	if(index!=-1){
		string option;
		cout <<  "Are you sure you want to delete " << products[index].name << " (y/n)"<<endl;
		cin >> option;
		if(option=="y" || option == "Y"){
			confirm = true;	
		}
	}
	if(confirm){
		products.erase(products.begin()+index);
	}
}
void addQuantity(){
	string name;
	cout << "---Add Quantity---" << endl;
	cout << "Enter Name : ";
	cin >> name;
	int index = findProductByName(name);
	if(index!=-1){
		int _quantity;
		cout << "Enter Quantity : ";
		cin >> _quantity;
		products[index].quantity += _quantity;
	} else{
		cout << "Product Not Found" << endl;
	}
}
void viewProducts(){
	cout << "---View Products---" <<endl;
	if(products.size()){
		cout << "  NAME     PRICE     QUANTITY"<<endl;
		for(int i=0;i < products.size();i++){
			cout << products[i].name << " " << products[i].price << " " <<products[i].quantity << endl;
		}
	}
	else{
		cout << "No Products to be displayed" << endl;
	}
}
void productManagement(){
	int choice;
	cout << "---Products Management---" << endl;
	cout << "1 - Add a Product" << endl;
	cout << "2 - Delete a Product" << endl;
	cout << "3 - Add Quantity" << endl;
	cout << "4 - View Products" << endl;
	cout << "Enter Any Key To Go Back" << endl;
	cout << endl << "--> ";
	cin >> choice;
	cout << endl;
	if(choice==1){
		addProduct();
	} else if(choice==2){
		deleteProduct();
	} else if(choice==3){
		addQuantity();
	} else if(choice==4){
		viewProducts();
	}
	return;
}
void invoiceGeneration(){ 
	string name;
	vector<invoiceEntry> invoiceProducts;
       	double invoiceTotal = 0;	
	cout << "---Invoice Generation---" << endl;
	cout << "Date : " << getDate() << endl;
	while(name!="0"){
		cout << "Enter Name(0 for Done): ";
		cin >> name;
		int index = findProductByName(name);
		if(name=="0"){
			break;
		} else if(index!=-1){
			int quantity = 0;
			cout << "Enter Quantity: ";
			cin >> quantity;
			if(quantity<1){
				cout << "Quantity must be greater than 0" << endl;
			} else if(quantity > products[index].quantity){
				cout << "Quantity more than in stock quantity" << endl;
			} else{
				invoiceEntry temp;
				temp.index = index;
				temp.quantity = quantity;
				invoiceProducts.push_back(temp);
			}	
		} else{
			cout << "Product Not Found" << endl;
		}
	}
	cout << "NAME PRICE QUANTITY TOTAL"<<endl;
	for(int i = 0 ;i<invoiceProducts.size();i++){
		products[invoiceProducts[i].index].quantity-=invoiceProducts[i].quantity;
		string name = products[invoiceProducts[i].index].name;
		int quantity = invoiceProducts[i].quantity;
		double price = products[invoiceProducts[i].index].price;
		double total = price * quantity;
		invoiceTotal += total;
		cout<< name << " " << price << " " << quantity << " " << total <<endl;	
		lowQuantityChecker(invoiceProducts[i].index);
	}	
	cout << "TOTAL = " << invoiceTotal << endl;	
}
void viewNotifications(){
	cout << "---Notifications---" << endl;
	for(int i = notifications.size(); i >= 0; i--){
		cout << notifications[i] << endl;
	}
	while(notifications.size()){
		notifications.pop_back();
	}
	return;	
}
bool displayMenu(){
	int choice;
	cout << "---Main Menu----"<< endl;
	cout << "1 - Product Management" << endl;
	cout << "2 - Invoice Generation" << endl;
	cout << "3 - Notifications("<<notifications.size()<<")" << endl;
	cout << "0 - To Exit" << endl;
	cout << endl << "--> ";
	cin >> choice;
	cout << endl;
	if(choice==1){
		productManagement();
	} else if(choice == 2){
		invoiceGeneration();
	} else if(choice ==  3){
		viewNotifications();
	} else if (choice != 0){
		cout << "Invalid Choice" << endl;
	}
	return !choice;
}

int main(){
	readProducts();
	bool exitSystem = false;
	while(!exitSystem){
		exitSystem = displayMenu();
	}
	writeProducts();
	return 0;
}
