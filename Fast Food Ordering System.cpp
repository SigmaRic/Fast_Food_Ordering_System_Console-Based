//Project Title : Fast Food Ordering System

#include <iostream>//input / output streams (cin, cout)
#include <string>//string class
#include <iomanip>//output formatting (setw, setprecision)
#include <fstream>//File handling: ifstream / ofstream for .txt files
#include <cstdlib>//system(), atoi(), atof()
#include <ctime>//current date and time for order timestamps
#include <windows.h>//Windows console: system("cls"/"color"), Sleep()
using namespace std;


//Fixed inner width for every centered UI box (total box width = W + 2 borders)
const int W=74;


//Base class for all menu items (parent for inheritance + polymorphism)
class MenuItem
{
	protected:
	int id;
	string category;
	string name;
	double price;

	public:
	MenuItem()
	{id=0;category="None";name="None";price=0.0;}

	MenuItem(int i,string c,string n,double p)
	{id=i;category=c;name=n;price=p;}

	int getID()
	{return id;}

	string getCategory()
	{return category;}

	string getName()
	{return name;}

	double getPrice()
	{return price;}

	void setName(string n)
	{name=n;}

	void setPrice(double p)
	{price=p;}

	//Polymorphic: each derived class returns its own variant (spice / temp / style / set)
	virtual string getVariant()
	{return "-";}

	//Polymorphic display, overridden by every derived menu class
	virtual void display()
	{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<id<<setw(34)<<name<<setw(12)<<getVariant()<<"RM"<<fixed<<setprecision(2)<<price<<endl;}

	virtual ~MenuItem()
	{}

	friend//Operator overloading (friend): print a MenuItem as "id | category | name | price"
ostream& operator<<(ostream &out,MenuItem &m);
	friend//Operator overloading (friend): two menu items are equal when their IDs match
bool operator==(MenuItem &a,MenuItem &b);
	friend//Friend function: compare the prices of two menu items
void compareItem(MenuItem &a,MenuItem &b);
};


ostream& operator<<(ostream &out,MenuItem &m)
{
out<<m.id<<" | "<<m.category<<" | "<<m.name<<" | RM"<<fixed<<setprecision(2)<<m.price;
return out;
}


bool operator==(MenuItem &a,MenuItem &b)
{
if(a.id==b.id)
return true;

else
return false;
}


void compareItem(MenuItem &a,MenuItem &b)
{
if(a.price>b.price)
cout<<a.name<<" is more expensive than "<<b.name<<endl;

else if(a.price<b.price)
cout<<b.name<<" is more expensive than "<<a.name<<endl;

else
cout<<a.name<<" and "<<b.name<<" cost the same"<<endl;
}



//Derived class: food / fried-chicken item (adds a spice level)
class FoodItem : public MenuItem
{
	private:
	string spiceLevel;

	public:
	FoodItem():MenuItem()
	{spiceLevel="Non-Spicy";}

	FoodItem(int i,string c,string n,double p,string s):MenuItem(i,c,n,p)
	{spiceLevel=s;}

	string getVariant()
	{return spiceLevel;}

	void display()
	{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<id<<setw(34)<<name<<setw(12)<<getVariant()<<"RM"<<fixed<<setprecision(2)<<price<<endl;}

	~FoodItem()
	{}
};


//Derived class: beverage (adds a temperature: hot / cold)
class BeverageItem : public MenuItem
{
	private:
	string temperature;

	public:
	BeverageItem():MenuItem()
	{temperature="Cold";}

	BeverageItem(int i,string c,string n,double p,string t):MenuItem(i,c,n,p)
	{temperature=t;}

	string getVariant()
	{return temperature;}

	void display()
	{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<id<<setw(34)<<name<<setw(12)<<getVariant()<<"RM"<<fixed<<setprecision(2)<<price<<endl;}

	~BeverageItem()
	{}
};


//Derived class: dessert (adds a style)
class DessertItem : public MenuItem
{
	private:
	string style;

	public:
	DessertItem():MenuItem()
	{style="Sweet";}

	DessertItem(int i,string c,string n,double p,string s):MenuItem(i,c,n,p)
	{style=s;}

	string getVariant()
	{return style;}

	void display()
	{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<id<<setw(34)<<name<<setw(12)<<getVariant()<<"RM"<<fixed<<setprecision(2)<<price<<endl;}

	~DessertItem()
	{}
};


//Derived class: combo set (adds a set type)
class ComboItem : public MenuItem
{
	private:
	string setType;

	public:
	ComboItem():MenuItem()
	{setType="Set";}

	ComboItem(int i,string c,string n,double p,string s):MenuItem(i,c,n,p)
	{setType=s;}

	string getVariant()
	{return setType;}

	void display()
	{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<id<<setw(34)<<name<<setw(12)<<getVariant()<<"RM"<<fixed<<setprecision(2)<<price<<endl;}

	~ComboItem()
	{}
};


//Base class for all users (parent of Customer and Admin)
class User
{
	protected:
	string username;
	string password;
	string name;
	string role;

	public:
	User()
	{username="";password="";name="";role="";}

	User(string u,string p,string n,string r)
	{username=u;password=p;name=n;role=r;}

	string getUsername()
	{return username;}

	string getPassword()
	{return password;}

	void setPassword(string p)
	{password=p;}

	string getName()
	{return name;}

	string getRole()
	{return role;}

	bool checkPassword(string p)
	{
	if(password==p)
	return true;

	else
	return false;
	}

	virtual void displayProfile()
	{
	cout<<"Username : "<<username<<endl;
	cout<<"Name     : "<<name<<endl;
	cout<<"Role     : "<<role<<endl;
	}

	virtual ~User()
	{}

	friend//Operator overloading (friend): print a user as "username (role) - name"
ostream& operator<<(ostream &out,User &u);
	friend//Friend function: print a small boxed user info card
void displayUserCard(User &u);
};


ostream& operator<<(ostream &out,User &u)
{
out<<u.username<<" ("<<u.role<<") - "<<u.name;
return out;
}


void displayUserCard(User &u)
{
cout<<"\t\t\t\t\t\t\t\t"<<"+-----------------------------+"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"|  Name : "<<u.name<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"|  Role : "<<u.role<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+-----------------------------+"<<endl;
}


//Derived class: a customer account (adds phone number + total order count)
class Customer : public User
{
	private:
	string phone;
	int totalOrders;

	public:
	Customer():User()
	{phone="";totalOrders=0;role="Customer";}

	Customer(string u,string p,string n,string ph):User(u,p,n,"Customer")
	{phone=ph;totalOrders=0;}

	string getPhone()
	{return phone;}

	void setPhone(string ph)
	{phone=ph;}

	int getTotalOrders()
	{return totalOrders;}

	void addOrderCount()
	{totalOrders++;}

	void displayProfile()
	{
	cout<<"Customer Name : "<<name<<endl;
	cout<<"Username      : "<<username<<endl;
	cout<<"Phone         : "<<phone<<endl;
	cout<<"Total Orders  : "<<totalOrders<<endl;
	}

	~Customer()
	{}
};


//Derived class: an admin / staff account (adds staff ID + phone)
class Admin : public User
{
	private:
	string staffID;
	string phone;

	public:
	Admin():User()
	{staffID="";phone="";role="Admin";}

	Admin(string u,string p,string n,string s):User(u,p,n,"Admin")
	{staffID=s;phone="";}

	string getStaffID()
	{return staffID;}

	string getPhone()
	{return phone;}

	void setPhone(string ph)
	{phone=ph;}

	void displayProfile()
	{
	cout<<"Admin Name : "<<name<<endl;
	cout<<"Username   : "<<username<<endl;
	cout<<"Staff ID   : "<<staffID<<endl;
	}

	~Admin()
	{}
};


//Node of the menu LINKED LIST (holds one MenuItem + pointer to next)
struct MenuNode
{
MenuItem *data;
MenuNode *next;
};


//Node of the order QUEUE
struct OrderNode
{
int orderID;
string customer;
double total;
string status;
string dateTime;
OrderNode *next;
};


//Node of the order-history STACK
struct HistoryNode
{
int orderID;
string customer;
double total;
string dateTime;
HistoryNode *next;
};


//DATA STRUCTURE - Singly Linked List: stores every menu item
class MenuList
{
	private:
	MenuNode *head;
	int count;

	public:
	MenuList()
	{head=NULL;count=0;}

	bool isEmpty()
	{
	if(head==NULL)
	return true;

	else
	return false;
	}

	int getCount()
	{return count;}

	//Linked list: append a new menu-item node at the end of the list
	void insertEnd(MenuItem *item)
	{
	MenuNode *newnode=new MenuNode;
	newnode->data=item;
	newnode->next=NULL;

	if(isEmpty())
	head=newnode;

	else
	{
	MenuNode *temp=head;
	while(temp->next!=NULL)
	temp=temp->next;
	temp->next=newnode;
	}

	count++;
	}

	//File handling: read the records from the file and rebuild this structure
	void loadFromFile(string filename)
	{
	ifstream file(filename.c_str());

	if(!file)
	{cout<<"Error: cannot open "<<filename<<endl;
	return;}

	string line;

	while(getline(file,line))
	{
	if(line=="")
	continue;

	int p1=line.find('|');
	int p2=line.find('|',p1+1);
	int p3=line.find('|',p2+1);
	int p4=line.find('|',p3+1);

	if(p1<0||p2<0||p3<0||p4<0)
	continue;

	string sid=line.substr(0,p1);
	string cat=line.substr(p1+1,p2-p1-1);
	string nm=line.substr(p2+1,p3-p2-1);
	string var=line.substr(p3+1,p4-p3-1);
	string spr=line.substr(p4+1);

	int id=atoi(sid.c_str());
	double price=atof(spr.substr(2).c_str());

	MenuItem *item;

	if(cat=="Beverage")
	item=new BeverageItem(id,cat,nm,price,var);

	else if(cat=="Dessert")
	item=new DessertItem(id,cat,nm,price,var);

	else if(cat=="Combo")
	item=new ComboItem(id,cat,nm,price,var);

	else
	item=new FoodItem(id,cat,nm,price,var);

	insertEnd(item);
	}

	file.close();
	}

	//Walk the linked list and display every menu item
	void displayAll()
	{
	if(isEmpty())
	{cout<<"\t\t\t\t\t\t\t\t"<<"Menu is empty."<<endl;
	return;}

	MenuNode *temp=head;

	while(temp!=NULL)
	{temp->data->display();
	temp=temp->next;}
	}

	//Walk the linked list and display only items of one category
	void displayByCategory(string cat)
	{
	MenuNode *temp=head;
	int found=0;

	while(temp!=NULL)
	{
	if(temp->data->getCategory()==cat)
	{temp->data->display();
	found++;}

	temp=temp->next;
	}

	if(found==0)
	cout<<"\t\t\t\t\t\t\t\t"<<"No items found in category: "<<cat<<endl;
	}

	//Copy the linked list into an array so it can be sorted / searched
	int toArray(MenuItem *arr[])
	{
	MenuNode *temp=head;
	int i=0;

	while(temp!=NULL)
	{arr[i]=temp->data;
	i++;
	temp=temp->next;}

	return i;
	}

	//Sorting - Insertion Sort: order menu items by price (low to high)
	void sortByPrice()
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	for(int i=1;i<n;i++)
	{
	MenuItem *key=arr[i];
	int j=i-1;

	while(j>=0&&arr[j]->getPrice()>key->getPrice())
	{arr[j+1]=arr[j];
	j--;}

	arr[j+1]=key;
	}

	cout<<"\t\t\t\t\t\t\t\t"<<"----- Menu sorted by PRICE (low to high) -----"<<endl;
	for(int i=0;i<n;i++)
	arr[i]->display();
	}

	//Sorting - Selection Sort: order menu items by name (A to Z)
	void sortByName()
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	for(int i=0;i<n-1;i++)
	{
	int min=i;

	for(int j=i+1;j<n;j++)
	{
	if(arr[j]->getName()<arr[min]->getName())
	min=j;
	}

	MenuItem *temp=arr[min];
	arr[min]=arr[i];
	arr[i]=temp;
	}

	cout<<"\t\t\t\t\t\t\t\t"<<"----- Menu sorted by NAME (A to Z) -----"<<endl;
	for(int i=0;i<n;i++)
	arr[i]->display();
	}

	//Sorting - Bubble Sort: order menu items by ID (ascending)
	void sortByID()
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	for(int i=0;i<n-1;i++)
	{
	for(int j=0;j<n-1-i;j++)
	{
	if(arr[j]->getID()>arr[j+1]->getID())
	{MenuItem *temp=arr[j];
	arr[j]=arr[j+1];
	arr[j+1]=temp;}
	}
	}

	cout<<"\t\t\t\t\t\t\t\t"<<"----- Menu sorted by ID -----"<<endl;
	for(int i=0;i<n;i++)
	arr[i]->display();
	}

	//Searching - Binary Search: array is first bubble-sorted by ID, then halved to find the ID
	MenuItem* searchByID(int id)
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	for(int i=0;i<n-1;i++)
	{
	for(int j=0;j<n-1-i;j++)
	{
	if(arr[j]->getID()>arr[j+1]->getID())
	{MenuItem *temp=arr[j];
	arr[j]=arr[j+1];
	arr[j+1]=temp;}
	}
	}

	//Binary Search: repeatedly halve the sorted range until the target is found
	int first=0,last=n-1;

	while(first<=last)
	{
	int mid=(first+last)/2;

	if(arr[mid]->getID()==id)
	return arr[mid];

	else if(arr[mid]->getID()<id)
	first=mid+1;

	else
	last=mid-1;
	}

	return NULL;
	}

	//Searching - Hashing: load items into a hash table (ID % size, linear probing) then look the ID up
	MenuItem* hashSearchByID(int id)
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	int size=101;
	MenuItem *table[101];

	for(int i=0;i<size;i++)
	table[i]=NULL;

	for(int i=0;i<n;i++)
	{
	int index=arr[i]->getID()%size;

	while(table[index]!=NULL)
	index=(index+1)%size;

	table[index]=arr[i];
	}

	int index=id%size;
	int start=index;

	while(table[index]!=NULL)
	{
	if(table[index]->getID()==id)
	return table[index];

	index=(index+1)%size;

	if(index==start)
	break;
	}

	return NULL;
	}

	//Searching - Binary Search: array is first selection-sorted by name, then halved to find the name
	MenuItem* searchByName(string target)
	{
	MenuItem *arr[200];
	int n=toArray(arr);

	for(int i=0;i<n-1;i++)
	{
	int min=i;

	for(int j=i+1;j<n;j++)
	{
	if(arr[j]->getName()<arr[min]->getName())
	min=j;
	}

	MenuItem *temp=arr[min];
	arr[min]=arr[i];
	arr[i]=temp;
	}

	//Binary Search: repeatedly halve the sorted range until the target is found
	int first=0,last=n-1;

	while(first<=last)
	{
	int mid=(first+last)/2;

	if(arr[mid]->getName()==target)
	return arr[mid];

	else if(arr[mid]->getName()<target)
	first=mid+1;

	else
	last=mid-1;
	}

	return NULL;
	}

	//File handling: write this structure's contents out to the file
	void saveToFile(string filename)
	{
	ofstream file(filename.c_str());

	if(!file)
	{cout<<"Error: cannot save to "<<filename<<endl;
	return;}

	file<<fixed<<setprecision(2);

	MenuNode *temp=head;

	while(temp!=NULL)
	{
	file<<temp->data->getID()<<"|"<<temp->data->getCategory()<<"|"<<temp->data->getName()<<"|"<<temp->data->getVariant()<<"|RM"<<temp->data->getPrice()<<endl;
	temp=temp->next;
	}

	file.close();
	}

	//Linked list: find the largest item ID currently in the list
	int getMaxID()
	{
	int max=0;
	MenuNode *temp=head;

	while(temp!=NULL)
	{
	if(temp->data->getID()>max)
	max=temp->data->getID();

	temp=temp->next;
	}

	return max;
	}

	//Create a new menu item (auto-assigns next ID) and link it into the list
	void addItem(string cat,string nm,double price,string var)
	{
	int newID=getMaxID()+1;
	MenuItem *item;

	if(cat=="Beverage")
	item=new BeverageItem(newID,cat,nm,price,var);

	else if(cat=="Dessert")
	item=new DessertItem(newID,cat,nm,price,var);

	else if(cat=="Combo")
	item=new ComboItem(newID,cat,nm,price,var);

	else
	item=new FoodItem(newID,cat,nm,price,var);

	insertEnd(item);
	cout<<"\t\t\t\t\t\t\t\t"<<">> New item added with ID "<<newID<<endl;
	}

	//Linked list: unlink and delete the node whose item ID matches
	bool deleteByID(int id)
	{
	if(isEmpty())
	return false;

	MenuNode *temp=head;
	MenuNode *prev=NULL;

	while(temp!=NULL)
	{
	if(temp->data->getID()==id)
	{
	if(prev==NULL)
	head=temp->next;

	else
	prev->next=temp->next;

	delete temp->data;
	delete temp;
	count--;
	return true;
	}

	prev=temp;
	temp=temp->next;
	}

	return false;
	}

	//Destructor: free every node and its MenuItem (prevents memory leaks)
	~MenuList()
	{
	MenuNode *temp;

	while(head!=NULL)
	{temp=head;
	head=head->next;
	delete temp->data;
	delete temp;}
	}
};


//DATA STRUCTURE - Queue (FIFO): buffers incoming orders
class OrderQueue
{
	private:
	OrderNode *front;
	OrderNode *rear;
	int count;

	public:
	OrderQueue()
	{front=NULL;rear=NULL;count=0;}

	bool isEmpty()
	{
	if(front==NULL)
	return true;

	else
	return false;
	}

	int getCount()
	{return count;}

	//Queue (FIFO): add a new order at the rear
	void enqueue(int oid,string cust,double total,string status,string dt)
	{
	OrderNode *newnode=new OrderNode;
	newnode->orderID=oid;
	newnode->customer=cust;
	newnode->total=total;
	newnode->status=status;
	newnode->dateTime=dt;
	newnode->next=NULL;

	if(isEmpty())
	{front=newnode;
	rear=newnode;}

	else
	{rear->next=newnode;
	rear=newnode;}

	count++;
	}

	//Queue (FIFO): remove the order at the front
	void dequeue()
	{
	if(isEmpty())
	return;

	OrderNode *temp=front;

	front=front->next;

	if(front==NULL)
	rear=NULL;

	delete temp;
	count--;
	}

	void display()
	{
	if(isEmpty())
	{cout<<"\t\t\t\t\t\t\t\t"<<"No orders."<<endl;
	return;}

	OrderNode *temp=front;

	while(temp!=NULL)
	{cout<<"\t\t\t\t\t\t\t\t"<<"Order #"<<temp->orderID<<" | "<<temp->customer<<" | RM"<<fixed<<setprecision(2)<<temp->total<<" | "<<temp->status<<" | "<<temp->dateTime<<endl;
	temp=temp->next;}
	}

	//File handling: write this structure's contents out to the file
	void saveToFile(string filename)
	{
	ofstream file(filename.c_str());

	if(!file)
	return;

	OrderNode *temp=front;

	while(temp!=NULL)
	{file<<temp->orderID<<"|"<<temp->customer<<"|"<<fixed<<setprecision(2)<<temp->total<<"|"<<temp->status<<"|"<<temp->dateTime<<endl;
	temp=temp->next;}

	file.close();
	}

	//File handling: read the records from the file and rebuild this structure
	void loadFromFile(string filename)
	{
	ifstream file(filename.c_str());

	if(!file)
	return;

	string line;

	while(getline(file,line))
	{
	if(line=="")
	continue;

	int p1=line.find('|');
	int p2=line.find('|',p1+1);
	int p3=line.find('|',p2+1);
	int p4=line.find('|',p3+1);

	if(p1<0||p2<0||p3<0||p4<0)
	continue;

	int oid=atoi(line.substr(0,p1).c_str());
	string cust=line.substr(p1+1,p2-p1-1);
	double total=atof(line.substr(p2+1,p3-p2-1).c_str());
	string status=line.substr(p3+1,p4-p3-1);
	string dt=line.substr(p4+1);

	enqueue(oid,cust,total,status,dt);
	}

	file.close();
	}

	//Queue: remove a specific order by its ID
	bool removeByID(int oid)
	{
	if(isEmpty())
	return false;

	if(front->orderID==oid)
	{
	OrderNode *temp=front;
	front=front->next;

	if(front==NULL)
	rear=NULL;

	delete temp;
	count--;
	return true;
	}

	OrderNode *prev=front;
	OrderNode *cur=front->next;

	while(cur!=NULL)
	{
	if(cur->orderID==oid)
	{
	prev->next=cur->next;

	if(cur==rear)
	rear=prev;

	delete cur;
	count--;
	return true;
	}

	prev=cur;
	cur=cur->next;
	}

	return false;
	}

	//Queue: check whether an order ID belongs to a given customer
	bool hasOrderForCustomer(int oid,string cust)
	{
	OrderNode *temp=front;

	while(temp!=NULL)
	{
	if(temp->orderID==oid&&temp->customer==cust)
	return true;

	temp=temp->next;
	}

	return false;
	}

	//Queue: display only the orders that belong to one customer
	void displayByCustomer(string cust)
	{
	OrderNode *temp=front;
	int found=0;

	while(temp!=NULL)
	{
	if(temp->customer==cust)
	{cout<<"\t\t\t\t\t\t\t\t"<<"Order #"<<temp->orderID<<" | RM"<<fixed<<setprecision(2)<<temp->total<<" | "<<temp->status<<" | "<<temp->dateTime<<endl;
	found++;}

	temp=temp->next;
	}

	if(found==0)
	cout<<"\t\t\t\t\t\t\t\t"<<"You have no orders."<<endl;
	}

	//Destructor: free every remaining order node
	~OrderQueue()
	{
	OrderNode *temp;

	while(front!=NULL)
	{temp=front;
	front=front->next;
	delete temp;}
	}
};


//DATA STRUCTURE - Stack (LIFO): keeps the order history
class HistoryStack
{
	private:
	HistoryNode *top;
	int count;

	public:
	HistoryStack()
	{top=NULL;count=0;}

	bool isEmpty()
	{
	if(top==NULL)
	return true;

	else
	return false;
	}

	int getCount()
	{return count;}

	//Stack (LIFO): push the newest order on top
	void push(int oid,string cust,double total,string dt)
	{
	HistoryNode *newnode=new HistoryNode;
	newnode->orderID=oid;
	newnode->customer=cust;
	newnode->total=total;
	newnode->dateTime=dt;
	newnode->next=top;
	top=newnode;
	count++;
	}

	//Stack (LIFO): remove the order on top
	void pop()
	{
	if(isEmpty())
	{cout<<"History is empty."<<endl;
	return;}

	HistoryNode *temp=top;
	cout<<"Removed latest history: order #"<<top->orderID<<endl;
	top=top->next;
	delete temp;
	count--;
	}

	void display()
	{
	if(isEmpty())
	{cout<<"No order history."<<endl;
	return;}

	HistoryNode *temp=top;

	while(temp!=NULL)
	{cout<<"Order #"<<temp->orderID<<" | "<<temp->customer<<" | RM"<<fixed<<setprecision(2)<<temp->total<<" | "<<temp->dateTime<<endl;
	temp=temp->next;}
	}

	//Destructor: free every history node
	~HistoryStack()
	{
	HistoryNode *temp;

	while(top!=NULL)
	{temp=top;
	top=top->next;
	delete temp;}
	}
};


//Holds one line of the shopping cart
struct CartItem
{
int itemID;
string name;
double price;
int qty;
};


//Global data structures shared across the whole program
//Linked list of all menu items
MenuList menu;
//FIFO queue of incoming orders
OrderQueue orderQueue;
//LIFO stack of completed-order history
HistoryStack orderHistory;
int orderCounter=1000;


//Helper: convert an int to a string (no STL stringstream used)
string intToStr(int n)
{
if(n==0)
return "0";

string s="";
bool neg=false;

if(n<0)
{neg=true;
n=-n;}

while(n>0)
{char c='0'+(n%10);
s=c+s;
n=n/10;}

if(neg)
s="-"+s;

return s;
}


//Helper: format a price as RMx.xx (rounded to 2 decimals)
string moneyStr(double amt)
{
int cents=(int)(amt*100+0.5);
int dollars=cents/100;
int rem=cents%100;
string r="RM"+intToStr(dollars)+".";

if(rem<10)
r=r+"0";

r=r+intToStr(rem);
return r;
}


//Input validation: keep prompting until the user enters an int within [minv, maxv]
int getValidInt(int minv,int maxv)
{
int x;

while(true)
{
if(cin>>x)
{
if(x>=minv&&x<=maxv)
return x;

cout<<"\t\t\t\t\t\t\t\t"<<">> Enter a number between "<<minv<<" and "<<maxv<<" : ";
}

else
{
if(cin.eof())
return minv;

cin.clear();
cin.ignore(10000,'\n');
cout<<"\t\t\t\t\t\t\t\t"<<">> Invalid input. Enter a number : ";
}
}
}


//Input validation: keep prompting until the user enters a number >= minv
double getValidDouble(double minv)
{
double x;

while(true)
{
if(cin>>x)
{
if(x>=minv)
return x;

cout<<"\t\t\t\t\t\t\t\t"<<">> Amount must be at least RM"<<fixed<<setprecision(2)<<minv<<" : ";
}

else
{
if(cin.eof())
return minv;

cin.clear();
cin.ignore(10000,'\n');
cout<<"\t\t\t\t\t\t\t\t"<<">> Invalid amount. Enter again : ";
}
}
}


//File handling: read order_history.txt at start-up so new order IDs continue from the last one
void restoreOrderCounter()
{
ifstream file("order_history.txt");

if(!file)
return;

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');

if(p1<0)
continue;

int oid=atoi(line.substr(0,p1).c_str());

if(oid>orderCounter)
orderCounter=oid;
}

file.close();
}


//UI helper: pad text with spaces on both sides so it is centered in a fixed width
string centerText(string text,int width)
{
int len=text.length();

if(len>=width)
return text.substr(0,width);

int totalPad=width-len;
int left=totalPad/2;
int right=totalPad-left;
string result="";

for(int i=0;i<left;i++)
result=result+" ";

result=result+text;

for(int i=0;i<right;i++)
result=result+" ";

return result;
}


//UI helper: pad text on the right so it is left-aligned in a fixed width
string leftText(string text,int width)
{
int len=text.length();

if(len>=width)
return text.substr(0,width);

string result=text;

for(int i=0;i<width-len;i++)
result=result+" ";

return result;
}


//UI helper: pad text on the left so it is right-aligned in a fixed width
string rightText(string text,int width)
{
int len=text.length();

if(len>=width)
return text.substr(0,width);

string result="";

for(int i=0;i<width-len;i++)
result=result+" ";

result=result+text;

return result;
}


//UI helper: draw a horizontal box border like +--------+
void printLine(char symbol,int width)
{
cout<<"\t\t\t\t\t\t\t\t"<<"+";

for(int i=0;i<width;i++)
cout<<symbol;

cout<<"+"<<endl;
}


//UI helper: print one centered line inside the box borders
void printCenter(string text)
{
cout<<"\t\t\t\t\t\t\t\t"<<"|"<<centerText(text,W)<<"|"<<endl;
}


//UI helper: print one left-aligned line inside the box borders
void printLeft(string text)
{
cout<<"\t\t\t\t\t\t\t\t"<<"|"<<leftText("  "+text,W)<<"|"<<endl;
}


//UI helper: print a centered box title
void printCenteredBoxTitle(string title)
{
cout<<"\t\t\t\t\t\t\t\t"<<"|"<<centerText(title,W)<<"|"<<endl;
}


//UI helper: print a numbered menu option like |  [1] Login |
void printMenuOption(int no,string option)
{
string s="  ["+intToStr(no)+"] "+option;
cout<<"\t\t\t\t\t\t\t\t"<<"|"<<leftText(s,W)<<"|"<<endl;
}


//UI helper: ask the user a yes (1) / no (0) confirmation
bool confirmAction(string msg)
{
cout<<endl;
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<msg<<endl;
printMenuOption(1,"Yes, confirm");
printMenuOption(0,"No, cancel");
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
int ch=getValidInt(0,1);

if(ch==1)
return true;

return false;
}


//Helper: return the current system date and time as "YYYY-MM-DD HH:MM"
string getDateTime()
{
time_t now=time(0);
char buf[30];
strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M",localtime(&now));
return string(buf);
}


//Hashing: turn a username into a hash-table index (sum of characters % table size)
int hashUsername(string uname)
{
int size=503;
int sum=0;

for(int i=0;i<(int)uname.length();i++)
sum=sum+(int)uname[i]*(i+1);

if(sum<0)
sum=sum*(-1);

return sum%size;
}


//Searching - Hashing: build a hash table of usernames, then look one up using linear probing
int findUserByHash(string target,string unames[],int n)
{
int size=503;
int table[503];

for(int i=0;i<size;i++)
table[i]=-1;

for(int i=0;i<n;i++)
{
int index=hashUsername(unames[i]);

while(table[index]!=-1)
index=(index+1)%size;

table[index]=i;
}

int index=hashUsername(target);
int start=index;

while(table[index]!=-1)
{
if(unames[table[index]]==target)
return table[index];

index=(index+1)%size;

if(index==start)
break;
}

return -1;
}


//File handling: read all users from users.txt (handles 5-field customer rows and 6-field admin rows)
int loadAllUsers(string unames[],string pwds[],string names[],string contacts[],string roles[],string phones[])
{
ifstream file("users.txt");

if(!file)
return -1;

string line;
int n=0;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);
int p4=line.find('|',p3+1);

if(p1<0||p2<0||p3<0||p4<0)
continue;

unames[n]=line.substr(0,p1);
pwds[n]=line.substr(p1+1,p2-p1-1);
names[n]=line.substr(p2+1,p3-p2-1);
contacts[n]=line.substr(p3+1,p4-p3-1);

int p5=line.find('|',p4+1);

if(p5>=0)
{
roles[n]=line.substr(p4+1,p5-p4-1);
phones[n]=line.substr(p5+1);
}

else
{
roles[n]=line.substr(p4+1);
phones[n]="";
}

n++;
}

file.close();
return n;
}


//Check whether a username is already taken
bool usernameExists(string uname)
{
string unames[500],pwds[500],names[500],contacts[500],roles[500],phones[500];
int n=loadAllUsers(unames,pwds,names,contacts,roles,phones);

if(n<=0)
return false;

int idx=findUserByHash(uname,unames,n);

if(idx>=0)
return true;

else
return false;
}


//Customer function: register a new customer and append the record to users.txt
void customerRegister()
{
string uname,pass,nm,phone;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("CUSTOMER REGISTRATION");
printLine('=',W);
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new username : ";
cin>>uname;

try
{
if(usernameExists(uname))
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new password : ";
cin>>pass;
cin.ignore();

cout<<"\t\t\t\t\t\t\t\t"<<"Enter your name    : ";
getline(cin,nm);

cout<<"\t\t\t\t\t\t\t\t"<<"Enter phone number : ";
getline(cin,phone);

ofstream file("users.txt",ios::app);

if(!file)
throw 2;

//File handling: append the new customer record (username|password|name|phone|role)
file<<uname<<"|"<<pass<<"|"<<nm<<"|"<<phone<<"|Customer"<<endl;
file.close();

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<">> Registration successful! You can now log in."<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Username already exists. Please try another."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: cannot save to users.txt"<<endl;
}

cout<<endl;
system("pause");
}


//Customer function: log a customer in (username looked up by hashing)
int customerLogin(Customer &c)
{
string uname,pass;

while(true)
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("CUSTOMER LOGIN");
printLine('=',W);
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter username : ";
cin>>uname;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter password : ";
cin>>pass;

try
{
string unames[500],pwds[500],names[500],contacts[500],roles[500],phones[500];
int n=loadAllUsers(unames,pwds,names,contacts,roles,phones);

if(n<0)
throw 1;

int idx=findUserByHash(uname,unames,n);

if(idx>=0&&pwds[idx]==pass&&roles[idx]=="Customer")
{
c=Customer(unames[idx],pwds[idx],names[idx],contacts[idx]);
return 1;
}

throw 2;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: users.txt not found."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Wrong username or password."<<endl;
}

char ans;

while(true)
{
cout<<"\t\t\t\t\t\t\t\t"<<"Do you want to try again? (Y/N) : ";
cin>>ans;

if(cin.eof())
return 0;

if(ans=='Y'||ans=='y')
break;

else if(ans=='N'||ans=='n')
return 0;

else
cout<<"\t\t\t\t\t\t\t\t"<<">> Invalid choice."<<endl;
}
}
}


//Menu function: display the full menu to the customer
void browseMenu()
{
int choice;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("BROWSE MENU");
printLine('=',W);
printMenuOption(1,"Show all items");
printMenuOption(2,"Fried Chicken");
printMenuOption(3,"Burger");
printMenuOption(4,"Side");
printMenuOption(5,"Dessert");
printMenuOption(6,"Beverage");
printMenuOption(7,"Combo");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
cin>>choice;
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);

if(choice==1)
menu.displayAll();

else if(choice==2)
menu.displayByCategory("Fried Chicken");

else if(choice==3)
menu.displayByCategory("Burger");

else if(choice==4)
menu.displayByCategory("Side");

else if(choice==5)
menu.displayByCategory("Dessert");

else if(choice==6)
menu.displayByCategory("Beverage");

else if(choice==7)
menu.displayByCategory("Combo");

else
cout<<"\t\t\t\t\t\t\t\t"<<"Invalid choice."<<endl;

cout<<endl;
system("pause");
}


//Menu function: search the menu - Binary Search by ID / by Name, or Hashing by ID
void searchMenuItem()
{
int choice;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SEARCH MENU");
printLine('=',W);
printMenuOption(1,"Search by ID   (Binary Search)");
printMenuOption(2,"Search by Name (Binary Search)");
printMenuOption(3,"Search by ID   (Hashing)");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
cin>>choice;

try
{
if(choice==1)
{
int id;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID : ";
cin>>id;

MenuItem *m=menu.searchByID(id);

if(m==NULL)
throw 1;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item found :"<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(16)<<"Category"<<setw(32)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+";
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<m->getID()<<setw(16)<<m->getCategory()<<setw(32)<<m->getName()<<setw(12)<<m->getVariant()<<moneyStr(m->getPrice())<<endl;
}

else if(choice==2)
{
string nm;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter exact item name : ";
getline(cin,nm);

MenuItem *m=menu.searchByName(nm);

if(m==NULL)
throw 1;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item found :"<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(16)<<"Category"<<setw(32)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+";
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<m->getID()<<setw(16)<<m->getCategory()<<setw(32)<<m->getName()<<setw(12)<<m->getVariant()<<moneyStr(m->getPrice())<<endl;
}

else if(choice==3)
{
int id;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID : ";
cin>>id;

MenuItem *m=menu.hashSearchByID(id);

if(m==NULL)
throw 1;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item found :"<<endl;
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(16)<<"Category"<<setw(32)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+";
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<m->getID()<<setw(16)<<m->getCategory()<<setw(32)<<m->getName()<<setw(12)<<m->getVariant()<<moneyStr(m->getPrice())<<endl;
}

else
cout<<"\t\t\t\t\t\t\t\t"<<"Invalid choice."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item not found."<<endl;
}

cout<<endl;
system("pause");
}


//Menu function: sort and display the menu (Insertion / Selection / Bubble Sort)
void sortMenuItem()
{
int choice;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SORT MENU");
printLine('=',W);
printMenuOption(1,"By Price (Insertion Sort)");
printMenuOption(2,"By Name  (Selection Sort)");
printMenuOption(3,"By ID    (Bubble Sort)");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
cin>>choice;
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);

if(choice==1)
menu.sortByPrice();

else if(choice==2)
menu.sortByName();

else if(choice==3)
menu.sortByID();

else
cout<<"\t\t\t\t\t\t\t\t"<<"Invalid choice."<<endl;

cout<<endl;
system("pause");
}


//Customer function: take payment, write the receipt + history + items, run the order through the queue
void checkout(Customer &c,CartItem cart[],int cartCount)
{
double subtotal=0;

for(int i=0;i<cartCount;i++)
subtotal=subtotal+(cart[i].price*cart[i].qty);

double service=subtotal*0.10;
double sst=(subtotal+service)*0.06;
double grandTotal=subtotal+service+sst;

string dt=getDateTime();

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("PAYMENT");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<"ID"<<setw(32)<<"Name"<<setw(6)<<"Qty"<<"Subtotal"<<endl;
printLine('-',W);

for(int i=0;i<cartCount;i++)
{
double sub=cart[i].price*cart[i].qty;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<cart[i].itemID<<setw(32)<<cart[i].name<<setw(6)<<cart[i].qty<<moneyStr(sub)<<endl;
}

printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(22)<<"Subtotal"<<": "<<moneyStr(subtotal)<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(22)<<"Service Charge (10%)"<<": "<<moneyStr(service)<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(22)<<"SST (6%)"<<": "<<moneyStr(sst)<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(22)<<"Grand Total"<<": "<<moneyStr(grandTotal)<<endl;
printLine('-',W);
printMenuOption(1,"Card");
printMenuOption(2,"E-Wallet");
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Select payment method : ";

int pm=getValidInt(1,2);
string payMethod;

if(pm==1)
payMethod="Card";

else
payMethod="E-Wallet";

if(!confirmAction("Confirm and place this order?"))
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Order cancelled."<<endl;
cout<<endl;
system("pause");
return;
}

orderCounter++;
int oid=orderCounter;

try
{
//File handling: write the formatted receipt to receipt.txt
ofstream rec("receipt.txt");

if(!rec)
throw 1;

rec<<"=============== FAST FOOD RECEIPT ==============="<<endl;
rec<<"Order ID : "<<oid<<endl;
rec<<"Customer : "<<c.getName()<<endl;
rec<<"Date     : "<<dt<<endl;
rec<<"-------------------------------------------------"<<endl;
rec<<"Item\t\t\tQty\tSubtotal"<<endl;

for(int i=0;i<cartCount;i++)
{
double sub=cart[i].price*cart[i].qty;
rec<<cart[i].name<<"\t"<<cart[i].qty<<"\tRM"<<fixed<<setprecision(2)<<sub<<endl;
}

rec<<"-------------------------------------------------"<<endl;
rec<<"Subtotal       : RM"<<fixed<<setprecision(2)<<subtotal<<endl;
rec<<"Service (10%)  : RM"<<service<<endl;
rec<<"SST (6%)       : RM"<<sst<<endl;
rec<<"TOTAL          : RM"<<grandTotal<<endl;
rec<<"Payment Method : "<<payMethod<<endl;
rec<<"================================================="<<endl;
rec.close();

//File handling: append this completed order to order_history.txt
ofstream hist("order_history.txt",ios::app);

if(!hist)
throw 2;

hist<<fixed<<setprecision(2);
hist<<oid<<"|"<<c.getName()<<"|"<<dt<<"|"<<grandTotal<<endl;
hist.close();

//File handling: append every cart line to order_items.txt
ofstream items("order_items.txt",ios::app);

if(items)
{
items<<fixed<<setprecision(2);

for(int i=0;i<cartCount;i++)
items<<oid<<"|"<<cart[i].name<<"|"<<cart[i].qty<<"|"<<cart[i].price<<endl;

items.close();
}

//Queue: enqueue the order then immediately dequeue it (FIFO buffer); also push to the history stack
orderQueue.enqueue(oid,c.getName(),grandTotal,"Completed",dt);
orderQueue.dequeue();
orderQueue.saveToFile("orders.txt");
orderHistory.push(oid,c.getName(),grandTotal,dt);
c.addOrderCount();

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("CHECKOUT SUCCESSFUL");
printLine('=',W);
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Order #"<<oid<<" placed successfully."<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Payment Method  : "<<payMethod<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Grand Total     : "<<moneyStr(grandTotal)<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Your order is completed."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: cannot write order files."<<endl;
}

cout<<endl;
system("pause");
}


//Customer function: build a shopping cart (add / edit / remove / view) then check out
void placeOrder(Customer &c)
{
CartItem cart[100];
int cartCount=0;
int choice;

do
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("PLACE ORDER");
printLine('=',W);
printMenuOption(1,"Add item to cart");
printMenuOption(2,"Edit item quantity");
printMenuOption(3,"Remove item from cart");
printMenuOption(4,"View cart");
printMenuOption(5,"Checkout");
printMenuOption(0,"Cancel order");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Items in cart : "<<cartCount<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
cin>>choice;

try
{
if(choice==1)
{
if(cartCount>=100)
throw 5;

int id,q;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);
menu.displayAll();
printLine('-',W);

cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID to add : ";
cin>>id;

MenuItem *m=menu.searchByID(id);

if(m==NULL)
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter quantity : ";
cin>>q;

if(q<=0)
throw 2;

cart[cartCount].itemID=m->getID();
cart[cartCount].name=m->getName();
cart[cartCount].price=m->getPrice();
cart[cartCount].qty=q;
cartCount++;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Added "<<q<<" x "<<m->getName()<<" to cart."<<endl;
}

else if(choice==2)
{
if(cartCount==0)
throw 3;

int id,newq;

cout<<endl;
printLine('-',W);
printCenter("YOUR CART");
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<"ID"<<setw(32)<<"Name"<<setw(6)<<"Qty"<<setw(14)<<"Unit Price"<<"Subtotal"<<endl;

for(int i=0;i<cartCount;i++)
{
double sub=cart[i].price*cart[i].qty;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<cart[i].itemID<<setw(32)<<cart[i].name<<setw(6)<<cart[i].qty<<setw(14)<<moneyStr(cart[i].price)<<moneyStr(sub)<<endl;
}

printLine('-',W);

cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID to edit : ";
cin>>id;

int idx=-1;

for(int i=0;i<cartCount;i++)
{
if(cart[i].itemID==id)
idx=i;
}

if(idx==-1)
throw 4;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new quantity : ";
cin>>newq;

if(newq<=0)
throw 2;

cart[idx].qty=newq;
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Quantity updated."<<endl;
}

else if(choice==3)
{
if(cartCount==0)
throw 3;

int id;

cout<<endl;
printLine('-',W);
printCenter("YOUR CART");
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<"ID"<<setw(32)<<"Name"<<setw(6)<<"Qty"<<setw(14)<<"Unit Price"<<"Subtotal"<<endl;

for(int i=0;i<cartCount;i++)
{
double sub=cart[i].price*cart[i].qty;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<cart[i].itemID<<setw(32)<<cart[i].name<<setw(6)<<cart[i].qty<<setw(14)<<moneyStr(cart[i].price)<<moneyStr(sub)<<endl;
}

printLine('-',W);

cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID to remove : ";
cin>>id;

int idx=-1;

for(int i=0;i<cartCount;i++)
{
if(cart[i].itemID==id)
idx=i;
}

if(idx==-1)
throw 4;

for(int i=idx;i<cartCount-1;i++)
cart[i]=cart[i+1];

cartCount--;
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item removed from cart."<<endl;
}

else if(choice==4)
{
if(cartCount==0)
throw 3;

double total=0;

cout<<endl;
printLine('-',W);
printCenter("YOUR CART");
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<"ID"<<setw(32)<<"Name"<<setw(6)<<"Qty"<<"Subtotal"<<endl;

for(int i=0;i<cartCount;i++)
{
double sub=cart[i].price*cart[i].qty;
total=total+sub;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(6)<<cart[i].itemID<<setw(32)<<cart[i].name<<setw(6)<<cart[i].qty<<moneyStr(sub)<<endl;
}

printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"TOTAL : "<<moneyStr(total)<<endl;
}

else if(choice==5)
{
if(cartCount==0)
throw 3;

checkout(c,cart,cartCount);
return;
}

else if(choice==0)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Order cancelled."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Invalid choice."<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item ID not found in menu."<<endl;

else if(e==2)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Quantity must be more than 0."<<endl;

else if(e==3)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Your cart is empty."<<endl;

else if(e==5)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Cart is full."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item not in cart."<<endl;
}

cout<<endl;
system("pause");
}
while(choice!=0);
}


//Customer function: read order_history.txt and show this customer's past orders
void viewOrderHistory(Customer &c)
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("YOUR ORDER HISTORY");
printLine('=',W);
cout<<endl;

try
{
ifstream file("order_history.txt");

if(!file)
throw 1;

string line;
int found=0;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(12)<<"Order ID"<<setw(24)<<"Date"<<"Total"<<endl;
printLine('-',W);

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

string oid=line.substr(0,p1);
string cust=line.substr(p1+1,p2-p1-1);
string dt=line.substr(p2+1,p3-p2-1);
string tot=line.substr(p3+1);

if(cust==c.getName())
{
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(12)<<oid<<setw(24)<<dt<<"RM"<<tot<<endl;
found++;
}
}

file.close();

if(found==0)
cout<<"\t\t\t\t\t\t\t\t"<<"No past orders found."<<endl;
}

catch(int e)
{
cout<<"\t\t\t\t\t\t\t\t"<<"No order history available yet."<<endl;
}

cout<<endl;
system("pause");
}


//Customer function: summarise this customer's spending and save it to order_summary.txt
void orderSummaryReport(Customer &c)
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ORDER SUMMARY REPORT");
printLine('=',W);
cout<<endl;

int totalOrders=0;
double totalSpent=0;

try
{
ifstream file("order_history.txt");

if(!file)
throw 1;

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

string cust=line.substr(p1+1,p2-p1-1);
string tot=line.substr(p3+1);

if(cust==c.getName())
{
totalOrders++;
totalSpent=totalSpent+atof(tot.c_str());
}
}

file.close();

ofstream out("order_summary.txt");

if(!out)
throw 2;

out<<"=========== ORDER SUMMARY ==========="<<endl;
out<<"Customer     : "<<c.getName()<<endl;
out<<"Total Orders : "<<totalOrders<<endl;
double avgSpent=0;

if(totalOrders>0)
avgSpent=totalSpent/totalOrders;

out<<"Total Spent  : RM"<<fixed<<setprecision(2)<<totalSpent<<endl;
out<<"Average/Order: RM"<<avgSpent<<endl;
out<<"====================================="<<endl;
out.close();

cout<<"\t\t\t\t\t\t\t\t"<<">> Report saved to order_summary.txt"<<endl;
cout<<endl;

ifstream in("order_summary.txt");
string rline;

while(getline(in,rline))
cout<<"\t\t\t\t\t\t\t\t"<<rline<<endl;

in.close();
}

catch(int e)
{
cout<<"\t\t\t\t\t\t\t\t"<<"No order data available for the report."<<endl;
}

cout<<endl;
system("pause");
}


//File handling: read order_items.txt and list the items of one order
void viewOrderItems(int oid)
{
ifstream file("order_items.txt");
bool found=false;

if(!file)
return;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(34)<<"Item"<<setw(6)<<"Qty"<<setw(12)<<"Unit"<<"Subtotal"<<endl;
printLine('-',W);

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

int oo=atoi(line.substr(0,p1).c_str());

if(oo!=oid)
continue;

string nm=line.substr(p1+1,p2-p1-1);
int q=atoi(line.substr(p2+1,p3-p2-1).c_str());
double pr=atof(line.substr(p3+1).c_str());
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(34)<<nm<<setw(6)<<q<<setw(12)<<moneyStr(pr)<<moneyStr(pr*q)<<endl;
found=true;
}

file.close();

if(!found)
cout<<"\t\t\t\t\t\t\t\t"<<"(No item details recorded for this order.)"<<endl;
}


//File handling: read order_history.txt into arrays for one customer
int loadCustomerOrders(string cust,int oids[],double totals[],string dts[])
{
ifstream file("order_history.txt");
int n=0;

if(!file)
return 0;

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

int oid=atoi(line.substr(0,p1).c_str());
string nm=line.substr(p1+1,p2-p1-1);
string dt=line.substr(p2+1,p3-p2-1);
double total=atof(line.substr(p3+1).c_str());

if(nm==cust)
{oids[n]=oid;
totals[n]=total;
dts[n]=dt;
n++;}
}

file.close();
return n;
}


//File handling: rewrite users.txt with one field of a customer record changed
void changeCustomerField(string uname,int fieldIndex,string newValue)
{
string lines[500];
int n=0;
ifstream in("users.txt");

if(!in)
return;

string line;

while(getline(in,line))
{
if(line!="")
{lines[n]=line;
n++;}
}

in.close();

string unames[500];

for(int i=0;i<n;i++)
{
int p0=lines[i].find('|');

if(p0<0)
unames[i]="";

else
unames[i]=lines[i].substr(0,p0);
}

int idx=findUserByHash(uname,unames,n);

if(idx>=0)
{
int p0=lines[idx].find('|');
int p1=lines[idx].find('|',p0+1);
int p2=lines[idx].find('|',p1+1);
int p3=lines[idx].find('|',p2+1);
string parts[5];
parts[0]=lines[idx].substr(0,p0);
parts[1]=lines[idx].substr(p0+1,p1-p0-1);
parts[2]=lines[idx].substr(p1+1,p2-p1-1);
parts[3]=lines[idx].substr(p2+1,p3-p2-1);
parts[4]=lines[idx].substr(p3+1);
parts[fieldIndex]=newValue;
lines[idx]=parts[0]+"|"+parts[1]+"|"+parts[2]+"|"+parts[3]+"|"+parts[4];
}

ofstream out("users.txt");

for(int i=0;i<n;i++)
out<<lines[i]<<endl;

out.close();
}


//Customer function: view profile and change phone number / password (updates memory + file)
void editProfile(Customer &c)
{
int choice;

do
{
system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("MY PROFILE");
printLine('=',W);
printLeft("Name         : "+c.getName());
printLeft("Username     : "+c.getUsername());
printLeft("Phone        : "+c.getPhone());
printLeft("Total Orders : "+intToStr(c.getTotalOrders()));
printLine('-',W);
printMenuOption(1,"Change Phone Number");
printMenuOption(2,"Change Password");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,2);

if(choice==1)
{
string ph;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new phone number : ";
getline(cin,ph);
changeCustomerField(c.getUsername(),3,ph);
c.setPhone(ph);
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Phone number updated."<<endl;
system("pause");
}

else if(choice==2)
{
string oldp,np,cf;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter current password : ";
cin>>oldp;

try
{
if(!c.checkPassword(oldp))
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new password : ";
cin>>np;
cout<<"\t\t\t\t\t\t\t\t"<<"Confirm new password : ";
cin>>cf;

if(np!=cf)
throw 2;

changeCustomerField(c.getUsername(),1,np);
c.setPassword(np);
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Password changed."<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Current password incorrect."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> New passwords do not match."<<endl;
}

system("pause");
}
}
while(choice!=0);
}


//Customer function: search this customer's own orders (Binary Search after sorting by ID)
void searchOwnOrder(Customer &c)
{
int oids[500];
double totals[500];
string dts[500];

system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SEARCH MY ORDER");
printLine('=',W);

int n=loadCustomerOrders(c.getName(),oids,totals,dts);

if(n==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<"You have no orders yet."<<endl<<endl;
system("pause");
return;
}

for(int i=0;i<n-1;i++)
{
for(int j=0;j<n-1-i;j++)
{
if(oids[j]>oids[j+1])
{
int ti=oids[j];oids[j]=oids[j+1];oids[j+1]=ti;
double td=totals[j];totals[j]=totals[j+1];totals[j+1]=td;
string ts=dts[j];dts[j]=dts[j+1];dts[j+1]=ts;
}
}
}

cout<<endl<<"\t\t\t\t\t\t\t\t"<<"Enter Order ID to search : ";
int key=getValidInt(1,999999);

int first=0,last=n-1,idx=-1;

while(first<=last)
{
int mid=(first+last)/2;

if(oids[mid]==key)
{idx=mid;
break;}

else if(oids[mid]<key)
first=mid+1;

else
last=mid-1;
}

cout<<endl;

if(idx==-1)
cout<<"\t\t\t\t\t\t\t\t"<<">> Order #"<<key<<" not found in your history."<<endl;

else
{
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Order #"<<oids[idx]<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Total  : "<<moneyStr(totals[idx])<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Date   : "<<dts[idx]<<endl;
printLine('-',W);
cout<<endl;
viewOrderItems(oids[idx]);
}

cout<<endl;
system("pause");
}


//Customer function: sort this customer's own orders (Bubble Sort) by ID or total
void sortOwnOrder(Customer &c)
{
int oids[500];
double totals[500];
string dts[500];

system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SORT MY ORDERS");
printLine('=',W);

int n=loadCustomerOrders(c.getName(),oids,totals,dts);

if(n==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<"You have no orders yet."<<endl<<endl;
system("pause");
return;
}

printMenuOption(1,"By Total (high to low)");
printMenuOption(2,"By Order ID (low to high)");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
int ch=getValidInt(1,2);

for(int i=0;i<n-1;i++)
{
for(int j=0;j<n-1-i;j++)
{
bool sw=false;

if(ch==1&&totals[j]<totals[j+1])
sw=true;

if(ch==2&&oids[j]>oids[j+1])
sw=true;

if(sw)
{
int ti=oids[j];oids[j]=oids[j+1];oids[j+1]=ti;
double td=totals[j];totals[j]=totals[j+1];totals[j+1]=td;
string ts=dts[j];dts[j]=dts[j+1];dts[j+1]=ts;
}
}
}

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(12)<<"Order ID"<<setw(14)<<"Total"<<"Date"<<endl;
printLine('-',W);

for(int i=0;i<n;i++)
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(12)<<oids[i]<<setw(14)<<moneyStr(totals[i])<<dts[i]<<endl;

cout<<endl;
system("pause");
}


//File handling: display the most recent saved receipt.txt
void viewLatestReceipt(Customer &c)
{
system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("LATEST RECEIPT");
printLine('=',W);
cout<<endl;

ifstream file("receipt.txt");
bool any=false;

if(file)
{
string line;

while(getline(file,line))
{cout<<"\t\t\t\t\t\t\t\t"<<line<<endl;
any=true;}

file.close();
}

if(!any)
cout<<"\t\t\t\t\t\t\t\t"<<">> No receipt available yet."<<endl;

cout<<endl;
system("pause");
}


//Customer function: rebuild a cart from a past order (reads order_items.txt) and check out again
void reorder(Customer &c)
{
int oids[500];
double totals[500];
string dts[500];

system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("REORDER A PAST ORDER");
printLine('=',W);

int n=loadCustomerOrders(c.getName(),oids,totals,dts);

if(n==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<"You have no past orders to reorder."<<endl<<endl;
system("pause");
return;
}

cout<<"\t\t\t\t\t\t\t\t"<<"Your past orders :"<<endl;

for(int i=0;i<n;i++)
cout<<"\t\t\t\t\t\t\t\t"<<"  #"<<oids[i]<<"   "<<moneyStr(totals[i])<<"   "<<dts[i]<<endl;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<"Enter Order ID to reorder (0 to back) : ";
int oid=getValidInt(0,999999);

if(oid==0)
return;

CartItem cart[100];
int cartCount=0;
ifstream file("order_items.txt");

if(file)
{
string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

int oo=atoi(line.substr(0,p1).c_str());

if(oo!=oid)
continue;

cart[cartCount].itemID=0;
cart[cartCount].name=line.substr(p1+1,p2-p1-1);
cart[cartCount].qty=atoi(line.substr(p2+1,p3-p2-1).c_str());
cart[cartCount].price=atof(line.substr(p3+1).c_str());
cartCount++;
}

file.close();
}

if(cartCount==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> No item details found for that order."<<endl<<endl;
system("pause");
return;
}

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Re-adding "<<cartCount<<" item(s) from order #"<<oid<<" ..."<<endl;
Sleep(800);
checkout(c,cart,cartCount);
}


//Customer function: the "My Orders" submenu
void customerOrdersMenu(Customer &c)
{
int choice;

do
{
system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("MY ORDERS");
printLine('=',W);
printMenuOption(1,"View Order History");
printMenuOption(2,"Search My Order");
printMenuOption(3,"Sort My Orders");
printMenuOption(4,"View Latest Receipt");
printMenuOption(5,"Order Summary Report");
printMenuOption(6,"Reorder Past Order");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,6);

if(choice==1)
viewOrderHistory(c);

else if(choice==2)
searchOwnOrder(c);

else if(choice==3)
sortOwnOrder(c);

else if(choice==4)
viewLatestReceipt(c);

else if(choice==5)
orderSummaryReport(c);

else if(choice==6)
reorder(c);
}
while(choice!=0);
}


//Menu function: filter and show menu items by category
void filterByCategory()
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("FILTER BY CATEGORY");
printLine('=',W);
printMenuOption(1,"Fried Chicken");
printMenuOption(2,"Burger");
printMenuOption(3,"Side");
printMenuOption(4,"Dessert");
printMenuOption(5,"Beverage");
printMenuOption(6,"Combo");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
int ch=getValidInt(1,6);
string cat;

if(ch==1)
cat="Fried Chicken";

else if(ch==2)
cat="Burger";

else if(ch==3)
cat="Side";

else if(ch==4)
cat="Dessert";

else if(ch==5)
cat="Beverage";

else
cat="Combo";

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);
menu.displayByCategory(cat);
cout<<endl;
system("pause");
}


//Menu function: filter and show menu items by variant
void filterByVariant()
{
MenuItem *arr[200];
int n=menu.toArray(arr);

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("FILTER BY VARIANT");
printLine('=',W);
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter variant (e.g. Spicy, Cold, Hot, Regular) : ";
string v;
getline(cin,v);

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);

int found=0;

for(int i=0;i<n;i++)
{
if(arr[i]->getVariant()==v)
{arr[i]->display();
found++;}
}

if(found==0)
cout<<"\t\t\t\t\t\t\t\t"<<"No items found with variant '"<<v<<"'."<<endl;

cout<<endl;
system("pause");
}


//Menu function: filter and show menu items within a price range
void filterByPriceRange()
{
MenuItem *arr[200];
int n=menu.toArray(arr);

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("FILTER BY PRICE RANGE");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter minimum price : RM";
double lo=getValidDouble(0);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter maximum price : RM";
double hi=getValidDouble(lo);

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);

int found=0;

for(int i=0;i<n;i++)
{
if(arr[i]->getPrice()>=lo&&arr[i]->getPrice()<=hi)
{arr[i]->display();
found++;}
}

if(found==0)
cout<<"\t\t\t\t\t\t\t\t"<<"No items found in that price range."<<endl;

cout<<endl;
system("pause");
}


//Menu function: the filter submenu
void filterMenu()
{
int choice;

do
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("FILTER MENU");
printLine('=',W);
printMenuOption(1,"Filter by Category");
printMenuOption(2,"Filter by Variant");
printMenuOption(3,"Filter by Price Range");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,3);

if(choice==1)
filterByCategory();

else if(choice==2)
filterByVariant();

else if(choice==3)
filterByPriceRange();
}
while(choice!=0);
}


//Customer function: the main customer menu (browse, search, sort, filter, order, profile)
void customerDashboard(Customer &c)
{
int choice;

do
{
system("color 3F");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("CUSTOMER DASHBOARD");
printLine('=',W);
printLeft("Welcome, "+c.getName());
printLine('-',W);
printMenuOption(1,"Browse Menu");
printMenuOption(2,"Search Menu");
printMenuOption(3,"Sort Menu");
printMenuOption(4,"Filter Menu");
printMenuOption(5,"Place Order");
printMenuOption(6,"My Orders");
printMenuOption(7,"My Profile");
printMenuOption(0,"Logout");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,7);

if(choice==1)
browseMenu();

else if(choice==2)
searchMenuItem();

else if(choice==3)
sortMenuItem();

else if(choice==4)
filterMenu();

else if(choice==5)
placeOrder(c);

else if(choice==6)
customerOrdersMenu(c);

else if(choice==7)
editProfile(c);

else if(choice==0)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Logging out..."<<endl;
}
while(choice!=0);
}


//Admin function: register a new admin account and append it to users.txt
void adminRegister()
{
string uname,pass,nm,sid,phone;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("STAFF REGISTRATION");
printLine('=',W);
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new staff username : ";
cin>>uname;

try
{
if(usernameExists(uname))
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new password       : ";
cin>>pass;
cin.ignore();

cout<<"\t\t\t\t\t\t\t\t"<<"Enter staff name         : ";
getline(cin,nm);

cout<<"\t\t\t\t\t\t\t\t"<<"Enter staff ID           : ";
getline(cin,sid);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter phone number       : ";
getline(cin,phone);

ofstream file("users.txt",ios::app);

if(!file)
throw 2;

file<<uname<<"|"<<pass<<"|"<<nm<<"|"<<sid<<"|Admin|"<<phone<<endl;
file.close();

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Staff account created successfully!"<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Username already exists. Please try another."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: cannot save to users.txt"<<endl;
}

cout<<endl;
system("pause");
}


//Admin function: log an admin in (username looked up by hashing)
int adminLogin(Admin &a)
{
string uname,pass;

while(true)
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ADMIN LOGIN");
printLine('=',W);
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter username : ";
cin>>uname;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter password : ";
cin>>pass;

try
{
string unames[500],pwds[500],names[500],contacts[500],roles[500],phones[500];
int n=loadAllUsers(unames,pwds,names,contacts,roles,phones);

if(uname=="kasing"&&pass=="lim123")
{
int idx=findUserByHash(uname,unames,n>0?n:0);

if(idx>=0&&roles[idx]=="Admin")
{a=Admin(unames[idx],pwds[idx],names[idx],contacts[idx]);
a.setPhone(phones[idx]);}

else
a=Admin("kasing","lim123","Lim Ka Sing","S001");

return 1;
}

if(n<0)
throw 1;

int idx=findUserByHash(uname,unames,n);

if(idx>=0&&pwds[idx]==pass&&roles[idx]=="Admin")
{
a=Admin(unames[idx],pwds[idx],names[idx],contacts[idx]);
a.setPhone(phones[idx]);
return 1;
}

throw 2;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: users.txt not found."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Wrong username or password."<<endl;
}

char ans;

while(true)
{
cout<<"\t\t\t\t\t\t\t\t"<<"Do you want to try again? (Y/N) : ";
cin>>ans;

if(cin.eof())
return 0;

if(ans=='Y'||ans=='y')
break;

else if(ans=='N'||ans=='n')
return 0;

else
cout<<"\t\t\t\t\t\t\t\t"<<">> Invalid choice."<<endl;
}
}
}


//Admin / Menu function: add a new menu item, then save the menu to file
void adminAddMenuItem()
{
string cat,nm,var;
double price;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ADD MENU ITEM");
printLine('=',W);
cout<<endl;

try
{
cout<<"\t\t\t\t\t\t\t\t"<<"Category (Fried Chicken/Burger/Side/Dessert/Beverage/Combo) :"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"> ";
cin.ignore();
getline(cin,cat);

cout<<"\t\t\t\t\t\t\t\t"<<"Item name : ";
getline(cin,nm);

cout<<"\t\t\t\t\t\t\t\t"<<"Variant (Spicy/Non-Spicy/Hot/Cold/Sweet/Set/Regular) : ";
getline(cin,var);

cout<<"\t\t\t\t\t\t\t\t"<<"Price (RM) : ";
cin>>price;

if(price<=0)
throw 1;

menu.addItem(cat,nm,price,var);
menu.saveToFile("menu.txt");

cout<<"\t\t\t\t\t\t\t\t"<<">> Menu saved. Customers can now see this item."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Invalid price. Item not added."<<endl;
}

cout<<endl;
system("pause");
}


//Admin / Menu function: list the whole menu so the admin can pick an item ID
void showMenuForSelection()
{
MenuItem *arr[200];
int cnt=menu.toArray(arr);

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(16)<<"Category"<<setw(32)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;

for(int i=0;i<cnt;i++)
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<arr[i]->getID()<<setw(16)<<arr[i]->getCategory()<<setw(32)<<arr[i]->getName()<<setw(12)<<arr[i]->getVariant()<<moneyStr(arr[i]->getPrice())<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;
}


//Admin / Menu function: edit a menu item's name / price, then save the menu
void adminEditMenuItem()
{
int id,choice;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("EDIT MENU ITEM");
printLine('=',W);
cout<<endl;
showMenuForSelection();
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID to edit : ";
cin>>id;

try
{
MenuItem *m=menu.searchByID(id);

if(m==NULL)
throw 1;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<"Current item :"<<endl;
m->display();

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"1. Edit name"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"2. Edit price"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
cin>>choice;

if(choice==1)
{
string newName;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new name : ";
getline(cin,newName);
m->setName(newName);
}

else if(choice==2)
{
double newPrice;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new price (RM) : ";
cin>>newPrice;

if(newPrice<=0)
throw 2;

m->setPrice(newPrice);
}

else
throw 3;

menu.saveToFile("menu.txt");

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item updated and saved."<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"New details :"<<endl;
m->display();
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item ID not found."<<endl;

else if(e==2)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Invalid price."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Invalid choice."<<endl;
}

cout<<endl;
system("pause");
}


//Admin / Menu function: delete a menu item, then save the menu
void adminDeleteMenuItem()
{
int id;

system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("DELETE MENU ITEM");
printLine('=',W);
cout<<endl;
showMenuForSelection();
cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter item ID to delete : ";
cin>>id;

try
{
MenuItem *m=menu.searchByID(id);

if(m==NULL)
throw 1;

cout<<endl<<"\t\t\t\t\t\t\t\t"<<"Item to be deleted :"<<endl;
m->display();

bool ok=menu.deleteByID(id);

if(!ok)
throw 1;

menu.saveToFile("menu.txt");

cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item deleted and menu saved."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Item ID not found."<<endl;
}

cout<<endl;
system("pause");
}


//Admin function: build a sales report from order_history.txt and save it to sales_report.txt
void salesReport()
{
int oids[1000];
double totals[1000];
int n=0;

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SALES REPORT");
printLine('=',W);
cout<<endl;

try
{
ifstream file("order_history.txt");

if(!file)
throw 1;

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

oids[n]=atoi(line.substr(0,p1).c_str());
totals[n]=atof(line.substr(p3+1).c_str());
n++;
}

file.close();

if(n==0)
throw 1;

double totalGross=0;
double highest=totals[0];
double lowest=totals[0];
int hiId=oids[0];
int loId=oids[0];

for(int i=0;i<n;i++)
{
totalGross=totalGross+totals[i];

if(totals[i]>highest)
{highest=totals[i];
hiId=oids[i];}

if(totals[i]<lowest)
{lowest=totals[i];
loId=oids[i];}
}

double avg=totalGross/n;
double estSubtotal=totalGross/1.166;
double estService=estSubtotal*0.10;
double estSST=(estSubtotal+estService)*0.06;

ofstream out("sales_report.txt");

if(!out)
throw 2;

out<<fixed<<setprecision(2);
out<<"================ SALES REPORT ================"<<endl;
out<<"Generated by : Lim Ka Sing (Admin)"<<endl;
out<<"Date         : "<<getDateTime()<<endl;
out<<"----------------------------------------------"<<endl;
out<<"Total Orders     : "<<n<<endl;
out<<"Gross Sales      : RM"<<totalGross<<endl;
out<<"Est. Subtotal    : RM"<<estSubtotal<<endl;
out<<"Est. Service 10% : RM"<<estService<<endl;
out<<"Est. SST 6%      : RM"<<estSST<<endl;
out<<"Average Order    : RM"<<avg<<endl;
out<<"Highest Order    : RM"<<highest<<" (#"<<hiId<<")"<<endl;
out<<"Lowest Order     : RM"<<lowest<<" (#"<<loId<<")"<<endl;
out<<"=============================================="<<endl;
out.close();

cout<<"\t\t\t\t\t\t\t\t"<<">> Report saved to sales_report.txt"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<">> Retrieving report from file..."<<endl;
cout<<endl;

ifstream in("sales_report.txt");
string rline;

while(getline(in,rline))
cout<<"\t\t\t\t\t\t\t\t"<<rline<<endl;

in.close();
}

catch(int e)
{
cout<<"\t\t\t\t\t\t\t\t"<<"No sales data available for the report."<<endl;
}

cout<<endl;
system("pause");
}


//File handling: read users.txt into arrays (username / name / contact / role)
int loadUsers(string unames[],string names[],string contacts[],string roles[])
{
ifstream file("users.txt");
int n=0;

if(!file)
return 0;

string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);
int p4=line.find('|',p3+1);

if(p1<0||p2<0||p3<0||p4<0)
continue;

unames[n]=line.substr(0,p1);
names[n]=line.substr(p2+1,p3-p2-1);
contacts[n]=line.substr(p3+1,p4-p3-1);

int p5=line.find('|',p4+1);

if(p5>=0)
roles[n]=line.substr(p4+1,p5-p4-1);

else
roles[n]=line.substr(p4+1);

n++;
}

file.close();
return n;
}


//Admin function: list every customer account
void viewAllCustomers()
{
string unames[500],names[500],contacts[500],roles[500];
int n=loadUsers(unames,names,contacts,roles);

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ALL CUSTOMERS");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<"Username"<<setw(24)<<"Name"<<"Phone"<<endl;
printLine('-',W);

int count=0;

for(int i=0;i<n;i++)
{
if(roles[i]=="Customer")
{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<unames[i]<<setw(24)<<names[i]<<contacts[i]<<endl;
count++;}
}

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Total customers : "<<count<<endl;
cout<<endl;
system("pause");
}


//Admin function: list every admin / staff account
void viewAllStaff()
{
string unames[500],names[500],contacts[500],roles[500];
int n=loadUsers(unames,names,contacts,roles);

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ALL STAFF");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<"Username"<<setw(24)<<"Name"<<"Staff ID"<<endl;
printLine('-',W);

int count=0;

for(int i=0;i<n;i++)
{
if(roles[i]=="Admin")
{cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<unames[i]<<setw(24)<<names[i]<<contacts[i]<<endl;
count++;}
}

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Total staff : "<<count<<endl;
cout<<endl;
system("pause");
}


//Admin function: find a customer by username (hashing lookup)
void searchCustomer()
{
string unames[500],names[500],contacts[500],roles[500];
int n=loadUsers(unames,names,contacts,roles);

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("SEARCH CUSTOMER");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter customer username : ";
string key;
cin>>key;

int idx=findUserByHash(key,unames,n);

if(idx>=0&&roles[idx]!="Customer")
idx=-1;

cout<<endl;

if(idx==-1)
cout<<"\t\t\t\t\t\t\t\t"<<">> Customer not found."<<endl;

else
{
printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Username : "<<unames[idx]<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Name     : "<<names[idx]<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Phone    : "<<contacts[idx]<<endl;
printLine('-',W);
}

cout<<endl;
system("pause");
}


//Admin function: list customers then delete one (rewrites users.txt)
void deleteCustomer()
{
string lines[500];
int n=0;
ifstream in("users.txt");

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("DELETE CUSTOMER");
printLine('=',W);

if(!in)
{
cout<<"\t\t\t\t\t\t\t\t"<<">> Cannot open users.txt"<<endl<<endl;
system("pause");
return;
}

string line;

while(getline(in,line))
{
if(line!="")
{lines[n]=line;
n++;}
}

in.close();

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(20)<<"Username"<<setw(28)<<"Name"<<"Phone"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;

int shown=0;

for(int i=0;i<n;i++)
{
int pa=lines[i].find('|');
int pb=lines[i].find('|',pa+1);
int pc=lines[i].find('|',pb+1);
int pd=lines[i].find('|',pc+1);

if(pa<0||pb<0||pc<0||pd<0)
continue;

int pe=lines[i].find('|',pd+1);
string rl;

if(pe>=0)
rl=lines[i].substr(pd+1,pe-pd-1);

else
rl=lines[i].substr(pd+1);

if(rl!="Customer")
continue;

string un=lines[i].substr(0,pa);
string nm=lines[i].substr(pb+1,pc-pb-1);
string ph=lines[i].substr(pc+1,pd-pc-1);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(20)<<un<<setw(28)<<nm<<ph<<endl;
shown++;
}

cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;

if(shown==0)
cout<<"\t\t\t\t\t\t\t\t"<<">> No customers registered."<<endl;

cout<<endl;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter customer username to delete : ";
string key;
cin>>key;

string unames[500];

for(int i=0;i<n;i++)
{
int p1=lines[i].find('|');

if(p1<0)
unames[i]="";

else
unames[i]=lines[i].substr(0,p1);
}

int idx=findUserByHash(key,unames,n);

if(idx>=0)
{
int qa=lines[idx].find('|');
int qb=lines[idx].find('|',qa+1);
int qc=lines[idx].find('|',qb+1);
int qd=lines[idx].find('|',qc+1);
int qe=lines[idx].find('|',qd+1);
string role;

if(qe>=0)
role=lines[idx].substr(qd+1,qe-qd-1);

else
role=lines[idx].substr(qd+1);

if(role!="Customer")
idx=-1;
}

try
{
if(idx==-1)
throw 1;

if(!confirmAction("Delete customer '"+key+"' permanently?"))
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Deletion cancelled."<<endl<<endl;
system("pause");
return;
}

ofstream out("users.txt");

for(int i=0;i<n;i++)
{
if(i!=idx)
out<<lines[i]<<endl;
}

out.close();
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Customer '"<<key<<"' deleted successfully."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Customer not found (staff cannot be deleted here)."<<endl;
}

cout<<endl;
system("pause");
}


//File handling: rewrite users.txt with one field of an admin changed (keeps the 6-field admin format)
void updateAdminField(string uname,string field,string value)
{
string lines[500];
int n=0;
ifstream in("users.txt");

if(!in)
return;

string line;

while(getline(in,line))
{
if(line!="")
{lines[n]=line;
n++;}
}

in.close();

for(int i=0;i<n;i++)
{
int pa=lines[i].find('|');

if(pa<0)
continue;

if(lines[i].substr(0,pa)!=uname)
continue;

int pb=lines[i].find('|',pa+1);
int pc=lines[i].find('|',pb+1);
int pd=lines[i].find('|',pc+1);

if(pb<0||pc<0||pd<0)
continue;

int pe=lines[i].find('|',pd+1);
string user=lines[i].substr(0,pa);
string pass=lines[i].substr(pa+1,pb-pa-1);
string nm=lines[i].substr(pb+1,pc-pb-1);
string sid=lines[i].substr(pc+1,pd-pc-1);
string role;
string phone;

if(pe>=0)
{role=lines[i].substr(pd+1,pe-pd-1);
phone=lines[i].substr(pe+1);}

else
{role=lines[i].substr(pd+1);
phone="";}

if(field=="password")
pass=value;

else if(field=="phone")
phone=value;

lines[i]=user+"|"+pass+"|"+nm+"|"+sid+"|"+role+"|"+phone;
}

ofstream out("users.txt");

for(int i=0;i<n;i++)
out<<lines[i]<<endl;

out.close();
}


//Admin function: view profile and change phone number / password (updates memory + file)
void adminProfile(Admin &a)
{
int choice;

do
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("MY PROFILE");
printLine('=',W);
printLeft("Username : "+a.getUsername());
printLeft("Staff ID : "+a.getStaffID());
printLeft("Name     : "+a.getName());
printLeft("Phone    : "+a.getPhone());
printLeft("Role     : "+a.getRole());
printLine('-',W);
printMenuOption(1,"Edit Phone");
printMenuOption(2,"Change Password");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,2);

if(choice==1)
{
string ph;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new phone number : ";
getline(cin,ph);
updateAdminField(a.getUsername(),"phone",ph);
a.setPhone(ph);
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Phone number updated."<<endl;
system("pause");
}

else if(choice==2)
{
string oldp,np,cf;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter current password : ";
cin>>oldp;

try
{
if(!a.checkPassword(oldp))
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter new password : ";
cin>>np;
cout<<"\t\t\t\t\t\t\t\t"<<"Confirm new password : ";
cin>>cf;

if(np!=cf)
throw 2;

updateAdminField(a.getUsername(),"password",np);
a.setPassword(np);
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Password changed."<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Current password incorrect."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Passwords do not match."<<endl;
}

system("pause");
}
}
while(choice!=0);
}


//Admin function: create a new staff account from the dashboard
void adminAddStaff()
{
string uname,pass,nm,sid,phone;

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ADD NEW STAFF");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new staff username : ";
cin>>uname;

try
{
if(usernameExists(uname))
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Enter password           : ";
cin>>pass;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter staff name         : ";
getline(cin,nm);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter staff ID           : ";
getline(cin,sid);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter phone number       : ";
getline(cin,phone);

ofstream file("users.txt",ios::app);

if(!file)
throw 2;

file<<uname<<"|"<<pass<<"|"<<nm<<"|"<<sid<<"|Admin|"<<phone<<endl;
file.close();
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Staff account created successfully."<<endl;
}

catch(int e)
{
if(e==1)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Username already exists."<<endl;

else
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Error: cannot save to users.txt"<<endl;
}

cout<<endl;
system("pause");
}


//Admin function: change a customer's name (rewrites users.txt)
void editCustomer()
{
string unames[500],names[500],contacts[500],roles[500];
int n=loadUsers(unames,names,contacts,roles);

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("EDIT CUSTOMER NAME");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter customer username : ";
string key;
cin>>key;

int idx=findUserByHash(key,unames,n);

if(idx>=0&&roles[idx]!="Customer")
idx=-1;

try
{
if(idx==-1)
throw 1;

cout<<"\t\t\t\t\t\t\t\t"<<"Current name : "<<names[idx]<<endl;
cin.ignore();
cout<<"\t\t\t\t\t\t\t\t"<<"Enter new name : ";
string nm;
getline(cin,nm);
changeCustomerField(key,2,nm);
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Name updated for '"<<key<<"'."<<endl;
}

catch(int e)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Customer not found."<<endl;
}

cout<<endl;
system("pause");
}


//Admin function: menu statistics - count per category, cheapest / priciest, average price
void menuStatistics()
{
MenuItem *arr[200];
int n=menu.toArray(arr);

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("MENU STATISTICS");
printLine('=',W);

if(n==0)
{
cout<<"\t\t\t\t\t\t\t\t"<<"Menu is empty."<<endl<<endl;
system("pause");
return;
}

string cats[7]={"Fried Chicken","Burger","Side","Dessert","Beverage","Combo","Other"};
int counts[7]={0,0,0,0,0,0,0};
double cheapest=arr[0]->getPrice();
double priciest=arr[0]->getPrice();
string cheapName=arr[0]->getName();
string priceyName=arr[0]->getName();
double sumPrice=0;

for(int i=0;i<n;i++)
{
string c=arr[i]->getCategory();
int idx=6;

if(c=="Fried Chicken")
idx=0;

else if(c=="Burger")
idx=1;

else if(c=="Side")
idx=2;

else if(c=="Dessert")
idx=3;

else if(c=="Beverage")
idx=4;

else if(c=="Combo")
idx=5;

counts[idx]++;
sumPrice=sumPrice+arr[i]->getPrice();

if(arr[i]->getPrice()<cheapest)
{cheapest=arr[i]->getPrice();
cheapName=arr[i]->getName();}

if(arr[i]->getPrice()>priciest)
{priciest=arr[i]->getPrice();
priceyName=arr[i]->getName();}
}

cout<<"\t\t\t\t\t\t\t\t"<<"Total items : "<<n<<endl;
printLine('-',W);

for(int i=0;i<7;i++)
{
if(counts[i]>0)
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(20)<<cats[i]<<": "<<counts[i]<<" item(s)"<<endl;
}

printLine('-',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Cheapest      : "<<cheapName<<" ("<<moneyStr(cheapest)<<")"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Most Expensive: "<<priceyName<<" ("<<moneyStr(priciest)<<")"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Average Price : "<<moneyStr(sumPrice/n)<<endl;
cout<<endl;
system("pause");
}


//Admin function: read order_items.txt, tally quantities, show best sellers (Bubble Sort by quantity)
void topSellingItems()
{
string names[1000];
int qtys[1000];
int n=0;

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("TOP SELLING ITEMS");
printLine('=',W);

ifstream file("order_items.txt");

if(file)
{
string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

string nm=line.substr(p1+1,p2-p1-1);
int q=atoi(line.substr(p2+1,p3-p2-1).c_str());
int found=-1;

for(int i=0;i<n;i++)
{
if(names[i]==nm)
{found=i;
break;}
}

if(found==-1)
{names[n]=nm;
qtys[n]=q;
n++;}

else
qtys[found]=qtys[found]+q;
}

file.close();
}

if(n==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<"No sales data recorded yet."<<endl<<endl;
system("pause");
return;
}

for(int i=0;i<n-1;i++)
{
for(int j=0;j<n-1-i;j++)
{
if(qtys[j]<qtys[j+1])
{
int tq=qtys[j];qtys[j]=qtys[j+1];qtys[j+1]=tq;
string tn=names[j];names[j]=names[j+1];names[j+1]=tn;
}
}
}

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(8)<<"Rank"<<setw(36)<<"Item"<<"Qty Sold"<<endl;
printLine('-',W);

for(int i=0;i<n;i++)
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(8)<<(i+1)<<setw(36)<<names[i]<<qtys[i]<<endl;

cout<<endl;
system("pause");
}


//Admin function: read order_history.txt and total the sales for each day
void dailySalesBreakdown()
{
string dates[1000];
double sums[1000];
int counts[1000];
int n=0;

system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("DAILY SALES BREAKDOWN");
printLine('=',W);

ifstream file("order_history.txt");

if(file)
{
string line;

while(getline(file,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

string dt=line.substr(p2+1,p3-p2-1);
string day=dt.substr(0,10);
double tot=atof(line.substr(p3+1).c_str());
int found=-1;

for(int i=0;i<n;i++)
{
if(dates[i]==day)
{found=i;
break;}
}

if(found==-1)
{dates[n]=day;
sums[n]=tot;
counts[n]=1;
n++;}

else
{sums[found]=sums[found]+tot;
counts[found]++;}
}

file.close();
}

if(n==0)
{
cout<<endl<<"\t\t\t\t\t\t\t\t"<<"No sales data recorded yet."<<endl<<endl;
system("pause");
return;
}

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<"Date"<<setw(12)<<"Orders"<<"Sales"<<endl;
printLine('-',W);

for(int i=0;i<n;i++)
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(16)<<dates[i]<<setw(12)<<counts[i]<<moneyStr(sums[i])<<endl;

cout<<endl;
system("pause");
}


//Admin function: the Reports submenu
void adminReports()
{
int choice;

do
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("REPORTS");
printLine('=',W);
printMenuOption(1,"Sales Report");
printMenuOption(2,"Top Selling Items");
printMenuOption(3,"Daily Sales Breakdown");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,3);

if(choice==1)
salesReport();

else if(choice==2)
topSellingItems();

else if(choice==3)
dailySalesBreakdown();
}
while(choice!=0);
}


//Admin / Menu function: show two menu items side by side and compare their prices
void compareMenuItems()
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("COMPARE TWO MENU ITEMS");
printLine('=',W);
showMenuForSelection();
cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Enter first item ID  : ";
int id1=getValidInt(1,999999);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter second item ID : ";
int id2=getValidInt(1,999999);

MenuItem *a=menu.searchByID(id1);
MenuItem *b=menu.searchByID(id2);

cout<<endl;

if(a==NULL||b==NULL)
{
cout<<"\t\t\t\t\t\t\t\t"<<">> One or both item IDs were not found."<<endl;
}

else
{
cout<<"\t\t\t\t\t\t\t\t"<<"+"<<string(74,'-')<<"+"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  Field      "<<setw(30)<<"Item 1"<<"Item 2"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+"<<string(74,'-')<<"+"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  ID       : "<<setw(30)<<a->getID()<<b->getID()<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  Category : "<<setw(30)<<a->getCategory()<<b->getCategory()<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  Name     : "<<setw(30)<<a->getName()<<b->getName()<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  Variant  : "<<setw(30)<<a->getVariant()<<b->getVariant()<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"  Price    : "<<setw(30)<<moneyStr(a->getPrice())<<moneyStr(b->getPrice())<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+"<<string(74,'-')<<"+"<<endl;
cout<<endl;

if((*a)==(*b))
cout<<"\t\t\t\t\t\t\t\t"<<"These are the same item."<<endl;

else
{
cout<<"\t\t\t\t\t\t\t\t";
compareItem(*a,*b);
}
}

cout<<endl;
system("pause");
}


//Admin function: the Menu Management submenu (add / edit / delete / display / stats / compare)
void adminMenuManagement()
{
int choice;

do
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("MENU MANAGEMENT");
printLine('=',W);
printMenuOption(1,"Add Menu Item");
printMenuOption(2,"Edit Menu Item");
printMenuOption(3,"Delete Menu Item");
printMenuOption(4,"Display Full Menu");
printMenuOption(5,"Menu Statistics");
printMenuOption(6,"Compare Two Items");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,6);

if(choice==1)
adminAddMenuItem();

else if(choice==2)
adminEditMenuItem();

else if(choice==3)
adminDeleteMenuItem();

else if(choice==4)
{
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("FULL MENU");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(5)<<"ID"<<setw(34)<<"Name"<<setw(12)<<"Variant"<<"Price"<<endl;
printLine('-',W);
menu.displayAll();
cout<<endl;
system("pause");
}

else if(choice==5)
menuStatistics();

else if(choice==6)
compareMenuItems();
}
while(choice!=0);
}


//Admin function: read order_history.txt and display all orders (View Order)
void adminOrderManagement()
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("VIEW ORDER");
printLine('=',W);
cout<<endl;

ifstream in("order_history.txt");

if(!in)
{
cout<<"\t\t\t\t\t\t\t\t"<<">> No order records found."<<endl;
cout<<endl;
system("pause");
return;
}

string line;
int count=0;

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(10)<<"Order ID"<<setw(24)<<"Customer"<<setw(22)<<"Date"<<"Total"<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;

while(getline(in,line))
{
if(line=="")
continue;

int p1=line.find('|');
int p2=line.find('|',p1+1);
int p3=line.find('|',p2+1);

if(p1<0||p2<0||p3<0)
continue;

string oid=line.substr(0,p1);
string nm=line.substr(p1+1,p2-p1-1);
string dt=line.substr(p2+1,p3-p2-1);
string tot=line.substr(p3+1);

cout<<"\t\t\t\t\t\t\t\t"<<left<<setw(10)<<oid<<setw(24)<<nm<<setw(22)<<dt<<"RM"<<tot<<endl;
count++;
}

in.close();

cout<<"\t\t\t\t\t\t\t\t"<<"+--------------------------------------------------------------------------+"<<endl;

if(count==0)
cout<<"\t\t\t\t\t\t\t\t"<<">> No orders yet."<<endl;

cout<<endl;
cout<<"\t\t\t\t\t\t\t\t"<<"Total orders : "<<count<<endl;
cout<<endl;
system("pause");
}


//Admin function: the Customer Management submenu
void adminCustomerManagement()
{
int choice;

do
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("CUSTOMER MANAGEMENT");
printLine('=',W);
printMenuOption(1,"View All Customers");
printMenuOption(2,"Search Customer");
printMenuOption(3,"Edit Customer Name");
printMenuOption(4,"Delete Customer");
printMenuOption(5,"View All Staff");
printMenuOption(6,"Add New Staff");
printMenuOption(0,"Back");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,6);

if(choice==1)
viewAllCustomers();

else if(choice==2)
searchCustomer();

else if(choice==3)
editCustomer();

else if(choice==4)
deleteCustomer();

else if(choice==5)
viewAllStaff();

else if(choice==6)
adminAddStaff();
}
while(choice!=0);
}


//Admin function: the main admin menu
void adminDashboard(Admin &a)
{
int choice;

do
{
system("color E0");
system("cls");
cout<<endl;
printLine('=',W);
printCenteredBoxTitle("ADMIN DASHBOARD");
printLine('=',W);
printLeft("Welcome, "+a.getName()+" ("+a.getStaffID()+")");
printLine('-',W);
printMenuOption(1,"Menu Management");
printMenuOption(2,"Search Menu");
printMenuOption(3,"Sort Menu");
printMenuOption(4,"View Order");
printMenuOption(5,"Customer Management");
printMenuOption(6,"Reports");
printMenuOption(7,"My Profile");
printMenuOption(0,"Logout");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,7);

if(choice==1)
adminMenuManagement();

else if(choice==2)
searchMenuItem();

else if(choice==3)
sortMenuItem();

else if(choice==4)
adminOrderManagement();

else if(choice==5)
adminCustomerManagement();

else if(choice==6)
adminReports();

else if(choice==7)
adminProfile(a);

else if(choice==0)
cout<<endl<<"\t\t\t\t\t\t\t\t"<<">> Logging out..."<<endl;
}
while(choice!=0);
}


//UI: animated loading screen shown at start-up
void loadingScreen()
{
system("color 0E");
system("cls");
cout<<endl<<endl<<endl;
printLine('=',W);
printCenter("");
printCenter("FAST FOOD ORDERING SYSTEM");
printCenter("");
printLine('=',W);
cout<<endl<<endl;
cout<<"\t\t\t\t\t\t\t\tLoading  ";

for(int i=0;i<30;i++)
{
cout<<char(219);
Sleep(70);
}

cout<<"  100%"<<endl;
Sleep(500);
}


//UI: goodbye screen shown on exit
void exitScreen()
{
system("color 0A");
system("cls");
cout<<endl<<endl<<endl;
printLine('=',W);
printCenter("");
printCenter("THANK YOU FOR USING OUR SYSTEM!");
printCenter("~~ See you again ~~");
printCenter("");
printLine('=',W);
cout<<endl<<endl;
Sleep(1000);
}


//File handling: on first run, seed users.txt with default accounts and create the empty output .txt files
void initializeFiles()
{
ifstream check("users.txt");

if(!check)
{
ofstream file("users.txt");
file<<"kasing|lim123|Lim Ka Sing|S001|Admin|0123456700"<<endl;
file<<"shande|tan123|Tan Shan De|0123456789|Customer"<<endl;
file<<"mengsheng|abc123|Soh Meng Sheng|0129876543|Customer"<<endl;
file.close();
}

else
check.close();

string outfiles[6]={"receipt.txt","order_history.txt","orders.txt","sales_report.txt","order_summary.txt","order_items.txt"};

for(int i=0;i<6;i++)
{
ifstream f(outfiles[i].c_str());

if(!f)
{ofstream cf(outfiles[i].c_str());
cf.close();}

else
f.close();
}
}


//Main menu loop: customer login / register, admin login / register, exit
void mainPage()
{
int choice;

do
{
system("color B0");
system("cls");
cout<<endl;
printLine('=',W);
printCenter("");
printCenter("FAST FOOD ORDERING SYSTEM");
printCenter("");
printLine('=',W);
printCenter("");
printMenuOption(1,"Customer Login");
printMenuOption(2,"Customer Register");
printMenuOption(3,"Admin Login");
printMenuOption(4,"Admin Register");
printMenuOption(0,"Exit");
printCenter("");
printLine('=',W);
cout<<"\t\t\t\t\t\t\t\t"<<"Enter choice : ";
choice=getValidInt(0,4);

if(choice==1)
{
Customer c;

if(customerLogin(c)==1)
customerDashboard(c);
}

else if(choice==2)
customerRegister();

else if(choice==3)
{
Admin a;

if(adminLogin(a)==1)
adminDashboard(a);
}

else if(choice==4)
adminRegister();

else if(choice==0)
exitScreen();

else
{
cout<<endl<<"\t>> Invalid choice. Please try again."<<endl;
system("pause");
}
}
while(choice!=0);
}


//Program entry point
int main()
{
initializeFiles();
menu.loadFromFile("menu.txt");

if(menu.getCount()==0)
{
cout<<"\t\t\t\t\t\t\t\t"<<"Warning: menu.txt not found or empty. Please keep menu.txt in the same folder."<<endl;
system("pause");
}

orderQueue.loadFromFile("orders.txt");
restoreOrderCounter();

loadingScreen();
mainPage();

return 0;
}
