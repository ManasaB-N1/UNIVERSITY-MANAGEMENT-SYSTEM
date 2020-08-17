//university.cpp
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class university
{
public: char name[15],Usn[15],age[10],Sem[10],Branch[15];
public: char Cname[15],Cid[5],location[15],Course[15];
public: char COURSE[10],CID[5],sdate[5],edate[5],smonth[10],emonth[10],syear[5],eyear[5];
public: char sname[10],usn[5],course[10],branch[10],sem[10],theory1[12],theory2[12],theory3[12],theory4[12],theory5[12],theory6[12],lab1[12],lab2[12];
}unirec[500],found[100];
char uni_no[50],rt_name[50];
char findex[100][90];

//student.cpp
int studentget_num_records()
{
		fstream file;
		int i=0;
			file.open("studentrecord.txt",ios::in);
		if(!file)
			{
				return 0;	
			}
			while(!file.eof())
			{	
	  			file.getline(findex[i],5,'|');
  				file.getline(unirec[i].Usn,15,'|');
  				file.getline(unirec[i].name,15,'|');
  				file.getline(unirec[i].age,10,'|');
  				file.getline(unirec[i].Sem,10,'|');
  				file.getline(unirec[i].Branch,15,'\n'); 
 				i++;
			}
		i--;	
	file.close();
	return i;
}

void studentretrieve_record(char* ind)
{
	 int i,no;
	 no=studentget_num_records();	
	 for(i=0;i<no;i++)
	 {	
  			if(strcmp(ind,findex[i])==0)
			{
   				cout<<"USN   : "<<unirec[i].Usn<<"\nNAME   : "<<unirec[i].name<<"\nAGE   : "<<unirec[i].age<<"\nSEM   :"<<unirec[i].Sem<<"\nBRANCH   :"<<unirec[i].Branch<<endl;
			}
 	}
	 return;
}

void studentsearch_records()
{
 	int k=0,i,no;
	char name[15],Usn[5],ind[5],chUsn[5],resind[5][20];
	fstream file;
		 file.open("studentsecindex.txt",ios::in);
 		cout<<"Please enter the name of the student whose record is to be displayed\n";
		 cin>>rt_name;
		 while(!file.eof())
		 {
  				file.getline(name,15,'|');
				file.getline(Usn,5,'|');
				file.getline(ind,5,'\n');
		 if(strcmp(name,rt_name)==0)
  				{
  					strcpy(found[k].name,name);
   					strcpy(found[k].Usn,Usn);
   					strcpy(resind[k],ind);
   					k++;  
  				}
		 }
		 file.close();
	if(k==1)
 	{
		  studentretrieve_record(resind[0]);
		  return;
 	}
	 else
	 {
 		 cout<<"Please choose the candidate's USN : \n";
 		 for(i=0;i<k;i++)
   			cout<<"Name : "<<found[i].name<<"  USN  : "<<found[i].Usn<<endl;
 	}
	 cin>>chUsn;
 	for(i=0;i<k;i++)
	 {
  			if(strcmp(chUsn,found[i].Usn)==0)
  			{
   					studentretrieve_record(resind[i]);
					 return;
  			}
 	}
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void studentdelete_record(char indx[])
{
	 int i,no,flag;
 	fstream file1,file2;

		no=studentget_num_records();
 		flag=-1;
 		for(i=0;i<no;i++)
 		{
  					if(strcmp(findex[i],indx)==0)
   					flag=i;
 		}
 		if(flag==-1)
 		{
  				cout<<"Error !\n";
  				return;
}
		if(flag==(no-1))
 		{
  				no--;
  				cout<<"Deleted !\n";
 		} 
		else
		{
 				for(i=flag;i<no;i++)
 				{
  						unirec[i]=unirec[i+1];
 				}
 				no--;
 				cout<<"Deleted !\n";
		}
		file1.open("studentsecindex.txt",ios::out);
 		file2.open("studentrecord.txt",ios::out);
 		for(i=0;i<no;i++)
 		{
  		file1<<unirec[i].name<<"|"<<unirec[i].Usn<<"|"<<i<<"\n";
file2<<i<<"|"<<unirec[i].Usn<<"|"<<unirec[i].name<<"|"<<unirec[i].age<<"|"<<unirec[i].Sem<<"|"<<unirec[i].Branch<<"\n";
 		}
		file2.close();
 		file1.close();
 		return;    
}

void studentremove_record()
{
 	fstream file;
	 int i,k=0,no;
	 char name[15],Usn[15],ind[5],chUsn[5],resind[20][5],st_name[15];
		cout<<"Please enter the name of the student whose record is to be deleted\n";
   		cin>>st_name;
		 file.open("studentsecindex.txt",ios::in);
		 while(! file.eof())
 		{
			  file.getline(name,15,'|');
			  file.getline(Usn,15,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(st_name,name)==0)
  			  {
		   			strcpy(found[k].name,name);
		  		 	strcpy(found[k].Usn,Usn);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		studentdelete_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the candidate's USN : \n";
 		for(i=0;i<k;i++)
   		cout<<"Name : "<<found[i].name<<"  USN  : "<<found[i].Usn<<endl;
	 }
	 cin>>chUsn;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chUsn,found[i].Usn)==0)
  			{
   				studentdelete_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void studentsort_records(int no)
{
	 int i,j;
	 university  temp;
		for(i=0;i<no-1;i++)
		{
	  		for(j=0;j<no-i-1;j++)
			{
   				if(strcmp(unirec[j].name,unirec[j+1].name)>0)
   				{
    						temp=unirec[j];
    						unirec[j]=unirec[j+1];
    						unirec[j+1]=temp;
   				}
	 		}
		}		
}

void studentcreate_indexfile(int no)
{
 	fstream file1,file2;
 	int i;
 			file1.open("studentsecindex.txt",ios::out);
 			file2.open("studentrecord.txt",ios::out);
for(i=0;i<no;i++)
		{
		file1<<unirec[i].name<<"|"<<unirec[i].Usn<<"|"<<i<<"\n"; file2<<i<<"|"<<unirec[i].Usn<<"|"<<unirec[i].name<<"|"<<unirec[i].age<<"|"<<unirec[i].Sem<<"|"<<unirec[i].Branch<<"\n";
 	}
	file1.close();
	file2.close();
}

void studentadd_records()
{	
 	int i,j,k,cnt,no;
	fstream file;
	char name[15],Usn[15],ind[5];
	char line[50],line1[50];
	cout<<"\nEnter the no. of students : ";
	cin>>no;
	cout<<"\nEnter the details :\n"; 
	cnt =studentget_num_records();
	for(i=cnt;i<(cnt+no);i++)
   	{                  
		cout<<"\nNAME : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].name,line);
cout<<unirec[i].name;

		cout<<"\nAGE      : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].age,line);
cout<<unirec[i].age;

		cout<<"\nUSN      : ";
		 cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='A' && line[k]<='Z') &&  !(line[k]>='0' && line[k]<='9')  && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
file.open("studentsecindex.txt",ios::in);
 while(! file.eof())
 		{
			  file.getline(name,15,'|');
			  file.getline(Usn,15,'|');
			  file.getline(ind,5,'\n');
		if(strcmp(Usn,line)==0)
		{
		cout<<"this usn already exists\n";
		cout<<"enter usn again\n";
		cout<<"\nUSN      : ";
		cin>>line1;
	for(int k=0,j;line1[k]!='\0';++k)
	{
	while(!(line1[k]>='A' && line1[k]<='Z') &&  !(line1[k]>='0' && line1[k]<='9')  && !(line1[k]=='\0')){
	for(j=k;line1[j]!='\0';++j){
	line1[j]=line1[j+1];
	}
	line1[j]='\0';
	}
	}
	strcpy(unirec[i].Usn,line1);
	cout<<unirec[i].Usn;
		break;
		return;
		}
		else
		{
		strcpy(unirec[i].Usn,line);
		cout<<unirec[i].Usn;
		}
	}
	file.close();




		cout<<"\nSEMESTER : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9')  && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].Sem,line);
cout<<unirec[i].Sem;


		cout<<"\nBRANCH   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].Branch,line);
cout<<unirec[i].Branch;

	}
		studentsort_records((cnt+no));
  	 	studentcreate_indexfile((cnt+no));
}

void studentdisplay_records()
{
	university s;
	fstream file;
	int i=0;
		file.open("studentrecord.txt",ios::in);
		if(!file)
		{	
				cout<<"Error\n";
				return;	
		}
cout<<"                      S T U D E N T     D I S P L A Y     L I S T                                 \n";
cout<<"************************************************************************************************************************************************************************************************************";
		cout<<"\nUSN\t\tName\t\tAge\t\tSem\t\tBranch\n";  
cout<<"************************************************************************************************************************************************************************************************************\n";

		while(!file.eof())
		{	
	  			file.getline(findex[i],5,'|');
                                file.getline(s.Usn,15,'|');
  				file.getline(s.name,15,'|');
  				file.getline(s.age,10,'|');
  				file.getline(s.Sem,10,'|');
  				file.getline(s.Branch,15,'\n'); 
	cout<<s.Usn<<"\t\t"<<s.name<<"\t\t"<<s.age<<"\t\t"<<s.Sem<<"\t\t"<<s.Branch<<"\t\t"<<endl;
 		}
	file.close();
	return;
}
void studentmodify_record(char indx[])
{
		
		char name[15],Usn[15],age[10],Sem[10],Branch[15];
		int i,no;
		no=studentget_num_records();
		for(i=0;i<no;i++)
		{
			if(strcmp(indx,findex[i])==0)

  			{
				cout<<"\nThe old values of the records are "; 
				cout<<"\nNAME   = "<<unirec[i].name;
				cout<<"\nUSN    = "<<unirec[i].Usn;
				cout<<"\nAGE    = "<<unirec[i].age;
				cout<<"\nSEM    = "<<unirec[i].Sem;
				cout<<"\nBRANCH = "<<unirec[i].Branch<<endl;
				cout<<"\nEnter the new values \n";
				cout<<"\nNAME   = ";  cin>>unirec[i].name;
				cout<<"\nUSN    = ";  cin>>unirec[i].Usn;
				cout<<"\nAGE    = ";  cin>>unirec[i].age;
				cout<<"\nSEM    = ";  cin>>unirec[i].Sem;
				cout<<"\nBRANCH = ";  cin>>unirec[i].Branch;
				break;

  			}
 		}
studentsort_records((no));
studentcreate_indexfile((no));
return;
}
		

void studentmodify_records()
{
fstream file;
	 int i,k=0,no;
	 char name[15],Usn[15],ind[5],chUsn[5],resind[20][5],st_name[15];
		cout<<"Please enter the name of the student whose record is to be modified\n";
   		cin>>st_name;
		 file.open("studentsecindex.txt",ios::in);
		 while(!file.eof())
 		{
			  file.getline(name,15,'|');
			  file.getline(Usn,15,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(st_name,name)==0)
  			  {
		   			strcpy(found[k].name,name);
		  		 	strcpy(found[k].Usn,Usn);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		studentmodify_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the candidate's USN : \n";
 		for(i=0;i<k;i++)
   		cout<<"Name : "<<found[i].name<<"  USN  : "<<found[i].usn<<endl;
	 }
	 cin>>chUsn;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chUsn,found[i].Usn)==0)
  			{
   				studentmodify_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}


//college.cpp


int collegeget_num_records()
{
		fstream file;
		int i=0;
			file.open("collegerecord.txt",ios::in);
		if(!file)
			{
				return 0;	
			}
			while(!file.eof())
			{	
	  			file.getline(findex[i],5,'|');
  				file.getline(unirec[i].Cid,5,'|');
  				file.getline(unirec[i].Cname,15,'|');
  				file.getline(unirec[i].location,15,'|');
  				file.getline(unirec[i].Course,15,'\n'); 
 				i++;
			}
		i--;	
	file.close();
	return i;
}

void collegeretrieve_record(char* ind)
{
	 int i,no;
	 no=collegeget_num_records();	
	 for(i=0;i<no;i++)
	 {	
  			if(strcmp(ind,findex[i])==0)
			{
   				cout<<"cid       : "<<unirec[i].Cid<<"\ncname     : "<<unirec[i].Cname<<"\nlocation  : "<<unirec[i].location<<"\ncourse    :"<<unirec[i].Course<<endl;
			}
 	}
	 return;
}

void collegesearch_records()
{
 	int k=0,i,no;
	char Cname[15],Cid[5],ind[5],chid[5],resind[5][20];
	fstream file;
		 file.open("collegesecindex.txt",ios::in);
 		cout<<"Please enter the name of the college whose record is to be displayed\n";
		 cin>>rt_name;
		 while(!file.eof())
		 {
  				file.getline(Cname,15,'|');
				file.getline(Cid,5,'|');
				file.getline(ind,5,'\n');
		 if(strcmp(Cname,rt_name)==0)
  				{
  					strcpy(found[k].Cname,Cname);
   					strcpy(found[k].Cid,Cid);
   					strcpy(resind[k],ind);
   					k++;  
  				}
		 }
		 file.close();
	if(k==1)
 	{
		  collegeretrieve_record(resind[0]);
		  return;
 	}
	 else
	 {
 		 cout<<"Please choose the college's CID : \n";
 		 for(i=0;i<k;i++)
   			cout<<"college name : "<<found[i].Cname<<"college id   : "<<found[i].Cid<<endl;
 	}
	 cin>>chid;
 	for(i=0;i<k;i++)
	 {
  			if(strcmp(chid,found[i].Cid)==0)
  			{
   					collegeretrieve_record(resind[i]);
					 return;
  			}
 	}
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void collegedelete_record(char indx[])
{
	 int i,no,flag;
 	fstream file1,file2;

		no=collegeget_num_records();
 		flag=-1;
 		for(i=0;i<no;i++)
 		{
  					if(strcmp(findex[i],indx)==0)
   					flag=i;
 		}
 		if(flag==-1)
 		{
  				cout<<"Error !\n";
  				return;
}
		if(flag==(no-1))
 		{
  				no--;
  				cout<<"Deleted !\n";
 		} 
		else
		{
 				for(i=flag;i<no;i++)
 				{
  						unirec[i]=unirec[i+1];
 				}
 				no--;
 				cout<<"Deleted !\n";
		}
		file1.open("collegesecindex.txt",ios::out);
 		file2.open("collegerecord.txt",ios::out);
 		for(i=0;i<no;i++)
 		{
  		file1<<unirec[i].Cname<<"|"<<unirec[i].Cid<<"|"<<i<<"\n";
file2<<i<<"|"<<unirec[i].Cid<<"|"<<unirec[i].Cname<<"|"<<unirec[i].location<<"|"<<unirec[i].Course<<"\n";
 		}
		file2.close();
 		file1.close();
 		return;    
}

void collegeremove_record()
{
 	fstream file;
	 int i,k=0,no;
	 char Cname[15],Cid[5],ind[5],chid[5],resind[20][5],clg_name[15];
		cout<<"Please enter the name of the college whose record is to be deleted\n";
   		cin>>clg_name;
		 file.open("collegesecindex.txt",ios::in);
		 while(! file.eof())
 		{
			  file.getline(Cname,15,'|');
			  file.getline(Cid,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(clg_name,Cname)==0)
  			  {
		   			strcpy(found[k].Cname,Cname);
		  		 	strcpy(found[k].Cid,Cid);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		collegedelete_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the college's CID : \n";
 		for(i=0;i<k;i++)
   		cout<<"college name : "<<found[i].Cname<<"college id   : "<<found[i].Cid<<endl;
	 }
	 cin>>chid;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chid,found[i].Cid)==0)
  			{
   				collegedelete_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void collegesort_records(int no)
{
	 int i,j;
	 university  temp1;
		for(i=0;i<no-1;i++)
		{
	  		for(j=0;j<no-i-1;j++)
			{
   				if(strcmp(unirec[j].Cname,unirec[j+1].Cname)>0)
   				{
    						temp1=unirec[j];
    						unirec[j]=unirec[j+1];
    						unirec[j+1]=temp1;
   				}
	 		}
		}		
}

void collegecreate_indexfile(int no)
{
 	fstream file1,file2;
 	int i;
 			file1.open("collegesecindex.txt",ios::out);
 			file2.open("collegerecord.txt",ios::out);
for(i=0;i<no;i++)
		{
		file1<<unirec[i].Cname<<"|"<<unirec[i].Cid<<"|"<<i<<"\n"; file2<<i<<"|"<<unirec[i].Cid<<"|"<<unirec[i].Cname<<"|"<<unirec[i].location<<"|"<<unirec[i].Course<<"\n";
 	}
	file1.close();
	file2.close();
}

void collegeadd_records()
{	
 	int i,j,k,cnt,no;
	char line[50];
	cout<<"\nEnter the no. of colleges : ";
	cin>>no;
	cout<<"\nEnter the details :\n"; 
	cnt =collegeget_num_records();
	for(i=cnt;i<(cnt+no);i++)
   	{                  
		cout<<"\nCollege Name : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].Cname,line);
cout<<unirec[i].Cname;

		cout<<"\nCollege Id   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].Cid,line);
cout<<unirec[i].Cid;


		cout<<"\nLocation     : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].location,line);
cout<<unirec[i].location;

		cout<<"\nCourse       : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].Course,line);
cout<<unirec[i].Course;

	}
		collegesort_records((cnt+no));
  	 	collegecreate_indexfile((cnt+no));
}

void collegedisplay_records()
{
	university s;
	fstream file;
	int i=0;
		file.open("collegerecord.txt",ios::in);
		if(!file)
		{	
				cout<<"Error\n";
				return;	
		}
cout<<"            C O L L E G E     D I S P L A Y     L I S T                                 \n";
cout<<"************************************************************************************************************************************************************************************************************";
		cout<<"\ncid\t\tcname\t\tlocation\t\tcourse\n"; 
cout<<"************************************************************************************************************************************************************************************************************\n"; 
		while(!file.eof())
		{	
	  			file.getline(findex[i],5,'|');
                                file.getline(s.Cid,5,'|');
  				file.getline(s.Cname,15,'|');
  				file.getline(s.location,15,'|');
  				file.getline(s.Course,15,'\n'); 
	cout<<s.Cid<<"\t\t"<<s.Cname<<"\t\t"<<s.location<<"\t\t"<<s.Course<<"\t\t"<<endl;
 		}
	file.close();
	return;
}
void collegemodify_record(char indx[])
{
		
		char Cname[15],Cid[5],location[15],Course[15];
		int i,no;
		no=collegeget_num_records();
		for(i=0;i<no;i++)
		{
			if(strcmp(indx,findex[i])==0)

  			{
				cout<<"\nThe old values of the records are "; 
				cout<<"\ncollege name  = "<<unirec[i].Cname;
				cout<<"\ncollege id    = "<<unirec[i].Cid;
				cout<<"\nlocation      = "<<unirec[i].location;
				cout<<"\ncourse        = "<<unirec[i].Course<<endl;
				cout<<"\nEnter the new values \n";
				cout<<"\ncollege name  = ";  cin>>unirec[i].Cname;
				cout<<"\ncollege id    = ";  cin>>unirec[i].Cid;
				cout<<"\nlocation      = ";  cin>>unirec[i].location;
				cout<<"\ncourse        = ";  cin>>unirec[i].Course;
				break;

  			}
 		}
collegesort_records((no));
collegecreate_indexfile((no));
return;
}
		

void collegemodify_records()
{
fstream file;
	 int i,k=0,no;
	 char Cname[15],Cid[5],ind[5],chid[5],resind[20][5],clg_name[15];
		cout<<"Please enter the name of the college whose record is to be modified\n";
   		cin>>clg_name;
		 file.open("collegesecindex.txt",ios::in);
		 while(!file.eof())
 		{
			  file.getline(Cname,15,'|');
			  file.getline(Cid,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(clg_name,Cname)==0)
  			  {
		   			strcpy(found[k].Cname,Cname);
		  		 	strcpy(found[k].Cid,Cid);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		collegemodify_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the college's CID : \n";
 		for(i=0;i<k;i++)
   		cout<<"college name : "<<found[i].Cname<<"college id   : "<<found[i].Cid<<endl;
	 }
	 cin>>chid;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chid,found[i].Cid)==0)
  			{
   				collegemodify_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

//examschedule.cpp

int examsget_num_records()
{
		fstream file;
		int i=0;
			file.open("examsrecord.txt",ios::in);
		if(!file)
			{
				return 0;	
			}
			while(!file.eof())
			{	
	  			file.getline(findex[i],5,'|');
				file.getline(unirec[i].CID,5,'|');
  				file.getline(unirec[i].COURSE,10,'|');
  				file.getline(unirec[i].sdate,5,'|');
  				file.getline(unirec[i].edate,5,'|');
				file.getline(unirec[i].smonth,10,'|');
				file.getline(unirec[i].emonth,10,'|');
				file.getline(unirec[i].syear,5,'|');
  				file.getline(unirec[i].eyear,5,'\n'); 
 				i++;
			}
		i--;	
	file.close();
	return i;
}

void examsretrieve_record(char* ind)
{
	 int i,no;
	 no=examsget_num_records();	
	 for(i=0;i<no;i++)
	 {	
  			if(strcmp(ind,findex[i])==0)
			{
   				cout<<"cid    :"<<unirec[i].CID<<"\ncourse :"<<unirec[i].COURSE<<"\nsdate  :"<<unirec[i].sdate<<"\nedate  :"<<unirec[i].edate<<"\nsmonth :"<<unirec[i].smonth<<"\nemonth :"<<unirec[i].emonth<<"\nsyear  :"<<unirec[i].syear<<"\neyear  :"<<unirec[i].eyear<<endl;

			}
 	}
	 return;
}

void examssearch_records()
{
 	int k=0,i,no;
	char COURSE[10],CID[5],ind[5],chid[5],resind[5][20];
	fstream file;
		 file.open("examssecindex.txt",ios::in);
 		cout<<"Please enter the name of the course whose record is to be displayed\n";
		 cin>>rt_name;
		 while(!file.eof())
		 {
  				file.getline(COURSE,10,'|');
				file.getline(CID,5,'|');
				file.getline(ind,5,'\n');
		 if(strcmp(COURSE,rt_name)==0)
  				{
  					strcpy(found[k].COURSE,COURSE);
   					strcpy(found[k].CID,CID);
   					strcpy(resind[k],ind);
   					k++;  
  				}
		 }
		 file.close();
	if(k==1)
 	{
		  examsretrieve_record(resind[0]);
		  return;
 	}
	 else
	 {
 		 cout<<"Please choose the course's CID : \n";
 		 for(i=0;i<k;i++)
   			cout<<"course name : "<<found[i].COURSE<<"course id   : "<<found[i].CID<<endl;
 	}
	 cin>>chid;
 	for(i=0;i<k;i++)
	 {
  			if(strcmp(chid,found[i].CID)==0)
  			{
   					examsretrieve_record(resind[i]);
					 return;
  			}
 	}
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void examsdelete_record(char indx[])
{
	 int i,no,flag;
 	fstream file1,file2;

		no=examsget_num_records();
 		flag=-1;
 		for(i=0;i<no;i++)
 		{
  					if(strcmp(findex[i],indx)==0)
   					flag=i;
 		}
 		if(flag==-1)
 		{
  				cout<<"Error !\n";
  				return;
}
		if(flag==(no-1))
 		{
  				no--;
  				cout<<"Deleted !\n";
 		} 
		else
		{
 				for(i=flag;i<no;i++)
 				{
  						unirec[i]=unirec[i+1];
 				}
 				no--;
 				cout<<"Deleted !\n";
		}
		file1.open("examssecindex.txt",ios::out);
 		file2.open("examsrecord.txt",ios::out);
 		for(i=0;i<no;i++)
 		{
  		file1<<unirec[i].COURSE<<"|"<<unirec[i].CID<<"|"<<i<<"\n";
file2<<i<<"|"<<unirec[i].CID<<"|"<<unirec[i].COURSE<<"|"<<unirec[i].sdate<<"|"<<unirec[i].edate<<"|"<<unirec[i].smonth<<"|"<<unirec[i].emonth<<"|"<<unirec[i].syear<<"|"<<unirec[i].eyear<<"\n";
 		}
		file2.close();
 		file1.close();
 		return;    
}

void examsremove_record()
{
 	fstream file;
	 int i,k=0,no;
	 char COURSE[10],CID[5],ind[5],chid[5],resind[20][5],c_name[15];
		cout<<"Please enter the name of the course whose record is to be deleted\n";
   		cin>>c_name;
		 file.open("examssecindex.txt",ios::in);
		 while(! file.eof())
 		{
			  file.getline(COURSE,10,'|');
			  file.getline(CID,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(c_name,COURSE)==0)
  			  {
		   			strcpy(found[k].COURSE,COURSE);
		  		 	strcpy(found[k].CID,CID);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		examsdelete_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the course's CID : \n";
 		for(i=0;i<k;i++)
   		cout<<"course name: "<<found[i].COURSE<<"course id   : "<<found[i].CID<<endl;
	 }
	 cin>>chid;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chid,found[i].CID)==0)
  			{
   				examsdelete_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void examssort_records(int no)
{
	 int i,j;
	 university temp2;
		for(i=0;i<no-1;i++)
		{
	  		for(j=0;j<no-i-1;j++)
			{
   				if(strcmp(unirec[j].COURSE,unirec[j+1].COURSE)>0)
   				{
    						temp2=unirec[j];
    						unirec[j]=unirec[j+1];
    						unirec[j+1]=temp2;
   				}
	 		}
		}		
}

void examscreate_indexfile(int no)
{
 	fstream file1,file2;
 	int i;
 			file1.open("examssecindex.txt",ios::out);
 			file2.open("examsrecord.txt",ios::out);
for(i=0;i<no;i++)
		{
		file1<<unirec[i].COURSE<<"|"<<unirec[i].CID<<"|"<<i<<"\n"; file2<<i<<"|"<<unirec[i].CID<<"|"<<unirec[i].COURSE<<"|"<<unirec[i].sdate<<"|"<<unirec[i].edate<<"|"<<unirec[i].smonth<<"|"<<unirec[i].emonth<<"|"<<unirec[i].syear<<"|"<<unirec[i].eyear<<"\n";
 	}
	file1.close();
	file2.close();
}

void examsadd_records()
{	
 	int i,j,k,cnt,no;
	char line[50];
	cout<<"\nEnter the no. of exams to be scheduled : ";
	cin>>no;
	cout<<"\nEnter the details :\n"; 
	cnt =examsget_num_records();
	for(i=cnt;i<(cnt+no);i++)
   	{                  
		cout<<"\nCourse Name : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].COURSE,line);
cout<<unirec[i].COURSE;

		cout<<"\nCourse Id   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].CID,line);
cout<<unirec[i].CID;


		cout<<"\nStart Date  : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].sdate,line);
cout<<unirec[i].sdate;

		cout<<"\nEnd Date    : ";
		cin>>line;
for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].edate,line);
cout<<unirec[i].edate;

		cout<<"\nStart Month : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].smonth,line);
cout<<unirec[i].smonth;

		cout<<"\nEnd Month   : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].emonth,line);
cout<<unirec[i].emonth;

		cout<<"\nStart Year  : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].syear,line);
cout<<unirec[i].syear;

		cout<<"\nEnd Year    : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].eyear,line);
cout<<unirec[i].eyear;


	}
		examssort_records((cnt+no));
  	 	examscreate_indexfile((cnt+no));
}

void examsdisplay_records()
{
	university s;
	fstream file;
	int i=0;
		file.open("examsrecord.txt",ios::in);
		if(!file)
		{	
				cout<<"Error\n";
				return;	
		}
cout<<"                                                    E X A M S C H E D U L E     D I S P L A Y     L I S T                                 \n";
cout<<"************************************************************************************************************************************************************************************************************\n";		cout<<"cid\t\tcourse\t\tstartdate \t\tenddate   \t\tstartmonth\t\tendmonth  \t\tstartyear \t\tendyear   \n";
cout<<"************************************************************************************************************************************************************************************************************\n";  
		while(!file.eof())
		{	
				file.getline(findex[i],5,'|');
				file.getline(s.CID,5,'|');
  				file.getline(s.COURSE,10,'|');
  				file.getline(s.sdate,5,'|');
  				file.getline(s.edate,5,'|');
				file.getline(s.smonth,10,'|');
				file.getline(s.emonth,10,'|');
				file.getline(s.syear,5,'|');
  				file.getline(s.eyear,5,'\n'); 	
	  		
	cout<<s.CID<<"\t\t"<<s.COURSE<<"\t\t"<<s.sdate<<"\t\t\t"<<s.edate<<"\t\t\t"<<s.smonth<<"\t\t\t"<<s.emonth<<"\t\t\t"<<s.syear<<"\t\t\t"<<s.eyear<<"\t\t\t"<<endl;
 		}
	file.close();
	return;
}
void examsmodify_record(char indx[])
{
		
		char COURSE[10],CID[5],sdate[5],edate[5],smonth[10],emonth[10],syear[5],eyear[5];
		int i,no;
		no=examsget_num_records();
		for(i=0;i<no;i++)
		{
			if(strcmp(indx,findex[i])==0)

  			{
				cout<<"\nThe old values of the records are "; 
				cout<<"\ncourse name  = "<<unirec[i].COURSE;
				cout<<"\ncourse id    = "<<unirec[i].CID;
				cout<<"\nstart date   = "<<unirec[i].sdate;
				cout<<"\nend date     = "<<unirec[i].edate;
				cout<<"\nstart month  = "<<unirec[i].smonth;
				cout<<"\nend month    = "<<unirec[i].emonth;
				cout<<"\nstart year   = "<<unirec[i].syear;
				cout<<"\nend year     = "<<unirec[i].eyear<<endl;
				cout<<"\nEnter the new values \n";
				cout<<"\ncourse name  = ";   cin>>unirec[i].COURSE;
				cout<<"\ncourse id    = ";   cin>>unirec[i].CID;
				cout<<"\nstart date   = ";   cin>>unirec[i].sdate;
				cout<<"\nend date     = ";   cin>>unirec[i].edate;
				cout<<"\nstart month  = ";   cin>>unirec[i].smonth;
				cout<<"\nend month    = ";   cin>>unirec[i].emonth;
				cout<<"\nstart year   = ";   cin>>unirec[i].syear;
				cout<<"\nend year     = ";   cin>>unirec[i].eyear;
				break;

  			}
 		}
examssort_records((no));
examscreate_indexfile((no));
return;
}
		

void examsmodify_records()
{
fstream file;
	 int i,k=0,no;
	 char COURSE[10],CID[5],ind[5],chid[5],resind[20][5],c_name[10];
		cout<<"Please enter the name of the course whose record is to be modified\n";
   		cin>>c_name;
		 file.open("examssecindex.txt",ios::in);
		 while(!file.eof())
 		{
			  file.getline(COURSE,10,'|');
			  file.getline(CID,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(c_name,COURSE)==0)
  			  {
		   			strcpy(found[k].COURSE,COURSE);
		  		 	strcpy(found[k].CID,CID);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		examsmodify_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the course's CID : \n";
 		for(i=0;i<k;i++)
   		cout<<"course name : "<<found[i].COURSE<<"course id   : "<<found[i].CID<<endl;
	 }
	 cin>>chid;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chid,found[i].CID)==0)
  			{
   				examsmodify_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}


//result.cpp

int resultget_num_records()
{
		fstream file;
		int i=0;
			file.open("resultrecord.txt",ios::in);
		if(!file)
			{
				return 0;	
			}
			while(!file.eof())
			{	
	  			file.getline(findex[i],5,'|');
				file.getline(unirec[i].usn,5,'|');
  				file.getline(unirec[i].sname,10,'|');
  				file.getline(unirec[i].course,10,'|');
				file.getline(unirec[i].branch,10,'|');
				file.getline(unirec[i].sem,10,'|');
  				file.getline(unirec[i].theory1,12,'|');
				file.getline(unirec[i].theory2,12,'|');
				file.getline(unirec[i].theory3,12,'|');
				file.getline(unirec[i].theory4,12,'|');
				file.getline(unirec[i].theory5,12,'|');
				file.getline(unirec[i].theory6,12,'|');
				file.getline(unirec[i].lab1,12,'|');
				file.getline(unirec[i].lab2,12,'\n'); 
 				i++;
			}
		i--;	
	file.close();
	return i;
}

void resultretrieve_record(char* ind)
{
	 int i,no;
	 no=resultget_num_records();	
	 for(i=0;i<no;i++)
	 {	
  			if(strcmp(ind,findex[i])==0)
			{
   				cout<<"usn     :"<<unirec[i].usn<<"\nsname   :"<<unirec[i].sname<<"\ncourse  :"<<unirec[i].course<<"\nbranch   :"<<unirec[i].branch<<"\nsem  :"<<unirec[i].sem<<"\ntheory1 :"<<unirec[i].theory1<<"\ntheory2 :"<<unirec[i].theory2<<"\ntheory3 :"<<unirec[i].theory3<<"\ntheory4 :"<<unirec[i].theory4<<"\ntheory5 :"<<unirec[i].theory5<<"\ntheory6 :"<<unirec[i].theory6<<"\nlab1   :"<<unirec[i].lab1<<"\nlab2   :"<<unirec[i].lab2<<endl;
			}
 	}
	 return;
}

void resultsearch_records()
{
 	int k=0,i,no;
	char sname[10],usn[5],ind[5],chusn[5],resind[5][20];
	fstream file;
		 file.open("resultsecindex.txt",ios::in);
 		cout<<"Please enter the name of the student whose record is to be displayed\n";
		 cin>>rt_name;
		 while(!file.eof())
		 {
  				file.getline(sname,10,'|');
				file.getline(usn,5,'|');
				file.getline(ind,5,'\n');
		 if(strcmp(sname,rt_name)==0)
  				{
  					strcpy(found[k].sname,sname);
   					strcpy(found[k].usn,usn);
   					strcpy(resind[k],ind);
   					k++;  
  				}
		 }
		 file.close();
	if(k==1)
 	{
		  resultretrieve_record(resind[0]);
		  return;
 	}
	 else
	 {
 		 cout<<"Please choose the student's USN : \n";
 		 for(i=0;i<k;i++)
   			cout<<"student name : "<<found[i].sname<<"USN      : "<<found[i].usn<<endl;
 	}
	 cin>>chusn;
 	for(i=0;i<k;i++)
	 {
  			if(strcmp(chusn,found[i].usn)==0)
  			{
   					resultretrieve_record(resind[i]);
					 return;
  			}
 	}
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void resultdelete_record(char indx[])
{
	 int i,no,flag;
 	fstream file1,file2;

		no=resultget_num_records();
 		flag=-1;
 		for(i=0;i<no;i++)
 		{
  					if(strcmp(findex[i],indx)==0)
   					flag=i;
 		}
 		if(flag==-1)
 		{
  				cout<<"Error !\n";
  				return;
}
		if(flag==(no-1))
 		{
  				no--;
  				cout<<"Deleted !\n";
 		} 
		else
		{
 				for(i=flag;i<no;i++)
 				{
  						unirec[i]=unirec[i+1];
 				}
 				no--;
 				cout<<"Deleted !\n";
		}
		file1.open("resultsecindex.txt",ios::out);
 		file2.open("resultrecord.txt",ios::out);
 		for(i=0;i<no;i++)
 		{
  		file1<<unirec[i].sname<<"|"<<unirec[i].usn<<"|"<<i<<"\n";
file2<<i<<"|"<<unirec[i].usn<<"|"<<unirec[i].sname<<"|"<<unirec[i].course<<"|"<<unirec[i].branch<<"|"<<unirec[i].sem<<"|"<<unirec[i].theory1<<"|"<<unirec[i].theory2<<"|"<<unirec[i].theory3<<"|"<<unirec[i].theory4<<"|"<<unirec[i].theory5<<"|"<<unirec[i].theory6<<"|"<<unirec[i].lab1<<"|"<<unirec[i].lab2<<"\n";
 		}
		file2.close();
 		file1.close();
 		return;    
}

void resultremove_record()
{
 	fstream file;
	 int i,k=0,no;
	 char sname[10],usn[5],ind[5],chusn[5],resind[20][5],s_name[10];
		cout<<"Please enter the name of the student whose record is to be deleted\n";
   		cin>>s_name;
		 file.open("resultsecindex.txt",ios::in);
		 while(! file.eof())
 		{
			  file.getline(sname,10,'|');
			  file.getline(usn,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(s_name,sname)==0)
  			  {
		   			strcpy(found[k].sname,sname);
		  		 	strcpy(found[k].usn,usn);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		resultdelete_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the student's USN : \n";
 		for(i=0;i<k;i++)
   		cout<<"student name: "<<found[i].sname<<"     USN    : "<<found[i].usn<<endl;
	 }
	 cin>>chusn;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chusn,found[i].usn)==0)
  			{
   				resultdelete_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

void resultsort_records(int no)
{
	 int i,j;
	 university temp3;
		for(i=0;i<no-1;i++)
		{
	  		for(j=0;j<no-i-1;j++)
			{
   				if(strcmp(unirec[j].sname,unirec[j+1].sname)>0)
   				{
    						temp3=unirec[j];
    						unirec[j]=unirec[j+1];
    						unirec[j+1]=temp3;
   				}
	 		}
		}		
}

void resultcreate_indexfile(int no)
{
 	fstream file1,file2;
 	int i;
 			file1.open("resultsecindex.txt",ios::out);
 			file2.open("resultrecord.txt",ios::out);
for(i=0;i<no;i++)
		{
		file1<<unirec[i].sname<<"|"<<unirec[i].usn<<"|"<<i<<"\n"; file2<<i<<"|"<<unirec[i].usn<<"|"<<unirec[i].sname<<"|"<<unirec[i].course<<"|"<<unirec[i].branch<<"|"<<unirec[i].sem<<"|"<<unirec[i].theory1<<"|"<<unirec[i].theory2<<"|"<<unirec[i].theory3<<"|"<<unirec[i].theory4<<"|"<<unirec[i].theory5<<"|"<<unirec[i].theory6<<"|"<<unirec[i].lab1<<"|"<<unirec[i].lab2<<"\n";
 	}
	file1.close();
	file2.close();
}

void resultadd_records()
{	
 	int i,j,k,cnt,no;
	char line[50];
	cout<<"\nEnter the no. of students whose result is to be added : ";
	cin>>no;
	cout<<"\nEnter the details :\n"; 
	cnt =resultget_num_records();
	for(i=cnt;i<(cnt+no);i++)
   	{                  
		cout<<"\nSName     : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].sname,line);
cout<<unirec[i].sname;

		cout<<"\nUSN       : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].usn,line);
cout<<unirec[i].usn;

		cout<<"\nCourse    : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].course,line);
cout<<unirec[i].course;

		cout<<"\nBranch    : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='a' && line[k]<='z') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].branch,line);
cout<<unirec[i].branch;

		cout<<"\nSem       : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]=='\0')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].sem,line);
cout<<unirec[i].sem;

		cout<<"\nNOTE: Enter the subcode as well as marks in the theory prompt...marks(out of 100)....EX(theory1 :17IS51:95)\n";
		cout<<"\nTheory1   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory1,line);
cout<<unirec[i].theory1;

		cout<<"\nTheory2   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory2,line);
cout<<unirec[i].theory2;

		cout<<"\nTheory3   : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory3,line);
cout<<unirec[i].theory3;

		cout<<"\nTheory4   : ";
		cin>>line;

for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory4,line);
cout<<unirec[i].theory4;

		cout<<"\nTheory5   : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory5,line);
cout<<unirec[i].theory5;

		cout<<"\nTheory6   : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].theory6,line);
cout<<unirec[i].theory6;
		cout<<"\nNOTE: Enter the subcode as well as marks in the lab prompt...marks(out of 100)....EX(lab1 :17ISL57:96)\n";
		cout<<"\nLab1      : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].lab1,line);
cout<<unirec[i].lab1;

		cout<<"\nLab2      : ";
		cin>>line;


for(int k=0,j;line[k]!='\0';++k)
{
	while(!(line[k]>='0' && line[k]<='9') && !(line[k]>='A' && line[k]<='Z') && !(line[k]=='\0') && !(line[k]==':')){
	for(j=k;line[j]!='\0';++j){
	line[j]=line[j+1];
	}
	line[j]='\0';
}
}
strcpy(unirec[i].lab2,line);
cout<<unirec[i].lab2;


	}
		resultsort_records((cnt+no));
  	 	resultcreate_indexfile((cnt+no));
}

void resultdisplay_records()
{
	university s;
	fstream file;
	int i=0;
		file.open("resultrecord.txt",ios::in);
		if(!file)
		{	
				cout<<"Error\n";
				return;	
		}
cout<<"                                                   R E S U L T S     D I S P L A Y     L I S T                                  \n";
cout<<"***********************************************************************************************************************************************************************************************************";
		cout<<"\nusn\t\tsname\t\tcourse\t\tbranch\t\tsem\t\ttheory1\t\ttheory2\t\ttheory3\t\ttheory4\t\ttheory5\t\ttheory6\t\tlab1\t\tlab2\n";
		cout<<"***********************************************************************************************************************************************************************************************************\n";  
		while(!file.eof())
		{	
				file.getline(findex[i],5,'|');
				file.getline(s.usn,5,'|');
  				file.getline(s.sname,10,'|');
  				file.getline(s.course,10,'|');
  				file.getline(s.branch,10,'|');
				file.getline(s.sem,10,'|');
				file.getline(s.theory1,12,'|');
				file.getline(s.theory2,12,'|');
				file.getline(s.theory3,12,'|');
				file.getline(s.theory4,12,'|');
				file.getline(s.theory5,12,'|');
				file.getline(s.theory6,12,'|');
				file.getline(s.lab1,12,'|');
  				file.getline(s.lab2,12,'\n'); 	
	  		
	cout<<s.usn<<"\t\t"<<s.sname<<"\t\t"<<s.course<<"\t\t"<<s.branch<<"\t\t"<<s.sem<<"\t\t"<<s.theory1<<"\t"<<s.theory2<<"\t"<<s.theory3<<"\t"<<s.theory4<<"\t"<<s.theory5<<"\t"<<s.theory6<<"\t"<<s.lab1<<"\t"<<s.lab2<<"\t"<<endl;
 		}
	file.close();
	return;
}
void resultmodify_record(char indx[])
{
		
		char sname[10],usn[5],course[10],branch[10],sem[10],theory1[10],theory2[10],theory3[10],theory4[10],theory5[10],theory6[10],lab1[10],lab2[10];
		int i,no;
		no=resultget_num_records();
		for(i=0;i<no;i++)
		{
			if(strcmp(indx,findex[i])==0)

  			{
				cout<<"\nThe old values of the records are "; 
				cout<<"\nSName    = "<<unirec[i].sname;
				cout<<"\nUSN      = "<<unirec[i].usn;
				cout<<"\nCourse   = "<<unirec[i].course;
				cout<<"\nBranch   = "<<unirec[i].branch;
				cout<<"\nSem      = "<<unirec[i].sem;
				cout<<"\nTheory1  = "<<unirec[i].theory1;
				cout<<"\nTheory2  = "<<unirec[i].theory2;
				cout<<"\nTheory3  = "<<unirec[i].theory3;
				cout<<"\nTheory4  = "<<unirec[i].theory4;
				cout<<"\nTheory5  = "<<unirec[i].theory5;
				cout<<"\nTheory6  = "<<unirec[i].theory6;
				cout<<"\nLab1     = "<<unirec[i].lab1;
				cout<<"\nLab2     = "<<unirec[i].lab2<<endl;	
				
				cout<<"\nEnter the new values \n";
				cout<<"\nSName    : ";  cin>>unirec[i].sname;
				cout<<"\nUSN      : ";  cin>>unirec[i].usn;
				cout<<"\nCourse   : ";  cin>>unirec[i].course;
				cout<<"\nBranch   : ";  cin>>unirec[i].branch;
				cout<<"\nSem      : ";  cin>>unirec[i].sem;
				cout<<"\nTheory1  : ";  cin>>unirec[i].theory1;
				cout<<"\nTheory2  : ";  cin>>unirec[i].theory2;
				cout<<"\nTheory3  : ";  cin>>unirec[i].theory3;
				cout<<"\nTheory4  : ";  cin>>unirec[i].theory4;
				cout<<"\nTheory5  : ";  cin>>unirec[i].theory5;
				cout<<"\nTheory6  : ";  cin>>unirec[i].theory6;
				cout<<"\nLab1     : ";  cin>>unirec[i].lab1;
				cout<<"\nLab2     : ";  cin>>unirec[i].lab2;
				break;

  			}
 		}
resultsort_records((no));
resultcreate_indexfile((no));
return;
}
		

void resultmodify_records()
{
fstream file;
	 int i,k=0,no;
	 char sname[10],usn[5],ind[5],chusn[5],resind[20][5],s_name[10];
		cout<<"Please enter the name of the student whose record is to be modified\n";
   		cin>>s_name;
		 file.open("resultsecindex.txt",ios::in);
		 while(!file.eof())
 		{
			  file.getline(sname,10,'|');
			  file.getline(usn,5,'|');
			  file.getline(ind,5,'\n');
			  if(strcmp(s_name,sname)==0)
  			  {
		   			strcpy(found[k].sname,sname);
		  		 	strcpy(found[k].usn,usn);
		   			strcpy(resind[k],ind);
		   			k++;  
  			 }
 		}
	 file.close();
	 if(k==1)
 	{
  		resultmodify_record(resind[0]);
 		 return;
	 }
 	else
 	{
  			cout<<"Please choose the student's USN : \n";
 		for(i=0;i<k;i++)
   		cout<<"student name : "<<found[i].sname<<"USN   : "<<found[i].usn<<endl;
	 }
	 cin>>chusn;
	 for(i=0;i<k;i++)
 	{
  			if(strcmp(chusn,found[i].usn)==0)
  			{
   				resultmodify_record(resind[i]);
   				return;
  			}
	 }
 	cout<<"Invalid Entry !\n"; 
 	return;   
}

//performance.cpp

void performance()
{
cout<<"\n************************************************************************    P E R F O R M A N C E      ***************************************************************************************************\n";
cout<<"\n\t ____________________________ \n";
cout<<"\t|  *VISION / MISSION         |\n";
cout<<"\t|____________________________|\n";
cout<<"\n";
cout<<"\n\t\t01..V I S I O N:\n";
cout<<"\t\t................\n";
cout<<"\n\t\tOur university shall be recognised institution producing competent proffessionals responsive to the technological needs of the society.\n";
cout<<"\n\t\t02..M I S S I O N:\n";
cout<<"\t\t..................\n";
cout<<"\n\t\t1.T0 establish centres of excellence\n";
cout<<"\n\t\t2.To provide value based technical education through state-of-art infrastucture,qualified staff,best teaching mehods,academic exchange and collabborative programme with industries.\n";
cout<<"\n\t\t3.To encourage entrepreneurial skill and innovations in emerging technologies.\n";
cout<<"\n\t\t4.To inculcate professional ethics and leadership qualities to address the societal needs.\n";
cout<<"\n";
cout<<"\n";
cout<<"\t ____________________________\n";
cout<<"\t|       *FOUNDATION:         |\n";
cout<<"\t|____________________________|\n";
cout<<"\n\t\tNIE foundation was established by NIE Society(R) in 1984,Mysuru\n";
cout<<"\n\t\tThe NIEIT is being managed by 10 Board of Directors consisting of eminent educationist and Industrialist.\n";
cout<<"\n";
cout<<"\n";
cout<<"\t ____________________________\n";
cout<<"\t|      *ACCREDITATION:       |\n";
cout<<"\t|____________________________|\n";
cout<<"\n\t\tIn process for Accreditation.\n";
cout<<"\n";
cout<<"\n";
cout<<"\t ____________________________\n";
cout<<"\t|   *MANDATORY DISCLOSURE:   |\n";
cout<<"\t|____________________________|\n";
cout<<"\n\t\tAs required by the AICTE,the following is the mandatory disclosure provided by NIEIT,Mysore.\n";
cout<<"\n";
cout<<"\n";
cout<<"\n**************************************************************************    T H A N K     Y O U   ********************************************************************************************************\n";
return;
}

//Main

int main()
{


cout<<"............................................................... U N I V E R S I T Y     M A N A G E M E N T      S Y S T E M............................................................................\n\n";

int choice;
for(;;)
{
cout<<"\n\tW E L C O M E    T O   O U R   U N I V E R S I T Y";
cout<<"\n\t\t ______________________________ ";
cout<<"\n\t\t|       1.STUDENT             |";
cout<<"\n\t\t|_____________________________|";
cout<<"\n\t\t|       2.COLLEGE             |";
cout<<"\n\t\t|_____________________________|";
cout<<"\n\t\t|       3.EXAMSCHEDULE        |";
cout<<"\n\t\t|_____________________________|";
cout<<"\n\t\t|       4.RESULT              |";
cout<<"\n\t\t|_____________________________|";
cout<<"\n\t\t|       5.ABOUT US            |";
cout<<"\n\t\t|_____________________________|";
cout<<"\n";
	cin>>choice;
	switch(choice)
	{
		case 1:
		int choice1;
		for(;;)
	{	cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|      S T U D E N T         |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     4.MODIFY RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     5.DELETE RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     6.EXIT                 |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
		
		cin>>choice1;
		switch(choice1)
		{
		case 1:studentadd_records();      break;
		case 2:studentdisplay_records();  break;
		case 3:studentsearch_records();   break;
		case 4:studentmodify_records();   break;
		case 5:studentremove_record();  break;
		case 6:main(); break;
		}
	}
	
		case 2:
		int choice2;
		for(;;)
	{	cout<<"\n\t\t_____________________________";
		cout<<"\n\t\t|      C O L L E G E         |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     4.MODIFY RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     5.DELETE RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     6.EXIT                 |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
		
		cin>>choice2;
		switch(choice2)
		{
		case 1:collegeadd_records();      break;
		case 2:collegedisplay_records();  break;
		case 3:collegesearch_records();   break;
		case 4:collegemodify_records();   break;
		case 5:collegeremove_record();  break;
		case 6:main(); break;
		}
	}
		
		case 3:
		int choice3;
		for(;;)
	{	cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|  E X A M  S C H E D U L E  |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     4.MODIFY RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     5.DELETE RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     6.EXIT                 |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
		
		cin>>choice3;
		switch(choice3)
		{
		case 1:examsadd_records();      break;
		case 2:examsdisplay_records();  break;
		case 3:examssearch_records();   break;
		case 4:examsmodify_records();   break;
		case 5:examsremove_record();  break;
		case 6:main(); break;
		}
	}
	
		case 4:
		int choice4;
		for(;;)
	{	
		cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|       R E S U L T          |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     4.MODIFY RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     5.DELETE RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     6.EXIT                 |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
		
		cin>>choice4;
		switch(choice4)
		{
		case 1:resultadd_records();      break;
		case 2:resultdisplay_records();  break;
		case 3:resultsearch_records();   break;
		case 4:resultmodify_records();   break;
		case 5:resultremove_record();  break;
		case 6:main(); break;
		}
	}

		case 5:
		int choice5;
		for(;;)
	{	
		cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|     A B O U T   U S        |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.PERFORMANCE          |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.EXIT                 |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
		
		cin>>choice5;
		switch(choice5)
		{
		case 1:performance();      break;
		case 2:main(); break;
		}
	}
		default:cout<<"\nInvalid choice !\n";
		exit(0);
		}
	}
}


