#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// split a file in n-pieces with length of kbyte
void splitFile(int kbyte, char* fileName)
{
   FILE *streamIn;
   FILE *streamOut; 
   char *list = new char[kbyte];
   int  numread;
   char fileOut[128];
   int countFile = 0;

   /* Open file */
   if( (streamIn = fopen(fileName, "rb" )) == NULL ) {
      cout << "Problem opening the file " << fileName << endl;
    cout << "(" << strerror( errno ) << ")" << endl;
    return;
   }

   do {
    numread = fread( list, sizeof( char ), kbyte, streamIn );
    if (numread > 0) {
      sprintf(fileOut, "%s.l%d", fileName, countFile);
      if( (streamOut = fopen(fileOut, "wb" )) != NULL ) {
        fwrite( list, sizeof( char ), numread, streamOut );
        fclose(streamOut);
        countFile++;
      } else {
        cout << "Problem opening the file "<< fileOut << endl;
        break;
      }
    }  
   } while (numread == kbyte);
    
   delete []list;
   fclose(streamIn);
}

// join del file <filename>
void joinFile(char* fileName)
{
   FILE *streamIn;
   FILE *streamOut; 
   char list[1];
   int  numread;
   char fileIn[128];
   int countFile = 0;
   int openFlag = 0;

   sprintf(fileIn, "%s.l%d", fileName, countFile);
   while ((streamIn = fopen(fileIn, "rb" )) != NULL) {
     
     if (!openFlag) {
      /* open the file to be written */
      if( (streamOut = fopen(fileName, "w+b" )) == NULL ) {
        cout << "Problem opening the file " << fileName << endl;
        return;
      }
     }

     while (1) {
      numread = fread( list, sizeof( char ), 1, streamIn );
      if (numread < 1)  break;
      fwrite( list, sizeof( char ), numread, streamOut );    
     }
     fclose(streamIn);

     countFile++;
     sprintf(fileIn, "%s.l%d", fileName, countFile);
   }

   fclose(streamOut);
}

int main(int argc, char* argv[])
{
  if (argc < 3) {
    cout << "usage: lsplit [-b <files size (byte)>|-j] <filename>" << endl;
    cout << "-b -> to split a file" << endl;
    cout << "-j -> to join files\n" << endl;
    return 0;
  }

  if (strcmp(argv[1], "-b") == 0) {
    splitFile(atoi(argv[2]), argv[3]);
  } else if (strcmp(argv[1], "-j") == 0) { 
    joinFile(argv[2]);
  }

  return 0;
}