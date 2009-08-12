#ifndef _OBJRENT_H_

#include "types.h"

#ifndef FALSE
  #define FALSE  0
#endif

#ifndef TRUE
  #define TRUE  1
#endif

usint getkey(void)
{
  return getchar();  // blah
}

void _outtext(char *strn)
{
  cout << strn;
}

#define _OBJRENT_H_
#endif
