
#include </usr/include/python2.7/Python.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc , char *argv[])
{
	PyObject *pName , *pModule , *pDict , *pFunc;
	PyObject *pArgs , *pValue;


	Py_Initialize();

	PySys_SetPath("/tmp/test");

	pName = PyString_FromString(argv[1]);

	pModule = PyImport_Import(pName);

	if(pModule != NULL)
	{
		PyObject *pythonArgument;
		pythonArgument = PyTuple_New(1);
		pValue = PyString_FromString(argv[3]);


		if(pValue == NULL)
		{
			return 1;
		}

		
		PyTuple_SetItem(pythonArgument,0,pValue);
		pFunc = PyObject_GetAttrString(pModule,argv[2]);
		if (pFunc && PyCallable_Check(pFunc))
		{
			while (1){
			pValue = PyObject_CallObject(pFunc,pythonArgument);
				printf("Value returned from the function %s\n" ,PyString_AsString(pValue));
				sleep(5);
			}
		}
		else{
			if(PyErr_Occurred()){
				PyErr_Print();
				fprintf(stderr,"Cannot find function %s \n",argv[2]);

			}

		}
	}
	else{
		PyErr_Print();
		fprintf(stderr,"Faild to load %s \n",argv[1]);
		return 1;
	}
}
		
