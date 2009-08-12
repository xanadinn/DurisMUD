// ADDIG.CPP - it rocks, baby

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INLINEDEF

#include "addig.h"

#include "misc/strings.cpp"

#include "types.h"
#include "misc/strnnode.cpp"
#include "misc/keywords.cpp"
#include "edesc/edesc.cpp"
#include "obj/object.h"
#include "mob/mob.h"
#include "keys.h"

dikuObject *objectHead = NULL, *obj;
dikuMob *mobHead = NULL, *mob;

ulong numbLookupEntries = 200000, numbObjTypes = 0, madeChanges = FALSE,
      numbMobTypes = 0;

ulong lowestObjNumber = numbLookupEntries;   // handy
ulong highestObjNumber = 0;

ulong lowestMobNumber = numbLookupEntries;   // handy
ulong highestMobNumber = 0;

dikuObject **objLookup = new dikuObject*[numbLookupEntries];
dikuMob **mobLookup = new dikuMob*[numbLookupEntries];

void createPrompt(void) {}

#include "obj/object.cpp"
#include "obj/readobj.cpp"
#include "obj/writeobj.cpp"

#include "mob/mob.cpp"
#include "mob/readmob.cpp"
#include "mob/writemob.cpp"

#include "obj/delobjt.cpp"
#include "mob/delmobt.cpp"

//
// main
//

char main(char argc, char *argv[])
{
  FILE *areaFile;
  char strn[256], strn2[256], filename[256], material[256], keystrn[256],
       promptEm = TRUE, ch;
  ulong i, len, line = 0, onefile = FALSE;
  stringNode *kh;
  dikuObject *obj;
  dikuMob *mob;
  stringNode *sn, *old;


  if (!objLookup || !mobLookup)
  {
    cout << "Insufficient memory to run\n";
    return 1;
  }

  memset(objLookup, 0, sizeof(dikuObject *) * numbLookupEntries);
  memset(mobLookup, 0, sizeof(dikuMob *) * numbLookupEntries);

  if (argc > 1)
  {
    strcpy(strn, argv[1]);
    onefile = TRUE;
  }
  else
  {
    if ((areaFile = fopen("AREA", "rt")) == NULL)
    {
      cout << "couldn't open AREA, aborting..\n";
      exit(1);
    }
  }

 // read AREA file

  while (TRUE)
  {
    if (!onefile) if (!fgets(strn, 256, areaFile)) break; // eof
    line++;

    nolf(strn);
    len = strlen(strn);

   // remove comments

    //cout << "removing comments from line " << line << "..\n";

    for (i = 0; i < len; i++)
    {
      if (strn[i] == '*')
      {
        strn[i] = '\0';
        break;
      }
    }

    remTrailingSpaces(strn);
    remLeadingSpaces(strn);
    if (!strlen(strn)) continue;  // no filename

    sprintf(filename, "obj/%s", strn);

    cout << "attempting to read file " << filename << "..\n";

    if (!readObjectFile(filename))
    {
      cout << "couldn't open " << filename << ".obj" << endl;

      if (!onefile) continue;
      else return 1;
    }

   // check for objects with keyword _ignore_

    obj = objectHead;
    while (obj)
    {
      if (scanKeyword("_IGNORE_", obj->keywordListHead))
      {
        obj->extraBits.objExtraBits.ignoreItem = 1;

       // delete _ignore_ keyword..

        sn = obj->keywordListHead;
        old = NULL;

        while (sn)
        {
          if (!strcmp(sn->string, "_IGNORE_"))
          {
            if (sn == obj->keywordListHead)
            {
              obj->keywordListHead = obj->keywordListHead->Next;
              if (obj->keywordListHead) obj->keywordListHead->Last = NULL;

              delete sn;

            cout << "deleted _ignore_ keyword from obj #" << obj->objNumber << endl;
              break;
            }
            else
            {
              if (!old)
              {
                cout << "error.." << endl;
                break;
              }

              old->Next = sn->Next;
              if (sn->Next) sn->Next->Last = old;

              delete sn;

            cout << "deleted _ignore_ keyword from obj #" << obj->objNumber << endl;
              break;
            }
          }

          old = sn;
          sn = sn->Next;
        }
      }

      obj = obj->Next;
    }

    cout << filename << ".obj read and converted, writing..\n";

    writeObjectFile(filename);

    while (objectHead)
    {
      obj = objectHead->Next;

      deleteObjectType(objectHead, FALSE);
      objectHead = obj;
    }

    lowestObjNumber = numbLookupEntries;   // handy
    highestObjNumber = 0;

    memset(objLookup, 0, numbLookupEntries * sizeof(dikuObject*));

   // now, read mob file

    sprintf(filename, "mob/%s", strn);

    cout << "attempting to read file " << filename << "..\n";

    if (!readMobFile(filename))
    {
      cout << "couldn't open " << filename << ".mob" << endl;

      if (!onefile) continue;
      else return 1;
    }

   // check for mobs with keyword _IGNORE_

    mob = mobHead;
    while (mob)
    {
      if (scanKeyword("_IGNORE_", mob->keywordListHead))
      {
        mob->actionBits.mobActionBits.ignoreMob = 1;

       // delete _IGNORE_ keyword..

        sn = mob->keywordListHead;
        old = NULL;

        while (sn)
        {
          if (!strcmp(sn->string, "_IGNORE_"))
          {
            if (sn == mob->keywordListHead)
            {
              mob->keywordListHead = mob->keywordListHead->Next;
              if (mob->keywordListHead) mob->keywordListHead->Last = NULL;

              delete sn;

            cout << "deleted _IGNORE_ keyword from mob #" << mob->mobNumber << endl;
              break;
            }
            else
            {
              if (!old)
              {
                cout << "error.." << endl;
                break;
              }

              old->Next = sn->Next;
              if (sn->Next) sn->Next->Last = old;

              delete sn;

            cout << "deleted _IGNORE_ keyword from mob #" << mob->mobNumber << endl;
              break;
            }
          }

          old = sn;
          sn = sn->Next;
        }
      }

      mob = mob->Next;
    }

    cout << filename << ".mob read and converted, writing..\n";

    writeMobFile(filename);

    while (mobHead)
    {
      mob = mobHead->Next;

      deleteMobType(mobHead, FALSE);
      mobHead = mob;
    }

    lowestMobNumber = numbLookupEntries;   // handy
    highestMobNumber = 0;

    memset(mobLookup, 0, numbLookupEntries * sizeof(dikuMob*));
    if (onefile) return 0;
  }

  return 0;
}
