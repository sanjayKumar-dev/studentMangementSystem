#include <bits/stdc++.h>
#include <conio.h>
#include <fstream>
using namespace std;

class Student {
private:
	int Studentid;
	char name[20];
	float mark;

public:
	Student()
	{
		Studentid = 0;
		strcpy(name, "no title");
		mark = 0;
	}
	void getStudentData()
	{
		cout << "Enter studentid, name, "
			<< " mark: ";
		cin >> Studentid;
		cin.ignore();
		cin.getline(name, 19);
		cin >> mark;
	}

	void showStudentData()
	{
		cout << "\n"<< Studentid<< " " << name << " " << mark;
	}

	int storeStudent();
	void viewAllStudent();
	void searchStudent(char*);
	void deleteStudent(char*);
	void updateStudent(char*);
};

void Student::updateStudent(char* t)
{
	fstream file;
	file.open("myfile3.txt",ios::in | ios::out | ios::ate | ios::binary);
	file.seekg(0);
	file.read((char*)this, sizeof(*this));

	while (!file.eof()) {
		if (!strcmp(t, name)) {
			getStudentData();

			file.seekp(file.tellp() - sizeof(*this));
			file.write((char*)this, sizeof(*this));
		}
		file.read((char*)this, sizeof(*this));
	}

	file.close();
}

void Student::deleteStudent(char* t)
{
	ifstream fin;
	ofstream fout;
	fin.open("myfile3.txt",ios::app | ios::binary);
	if (!fin)
		cout << "\n File not found";
	else {
		fout.open("tempfile.txt",
				ios::app | ios::binary);
		fin.read((char*)this, sizeof(*this));
		while (!fin.eof()) {
			if (strcmp(name, t))
				fout.write((char*)this, sizeof(*this));
			fin.read((char*)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("myfile3.txt");
		rename("tempfile.txt", "myfile3.txt");
	}
}

void Student::searchStudent(char* t)
{
	int counter = 0;
	ifstream fin;
	fin.open("myfile3.txt",
			ios::in | ios::binary);


	if (!fin)
		cout << "File not found";
	else {
		fin.read((char*)this, sizeof(*this));

		while (!fin.eof()) {
			if (!strcmp(t, name)) {
				showStudentData();
				counter++;
			}
			fin.read((char*)this, sizeof(*this));
		}
		if (counter == 0)
			cout << "No record found";
		fin.close();
	}
}

void Student::viewAllStudent()
{
	ifstream fin;


	fin.open("myfile3.txt", ios::in | ios::binary);
	if (!fin)
		cout << "File not found";

	else {
		fin.read((char*)this, sizeof(*this));


		while (!fin.eof()) {
			showStudentData();


			fin.read((char*)this, sizeof(*this));
		}
		fin.close();
	}
}


int Student::storeStudent()
{
	if (Studentid == 0 && mark == 0) {
		cout << "book data not"
			<< " initialized";
		return (0);
	}
	else {
		ofstream fout;

		fout.open("myfile3.txt", ios::app | ios::binary);

		fout.write((char*)this, sizeof(*this));
		fout.close();
		return (1);
	}
}

int menu()
{
	int choice;
	cout << "\nStudent Management";
	cout << "\n1.Insert Student record";
	cout << "\n2.View all Student record";
	cout << "\n3.Search Student record";
	cout << "\n4.Delete Student record";
	cout << "\n5.Update Student record";
	cout << "\n6.Exit";
	cout << "\n\nEnter your choice : ";
	cin >> (choice);
	return (choice);
}

int main()
{
	Student b1;
	char name[20];

	while (1) {
		system("cls");
		switch (menu()) {
		case 1:
			b1.getStudentData();
			b1.storeStudent();
			cout << "\nRecord inserted";
			break;

		case 2:
			b1.viewAllStudent();
			break;

		case 3:
			cout << "\nEnter name of "
				<< "Student to search : ";
			cin.ignore();
			cin.getline(name, 19);
			b1.searchStudent(name);
			break;

		case 4:
			cout << "\nEnter Student name "
				<< "for delete record : ";
			cin.ignore();
			cin.getline(name, 19);
			b1.deleteStudent(name);
			break;

		case 5:
			cout << "\nEnter Student name "
				<< "to update record : ";
			cin.ignore();
			cin.getline(name, 19);
			b1.updateStudent(name);
			break;

		case 6:
			cout << "\n Thanks for using";
			cout << "\n Press any key to exit";
			getch();
			exit(0);

		default:
			cout << "Invalid input";
		}
		getch();
	}
}
