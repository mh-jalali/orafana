#include </usr/include/python2.7/Python.h>
#include <unistd.h>

int main()
{
    /*Set up the variables to hold methods, functions and class
      instances. farenheit will hold our return value  
    */
    PyObject *ret, *mymod, *class, *method, *args, *object;
    float farenheit;

    Py_Initialize();


    /* Make sure Python interpreter initialized successfully*/ 
    if (!Py_IsInitialized())
    {
        printf("Unable to initialize Python interpreter.");
        return 0;
    }
    
    /* Setting PYTHONPATH*/ 
    PySys_SetPath("/tmp/w");

    /* Load our module */
    mymod = PyImport_ImportModule("celsius");


    printf("Python interpreter initialized successfully\n");
    printf("Prefix: %s\nExec Prefix: %s\nPython Path: %s\n" , Py_GetPrefix() , Py_GetExecPrefix() , Py_GetProgramFullPath());
    printf("Module Path: %s\nVersion: %s\nPlatform: %s\n" , Py_GetPath() , Py_GetVersion() , Py_GetPlatform());
    printf("Copyright:: %s\nCompiler String: %s\nBuild Info: %s\n" , Py_GetCopyright() , Py_GetCompiler() , Py_GetBuildInfo());

    /* If we do't get a Python object back there was a problem */ 
    if (mymod == NULL)
    {
        printf("Can't open module");
    }

    /* Find the class*/
    class = PyObject_GetAttrString(mymod, "celsius");

    /* If found the class we can dump mymod , since we won't use it again */ 
    Py_DECREF(mymod);

    /* Make sure we got an object back*/
    if (class == NULL)
    {
        Py_DECREF(class);
        printf("Can't find class");
    }

    /* Build the argument call to our class - there are the arguments  
        that will be supplied when the object is created */
    args = Py_BuildValue("(f)", 200.0);

    if (args == NULL)
    {
        Py_DECREF(args);
        printf("Can't build argument list for class instance");
    }

    /* Create a new instance of our class by calling the class 
        with our argument list*/ 
    object = PyEval_CallObject(class, args);
    if (object == NULL)
    {
        Py_DECREF(object);
        printf("Can't create object instance");
    }

    /* Decrement the argument counter as we'll be using this again */
    Py_DECREF(args);

    /* Get the object method - note we use the object as the object
        from which we access the attribute by name, not the class */
    method = PyObject_GetAttrString(object, "farenheit");
    if (method == NULL)
    {
        Py_DECREF(method);
        printf("Can't find method");
    }

    /* Decrement the counter for our object, since we now jsut need 
        the method reference*/
    Py_DECREF(object);
     
    /* Build our arguments list - an empty tuple because there aren't 
        any arguments */
    args = Py_BuildValue("()");

    if (args == NULL)
    {
        Py_DECREF(args);
        printf("Can't build argument list for method call");
    }

    /* Call our object method with arguments */   
    ret = PyEval_CallObject(method, args);

    if (ret == NULL)
    {
        Py_DECREF(ret);
        printf("Couldn't call method");
    }

    /* Convert the return value back into a C variable and display it */
    PyArg_Parse(ret, "f", &farenheit);
    printf("Farenheit: %f\n", farenheit);

    /* Kill the remaining objects we don't need */
    Py_DECREF(method);
    Py_DECREF(ret);
    /* Close off the interpreter and terminate */
    Py_Finalize();

    return 0;
}
