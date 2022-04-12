#include <stdio.h>
#include <unistd.h>
#include </usr/include/python3.8/Python.h>


int main()
{
	PyObject* mymod , *strret , *strfunc , *strargs;
	FILE* file_py = fopen("/home/mh-jalali/Oracle/orafana/src/example/main_python.py","r");
	char *cstrret;
	Py_Initialize();
	//mymod = PyImport_ImportModule ("main_python");
	//strfunc = PyObject_GetAttrString(mymod , "rstring");
	//strargs = Py_BuildValue ("(s)" , "Hello World!");
	//strret = PyObject_CallObject(strfunc , strargs);
	//PyArg_Parse(strret , "s" , &cstrret);
	//printf("Result from python %s\n " , cstrret);
	PyRun_SimpleFile(file_py , "main_python.py");
	printf("Hello\n");
	if(Py_IsInitialized())
	{
		printf("Python is still ok");
	}
	else
	{
		printf("Python is dead");
	}
	Py_Finalize();
	return 0;   
}

