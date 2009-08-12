


/* ************************************************************************
   *  File: utils.c                                              Part of ACT *
   *  Usage: various internal functions of a utility nature                  *
   *                                                                         *
   *  All rights reserved.  See license.doc for complete information.        *
   *                                                                         *
   *  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
   *  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
   ************************************************************************ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "act.h"

char buf[MAX_STRING_LENGTH], buf1[MAX_STRING_LENGTH], buf2[MAX_STRING_LENGTH];


/*
 * get_line reads the next non-blank line off of the input stream.
 * The newline character is removed from the input.  Lines which begin
 * with '*' are considered to be comments.
 *
 * Returns the number of lines advanced in the file.
 */
int get_line(FILE * fl, char *buf, FILE * actfile)
{
  char temp[256];
  int lines = 0;

  *temp = 0;
  do {
    if (*temp)
      fprintf(actfile, "%s\n", temp);
    lines++;
    fgets(temp, 256, fl);
    if (*temp)
      temp[strlen(temp) - 1] = '\0';
  } while (!feof(fl) && (*temp == '*' || !*temp));

  if (feof(fl))
    return 0;
  else {
    strcpy(buf, temp);
    return lines;
  }
}


/* read and allocate space for a '~'-terminated string from a given file */
void fread_string(FILE * fl, char *error, FILE * outfile)
{
  char buf[MAX_STRING_LENGTH], tmp[512];
  register char *point;
  int done = 0, length = 0, templength = 0;

  *buf = '\0';

  do {
    if (!fgets(tmp, 512, fl)) {
      fprintf(stderr, "SYSERR: fread_string: format error at or near %s\n",
	      error);
      exit(1);
    }
    /* If there is a '~', end the string; else an "\r\n" over the '\n'. */
    fputs(tmp, outfile);
    if ((point = strchr(tmp, '~')) != NULL)
      done = 1;

    templength = strlen(tmp);

    if (length + templength >= MAX_STRING_LENGTH) {
      fprintf(stderr, "SYSERR: fread_string: string too large (utils.c)");
      exit(1);
    }
  } while (!done);
}


FILE *get_outputfile(char *fn, int mode)
{
  char name[256];
  FILE *temp;

  if (mode == MODE_ACT)
    sprintf(name, "%s.new", fn);
  else {
    fprintf(stderr, "Illegal mode of %d in get_outputfile()\n", mode);
    exit(1);
  }

  if ((temp = fopen(name, "wt")) == NULL) {
    fprintf(stderr, "Unable to create outputfile in get_outputfile()\n");
    exit(1);
  }
  fprintf(stderr, "Output file is %s\n", name);
  return (temp);
}


char *bitvector_to_string(int number, char *words[])
{
  int highnum = 0, cnt = 1, index = 0;

  for (*buf = 0; number > 0; index++, cnt <<= 1) {
    if (*words[index] == '\n')
      highnum = 1;
    if (number & cnt) {
      if (*buf)
	strcat(buf, "|");
      if (!highnum && *words[index] && str_cmp(words[index], "!UNUSED!"))
	strcat(buf, words[index]);
      else {
	printf("Warning: Unknown bit value \"%d\"\n", cnt);
	sprintf(buf + strlen(buf), "BIT_%d", cnt);
      }
      number -= cnt;
    }
  }
  if (!(*buf))
    strcpy(buf, "0");
  return (buf);
}


char *select_to_string(int number, char *words[])
{
  int index;

  for (index = 0; *words[index] != '\n'; index++)
    if (index == number)
      return (words[index]);
  sprintf(buf1, "SELECT_%d", number);
  return (buf1);
}


int find_index(char *s, char *words[])
{
  int index;

  for (index = 0; *words[index] != '\n'; index++)
    if (!str_cmp(words[index], s))
      return (1 << index);

  return (-1);
}


long string_to_bitvector(char *s, char *words[])
{
  char dup[MAX_STRING_LENGTH], *ptr;
  long num = 0, temp;

  if (!str_cmp(s, "0"))
    return (0);

  strcpy(dup, s);
  ptr = strtok(dup, "|");
  while (ptr) {
    if ((temp = find_index(ptr, words)) < 0) {
      if (!strn_cmp(ptr, "BIT_", 4))
	temp = atol(ptr + 4);
      printf("Warning: Unknown Flag \"%s\"\n", ptr);
    }
    if (temp > -1)
      num |= temp;
    ptr = strtok(NULL, "|");
  }
  return (num);
}


long string_to_select(char *s, char *words[])
{
  int index;

  for (index = 0; *words[index] != '\n'; index++)
    if (!str_cmp(words[index], s))
      return (index);
  if (!strn_cmp(s, "SELECT_", 7))
    index = atol(s + 7);
  else
    index = 0;
  printf("Warning: Unknown Selection \"%s\"\n", s);
  return (0);
}


/* returns: 0 if equal, 1 if arg1 > arg2, -1 if arg1 < arg2  */
/* scan 'till found different or end of both                 */
int str_cmp(char *arg1, char *arg2)
{
  int chk, i;

  for (i = 0; *(arg1 + i) || *(arg2 + i); i++)
    if ((chk = tolower(*(arg1 + i)) - tolower(*(arg2 + i))))
      if (chk < 0)
	return (-1);
      else
	return (1);
  return (0);
}



/* returns: 0 if equal, 1 if arg1 > arg2, -1 if arg1 < arg2  */
/* scan 'till found different, end of both, or n reached     */
int strn_cmp(char *arg1, char *arg2, int n)
{
  int chk, i;

  for (i = 0; (*(arg1 + i) || *(arg2 + i)) && (n > 0); i++, n--)
    if ((chk = tolower(*(arg1 + i)) - tolower(*(arg2 + i))))
      if (chk < 0)
	return (-1);
      else
	return (1);

  return (0);
}

int
number (int from, int to)
{
  if (to < from) 
    return ((erandom () % (from - to + 1)) + to);
  return ((erandom () % (to - from + 1)) + from);
}

int add_resources(int sector)
{
  int x = 0;
  int ore, gold, gem, herb, mineral, timber, fertile, people;

  switch (sector) {
  case SECT_FIELD:
  case SECT_UNDRWLD_WILD:
    if (!(ore = number(0, 9)))
      x += RESOURCE_ORE;
    if (!(fertile = number(0, 3)))
      x += RESOURCE_FERTILE;
    if (!(people = number(0, 7)))
      x += RESOURCE_PEOPLE;
    break;    
  case SECT_FOREST:
    if (!(timber = number(0, 3)))
      x += RESOURCE_TIMBER;
    if (!(fertile = number(0, 9)))
      x += RESOURCE_FERTILE;
    if (!(people = number(0, 8)))
      x += RESOURCE_PEOPLE;
    break;    
  case SECT_HILLS:
    if (!(ore = number(0, 4)))
      x += RESOURCE_ORE;
    if (!(gold = number(0, 19)))
      x += RESOURCE_GOLD;   
    if (!(gem = number(0, 29)))
      x += RESOURCE_GEM;
    if (!(mineral = number(0, 4)))
      x += RESOURCE_MINERAL;
    if (!(people = number(0, 17)))
      x += RESOURCE_PEOPLE;
    break;
  case SECT_MOUNTAIN:
  case SECT_UNDRWLD_MOUNTAIN:
    if (!(ore = number(0, 3)))
      x += RESOURCE_ORE;
    if (!(gold = number(0, 14)))
      x += RESOURCE_GOLD;   
    if (!(gem = number(0, 19)))
      x += RESOURCE_GEM;
    if (!(mineral = number(0, 3)))
      x += RESOURCE_MINERAL;
    if (!(people = number(0, 27)))
      x += RESOURCE_PEOPLE;
    break;
  case SECT_DESERT:
  case SECT_ARCTIC:
    if (!(ore = number(0, 9)))
      x += RESOURCE_ORE;
    if (!(mineral = number(0, 9)))
      x += RESOURCE_MINERAL;
    if (!(people = number(0, 19)))
      x += RESOURCE_PEOPLE;
    break;
  case SECT_SWAMP:
  case SECT_UNDRWLD_MUSHROOM:
    if (!(herb = number(0, 9)))
      x += RESOURCE_HERB;
    break;
  case SECT_UNDRWLD_CITY:
  case SECT_INSIDE:
  case SECT_CITY:
  case SECT_WATER_SWIM:
  case SECT_WATER_NOSWIM:
  case SECT_NO_GROUND:
  case SECT_UNDERWATER:
  case SECT_UNDERWATER_GR:
  case SECT_FIREPLANE:
  case SECT_OCEAN:
  case SECT_UNDRWLD_INSIDE:
  case SECT_UNDRWLD_WATER:
  case SECT_UNDRWLD_NOSWIM:
  case SECT_UNDRWLD_NOGROUND:
  case SECT_AIR_PLANE:
  case SECT_WATER_PLANE:
  case SECT_EARTH_PLANE:
  case SECT_ETHEREAL:
  case SECT_ASTRAL:
  case SECT_UNDRWLD_SLIME:
  case SECT_UNDRWLD_LOWCEIL:
  case SECT_UNDRWLD_LIQMITH:
  case SECT_CASTLE_WALL:
  case SECT_CASTLE_GATE:
  case SECT_CASTLE:
    x = RESOURCE_NONE;
    break;
  }
  return x;
}
