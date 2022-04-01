#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include "/u01/app/ogg/usrdecs.h"
#include </usr/include/python3.9/Python.h>


char *cstrret = NULL;
PyObject *mymod , *strfunc , *strargs , *strret = NULL;

void ERCALLBACK(ercallback_function_codes fundtion_code,
                void *buf, short *presult_code)
{
}


void close_callback (void)
{
}


void call_callback (ercallback_function_codes function_code,
                    void *buf , short *result_code)
                    {
                        ERCALLBACK(function_code , buf , result_code);
                    }


void info(char *msg, ...)
{
    short result_code;
    char info_msg[1000];

    va_list args;
    va_start(args, msg);
    vsprintf(info_msg, msg, args);
    va_end(args);

    call_callback(OUTPUT_MESSAGE_TO_REPORT, info_msg, &result_code);
}


void CUSEREXIT(exit_call_type_def exit_call_type,
               exit_result_def *exit_call_result,
               exit_params_def *exit_params)
{


    switch (exit_call_type)
    {
    case EXIT_CALL_START:
        info("\nUser exit: EXIT_CALL_START\n");
        Py_Initialize();
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_START)\n");
            info("Getting Python information\n");
            info("Prefix: %s\nExec Prefix: %s\nPython Path: %s\n",
            Py_GetPrefix(),
            Py_GetExecPrefix(),
            Py_GetProgramFullPath());
            info("Module Path: %s\n",
            Py_GetPath());
            info("Version: %s\nPlatform: %s\nCopyright: %s\n",
            Py_GetVersion(),
            Py_GetPlatform(),
            Py_GetCopyright());
            info("Compiler String: %s\nBuild Info: %s\n",
            Py_GetCompiler(),
            Py_GetBuildInfo());


            mymod = PyImport_ImportModule("reverse");
            if(!mymod == NULL)
            {
                info("Python module imported successfully .");
            }
            else
            {
                info("Unable to import python module .");
            }

            strfunc = PyObject_GetAttrString(mymod,"rstring");
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_START)\n");
        }
        break;
    case EXIT_CALL_STOP:
        info("\nUser exit: EXIT_CALL_STOP\n");
        Py_Finalize();
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_STOP)\n");

            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_STOP)\n");
        }
        break;
    case EXIT_CALL_PROCESS_MARKER:
        info("\nUser exit: EXIT_CALL_PROCESS_MARKER\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_PROCESS_MARKER)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_PROCESS_MARKER)\n");
        }
        break;
    case EXIT_CALL_FATAL_ERROR:
        info("\nUser exit: EXIT_CALL_FATAL_ERROR\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_FATAL_ERROR)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_FATAL_ERROR)\n");
        }
        break;
    case EXIT_CALL_BEGIN_TRANS:
        info("\nUser exit: EXIT_CALL_BEGIN_TRANS\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_BEGIN_TRANS)\n");
            //return 0;
        }
        elsePURGEOLDEXTRACTS /ggs/dirdat/AA*, USECHECKPOINTS
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_END_TRANS)\n");
        }
        break;
    case EXIT_CALL_PROCESS_RECORD:
        info("User exit: EXIT_CALL_PROCESS_RECORD\n");

        strargs = Py_BuildValue ("(s)","Hello World");

        strret = PyObject_CallObject (strfunc , strargs);

        PyArg_Parse(strret , "s" , &cstrret);

        info("Reversed string from python call inside (EXIT_CALL_PROCESS_RECORD) : %s\n",cstrret);

        *exit_call_result = EXIT_IGNORE_VAL;
        return;
        break;
    case EXIT_CALL_CHECKPOINT:
        info("\nUser exit: EXIT_CALL_CHECKPOINT\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_CHECKPOINT)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_CHECKPOINT)\n");
        }
        break;
    case EXIT_CALL_DISCARD_RECORD:
        info("\nUser exit: EXIT_CALL_DISCARD_RECORD\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_DISCARD_RECORD)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_DISCARD_RECORD)\n");
        }
        break;
    case EXIT_CALL_DISCARD_ASCII_RECORD:
        info("\nUser exit: EXIT_CALL_DISCARD_ASCII_RECORD\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_DISCARD_ASCII_RECORD)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_DISCARD_ASCII_RECORD)\n");
        }
        break;
    case EXIT_CALL_ABORT_TRANS:
        info("\nUser exit: EXIT_CALL_ABORT_TRANS\n");
        if (Py_IsInitialized())
        {
            info("\nPython interpreter initialized successfully . (EXIT_CALL_ABORT_TRANS)\n");
            //return 0;
        }
        else
        {
            info("\nUnable to initialize Python interpreter. (EXIT_CALL_ABORT_TRANS)\n");
        }
        break;
    }
}
