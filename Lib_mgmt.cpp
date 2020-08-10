#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

class book                                               //class to accept book details
{
	char book_no[6];
	char book_name[50];
	char author_name[20];
  public:
	void create_book()                       //function to create book record
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter the book no.";
		cin>>book_no;
		cout<<"\nEnter the name of the book ";
		gets(book_name);
		cout<<"\nEnter the author's name ";
		gets(author_name);
		cout<<"\n\n\nBook Created...!!";
	}

	void show_book()                        //function to show a particular book
	{
		cout<<"\nBook no. : "<<book_no;
		cout<<"\nBook Name : ";
		puts(book_name);
		cout<<"Author Name : ";
		puts(author_name);
	}

	void modify_book()               //function to modify a book record
	{
		cout<<"\nBook no. : "<<book_no;
		cout<<"\nModify book name: ";
		gets(book_name);
		cout<<"\nModify author's name: ";
		gets(author_name);
	}

	char* retbno()                       //function to return book no.
	{
		return book_no;
	}

void report()                                //function to display data members of class book
{
cout<<book_no<<setw(30)<<book_name<<setw(30)<<author_name<<endl;
}


};

class student                         //class to accept student details
{
	char student_admno[6];
	char student_name[20];
	char student_bno[6];
	int no_book_issued;
public:
	void create_student()                     //function to create student record
	{
		clrscr();
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter the admission no. ";
		cin>>student_admno;
		cout<<"\n\nEnter the name of the student ";
		gets(student_name);
		no_book_issued=0;
		student_bno[0]='/0';
		cout<<"\n\nStudent record created..";
	}

	void show_student()                          //function to show specific student
	{
		cout<<"\nAdmission no. : "<<student_admno;
		cout<<"\nStudent Name : ";
		puts(student_name);
		cout<<"\nNo of Book issued : "<<no_book_issued;
		if(no_book_issued==1)
			cout<<"\nBook No "<<student_bno;
	}

	void modify_student()                          //function to modify student
	{
		cout<<"\nAdmission no. : "<<student_admno;
		cout<<"\nModify Student Name : ";
		gets(student_name);
	}

	char* retadmno()                                 //function to return adm no.
	{
		return  student_admno;
	}

	char* retstbno()                                 //function to return book no 
	{
		return student_bno;
	}

	int retno_book_issued()                     // function to return no. of book issued
	{
		return no_book_issued;
	}


	void addno_book_issued()                //function to assign no. of book issued
	{no_book_issued=1;}

	void resetno_book_issued()             //function to reset no. of book issued
	{no_book_issued=0;}

	void get_student_bno(char t[])                   //function to get student book no.
	{
		strcpy(student_bno,t);
	}

	void report()                                             
	{cout<<"\t"<<student_admno<<setw(20)<<student_name<<setw(10)<<no_book_issued<<endl;}

};

fstream f1,f2;                            //global declaration of objects
book bk;
student st;


void write_book()                            //function to write in file
{
	char ch;
	f1.open("books.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		f1.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more books in record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	f1.close();
}

void write_student()                          //function to write in file students
{
	char ch;
	f1.open("students.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		f1.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more student records..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	f1.close();
}



void show_book(char n[])                          
{
	cout<<"\nBOOK DETAILS\n";
	int m=0;
	f1.open("books.dat",ios::in);
	while(f1.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			m=1;
		}
	}

	f1.close();
	if(m==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void show_student(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int m=0;
	f1.open("students.dat",ios::in);
	while(f1.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			m=1;
		}
	}

	f1.close();
	if(m==0)
		cout<<"\n\nStudent does not exist";
	getch();
}




void modify_book()
{
	char a[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of the book to be modified";
	cin>>a;
	f1.open("books.dat",ios::in|ios::out);
	while(f1.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),a)==0)
		{
			bk.show_book();
			cout<<"\nEnter new details of the book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			f1.seekp(pos,ios::cur);
			f1.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	f1.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter the admission no. of the student";
	cin>>n;
	f1.open("students.dat",ios::in|ios::out);
	while(f1.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter new details of the student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			f1.seekp(pos,ios::cur);
			f1.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	f1.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}




void delete_student()                                 //function to delete student record
{
	char b[6];
	int a=0;
	clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter the admission no. of the student to be deleted: ";
	cin>>b;
	f1.open("students.dat",ios::in|ios::out);
	fstream f3;
	f3.open("Temp.dat",ios::out);
	f1.seekg(0,ios::beg);
	while(f1.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),b)!=0)
			f3.write((char*)&st,sizeof(student));
		else
			a=1;
	}

	f3.close();
	f1.close();
	remove("students.dat");
	rename("Temp.dat","students.dat");
	if(a==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


void delete_book()                              //function to delete book record
{
	char a[6];
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter the book no. of the book to be deleted : ";
	cin>>a;
	f1.open("books.dat",ios::in|ios::out);
	fstream f3;
	f3.open("Temp.dat",ios::out);
	f1.seekg(0,ios::beg);
	while(f1.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),a)!=0)
		{
			f3.write((char*)&bk,sizeof(book));
		}
	}

	f3.close();
	f1.close();
	remove("books.dat");
	rename("Temp.dat","books.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}





void show_all_students()                             //function to display student list
{
	clrscr();
	f1.open("students.dat",ios::in);
	if(!f1)
	{
		cout<<" FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	while(f1.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	f1.close();
	getch();
}


void show_all_books()                              //function to show book list
{
	clrscr();
	f1.open("books.dat",ios::in);
	if(!f1)
	{
		cout<<"FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tBOOK LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

	while(f1.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	f1.close();
	getch();
}


void issue_book()                                 //function for issuing book
{
	char stadm[6],bookno[6];
	int found=0,n=0;
	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter student's admission no.";
	cin>>stadm;
	f1.open("students.dat",ios::in|ios::out);
	f2.open("books.dat",ios::in|ios::out);
	while(f1.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),stadm)==0)
		{
			found=1;
			if(st.retno_book_issued()==0)
			{
				cout<<"\n\n\tEnter the book no. ";
				cin>>bookno;
				while(f2.read((char*)&bk,sizeof(book))&& n==0)
				{
					if(strcmpi(bk.retbno(),bookno)==0)
					{
						bk.show_book();
						n=1;
						st.addno_book_issued();
						st.get_student_bno(bk.retbno());
						int pos=-1*sizeof(st);
						f1.seekp(pos,ios::cur);
						f1.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued...";
						cout<<"\n\n\tPlease write the date of issuing the book on the book...";
						cout<<"\n\tYou have to return the book within 15 days.";
					}
				}
				if(n==0)
					cout<<"Book number does not exist";
			}
			else
				cout<<"You have not returned the last book...Please return it first!!! ";

		}
	}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	f1.close();
	f2.close();
}



void book_deposit()                                  //function for returning book
{
    char stadm[6],bookno[6];
    int found=0,n=0,day,fine;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter student's admission no.";
    cin>>stadm;
    f1.open("students.dat",ios::in|ios::out);
    f2.open("books.dat",ios::in|ios::out);
    while(f1.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),stadm)==0)
	    {
		    found=1;
		    if(st.retno_book_issued()==1)
		    {
			while(f2.read((char*)&bk,sizeof(book))&& n==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				n=1;
				cout<<"\n\nEnter the no. of days after which the book is being returned:";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*2;
				   cout<<"You are late in retuning the book by "<<(day-15)<<"           days.";
				   cout<<"\n\nFine to be deposited is Rs. "<<fine;
				}
					st.resetno_book_issued();
					int pos=-1*sizeof(st);
					f1.seekp(pos,ios::cur);
					f1.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully...!!!";
			}
		    }
		  if(n==0)
		    cout<<"Book number does not exist";
		      }
		 else
			cout<<"No such book is issued....!!!";
		}
	   }
      if(found==0)
	cout<<"Student record  does not exist...";
	getch();
  f1.close();
  f2.close();
  }

void intro()                               //function to display introduction of project
 {
   clrscr() ;
   gotoxy(31,5) ;
   cout <<"Welcome to the Project" ;
   gotoxy(33,7) ;
   cout<<" BOOK LIBRARY" ;
   gotoxy(15,10) ;
   cout <<"This  project has facility of maintaining  records" ;
   gotoxy(15,11) ;
   cout <<"of BOOKS and STUDENTS." ;
   gotoxy(15,13) ;
   cout << "One student can issue only one book at a time. If he/she";
   gotoxy(15,14) ;
   cout << "does  not return book within 15 days,he/she will have  to";
   gotoxy(15,15) ;
   cout << "pay fine of Rs.2/- per day till the returning of the book.";
   gotoxy(27,25) ;
   cout<<"Press any key to continue";
   getch();
}

void menu()                                     //function for administrator’s menu
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\t\t\t\tADMINISTRATOR MENU";
	cout<<" \n\t\t\t\t~~~~~~~~~~~~~~~~~~";
	cout<<"\n\n\t1.Create student record";
	cout<<"\n\t2.Show all students record";
	cout<<"\n\t3.Show specific student record ";
	cout<<"\n\t4.Modify student record";
	cout<<"\n\t5.Delete student record";
	cout<<"\n\t6.Create book record";
	cout<<"\n\t7.Show all books ";
	cout<<"\n\t8.Show specific book ";
	cout<<"\n\t9.Modify book ";
	cout<<"\n\t10.Delete book ";
	cout<<"\n\t11.Back to main menu";
	cout<<"\n\n\t Enter your choice: ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_student();break;
		case 2: show_all_students();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tEnter the admission No. ";
			cin>>num;
			show_book(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: show_all_books();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\tEnter the book No. ";
			cin>>num;
			show_book(num);
			break;
			}
		case 9: modify_book();break;
		case 10: delete_book();break;
		case 11: return;
		default:cout<<"wrong choice...try again";
	}
	menu();
}


void main()                                       
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tMAIN MENU";
cout<<" \n\t\t\t\t~~~~~~~~~";
		cout<<"\n\n\t1. Issue book";
		cout<<"\n\n\t2. Return book";
		cout<<"\n\n\t3. Administrator menu";
		cout<<"\n\n\t4. Exit";
		cout<<"\n\n\tEnter your choice:";
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();
				 issue_book();
				 break;
			case '2':book_deposit();
				 break;
			case '3':menu();
				 break;
			case '4':exit(0);
			default :cout<<"wrong choice..!!";
		}
	}while(ch!='4');
}                                     //end of main function


