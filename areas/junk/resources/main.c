

/* ************************************************************************
   *  File: main.c                                               Part of ACT *
   *  Usage: Loading/saving chars, booting/resetting world, internal funcs   *
   *                                                                         *
   *  All rights reserved.  See license.doc for complete information.        *
   *                                                                         *
   *  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
   *  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
   ************************************************************************ */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "act.h"


#define AREA_LIST	"AREA.RES"
#define WLD_DIR		"wld"

#define MODE_WLD	0
#define MODE_MOB	1
#define MODE_OBJ	2



void discrete_load(FILE * fl, int mode, char *fn, int actmode)
{
  int nr = -1, last = 0;
  char line[256];
  FILE *actfile;

  actfile = get_outputfile(fn, actmode);
  for (;;) {
    /*
     * we have to do special processing with the obj files because they have
     * no end-of-record marker :(
     */
    if (!get_line(fl, line, actfile)) {
      fprintf(stderr, "EOF reached.\n");
      return;
    } else
      fprintf(actfile, "%s\n", line);
    if (*line == '$') {
      fclose(actfile);
      fprintf(stderr, "EOF marker reached.\n");
      return;
    }
    if (*line == '#') {
      last = nr;
      if (sscanf(line, "#%d", &nr) != 1) {
	fprintf(stderr, "Format error after wld #%d\n", last);
	exit(1);
      }
      if (nr >= 9999999) {
	fprintf(actfile, "$~\n");
	fclose(actfile);
	fprintf(stderr, "Too high vnums.\n");
	return;
      } else
	parse_room(fl, nr, actfile);
    } else {
      fprintf(stderr, "Format error in wld file near #%d\n", nr);
      fprintf(stderr, "Offending line: '%s'\n", line);
      exit(1);
    }
  }
}


void usage(char *arg)
{
  printf("\nUsage: %s world <file1> [file2] ...\n", arg);
  exit(0);
}


int get_actmode(char *arg)
{
  if (!strcmp(arg, "act"))
    return (MODE_ACT);
  else if (!strcmp(arg, "unact"))
    return (MODE_UNACT);
  fprintf(stderr, "ERROR: Unknown direction for get_actmode() (main.c)\n");
  exit(1);
}

void punt(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void main()
{
    FILE *area_list, *tmp_wld;
    char area[8192], area_name[80], wld_name[80];
    int area_count, wld_count;

    /*	Open the wld files up */
    area_list = fopen(AREA_LIST, "r");
    if (area_list==NULL)
	punt("AREA file cannot be opened");

    area_count = 0;
    wld_count = -1;
    for (;;) {
	fgets(area, 8191, area_list);
	if (area==NULL)
	    break;
	if (feof(area_list))
	    break;
	if (area[0]=='*')		/* a comment */
	    continue;
	area_count++;
	sscanf(area, "%s", area_name);
	/* open up individual wld for each area */
	sprintf(wld_name, "%s/%s.wld", WLD_DIR, area_name);
        printf("Working on file \"%s\"...", wld_name);
	tmp_wld = fopen(wld_name, "r");
        if (tmp_wld==NULL) {
            fprintf(stdout, "\twarning: %s not found\n", wld_name);
        }
        else {
          discrete_load(tmp_wld, 0, wld_name, MODE_ACT);
          fclose(tmp_wld);
        }

    }

    fclose(area_list);
    fprintf(stdout, "Done\n");
}
