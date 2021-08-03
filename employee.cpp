
//*************************************************************************************************************************************************
//                                     EMPLOYEE RECORD MANAGEMENT SYSTEM USING FILE STRUCTURES
//*************************************************************************************************************************************************

//****************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
int i = 0, j = 0;
struct employee
{

	char serial[5], firstname[10], lastname[10], department[10];
	float salary;
	short age, byte, prmbyte;
};
struct primary
{
	char serial[5];
	short byte;
};
struct secondary
{
	char serial[5];
	char department[10];
};
primary prm[20];
secondary sec[20];
void welcome()
{

    cout << "\n\n\n";
	cout << "  1) ADD NEW EMPLOYEE IN THIS SYSTEM" << endl; cout << "  2) UPDATE EMPLOYEE DETAILS USING EMPLOYEE ID" << endl; cout << "  3) DELETE EMPLOYEE DETAILS USING EMPLOYEE ID" << endl;
	cout << "  4) DISPLAY ALL EMPLOYEES DETAILS" << endl; cout << "  5) DIAPLAY ALL EMPLOYEES DEPARTMENTS" << endl; cout << "  6) SEARCH USING EMPLOYEE ID" << endl;
    cout << "  7) EXIT/CLOSE SYSTEM" << endl << endl;
	cout << "  Please Enter your choice : ";
}
void read(fstream& file, employee& e)
{
	short length;
	char ch;
	file.read((char*)&length, sizeof(short));
	file.get(ch);
	if (ch == '*')
	{
		file.read((char*)&e.byte, sizeof(short));
		file.get(ch);
		length -= 6;
		file.seekg(length, ios::cur);
	}
	else
	{
		file.seekg(-3, ios::cur);
		e.prmbyte = file.tellg();
		file.read((char*)&length, sizeof(short));
		file.read((char*)&length, sizeof(short));
		file.read((char*)&e.serial, length);
		e.serial[length] = NULL;
		file.read((char*)&length, sizeof(short)); file.read(e.firstname, length);
		e.firstname[length] = NULL;
		file.read((char*)&length, sizeof(short)); file.read(e.lastname, length);
		e.lastname[length] = NULL;
		file.read((char*)&length, sizeof(short)); file.read((char*)&e.age, length);
		file.read((char*)&length, sizeof(short)); file.read(e.department, length);
		e.department[length] = NULL;
		file.read((char*)&length, sizeof(short)); file.read((char*)&e.salary, length);

	}

}

//****************************************************************
//                   FUNCTION TO WRITE FILE
//****************************************************************

void write(fstream& file, employee& e, short sum)
{
	short len = 0;
	e.prmbyte = file.tellg();
	file.write((char*)&sum, sizeof(sum));
	len = strlen(e.serial);
	file.write((char*)&len, sizeof(short));
	file.write(e.serial, len);
	len = strlen(e.firstname);
	file.write((char*)&len, sizeof(short));
	file.write(e.firstname, len);
	len = strlen(e.lastname);
	file.write((char*)&len, sizeof(short));
	file.write(e.lastname, len);
	len = sizeof(e.age);
	file.write((char*)&len, sizeof(short));
	file.write((char*)&e.age, sizeof(e.age));
	len = strlen(e.department);
	file.write((char*)&len, sizeof(short));
	file.write(e.department, len);
	len = sizeof(e.salary);
	file.write((char*)&len, sizeof(short));
	file.write((char*)&e.salary, sizeof(e.salary));
}
void prm_array(employee e, int pos)
{
	for (int k = 0; k < 5; k++)
		prm[pos].serial[k] = e.serial[k];
	prm[pos].byte = e.prmbyte;
	if (pos >= 1)
	{

		int c;
		for (int g = 0; g < pos; g++)
		{
			c = strcmp(prm[pos].serial, prm[g].serial);
			if (c < 0)
			{
				char temp1[5];
				short temp2;
				for (int k = 0; k < 5; k++)
					temp1[k] = prm[pos].serial[k];
				for (int k = 0; k < 5; k++)
					prm[pos].serial[k] = prm[g].serial[k];
				for (int k = 0; k < 5; k++)
					prm[g].serial[k] = temp1[k];
				temp2 = prm[pos].byte;
				prm[pos].byte = prm[g].byte;
				prm[g].byte = temp2;
			}
		}
	}
}

//***************************************************************
//    			PRIMARY INDEXING
//***************************************************************

void primaryindex()
{
	fstream pindex;
	pindex.open("index1.txt", ios::in | ios::out | ios::binary | ios::trunc);
	if (pindex.is_open())
	{
		pindex.seekg(0, ios::beg);
		for (int g = 0; g < i; g++)
		{
			pindex.write((char*)&prm[g].serial, 5);
			pindex.write((char*)&prm[g].byte, sizeof(short));
		}
	}
	pindex.close();
}
void sec_array(employee e, int pos)
{
	bool b = false;
	for (int k = 0; k < 10; k++)
	{
		if (e.department[k] != NULL)
		{
			if (e.department[k] >= 65 && e.department[k] <= 90)
				e.department[k] += 32;
			sec[pos].department[k] = e.department[k];

		}

		else
		{
			for (int g = k; g < 10; g++)
				sec[pos].department[g] = NULL;
			break;
		}
	}


	for (int k = 0; k < 5; k++)
		sec[pos].serial[k] = e.serial[k];


	if (j >= 1)
	{
		char temp2[10], temp1[5];
		int c;
		if (pos < j)
		{
			b = true;
			j--;
		}
		for (int g = 0; g <= j; g++)
		{
			for (int m = 0; m <= j; m++)
			{
				c = strcmp(sec[g].department, sec[m].department);
				if (c < 0)
				{

					for (int k = 0; k < 10; k++)
						temp2[k] = sec[m].department[k];
					for (int k = 0; k < 10; k++)
						sec[m].department[k] = sec[g].department[k];
					for (int k = 0; k < 10; k++)
						sec[g].department[k] = temp2[k];
					for (int k = 0; k < 5; k++)
						temp1[k] = sec[m].serial[k];
					for (int k = 0; k < 5; k++)
						sec[m].serial[k] = sec[g].serial[k];
					for (int k = 0; k < 5; k++)
						sec[g].serial[k] = temp1[k];
				}

				else if (c == 0)
				{
					c = strcmp(sec[g].serial, sec[m].serial);
					if (c < 0)
					{
						for (int k = 0; k < 10; k++)
							temp2[k] = sec[m].department[k];
						for (int k = 0; k < 10; k++)
							sec[m].department[k] = sec[g].department[k];
						for (int k = 0; k < 10; k++)
							sec[g].department[k] = temp2[k];
						for (int k = 0; k < 5; k++)
							temp1[k] = sec[m].serial[k];
						for (int k = 0; k < 5; k++)
							sec[m].serial[k] = sec[g].serial[k];
						for (int k = 0; k < 5; k++)
							sec[g].serial[k] = temp1[k];
					}
				}
			}
		}
		if (b == true)
			j++;
	}

}

//***************************************************************
//    			BINARY SEARCHING CONCEPT
//***************************************************************

int binarysearch_prm(string serial, int first, int last)
{
	int mid = (first + last) / 2;
	if (prm[first].serial == serial)
		return first;
	else if (prm[mid].serial == serial)
		return mid;
	else if (prm[last].serial == serial)
		return last;
	else if (prm[mid].serial < serial && (mid + 1) < i)
		return binarysearch_prm(serial, mid + 1, last);
	else if (prm[mid].serial > serial && mid > 0)
		return binarysearch_prm(serial, first, mid - 1);
	else
		return -1;
}

//***************************************************************
//    			SECONDARY INDEXING
//***************************************************************

void secondaryindex()
{
	fstream sindex;
	sindex.open("index2.txt", ios::in | ios::out | ios::binary | ios::trunc);
	if (sindex.is_open())
	{
		sindex.seekg(0, ios::beg);
		for (int k = 0; k < j; k++)
		{

			sindex.write(sec[k].department, 10);
			sindex.write((char*)&sec[k].serial, 5);
		}
	}
	sindex.close();
}
void startup()
{
	fstream pindex, sindex;
	int b = 0, pos;
	short len;
	pindex.open("index1.txt", ios::in | ios::out | ios::binary);
	sindex.open("index2.txt", ios::in | ios::out | ios::binary);
	pindex.unsetf(ios::skipws);
	sindex.unsetf(ios::skipws);
	if (pindex.is_open())
	{
		pindex.seekg(0, ios::beg);
		while (!pindex.eof())
		{
			b = pindex.tellg();
			if (b != -1)
			{
				pindex.read((char*)&prm[i].serial, 5);
				sec[i].serial[5] = NULL;
				pindex.read((char*)&prm[i].byte, sizeof(short));
				i++;
			}
		}
		pindex.clear();
		i--;                          ///why
	}
	pindex.close();
	if (sindex.is_open())
	{
		sindex.seekg(0, ios::beg);
		while (!sindex.eof())
		{

			sindex.read(sec[j].department, 10);
			sindex.read(sec[j].serial, 5);
			j++;
		}
		sindex.clear();
		j--;
	}
	sindex.close();



}

//***************************************************************
//    			INSERTING THE DATA INTO SYSTEM
//***************************************************************

void add(fstream& file)
{
	int count = 0;
	short temp;
	bool f = false, b = false;
	employee s;
	short sum = 0, head, size = 0;
	cout << "  ENTER THE EMPLOYEE ID:";         cin >> s.serial;
	for (int m = 0; m < i; m++)
	{
		int n = 0;
		for (n = 0; n < 5; n++)
			if (prm[m].serial[n] != s.serial[n])
				break;
		if (n == 5)
		{
			cout << "This ID is Already exists!" << endl
				<< "please enter another ID :" << endl;
			cin >> s.serial;
			m = -1;
		}
	}

	cout << "  ENTER THE FIRST NAME:";         cin >> s.firstname;
	cout << "  ENTER THE LAST NAME:";         cin >> s.lastname;
	cout << "  ENTER THE AGE:";         cin >> s.age;
	cout << "  ENTER THE DEPARTMENT:";         cin >> s.department;
	cout << "  ENTER THE SALARY:";         cin >> s.salary;
	sum = strlen(s.firstname) + strlen(s.lastname) + strlen(s.department) + 23;
	file.seekg(0, ios::beg);
	file.read((char*)&head, sizeof(short));
	if (head == -1)
		file.seekp(0, ios::end);
	else                                                                //Frist fit
	{
		char ch;
		s.byte = head;
		do {
			count++;
			temp = s.byte;
			file.seekg(s.byte, ios::beg);
			file.read((char*)&size, sizeof(short));
			file.get(ch);
			file.read((char*)&s.byte, sizeof(short));
			file.get(ch);
			if (size >= sum)
			{
				f = true;
				file.seekp(-6, ios::cur);
				break;
			}
			if (s.byte == -1)
			{
				file.seekg(0, ios::end);
				break;
			}

		} while (size < sum);


	}
	write(file, s, sum);
	prm_array(s, i);
	i++;
	int h = j;
	string search = s.serial;
	for (h = 0; h < j; h++)
	{
		if (sec[h].serial == search)
		{
			sec_array(s, h);
			break;
		}
	}
	if (h == j)
	{
		sec_array(s, j);
		j++;
	}


	if (f == true)
	{
		char ch;
		file.seekg(temp, ios::beg);
		if (count > 1)
		{
			file.read((char*)&size, sizeof(short));
			file.get(ch);
			file.write((char*)&s.byte, sizeof(short));
		}
		else
		{
			file.seekg(0, ios::beg);
			file.write((char*)&s.byte, sizeof(short));
		}
	}
}

//***************************************************************
//    			DELETING THE DATA FROM SYSTEM
//***************************************************************

void delet(fstream& file, string search)
{

	int pos = -1;
	short  head, len, len2;
	employee e;
	for (int d = 0; d < i; d++)
	{
		if (prm[d].serial == search)
		{
			pos = d;
			break;
		}
	}
	if (pos == -1)
		cout << "  This ID is not find in this file !" << endl;
	else
	{
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(short));
		file.seekg(prm[pos].byte, ios::beg);
		file.read((char*)&len, sizeof(short));
		file.seekg(prm[pos].byte + 2, ios::beg);
		file.put('*');
		e.byte = head;
		file.write((char*)&e.byte, sizeof(short));
		file.put('|');
		file.seekp(0, ios::beg);
		head = prm[pos].byte;
		file.write((char*)&head, sizeof(short));
		for (int g = pos; g < i; g++)
		{
			for (int k = 0; k < 5; k++)
				prm[g].serial[k] = prm[g + 1].serial[k];
			prm[g].byte = prm[g + 1].byte;
		}
		i--;
	}
}

//***************************************************************
//    			UPDATING THE DATA IN THE SYSTEM
//***************************************************************

void update(fstream& file, string search)
{

	int pos = -1, c = 0;
	short len1, len2;
	employee e;
	for (int d = 0; d < i; d++)
	{
		if (prm[d].serial == search)
		{
			pos = d;
			break;
		}
	}
	if (pos >= 0)
	{
		for (int k = 0; k < 5; k++)
			e.serial[k] = prm[pos].serial[k];
		cout << "  ENTER THE NEW FIRST NAME:";         cin >> e.firstname;
		cout << "  ENTER THE NEW LAST NAME:";         cin >> e.lastname;
		cout << "  ENTER THE NEW AGE:";         cin >> e.age;
		cout << "  ENTER THE NEW DEPARTMENT:";         cin >> e.department;
		cout << "  ENTER THE NEW SALARY:";         cin >> e.salary;
		len1 = strlen(e.firstname) + strlen(e.lastname) + strlen(e.department) + 23;
		file.seekp(prm[pos].byte, ios::beg);
		file.read((char*)&len2, sizeof(short));
		string temp = e.serial;
		if (len1 <= len2)
		{
			file.seekp(prm[pos].byte, ios::beg);
			write(file, e, len1);

			for (int k = 0; k < j; k++)
				if (sec[k].serial == temp)
				{
					sec_array(e, k);
					break;
				}
		}
		else
		{
			delet(file, search);
			file.seekg(0, ios::end);
			write(file, e, len1);
			prm_array(e, i);
			for (int k = 0; k < j; k++)
				if (sec[k].serial == temp)
				{
					sec_array(e, k);
					break;
				}
			i++;
		}

	}
	else
		cout << "  This ID is not find in this file !" << endl;
}

//***************************************************************
//    			DISPLAYING ALL THE DATAS
//***************************************************************

void Display_All(fstream& file)
{

	employee e;
	if (i == 0)
		cout << "  This file is empty!" << endl;
	else
	{
		cout << endl;
		cout << "          EMP ID |  First name  |  Last name  | Age | Department |  Salary  " << endl;
		cout << "         ________|______________|_____________|_____|____________|__________" << endl;
		int khara;
		for (int k = 0; k < i; k++)
		{

			file.seekg(prm[k].byte, ios::beg);
			read(file, e);
			cout << "          " << e.serial << "   |  " << e.firstname;
			for (int k = 0; k < 11 - strlen(e.firstname); k++)
				cout << " ";
			cout << "|  " << e.lastname;
			for (int k = 0; k < 10 - strlen(e.lastname); k++)
				cout << " ";
			cout << "| " << e.age << "  | " << e.department;
			for (int k = 0; k < 11 - strlen(e.department); k++)
				cout << " ";
			cout << "|  " << e.salary << endl;
			cout << "                 |             |            |     |            |          " << endl;
			file.seekg(0, ios::beg);
		}
	}
}

//***************************************************************
//    			DISPLAYING ALL DEPARTMENT DETAILS
//***************************************************************

void display_department(fstream& file, string search)
{

	int pos = -1, count = 0;
	employee e;
	bool b = false;
	for (int k = 0; k < j; k++)
	{

		bool f = false;
		if (sec[k].department == search)
		{
			string temp = sec[k].serial;
			for (int d = 0; d < i; d++)
			{
				if (prm[d].serial == temp)
				{
					pos = d;
					break;
				}
			}
			if (pos >= 0)
			{
				count++;
				if (count == 1)
				{
					cout << endl;
					cout << "          EMP ID |  Firstname  |  Lastname  | Age | Department |  Salary  " << endl;
					cout << "         ________|_____________|____________|_____|____________|__________" << endl;
				}
				file.seekg(prm[pos].byte, ios::beg);
				read(file, e);
				cout << "          " << e.serial << "   |  " << e.firstname;
				for (int n = 0; n < 11 - strlen(e.firstname); n++)
					cout << " ";
				cout << "|  " << e.lastname;
				for (int n = 0; n < 10 - strlen(e.lastname); n++)
					cout << " ";
				cout << "| " << e.age << "  | " << e.department;
				for (int n = 0; n < 11 - strlen(e.department); n++)
					cout << " ";
				cout << "|  " << e.salary << endl;
				cout << "                 |             |            |     |            |          " << endl;
				b = true;

			}
			else
			{
				for (int g = k; g < j; g++)
				{
					for (int h = 0; h < 5; h++)
						sec[g].serial[h] = sec[g + 1].serial[h];
					for (int h = 0; h < 10; h++)
						sec[g].department[h] = sec[g + 1].department[h];
				}
				k--;
				j--;
			}
		}
	}
	if (b == false)
		cout << "  This department is not found!" << endl;
}

//***************************************************************
//    			SEARCHING BY EMPLOYEE ID
//***************************************************************

void search_by_serial(fstream& file, string search)
{

	int pos = -1, pos2;
	employee e;

	for (int d = 0; d < i; d++)
	{
		if (prm[d].serial == search)
		{
			pos = d;
			break;
		}
	}
	if (pos >= 0)
	{
		file.seekg(prm[pos].byte, ios::beg);
		read(file, e);
		cout << endl;
		cout << "          EMP ID |  Firstname  |  Lastname  | Age | Department |  Salary  " << endl;
		cout << "         ________|_____________|____________|_____|____________|__________" << endl;
		cout << "          " << e.serial << "   |  " << e.firstname;
		for (int k = 0; k < 11 - strlen(e.firstname); k++)
			cout << " ";
		cout << "|  " << e.lastname;
		for (int k = 0; k < 10 - strlen(e.lastname); k++)
			cout << " ";
		cout << "| " << e.age << "  | " << e.department;
		for (int k = 0; k < 11 - strlen(e.department); k++)
			cout << " ";
		cout << "|  " << e.salary << endl;
		cout << "                 |             |            |     |            |          " << endl;
	}
	else
		cout << "  This serial is not found!" << endl;
}

//***************************************************************
//    			CLOSING THE FILES
//***************************************************************

void exit()
{
	primaryindex();
	secondaryindex();
	cout << "  This file is closed, Tank you for using this system... !" << endl;
}
void cleanFile()
{
	fstream fin;
	fstream temp, index2, index1;
	fin.open("project.txt", std::ofstream::out | std::ofstream::trunc); fin.close();
	temp.open("temp_file.txt", std::ofstream::out | std::ofstream::trunc); temp.close();
	index2.open("index2.txt", std::ofstream::out | std::ofstream::trunc); index2.close();
	index1.open("index1.txt", std::ofstream::out | std::ofstream::trunc); index1.close();
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	fstream file;
	short header = -1;
	char ch = '0';
	int len = 0;
	string search;
	file.open("project.txt", ios::in | ios::out | ios::binary);
	if (file.is_open())
	{
		file.seekg(0, ios::end);
		int z = file.tellg();
		if (z == 0)
			file.write((char*)&header, sizeof(short));
		file.seekg(0);
		startup();

		while (1)
		{

			welcome();

			cin >> ch;
			if (ch == '1')
			{
				add(file);
			}
			else if (ch == '2')
			{

				cout << "  Enter the Employee ID which want to update:";
				cin >> search;
				update(file, search);
			}
			else if (ch == '3')
			{

				cout << "  Enter the Employee ID which want to delete:";
				cin >> search;
				delet(file, search);
			}
			else if (ch == '4')
			{
				Display_All(file);
			}
			else if (ch == '5')
			{

				cout << "  Enter the department which want to display:";
				cin >> search;
				for (int l = 0; l < 2; l++)
				{
					if (search.at(l) >= 65 && search.at(l) <= 90)
						search.at(l) += 32;
				}
				display_department(file, search);
			}
			else if (ch == '6')
			{

				cout << "  Enter the Employee ID which want to display:";
				cin >> search;
				search_by_serial(file, search);
			}


			else if (ch == '7')
			{

				exit();
				break;
			}

			system("pause");

			system("cls");
		}
	}
	else
	{
		cleanFile();
		return main();
	}

	file.close();
}


//***************************************************************
//    			END OF PROJECT
//***************************************************************

/* INPUTS TO BE GIVEN:
1

100
ahmed
naser
20
managment
50000



1
50
mohamed
aly
21
CS
450000



1
150
yhya
sayed
20
managment
50000



1
200
nasser
sayed
20
it
54000



0
*/

//***************************************************************
//    			END OF PROJECT
//***************************************************************

