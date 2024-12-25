#define _CRT_SECURE_NO_WARNINGS  1
#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <synchapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>
#include <processthreadsapi.h>
#include <io.h>

/// <summary>
/// This function will execute the FSM providing the input and output file names as arguments
/// </summary>
/// <param name="exeFilePathAndName"></param>
/// <param name="inputFilePathAndName"></param>
/// <param name="outputFilePathAndName"></param>
/// <returns></returns>
int ExecProgram (char* exeFilePathAndName, char* inputFilePathAndName, char* outputFilePathAndName) {
   char* cmdline = malloc (strlen (exeFilePathAndName) + strlen (inputFilePathAndName) + strlen (outputFilePathAndName) + 3);
   if (cmdline == NULL) {
      printf ("Unable to allocate memory\n");
      return 1;
   }
   sprintf (cmdline, "%s%s%s%s%s", exeFilePathAndName, " ", inputFilePathAndName, " ", outputFilePathAndName);

   // Set up structures for process information
   STARTUPINFOA si;
   PROCESS_INFORMATION pi;

   // Initialize memory for STARTUPINFO and PROCESS_INFORMATION structures
   ZeroMemory (&si, sizeof (si));
   si.cb = sizeof (si);
   ZeroMemory (&pi, sizeof (pi));

   // Attempt to create the process
   if (!CreateProcessA (
      NULL,            // Application name (NULL if using command line)
      cmdline,          // Command line (path to the executable)
      NULL,            // Process handle not inheritable
      NULL,            // Thread handle not inheritable
      FALSE,           // Set handle inheritance to FALSE
      0,               // No creation flags
      NULL,            // Use parent's environment block
      NULL,            // Use parent's starting directory
      &si,             // Pointer to STARTUPINFO structure
      &pi))            // Pointer to PROCESS_INFORMATION structure
   {
      // If CreateProcess fails, print an error message
      int err = GetLastError ();
      printf ("Failed to start process. Error: %lu\n", GetLastError ());
      free (cmdline);
      return 1;
   }

   // Wait until the process has finished execution
   WaitForSingleObject (pi.hProcess, INFINITE);

   // Close handles
   CloseHandle (pi.hProcess);
   CloseHandle (pi.hThread);

   free (cmdline);
   return 0;

}

/// <summary>
/// Test Harness
/// </summary>
/// <param name="argc"></param>
/// <param name="argv">argv[1] is the name of the FSM</param>
/// <returns></returns>
int main (int argc, char** argv) {
#define NTESTS 5
   printf ("FSM Test Harness\n");
   if (argc != 2) {
      printf ("Usage: %s <FSM executable name>\n,", argv[0]);
      return -1;
   }
   for (int i = 0; i < NTESTS; i++) {
      char input[260], reference[260];
      sprintf (input, "test%din.txt", i + 1);
      char* output = "C:\\etc\\tempOut.txt";
      sprintf (reference, "reference%d.txt", i + 1);
      if (ExecProgram (argv[1], input, output) != 0) printf ("Error executing test %d\n", i + 1);
      else {
         FILE* rfp = fopen (reference, "r"), * ofp = fopen (output, "r");
         if (rfp == NULL) printf ("Reference output file does not exist");
         else if (ofp == NULL) printf ("Temporary output file does not exist");
         else {
            int refFilesize = filelength (fileno (rfp)) + 1,
               outFilesize = filelength (fileno (ofp)) + 1, j = 0;
            char* refFileContent = (char*)malloc (refFilesize * sizeof (char)),
               * outFileContent = (char*)malloc (outFilesize * sizeof (char));
            fgets (refFileContent, refFilesize, rfp);
            fgets (outFileContent, outFilesize, ofp);
            char refFileChar = refFileContent[j], outFileChar = outFileContent[j];
            if (refFileChar == '\0' || outFileChar == '\0') printf ("File has no content!");
            else {
               int charNum = 0;
               while (refFileChar != '\0' || outFileChar != '\0') {
                  charNum++;
                  if (refFileChar != outFileChar) {
                     printf ("Error testing %s: Error at bit no. %d, Expected %c, Actual %c\n", input, charNum, outFileChar, refFileChar);
                     break;
                  }
                  refFileChar = refFileContent[++j];
                  outFileChar = outFileContent[j];
               }
               free (refFileContent);
               free (outFileContent);
               if (refFileChar == outFileChar) printf ("No error testing %s\n", input);
            }
         }
      }
   }
}