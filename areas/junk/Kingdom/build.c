#include <stdio.h>
#include <string.h>

void main(void)
{
  int x;
  FILE *fp;

  fp = fopen("castle_rooms.wld", "wt");
  for (x = 48000; x < 49000; x++) {
    fprintf(fp, "#%d\n", x);
    fprintf(fp, "Unnamed~\n~\n0 4104 0\nS\n");
  }
  fclose(fp);
}
