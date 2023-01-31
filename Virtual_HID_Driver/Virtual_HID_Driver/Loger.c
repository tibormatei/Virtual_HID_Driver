#include "Loger.h"
#include <stdio.h>

#define LOG_FILE_PATH "C:\\temp\\driver_log_file.txt"


FILE *fptr = NULL;

void write_log_message(const char* message)
{
    errno_t err = 1;

    if (fptr == NULL)
    {
        err = fopen_s(&fptr, LOG_FILE_PATH, "a");
    }
    if ((err != 0) && (message != NULL))
    {
        fprintf(fptr, "%s\n", message);
    }
}

void close_logger()
{
    if (fptr != NULL)
    {
        fclose(fptr);
    }
}
