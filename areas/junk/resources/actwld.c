
/* ************************************************************************
   *  File: actwld.c                                             Part of ACT *
   *  Usage: Loading/saving chars, booting/resetting world, internal funcs   *
   *                                                                         *
   *  All rights reserved.  See license.doc for complete information.        *
   *                                                                         *
   *  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
   *  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
   ************************************************************************ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "act.h"

char buf[8192], buf1[8192], buf2[8192];
extern char *room_bits[];
extern char *sector_types[];

void setup_dir(FILE * fl, int virtual_nr, int dir, FILE * outfile);



/* load the rooms */
void parse_room(FILE * fl, int virtual_nr, FILE * actfile)
{
  int t[10];
  char line[256];

  sprintf(buf2, "room #%d", virtual_nr);
  fread_string(fl, buf2, actfile);	/* room name */
  fread_string(fl, buf2, actfile);	/* room description */

  if (!get_line(fl, line, actfile) ||
      sscanf(line, " %d %d %d ", t, t + 1, t + 2) != 3) {
    fprintf(stderr, "Format error in room #%d, expected 3 ints.\n", virtual_nr);
    exit(1);
  }
  /* t[0] is the zone number; ignored with the zone-file system, but not here */

#if 0
  fprintf(actfile, "%d %s %s\n", t[0], bitvector_to_string(t[1], room_bits),
	  select_to_string(t[2], sector_types));
#else
  fprintf(actfile, "%d %d %d %d\n", t[0], t[1], t[2], add_resources(t[2]));
#endif

  sprintf(buf, "Format error in room #%d (expecting D/E/S)", virtual_nr);

  for (;;) {
    if (!get_line(fl, line, actfile)) {
      fprintf(stderr, "%s\n", buf);
      exit(1);
    }
    switch (*line) {
    case 'D':
      fprintf(actfile, "%s\n", line);
      setup_dir(fl, virtual_nr, atoi(line + 1), actfile);
      break;
    case 'E':
      fprintf(actfile, "%s\n", line);
      fread_string(fl, buf2, actfile);	/* Keywords */
      fread_string(fl, buf2, actfile);	/* Description */
      break;
    case 'S':			/* end of room */
      fprintf(actfile, "%s\n", line);
      return;
      break;
    default:
      fprintf(stderr, "%s\n", buf);
      exit(1);
      break;
    }
  }
}



/* read direction data */
void setup_dir(FILE * fl, int virtual_nr, int dir, FILE * outfile)
{
  int t[5];
  char line[256];

  sprintf(buf2, "room #%d, direction D%d", virtual_nr, dir);

  fread_string(fl, buf2, outfile);	/* Description */
  fread_string(fl, buf2, outfile);	/* Door Keywords */

  if (!get_line(fl, line, outfile)) {
    fprintf(stderr, "Format error, %s\n", buf2);
    exit(1);
  }
  if (sscanf(line, " %d %d %d ", t, t + 1, t + 2) != 3) {
    fprintf(stderr, "Format error, %s\n", buf2);
    exit(1);
  }
  fprintf(outfile, "%d %d %d\n", t[0], t[1], t[2]);	/* Key, To Room */
}
