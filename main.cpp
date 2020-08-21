#include<vector>
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>
#include<sstream>
#include<algorithm>
using namespace std;
//Width size is used for setting the width while writing in console as well as in file
int WIDTH_SIZE1 = 35;		//for title
int WIDTH_SIZE2 = 22;		//for Author........for type..its equal to WIDTH_SIZE2/2
int WIDTH_SIZE3 = 4;		//for year and number of pages/// ....num of pages  = WIDTH_SIZE3+2
int TOTAL_WIDTH_SIZE = WIDTH_SIZE1 + WIDTH_SIZE2 + (WIDTH_SIZE2/2) + WIDTH_SIZE3*2 +2;

void check_Numeric(int &flag, int min, int max)
{
	string line;
	while(getline(cin, line)) 
	{
		stringstream ss(line);
		if(ss >> flag)
			if(ss.eof() && (flag>=min && flag<=max))
				break;
		cout<<"Invalid Input! "<<endl;
	}
}
void check_string_input(string &line)
{
	while(getline(cin, line))
	{
		if(line.find(' ', 0) == -1)
			break;
		cout<<"Invalid Input! "<<endl;
	}
}

class Book 
{
	int date_pub, num_pages;		//date of publication
	string title, author, type;		//information of title and author
public:
	//constructors and destructors:
	Book();
	Book(const int &,const int &,const string &,const string &, const string &);
	Book(const Book &b);
	~Book();
	//input and output:
	friend istream& operator>>(istream &in,Book &b);
	friend ostream& operator<<(ostream &out,const Book &b);
	// getters and setters :
	string getTitle() const;
	string getAuthor() const;
	string getType() const;
	int getDate_publication() const;
	int getPages() const;

	void setTitle(const string &);
	void setAuthor(const string &);
	void setDate(const int &);
	void setPages(const int &);
	void setType(const string &);
	//assignment operator:
	Book& operator=(const Book&);
};
//default constructor
Book::Book() 
{
	title = "";
	author = "";
	date_pub = 0;
}
//non-default constructors
Book::Book(const int &date_pub,const int &pages, const string &title,const string &author, const string &type)
{
	this->date_pub = date_pub;
	this->title = title;
	this->author = author;
	this->type = type;
	this->num_pages = pages;
}
Book::Book(const Book &b) 
{
	this->date_pub = b.getDate_publication();
	this->title = b.getTitle();
	this->author = b.getAuthor();
	this->num_pages = b.getPages();
	this->type = b.getType();
}
Book::~Book() 
{
}
//setters
void Book::setAuthor(const string &str) 
{
	author = str;
}
void Book::setTitle(const string &str)
{
	title = str;
}
void Book::setDate(const int &date)
{
	date_pub = date;
}
void Book::setPages(const int &pages) 
{
	num_pages = pages;
}
void Book::setType(const string &str)
{
	type = str;
}
//getters
string Book::getAuthor() const 
{
	return this->author;
}
int Book::getDate_publication() const 
{
	return this->date_pub;
}
string Book::getTitle() const
{
	return this->title;
}
string Book::getType() const
{
	return this->type;
}
int Book::getPages() const
{
	return num_pages;
}
// input operator and output operators
istream& operator>>(istream &in, Book &b)
{
	int temp;
	string str;
	int count=0;


	cout<<"Enter Date of Publication: ";
    while (getline(in, str)) 
	{
        stringstream ss(str);
        if (ss >> temp)
		{
            if (ss.eof())
			{   // Successful integer
                break;
            }
        }
        if(count>=1) 
		{
        	cout << "Please enter a valid input: " << endl;
        }
        count++;
    }
	b.setDate(temp);


	str.clear();
	cout<<endl<<"Enter number of pages of the book: "<<endl;
	while(getline(in,str))
	{
		stringstream ss(str);
		if(ss >> temp)
			if(ss.eof())
				break;

		cout<<"Please enter a valid input! "<<endl;
	}
	b.setPages(temp);

	str.clear();
	cout<<endl<<"Enter the Title: ";
	while(getline(in,str)) 
	{
		if(str.find(' ', 0) == -1)
			break;
		cout<<"Please enter a valid title!"<<endl;
	}
	b.setTitle(str);


	str.clear();
	cout<<endl<<"Enter the Author's name: ";
	while(getline(in, str))
	{
		if(str.find(' ', 0) == -1)
			break;
		cout<<"Please enter a valid author!"<<endl;
	}
	b.setAuthor(str);


	str.clear();
	cout<<endl<<"Enter the type of book(softcover, hardcover or digital..)";
	while(getline(in, str)) 
	{
		if(str.find(' ', 0) == -1)
			break;
		cout<<"Please enter a valid type!"<<endl;
	}
	b.setType(str);

	return in;
}
ostream& operator<<(ostream &out,const Book &b)
{
		out<<left<<setw(WIDTH_SIZE1)<<b.getTitle();
		out<<" "<<left<<setw(WIDTH_SIZE2)<<b.getAuthor();
		out<<" "<<left<<setw(WIDTH_SIZE3)<<b.getDate_publication();
		out<<" "<<left<<setw(WIDTH_SIZE2/2)<<b.getType();
		out<<" "<<left<<setw(WIDTH_SIZE3+2)<<b.getPages();
		return out;
}
//assignment operator
Book& Book::operator=(const Book &b) 
{
	this->~Book();
	this->setTitle(b.getTitle());
	this->setAuthor(b.getAuthor());
	this->setPages(b.getPages());
	this->setDate(b.getDate_publication());
	this->setType(b.getType());

	return *this;
}

bool comp_Title(const Book b1,const Book b2) 
{
	return (b1.getTitle() <b2.getTitle());
}

bool comp_Author(const Book b1,const Book b2)
{
	return (b1.getAuthor() < b2.getAuthor());
}

bool comp_Date(const Book b1,const Book b2)
{
	return (b1.getDate_publication() < b2.getDate_publication());
}

bool comp_Type(const Book b1,const Book b2)
{
	return (b1.getType() < b2.getType());
}

bool comp_Pages(const Book b1,const Book b2) 
{
	return (b1.getPages() < b2.getPages());
}


class Database 
{
	vector<Book> list;
public:
	Database() {}
	Database(const Database &);
	~Database();
	void read_files(ifstream &);
	void print_files(ofstream &);
	int getSize() const;
	void addNewBook();
	Book operator[](const int& ) const;
	void delete_book(const int &);
	bool update(const int &);
	bool Advanced_Search(vector<int> &) const;
	void mySort(vector<int> &) const;
	friend ostream &operator<<(ostream &out, const Database &);
};

//non-default database constructor 
Database::Database(const Database &db)
{
	if(list.size()>0)
		this->~Database();
	for(int i=0;i<db.getSize();i++) 
	{
		this->list.push_back(db.list[i]);
	}
}
//destructor
Database::~Database() 
{
	this->list.clear();
}

bool Database::update(const int &index)
{
	/*
	pre-condition: input for this function = position of the book in our database that needs to be update.
	post-condition: output = true if the user successfully updates otherwise false.
	*/
	int temp;
	string str;
	cout<<"Enter what do you wanna update? "<<endl;
	cout<<"	1.Title"<<endl;
	cout<<"	2.Author"<<endl;
	cout<<"	3.Date of publication"<<endl;
	cout<<"	4.Number of Pages"<<endl;
	cout<<"	5.Type of cover"<<endl;
	cout<<" 6.Cancel "<<endl;
	check_Numeric(temp, 1, 6);
	switch(temp)
	{
		case 1:
			cout<<"Enter new Title:"<<endl;
			check_string_input(str);
			this->list[index].setTitle(str);
			return 0;
			break;
		case 2:
			cout<<"Enter new Author:"<<endl;
			check_string_input(str);
			this->list[index].setAuthor(str);
			return 0;
			break;

		case 4:
			cout<<"Enter new number of pages:"<<endl;
			check_Numeric(temp, 0, 32000);
			this->list[index].setPages(temp);
			return 0;
			break;
		case 5:
			cout<<"Enter new type:"<<endl;
			check_string_input(str);
			this->list[index].setType(str);
			return 0;
			break;
		case 6:
			return false;

        return false;
	}
}

void Database::mySort(vector<int> &positions) const 
{
	int temp;
	vector<Book> record;
	for(int i = 0;i<positions.size();i++)
		record.push_back(this->list[positions[i]]);
	cout<<"1. Sort by Title "<<endl;
	cout<<"2. Sort by Author"<<endl;
	cout<<"3. Sort by Year"<<endl;
	cout<<"4. Sort by number of pages: "<<endl;
	cout<<"5. Sort by type: "<<endl;
	cout<<"6. Back."<<endl;
	check_Numeric(temp,1,6);

	switch(temp)
	{
		case 1:
			sort(record.begin(), record.end(), comp_Title);
			break;

		case 2:
			sort(record.begin(), record.end(), comp_Author);
			break;

		case 3:
			sort(record.begin(), record.end(),comp_Date);
			break;

		case 4:
			sort(record.begin(), record.end(), comp_Pages);
			break;

		case 5:
			sort(record.begin(), record.end(), comp_Type);
			break;

		case 6:
			return;
	}   
	for(int i=0;i<record.size();i++)
        cout<<record[i]<<endl;
	return;
}
void Database::delete_book(const int& index) 
{
	this->list.erase(this->list.begin()+index);
}
void Database::read_files(ifstream& fin)
{
	string temp = "";
	char ch = '\0';
	int n=0;
	Book b1;
	while(fin.eof()==false) {
		fin>>temp;
		b1.setTitle(temp);

		temp.clear();
		fin>>ws>>temp;
		b1.setAuthor(temp);

		temp.clear();
		fin>>ws>>n;
		b1.setDate(n);

		fin>>ws; fin>>temp;
		b1.setType(temp);

		fin>>ws; fin>>n;
		b1.setPages(n);

		this->list.push_back(b1);
		temp.clear();
	}
}
void Database::print_files(ofstream &fout) /*this function saves the database*/ 
{
	//printing now:
	for(int i=0;i<this->getSize();i++) 
	{
		fout<<left<<setw(WIDTH_SIZE1)<<this->list[i].getTitle();
		fout<<" "<<left<<setw(WIDTH_SIZE2)<<this->list[i].getAuthor();
		fout<<" "<<left<<setw(WIDTH_SIZE3)<<this->list[i].getDate_publication();
		fout<<" "<<left<<setw(WIDTH_SIZE2/2)<<this->list[i].getType();
		fout<<" "<<left<<setw(WIDTH_SIZE3+2)<<this->list[i].getPages()<<endl;
	}
}

Book Database::operator[](const int& index)const 
{
	return this->list[index];
}
int Database::getSize() const 
{
	return this->list.size();
}

ostream& operator<<(ostream &out, const Database &db) 
{   
	for(int i=0;i<db.getSize();i++) 
	{
		cout<<db.list[i];
		cout<<endl;
	}
	return out;
}

void Database::addNewBook() /* this function represents 1st case that is adding new book to the database */ 
{
	cout<<"Use underscores( _ ) instead of spaces "<<endl;
	Book b1;
	cout<<"Enter the info about the new book below....  "<<endl;
	cin>>b1;
	system("cls");
	cout<<"Adding the book: "<<endl;
	cout<<b1<<endl;
	cout<<"Book added Successfully!"<<endl;
	this->list.push_back(b1);
}

bool Title_or_Author()
{
	int temp;
	cout<<"Do you want to search with: "<<endl;
	cout<<"1. Title. "<<endl;
	cout<<"2. Author. "<<endl;
	check_Numeric(temp,1,2);
	switch(temp)	
	{
		case 1:
			return 1;
		case 2:
			return 0;
		default:
			cout<<"Please Enter a valid input. "<<endl;
			return Title_or_Author();
	}
	return 0;
}
bool year_or_pages()
{
	int temp;
	cout<<"Do you want to search with: "<<endl;
	cout<<"1. Year. "<<endl;
	cout<<"2. Pages. "<<endl;
	check_Numeric(temp,1,2);
	switch(temp)	
	{
		case 1:
			return 1;
		case 2:
			return 0;
		default:
			cout<<"Please Enter a valid input. "<<endl;
			return year_or_pages();
	}
	return 0;
}
bool Database::Advanced_Search(vector<int> &positions) const
{
	//positions in the list from previous search;
	int temp;
	int min, max;
	vector<int> current_search_positions;
	string str1, str2;
	cout<<"Please choose an option: "<<endl;
	cout<<"1. AND Search "<<endl;
	cout<<"2. OR Search "<<endl;
	cout<<"3. NOT Search "<<endl;
	cout<<"4. In Between "<<endl;
	cout<<"5. Back to Main menu"<<endl;
	check_Numeric(temp,1,5);
	switch(temp){
		case 1:
			cout<<"Enter 1st string to search: ";
			check_string_input(str1);
			cout<<endl<<"Enter 2nd string for search: "<<endl;
			check_string_input(str2);
			if(Title_or_Author() == 1)
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getTitle().find(str1,0) != -1 && this->list[positions[i]].getTitle().find(str2,0) != -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}

				}
			else
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getAuthor().find(str1,0) != -1 && this->list[positions[i]].getAuthor().find(str2,0) != -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}

			break;
		case 2:
			cout<<"Enter 1st string to search: ";
			check_string_input(str1);
			cout<<endl<<"Enter 2nd string for search: "<<endl;
			check_string_input(str2);

			if(Title_or_Author() == 1)
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getTitle().find(str1,0) != -1 || this->list[positions[i]].getTitle().find(str2,0) != -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			else
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getAuthor().find(str1,0) != -1 || this->list[positions[i]].getAuthor().find(str2,0) != -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			break;
		case 3:
			cout<<"Enter the string 'NOT' to search: ";
			check_string_input(str1);
			if(Title_or_Author() == 1)
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getTitle().find(str1,0) == -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			else
				for(int i=0;i<positions.size();i++) {
					if(this->list[positions[i]].getAuthor().find(str1,0) == -1 ) {
						cout<<this->list[i]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			break;
		case 4:
			system("cls");
			do 
			{
				cout<<"Enter minimum Range for search : "<<endl;
				check_Numeric(min, 0, 32000);
				cout<<"Enter maximum Range for search: "<<endl;
				check_Numeric(max,0, 32000);
				if(min>=max) 
				{
					cout<<"cannot perform search with maximum less than minimum"<<endl;
					cout<<"Please input again"<<endl;
				}
				else
					break;
 			}	while(true);
			if(year_or_pages() == 1)
				for(int i = 0;i< positions.size(); i++) 
				{
					if(this->list[positions[i]].getDate_publication() >= min && this->list[positions[i]].getDate_publication() <= max) 
					{
						cout<<this->list[positions[i]]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			else
				for(int i = 0;i< positions.size(); i++) 
				{
					if(this->list[positions[i]].getPages() >= min && this->list[positions[i]].getPages() <= max) 
					{
						cout<<this->list[positions[i]]<<endl;
						current_search_positions.push_back(positions[i]);
					}
				}
			break;
		case 5:
			return 0;
	}
	//copying current search positions in the vector<positions> // passed by reference for recursion
	positions.clear();
	positions = current_search_positions;

	cout<<endl<<endl<<"1. Do you want to add more filters to this search? "<<endl;
	cout<<"2. Do you want to sort this search? "<<endl;
	cout<<"3. Back to main menu. "<<endl;
	check_Numeric(temp,1,3);
	switch(temp) 
	{
		case 1:
			return true;
		case 2:
			mySort(positions);
			break;
		case 3:
			return false; 
	}
	return 0;
}

int Search(const Database &db1,const int &flag) 
{

	/* this functions represents 2nd,3rd,4th case 
	
	pre-condition: we will get the database and a flag,
					if flag=0 we will search the database 
					or if flag = 1 or 2 we will first search and
					then update or delete the required book in the database.
	
	post-condition: it will return -1 for restarting this function,
					it will return -2 for closing this function as well as the task of updating or deleting is unsuccessful.
	*/
	int temp, temp2 ,check=0;
	bool signal = true;
	int k=1, input_options=2;
	vector<int> arr;	// array for integers
	cout<<"NOTE: 1. Use underscores( _ ) instead of spaces "<<endl;
	cout<<"      2. All the search results are in the format (Title,Author,year,format,page number)"<<endl;
	cout<<"How do you want to search your book?"<<endl;
	cout<<" 1. Search all books published in a certain year."<<endl;
	if(flag==0) 
	{
		cout<<" 2. Advanced Search."<<endl;
		input_options++;
	}

	cout<<" "<<input_options<<". Back"<<endl;
	check_Numeric(temp,1,input_options);
	if(flag!=0 && temp == 2)
		temp=3;
	switch(temp)
	{
		case 1:
			cout<<"Enter the year you want to search for the book."<<endl;
			check_Numeric(temp,0,32000);
			cout<<"   Title				Author                 Year Format  Page-NUMBER"<<endl; 
			for(int i=0;i<db1.getSize();i++) 
			{
				if(db1[i].getDate_publication() == temp)
				{
					cout<<left<<setw(WIDTH_SIZE3)<<k<<db1[i]<<endl;
					arr.push_back(i);
					signal = false;
					k++;
				}
			}
			cout<<endl<<"Do you want to sort this search? (enter 1 for yes any other number for no)"<<endl;
			check_Numeric(temp2,0,INT_MAX);
			if(temp2==1)
				db1.mySort(arr);

			if(signal==true)
			{
				cout<<"Sorry no books found with year "<<temp<<endl;
			}
			//for deleting and updating:
			if(flag>=1 && signal==false) 
			{
				if(flag==1)
					cout<<endl<<"Enter which position of the book from the above list you want to delete: "<<endl;
				else if(flag==2)
					cout<<endl<<"Enter the position of the book from the above you want to update: "<<endl;

				check_Numeric(temp2, 1,arr.size());
				return arr[temp2-1];
			}
			system("pause");
			break;

		case 2:
			for(int i=0;i<db1.getSize();i++)  
			{
				arr.push_back(i);
			}
			while(true) 
			{
				if(db1.Advanced_Search(arr) == false)
					break;
			}
			return -2;
			system("pause");
			break;

		case 3:
			return -2;

		default:
			cout<<"Option not valid, please choose from the given options"<<endl;
			return -1;
	}
	system("cls");
	cout<<endl<<"Do you want to try again?"<<endl<<"enter 1 for yes, Otherwise enter any-other number: ";
	check_Numeric(check,1,INT_MAX);
	if(check==1)
	{
		return -1;	// for restarting this function could be implemented by recursion as well
	}
	else
	{
		return -2;	// opposite of that, returning to main menu
	}
}

bool startMenu(Database &db)
{
		int i=0, pos=0;
		int check = 0;
		Book b1;
		string temp;
		ifstream fin;
		ofstream fout;
		system("cls");

		cout<<"Welcome to the book records database application. What would you like to do?"<<endl;
		cout<<"		1. Add a new book record to the database.		"<<endl;
		cout<<"		2. Delete an existing record from the database.	"<<endl;
		cout<<"		3. Update any information of an existing book record in the database.		"<<endl;
		cout<<"		4. Search for a book or book records in database.		"<<endl;
		cout<<"		5. Load database from a file							"<<endl;
		cout<<"		6. Save the database to a file "<<endl;
		cout<<"		7. Exit Application"<<endl;
		cout<<"Enter your choice please: "<<endl;
		check_Numeric(i,1,7);

	switch(i) 
	{
		case 1:
			system("cls");
			db.addNewBook();
			break;
		case 2:
			system("cls");
			cout<<"Search an item for deleting: "<<endl;
			while(true) 
			{
				pos = Search(db,1);
				if(pos == -2) 
				{
					cout<<"Book deleting failed!!"<<endl;
					return true;
				}
				else if(pos==-1)
					system("cls");
				else
				{
					cout<<"Deleting this item: "<<endl<<db.operator[](pos)<<endl;
					db.delete_book(pos);
					//Print_on_file(b1, fin_out, pos);
					cout<<"Item deleted successfully!"<<endl;
					break;
				}
			}
			break;
		case 3:
			system("cls");
			cout<<"Search the book for updating: "<<endl;
			while(true)
			{
				pos = Search(db,2);
				if(pos == -2)
				{
					cout<<"Book updating failed!!"<<endl;
					return true;
				}
				else if(pos==-1)
					system("cls");
				else 
				{
					system("cls");
					cout<<"Updating this book: "<<db.operator[](pos).getTitle()<<endl;
					system("pause");
					if(db.update(pos) == false)
						return true;
					else
						cout<<"Book updated successfully!"<<endl;

					break;
				}
			}
			break;
		case 4:
			system("cls");
			pos=0;
			while(true)
			{
				pos = Search(db, 0);
				if(pos == -2)
					return true;
				else if(pos==-1)
					continue;
				else
					break;
			}

			break;
		case 5:
			system("cls");
			cout<<"Reading from the file: "<<endl;
			fin.open("MyDataBase.txt");

			if(fin.fail()==true) 
			{
				cerr<<"file opened incorrectly!"<<endl;
				system("pause");
				return true;
			}
			db.read_files(fin);
			fin.close();

			cout<<"File loading Successful"<<endl;
			break;
		case 6:
			system("cls");
			cout<<"writing to the file: "<<endl;
			fout.open("MyDataBase.txt");
			if(fout.fail() == true)
			{
				cerr<<"File loading unsuccessful!"<<endl;
				system("pause");
				return true;
			}
			db.print_files(fout);
			fout.close();

			cout<<"File writing successful"<<endl;
			break;
		case 7:
			system("cls");
			//db1.~Database();
			//return false;
			cout<<"NOTE: The data is in format (Title,Author,Year,Format,Page number)"<<endl;
			cout<<db;
			break;
		default:
			cout<<"Option not valid, please choose from the given options";
	}
	cout<<endl<<endl<<"Do you want to revert to Main menu?"<<endl<<"Enter 1 for yes, Else enter any other number :";
	check_Numeric(check, 1, INT_MAX);

	if(check==1)
		return true;
	else
		return false;
}

int main() 
{
	Database db1;
	// we are using while loop to use startMenu function it will break when user give command to close the application.
	while(true)
	{
		bool flag = startMenu(db1);
		if(flag==false)
		{
			break;
		}
	}
	system("cls");
	cout<<"Thanks for using this library";
	cout<<endl<<"Have a good day"<<endl;
	system("pause");

	return 0;
}
