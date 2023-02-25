#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int CallIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int CallIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
Description: To use, simply call.

Example: ClearScreen()

Output: Clears screen by printing 40 lines.

Return: None.
*/
void ClearScreen() 
{
	for (int i = 0; i < 40; ++i) {
		cout << endl;
	}
}

/*
Description: To use, simply call.

Example: DisplayMenu()

Output: Prints menu

Return: None
*/
void DisplayMenu() 
{
	cout << endl;
	cout << setw(44) << setfill('*') << "" << endl;
	cout << setw(20) << "";
	cout << "MENU";
	cout << setw(20) << "" << endl;
	cout << "[1]  List Items Sold" << endl;
	cout << "[2]  Find Item's Sales Frequency" << endl;
	cout << "[3]  Display Sales Chart" << endl;
	cout << "[4]  Exit" << endl;
}

/*
Description: To use, simply call.

Example: PrintHistogram()

Input: None. Calls python function WriteDataFile to produce frequency.dat which this function then uses to produce chart

Output: Prints histogram of each unique item in InputFile.txt showing their frequency

Return: Returns 1 if frequency.dat file fails to open. Otherwise, returns 0.
*/
int PrintHistogram()
{
	ifstream inFS;
	string itemName;
	int itemFrequency;

	// use python function to produce frequency.dat file
	CallProcedure("WriteDataFile");

	// open file
	inFS.open("frequency.dat");
	if (!inFS.is_open())
	{
		cout << "Could not open frequency.dat" << endl;
		return 1;
	}

	// print histogram
	while (!inFS.fail())
	{
		inFS >> itemName;
		inFS >> itemFrequency;

		if (inFS.eof()) { break; }

		cout << setfill(' ') << setw(12) << itemName << "|";

		for (int i = 0; i < itemFrequency; ++i)
		{
			cout << "*";
		}

		cout << endl;
	}

	// check that end of file was reached
	if (!inFS.eof())
	{
		cout << "Input error before reaching end of file." << endl;
	}

	// close file
	inFS.close();

	return 0;
}

void main()
{
	char userInput = '\0';
	string userItem;

	ClearScreen();
	while (userInput == '\0')
	{
		DisplayMenu();

		// Get input from user. Ignore all but first character.
		cin >> userInput;
		cin.ignore(10000, '\n');

		// If user enters 1 use python to print each unique item and its frequency.
		if (userInput == '1')
		{
			ClearScreen();
			CallProcedure("PrintSalesList");
			
			userInput = '\0';
			continue;
		}
		// If user enters 2 get user to input item name then use python to print that item's frequency.
		else if (userInput == '2')
		{
			ClearScreen();
			
			cout << "Enter item name: ";
			cin >> userItem;
			
			cout << endl << userItem << ": ";
			cout << CallIntFunc("PrintItemsSales", userItem) << endl;

			userInput = '\0';
			continue;
		}
		// If user enters 3 print a histogram showing each item and its frequency.
		else if (userInput == '3')
		{
			ClearScreen();
			PrintHistogram();
			
			userInput = '\0';
			continue;
		}
		// If user enters 4 exit the program.
		else if (userInput == '4')
		{
			ClearScreen();
			cout << "Goodbye";
			
			userInput = '\0';
			break;
		}
		// If user enters anything else prompt use for a valid input.
		else
		{
			ClearScreen();
			cout << "Enter valid selection.";
			
			userInput = '\0';
			continue;
		}
	}
}