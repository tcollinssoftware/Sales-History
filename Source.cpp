#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <algorithm>
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
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
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
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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

void readHistogram() {
	//Parse file
	ifstream infile("frequency.dat");
	//Declare string, int for line data
	string a;
	int b;

	//Iterating per line, a and b
	while (infile >> a >> b) {
		//Output a formatted with a space followed by
		cout << a << " ";
		//Iterate the range from 0 to b
		for (int i = 0; i < b; i++) {
			//Output asterisk
			cout << "*";
		}
		//Tailing newline
		cout << "\n";
	}
}

//Display menu and handle user input
void userMenu() {
	//Clear input
	cin.clear();
	//Output menu
	cout << "**************************\n"
		<< "* 1. Show all sales.     *\n"
		<< "* 2. Lookup item.        *\n"
		<< "* 3. Generate histogram. *\n"
		<< "* 4. Read histogram.     *\n"
		<< "* 5. Desc. histogram.    *\n"
		<< "* 6. Asc. histogram.     *\n"
		<< "* 7. Exit program.       *\n"
		<< "**************************\n";

	//Declare int for input
	int menuInput;
	//Take input
	cin >> menuInput;

	//If cin doesn't accept input assignment or input int doesn't fall within bounds
	if (!cin or menuInput < 1 or menuInput > 7) {
		//Clear input
		cin.clear();
		//Prompt for input again
		cout << "Please input a numeric choice from the menu.\n";
		//Ignore last input
		cin.ignore();
		//Recurse to menu function
		userMenu();
	}

	//Branch per input
	if (menuInput == 1) {
		//Call python method to display all item counts
		CallProcedure("countItems");
	}

	if (menuInput == 2) {
		//Declare string var for input for search
		string userIn;
		cout << "Which item do you want to search?\n";
		cin >> userIn;
		//Call python method to search a specific item and return count into output
		cout << callIntFunc("findItemCount", userIn) << "\n";
	}

	if (menuInput == 3) {
		//Call python method to generate histogram
		CallProcedure("generateHistogram");
		//Call C++ method to display histogram
		readHistogram();
	}

	//Output histogram raw
	if (menuInput == 4) {
		readHistogram();
	}

	//Output histogram descending
	if (menuInput == 5) {
		CallProcedure("descendingHistogram");
	}

	//Output histogram ascending
	if (menuInput == 6) {
		CallProcedure("ascendingHistogram");
	}

	if (menuInput == 7) {
		//Terminate
		exit;
	}

}

void main()
{
	//Call method for menu
	userMenu();
}