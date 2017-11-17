/*

  main.c
  fctest

Fog Creek test program
Sort the characters in the following string:

abcdefghijklmnopqrstuvwxyz_

by the number of times the character appears in the following text (descending):
[elided]

Now take the sorted string, and drop all the characters after (and including) the _. The remaining word is the answer.

  Created by Howard S Shubs on 10/26/17.
  Copyright © 2017 Howard S Shubs. All rights reserved.
 
I'm making a few assumptions here.  Characters are one byte.  They're all effectively ASCII.
All characters are either within the range specified above, or we drop them on the floor quietly.

*/

/*
 *  Includes
 *
 */
#include <stdio.h>
#include <ctype.h>

/*
 *  typedefs
 *
 */
typedef struct associative
{
    char key;       // character the count is associated with
    unsigned int count;    // how many of these characters have we found?
} ASSOCIATIVE;

/*
 *  defines
 *
 */
#define CHARSET "abcdefghijklmnopqrstuvwxyz_"
#define ARRAY_SIZE 27

/*
 *  prototypes
 *
 */
void Init (ASSOCIATIVE sort[]);
void ReadIn (ASSOCIATIVE sort[]);
void SortIt (ASSOCIATIVE sort[]);
void Report (ASSOCIATIVE sort[]);

int main(int argc, const char * argv[])
{
    ASSOCIATIVE sort[ARRAY_SIZE];   // main sort array.  a == element 0, _ == element 26.

    // initialize array
    Init (sort);
    
    // process input file
    ReadIn (sort);

    // time to sort
    SortIt (sort);
    
    // report the result
    Report (sort);
    return 0;
}

/*
 *  Init
 *
 *  Initialize the array of ASSOCIATIVE structs.
 *
 */
void Init (ASSOCIATIVE sort[])
{
    unsigned short int ii;            // generic loop index

    for (ii = 0; ii < ARRAY_SIZE ; ii++)
    {
        sort[ii].key = CHARSET[ii];
        sort[ii].count = 0;
    }

}

/*
 *  ReadIn
 *
 *  Read the input file, counting the characters read in sort[].
 *
 */
void ReadIn (ASSOCIATIVE sort[])
{
    char thischar;                    // current character
    FILE *infile = fopen("/Users/hshubs/dev/fctest/fctest.txt", "r"); // open the input file readonly

    while (! feof (infile))
    {
        thischar = fgetc (infile);  // get next character
        if (islower (thischar))     // if character is alphabetic and lowercase
            sort[thischar - 'a'].count++;
        else if (thischar == '_')
            sort[26].count++;
        // else the character is not of interest.  Ignore it.
    };
    fclose (infile);    // done with the input file
}

/*
 *  SortIt
 *
 *  Sort the associative array by its COUNT member.  This is a short array, so I'm not going to
 *  worry about efficiency.  A bubble sort will do.  O(n^2) doesn't scare me here, but this actually
 *  uses a smaller number of iterations, so I may be misremembering which sort I'm using.  Regardless,
 *  it's written for "simple" rather than "efficient".
 *  Descending sort!
 *
 */
void SortIt (ASSOCIATIVE sort[])
{
    unsigned short int ii;  // generic outer loop index
    unsigned short int jj;  // generic inner loop index
    
    for (ii = 0; ii < ARRAY_SIZE-1; ii++)
        for (jj = ii+1; jj < ARRAY_SIZE; jj++)
        {
            if (sort[ii].count < sort[jj].count)
            {
                ASSOCIATIVE temp = sort[ii];   // save element

                sort[ii] = sort[jj];
                sort[jj] = temp;
            }
        }
}

/*
 *  Report
 *
 *  Report the result.
 *
 */
void Report (ASSOCIATIVE sort[])
{
    unsigned short ii = 0;  // generic loop index
    
    // emit characters until we find the underscore, then emit an end-of-line to make it pretty.
    while (sort[ii].key != '_')
        putchar (sort[ii++].key);
    putchar ('\n');
}
