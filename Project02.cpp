#include <iostream>
#include<fstream>
using namespace std;

class Store {
	private:
	char itemName[30], brand[30], detail[100];
	int product_id, quantity;
	float product_price;
	
	public:
		void registeer(){
			cin.getline(itemName, 30);
			cout << "\n\t\t\t\t\t Please Enter Product Name: ";
			cin.getline(itemName, 30);
			cout << "\n\t\t\t\t\t Please Enter Product Brand: ";
			cin.getline(brand,30);
			cout << "\n\t\t\t\t\t Please Enter Product Detail: ";
			cin.getline(detail, 100);
			cout << "\n\t\t\t\t\t Please Enter Product Code: " ;
			cin >> product_id;
			cout << "\n\t\t\t\t\t Please Enter Product Quantity: ";
			cin >> quantity;
			cout << "\n\t\t\t\t\t Please Enter Product Price (RM): ";
			cin >> product_price;
		}
		
		void display(){
			cout << " \n\t\t\t\t\t PRODUCT NAME: " << itemName;
			cout << " \n\t\t\t\t\t PRODUCT BRAND: " << brand;
			cout << " \n\t\t\t\t\t DETAIL: " << detail;
			cout << " \n\t\t\t\t\t CODE: " << product_id;
			cout << " \n\t\t\t\t\t QUANTITY LEFT: " << quantity;
			cout << " \n\t\t\t\t\t PRODUCT PRICE: " << product_price;
		}
		
		int pid()
		{return product_id;}
		
};

fstream f;
Store x;

void write_in_file(){
	f.open("store.dat", ios::out|ios::app);
	x.registeer();
	f.write((char*)&x, sizeof(x));
	f.close();
	cout << "\n\t\t\t\t\t REGISTER SUCCESSFULLY\n";
}

void display_all(){
	cout << "\n\t\t\t\t\t DISPLAY ALL RECORD \n\n";
	f.open("store.dat", ios::in);
	while (f.read((char*)&x, sizeof(x))){
		x.display();
		cout << "\n\t\t\t\t\t =========================================== \n";
	}
	f.close();
}

void display_specific(int n){
	int flag=0;
	f.open("store.dat", ios::in);
	while (f.read((char*)&x, sizeof(x))){
		if (x.pid()==n){
			x.display();
			flag=1;
		}
	}
	f.close();
	if (flag==0){
		cout << " \n\t\t\t\t\t BEEP! PRODUCT NOT FOUND!!!\n";
	}
}

void update(){
	int id, found=0;
	cout << "\n\t\t\t\t\t UPDATING..."<< endl;
	cout << "\n\t\t\t\t\t Enter the product code : ";
	cin >> id;
	f.open("store.dat", ios::in|ios::out);
	while (f.read((char*)&x, sizeof(x)) && found==0){
		if (x.pid()==id){
		x.display();
		
		cout << "\n\t\t\t\t\t Please Enter New Info Of Product" << endl;
		x.registeer();
		int pos=-1*((int)sizeof(x));
		f.seekp(pos, ios::cur);
		f.write((char*)&x, sizeof(x));
		cout << "\n\t\t\t\t\t RECORD UPDATED\n";
		found=1;
		}
	}
	f.close();
	if (found==0){
		cout << "\n\t\t\t\t\t PRODUCT NOT FOUND!!!\n";
	}
}

void delette(){
	int id;
	cout << "\n\t\t\t\t\t DELETING..."<< endl;
	cout << "\t\t\t\t\t Enter the product code : ";
	cin >> id;
	f.open("store.dat", ios::in|ios::out);
	fstream f2;
	f2.open("temp.dat", ios::out);
	f.seekg(0, ios::beg);
	while (f.read((char*)&x, sizeof(x))){
		if (x.pid()!=id){
			f2.write((char*)&x, sizeof(x));
		}
	}
	f2.close();
	f.close();
	remove("store.dat");
	rename("temp.dat", "store.dat");
	cout << "\n\t\t\t\t\t RECORD DELETED\n";
}

int main(){
	int option;
	do{
		cout <<"\n\t\t\t\t\t ### STOCK INVENTORY ### " <<endl;
		cout <<"\n\t\t\t\t\t -> MAIN MENU " << endl;
		cout << "\t\t\t\t\t 1. REGISTER PRODUCT" << endl;
		cout << "\t\t\t\t\t 2. DISPLAY ALL PRODUCTS" << endl;
		cout << "\t\t\t\t\t 3. SEARCH PRODUCTS" << endl;
		cout << "\t\t\t\t\t 4. UPDATE PRODUCTS" << endl;
		cout << "\t\t\t\t\t 5. DELETE PRODUCTS" << endl;
		cout << "\t\t\t\t\t 6. EXIT" << endl;
		cout << "\n\t\t\t\t\t Please choose your option : " ;
		cin >> option;
	
		switch(option){
			case 1: write_in_file();
					break;
			case 2: display_all();
					break;
			case 3: int id;
					cout << "\n\t\t\t\t\t Enter the product code: ";
					cin >> id;
					display_specific(id);
					cout << "\n"; 
					break;
			case 4: update();
					break;
			case 5: delette();
					break;
		}
	}

	while (option!=6);
	return 0;
}
