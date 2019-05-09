#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>
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
			fout << products[i].name << "," << products[i].quantity << "," << products[i].price << endl;
		}
		fout.close();
	}
}
void readProducts(){
	string temp;
	fin.open(PRODUCT_FILE);
	if(fin.is_open()){
		while(getline(fin,temp)){
			string _name,_quantity,_price;
			Product tempProduct;
			stringstream linestream(temp);
			getline(linestream,_name,',');
			getline(linestream,_quantity,',');
			getline(linestream,_price,',');
			tempProduct.name = _name;
			tempProduct.quantity = stoi(_quantity.c_str());
			tempProduct.price  = stod(_price.c_str());
			products.push_back(tempProduct);
		}
		//products.pop_back();
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
void displayLogo(){
	cout << endl << endl;
//	cout << "	 ,---.  ,--.  ,--. ,-----. ,------.  " << endl;
//	cout << "	'   .-' |  '--'  |'  .-.  '|  .--. ' " << endl;
//	cout << "	`.  `-. |  .--.  ||  | |  ||  '--' | " << endl;
//	cout << "	.-'    ||  |  |  |'  '-'  '|  | --'  " << endl;
//	cout << "	`-----' `--'  `--' `-----' `--'      " << endl;
 	cout << "	 ___                      _                     ____            _                	" << endl; 
 	cout << "	|_ _|_ ____   _____ _ __ | |_ ___  _ __ _   _  / ___| _   _ ___| |_ ___ _ __ ___  	" << endl;
  	cout << "	 | || '_ \\ \\ / / _ \\ '_ \\| __/ _ \\| '__| | | | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ 	" << endl;	
  	cout << "	 | || | | \\ V /  __/ | | | || (_) | |  | |_| |  ___) | |_| \\__ \\ ||  __/ | | | | |	" << endl;
	cout << "	|___|_| |_|\\_/ \\___|_| |_|\\__\\___/|_|   \\__, | |____/ \\__, |___/\\__\\___|_| |_| |_|	" << endl;
        cout << "             			                 |___/         |___/  				" << endl;
	cout << endl;
}
void viewProducts(){
	displayLogo();
	cout << "		---View Products---" <<endl;
	if(products.size()){
		cout << "         NAME       PRICE   QUANTITY"<<endl;
		for(int i=0;i < products.size();i++){
			cout << setw(15) << products[i].name << setw(10) <<products[i].price << setw(10) <<products[i].quantity << endl;
		}
	}
	else{
		cout << "No Products to be displayed" << endl;
	}
	string temp;
	cout << endl << "Enter any key to continue...";
	cin >> temp;
}
void addProduct(){
	cin.clear();
	cin.ignore();
	Product temp;
	temp.name = "";
	cout << "---Add a Product---" << endl;
	cout << "Name : " ;
	getline(cin, temp.name);
	cout << "Price : ";
	cin >> temp.price;
	while(1){
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout << "Please Enter a Positive Number" << endl;
			cin>> temp.price;
		} else {
			break;
		}
	}
	cout << "Quantity : ";
	cin >> temp.quantity;
	while(1){
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout << "Please Enter a Positive Number" << endl;
			cin>> temp.quantity;
		} else{
			break;
		}
	}
	products.push_back(temp);
	cout << endl <<  "***Product Added Sucessfully***" << endl;
	return;
}
void deleteProduct(){
	string _name;
	displayLogo();
	cout << "		---Delete a Product---" << endl;
	cin.clear();
	cin.ignore();
	cout << "Name : ";
	getline(cin,_name);
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
	} else {
		cout << "Product not found" << endl;
	}
	if(confirm){
		products.erase(products.begin()+index);
		viewProducts();
		notifications.push_back("Deleted " + products[index].name + " successfully");
	}
}
void addQuantity(){
	string name;
	displayLogo();
	cout << "		---Add Quantity---" << endl;
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
void editProduct(){
	string _name;
	displayLogo();
	cin.clear();
	cin.ignore();
	cout << "		---Edit Product---" << endl;
	cout << "Enter Name : ";
	getline(cin,_name);
	int index = findProductByName(_name);
	if(index!=-1){
		double _newPrice;
		int _newQuantity;
		string _newName;
		cout << "Enter New Name : ";
		getline(cin,_newName);
		cout << "Enter New Price : ";
		cin >> _newPrice;
		cout << "Enter New Quantity : ";
		cin >> _newQuantity;
		products[index].name = _newName;
		products[index].price = _newPrice;
		products[index].quantity = _newQuantity;
		cout << "***Product Updated Successfully***" << endl;
	} else {
		cout << "Product Not Found" << endl;
	}
	string hold;
	cout << "Enter any key to continue..." << endl;
	cin >> hold;
	return;
}
void productManagement(){
	int choice;
	displayLogo();
	cout << "		---Products Management---" << endl;
	cout << "1 - Add a Product" << endl;
	cout << "2 - Delete a Product" << endl;
	cout << "3 - Add Quantity" << endl;
	cout << "4 - View Products" << endl;
	cout << "5 - Edit Product" << endl;
	cout << "Enter 0 To Go Back" << endl;
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
	} else if(choice==5){
		editProduct();
	}
	return;
}
void invoiceGeneration(){ 
	string name;
	vector<invoiceEntry> invoiceProducts;
       	double invoiceTotal = 0;
	displayLogo();	
	cout << "		---Invoice Generation---" << endl;
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
	cout << "	NAME 	     PRICE  QUANTITY 	 TOTAL"<<endl;
	for(int i = 0 ;i<invoiceProducts.size();i++){
		products[invoiceProducts[i].index].quantity-=invoiceProducts[i].quantity;
		string name = products[invoiceProducts[i].index].name;
		int quantity = invoiceProducts[i].quantity;
		double price = products[invoiceProducts[i].index].price;
		double total = price * quantity;
		invoiceTotal += total;
		cout << setw(15) << name << setw(10) << price << setw(10) << quantity << setw(10) << total <<endl;	
		lowQuantityChecker(invoiceProducts[i].index);
	}	
	cout << endl << setw(30)  <<"TOTAL = " << invoiceTotal << endl;	
	string hold;
	cout << endl << "Enter any key to continue..." << endl;
	cin >> hold;
	return;
}
void viewNotifications(){
	cout << "---Notifications---" << endl;
	if(notifications.size()){		
		for(int i = notifications.size(); i >= 0; i--){
			cout << notifications[i] << endl;
		}
		while(notifications.size()){
			notifications.pop_back();
		}
	} else {
		cout << "No Notifications Yet" << endl;
	}
	string hold;
	cout << endl <<"Enter any key to continue...." << endl;
	cin >> hold;
	return;	
}
bool displayMenu(){
	int choice;
	displayLogo();
	cout << "		---Main Menu----"<< endl;
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
