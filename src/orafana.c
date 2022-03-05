#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include "/home/mh-jalali/Oracle/OGG/usrdecs.h"
#include </usr/include/python2.7/Python.h>

void ERCALLBACK(ercallback_function_codes fundtion_code,
                void *buf, short *presult_code)
{
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
    short result_code;
    static short callback_opened = 0;
    char table_name;
    char column_name;
    char *cstr;
    PyObject *pName , *pModule , *pFunc , *pArgs , *pValue;



    switch (exit_call_type)
    {
    case EXIT_CALL_START:
        //TODO : Import Python Module
        //TODO : Check For Import faild or not
        info("EXIT_CALL_START is called.");
        Py_Initialize();
        if (!Py_IsInitialized())
        {
            info("Unable to initialize Python interpreter.");
        }
        else
        {
            info("Python interpreter initialized successfully");
            info("Prefix: %s\nExec Prefix: %s\nPython Path: %s\n" , Py_GetPrefix() , Py_GetExecPrefix() , Py_GetProgramFullPath());
            info("Module Path: %s\nVersion: %s\nPlatform: %s\n" , Py_GetPath() , Py_GetVersion() , Py_GetPlatform());
            info("Copyright:: %s\nCompiler String: %s\nBuild Info: %s\n" , Py_GetCopyright() , Py_GetCompiler() , Py_GetBuildInfo());
        }
        info("\n");
        break;

    case EXIT_CALL_STOP:
        info("");
        Py_FinalizeEx();
        info("");
        break;
    case EXIT_CALL_PROCESS_RECORD:
        info("");
        pValue = PyObject_CallObject(pFunc , pArgs);
        if (pValue != NULL)
        {
            info("");
            Py_DECREF(pValue);
        }
        else
        {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            info("");
        }
        break;
    case EXIT_CALL_PROCESS_MARKER:
        info("");
        break;
    case EXIT_CALL_FATAL_ERROR:
        info("");
        break;
    case EXIT_CALL_BEGIN_TRANS:
        info("");
        break;
    case EXIT_CALL_END_TRANS:
        info("");
        break;
    case EXIT_CALL_CHECKPOINT:
        info("");
        break;
    case EXIT_CALL_DISCARD_RECORD:
        info("");
        break;
    case EXIT_CALL_DISCARD_ASCII_RECORD:
        info("");
        break;
    case EXIT_CALL_ABORT_TRANS:
        info("");
        break;
    }
}