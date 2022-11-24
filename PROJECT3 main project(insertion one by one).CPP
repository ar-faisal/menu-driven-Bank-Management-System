#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<iomanip.h>

class PASSBOOK
 { int acno;
   int idate,imonth,iyear;
   char name[20];
   char address[25];
   char mobile_no[11];
   char aadhar_no[13];
   char accounttype[20];
   float balance;

   public:
   void getdata()
    { cout<<"\nAcc number:";
      cin>>acno;
      cout<<"Name:";
      gets(name);
      cout<<"Address:";
      gets(address);
      cout<<"Mobile number:";
      gets(mobile_no);
      cout<<"Aadhar number:";
      gets(aadhar_no);
      cout<<"Account type(current or saving):";
      gets(accounttype);
      do
	 { cout<<"Your ACCOUNT MUST HAVE MINIMUM BALANCE OF RS 500\n";
	   cout<<"Balance:";
	   cin>>balance;
	 } while(balance<500);
      cout<<"Date of account registry(d/m/yy):";
      cin>>idate>>imonth>>iyear;

    }

   void putdata()
    { cout<<"\n\t\t\tNATIONAL ABC BANK"<<endl;
      cout<<"\t\t\tKamla Nagar, Delhi-110007"<<endl;
      cout<<"\n\tDate of last transaction:"<<setw(21)<<idate<<"/"<<imonth<<"/"<<iyear;
      cout<<"\n\n\tAccount number:"<<setw(36)<<acno<<endl;
      cout<<"\n\tName:"<<setw(46)<<name<<endl;
      cout<<"\n\tAddress:"<<setw(43)<<address<<endl;
      cout<<"\n\tMobile number:"<<setw(37)<<mobile_no<<endl;
      cout<<"\n\tAadhar number:"<<setw(37)<<aadhar_no<<endl;
      cout<<"\n\tAccount type:"<<setw(38)<<accounttype<<endl;
      cout<<"\n\tBalance:"<<setw(43)<<balance<<endl;

    }

   void deposit(int amt){ balance+=amt;}
   void withdraw(int amt){ balance-=amt;}
   void date(int newdate){ idate=newdate;}
   void month(int newmonth){ imonth=newmonth;}
   void year(int newyear){ iyear=newyear;}
   float rbalance(){ return balance;}
   int racno(){ return acno;}

 };

void input()
 { clrscr();
   PASSBOOK bank,bank1;
   fstream fin,fout;
   fin.open("ACCOUNT.dat",ios::in|ios::binary);
   fout.open("temp.dat",ios::out|ios::binary);

   fin.read((char*)&bank,sizeof(bank));
   cout<<"Enter details of account whose record is to be inserted\n";
   bank1.getdata();
   while(!fin.eof())
	{ if(bank.racno()<=bank1.racno())
	    { fout.write((char*)&bank,sizeof(bank));
	      fin.read((char*)&bank,sizeof(bank));
	    }
	  else
	    { fout.write((char*)&bank1,sizeof(bank1));
	      fout.write((char*)&bank,sizeof(bank));
	      break;
	    }
	}

   if(!fin.eof())
     { while(fin.read((char*)&bank,sizeof(bank)))
	    { fout.write((char*)&bank,sizeof(bank));
	    }
     }
   else fout.write((char*)&bank1,sizeof(bank1));
   fin.close();
   fout.close();
   remove("ACCOUNT.dat");
   rename("temp.dat","ACCOUNT.dat");
   cout<<"Your account has been successfully registered\n";
 }

void display()
 { clrscr();
   int no,found=0;
   PASSBOOK a;
   fstream fin;
   fin.open("ACCOUNT.dat",ios::binary|ios::in);
   cout<<"Enter account no. whose details you want to display:";
   cin>>no;
   while(fin.read((char*)&a,sizeof(a)))
	{ if(a.racno()==no)
	    { a.putdata();
	      found++;
	    }
	}

   if(!found) cout<<"Such an account does not exist!!!\n";
   fin.close();

   getch();
 }

void displayAll()
 { clrscr();
   PASSBOOK a;
   fstream fin;
   fin.open("ACCOUNT.dat",ios::in|ios::binary);
   while(fin.read((char*)&a,sizeof(a)))
	{ a.putdata();
	  cout<<endl;
	}
   fin.close();

   getch();
 }

void transact()
 { clrscr();
   int no,found=0;
   PASSBOOK a;
   float amt;
   int newdate,newmonth,newyear;
   fstream fin;
   fin.open("ACCOUNT.dat",ios::binary|ios::in|ios::out);
   cout<<"Enter Acc no.:";cin>> no;
   while(found==0 && fin.read((char*)&a,sizeof(a)))
	{ if(a.racno()==no)
	  found++;
	}

   int x=fin.tellg();
   if(!found)cout<<"Such an account does not exist!!!";
   else
       {
	 char ch;
	 do
		     { cout<<"\n\n[W]:withdraw  [D]:deposit  [E]:exit:";cin>>ch;
		       ch=toupper(ch);
		       if(ch=='W')
			 {
			   cout<<"Enter amount to be withdrawn:";cin>>amt;
			   if(a.rbalance()>=(amt+500))
			     { a.withdraw(amt);
			       cout<<"enter the date of transaction(d/m/yy):";
			       cin>>newdate>>newmonth>>newyear;
			       a.date(newdate);
			       a.month(newmonth);
			       a.year(newyear);
			       cout<<"Withdraw SUCCESSFUL!\n";
			       cout<<"Net balance= RS. "<<a.rbalance();
			       cout<<"\nDate of last transaction:";
			       cout<<newdate<<"/"<<newmonth<<"/"<<newyear;
			     }

			   else
			     { cout<<"INSUFFICIENT BALANCE!!!\n";
			       cout<<"balance= RS. "<<a.rbalance();
			     }
			 }

		       else if(ch=='D')
			      {
				cout<<"enter the date of transaction(d/m/yy):";
				cin>>newdate>>newmonth>>newyear;
				a.date(newdate);
				a.month(newmonth);
				a.year(newyear);
				cout<<"enter amount to be deposited:";cin>>amt;
				a.deposit(amt);
				cout<<"Deposit SUCCESSFUL!\n";
				cout<<"Net balance= RS. "<<a.rbalance();
				cout<<"\nDate of last transaction:";
				cout<<newdate<<"/"<<newmonth<<"/"<<newyear;
			      }

		       if((ch=='W')||(ch=='D'))
			 { fin.seekp(x-sizeof(a));
			   fin.write((char*)&a,sizeof(a));
			 }
		     }while(ch!='E');


       }

   fin.close();
 }

void Delete()
 { clrscr();
   PASSBOOK a;
   ifstream fin("ACCOUNT.dat",ios::in|ios::binary);
   ofstream fout("temp.dat",ios::out|ios::binary);
   int accno;
   int flag=0;
   cout<<"Enter account number whose record is to be deleted\n";
   cin>>accno;
   while(fin.read((char*)&a,sizeof(a)))
	{ if(a.racno()==accno)
	   flag++;

	  else
	    fout.write((char*)&a,sizeof(a));
	}

   if(!flag)
   cout<<"Account number not found...\n";

   else
   cout<<"ACCOUNT DELETED!!!";
   fin.close();
   fout.close();
   remove("ACCOUNT.dat");
   rename("temp.dat","ACCOUNT.dat");
   getch();
 }

void modify()
 { clrscr();
   PASSBOOK a;
   fstream fio;
   int accno,found=0;
   cout<<"Enter account number to be modified:";
   cin>>accno;

   fio.open("ACCOUNT.dat",ios::in|ios::out|ios::binary);
   while(fio.read((char*)&a,sizeof(a)))
	{
	  if(a.racno()==accno)
	    { a.putdata();
	      cout<<"\nEnter the details of new account";
	      a.getdata();
	      int pos=-1*sizeof(a);
	      fio.seekp(pos,ios::cur);
	      fio.write((char*)&a,sizeof(a));
	      found++;
	    }
	}

   if(!found)
   cout<<"Account number not found!!!";
   fio.close();
 }



void main()
 { clrscr();
   int exit=1;
   while(exit)
      { clrscr();
	char ch;
	cout<<"\n\n\n\n\tMENU:"<<endl;
	cout<<"\n\n\t(A):register"<<endl;
	cout<<"\n\n\t(B):transact"<<endl;
	cout<<"\n\n\t(C):display"<<endl;
	cout<<"\n\n\t(D):display all"<<endl;
	cout<<"\n\n\t(E):modify"<<endl;
	cout<<"\n\n\t(F):delete"<<endl;
	cout<<"\n\n\t(Q):quit"<<endl;
	cin>>ch;
	ch=toupper(ch);
	switch(ch)
	      { case 'A':input();
		break;
		case 'B':transact();
		break;
		case 'C':display();
		break;
		case 'D':displayAll();
		break;
		case 'E':modify();
		break;
		case 'F':Delete();
		break;
		case 'Q':exit=0;
		break;
		default:
		cout<<"Entered option is invalid!!!\n";

	      }

	getch();
      }
 }
