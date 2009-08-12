//
//  File: edesc.cpp      originally part of dikuEdit
//
//  Usage: functions for manipulating extra desc records
//
//  Copyright 1995-98 (C) Michael Glosenger
//


#include <iostream.h>

#include "../fh.h"
#include "../types.h"

#include "edesc.h"

//
// getNumbExtraDescs : Returns the number of extra descs in a list
//
//   *extraDescNode : head of list
//

INLINEDEF ulong getNumbExtraDescs(extraDesc *extraDescNode)
{
  ulong i = 0;


  while (extraDescNode)
  {
    i++;

    extraDescNode = extraDescNode->Next;
  }

  return i;
}


//
// copyExtraDescs : Copies a list of extra descs, returning the address of the
//                  head of the new list
//
//   *srcExtraDesc : head node of list to copy
//

extraDesc *copyExtraDescs(extraDesc *srcExtraDesc)
{
  extraDesc *newExtraDesc, *prevExtraDesc = NULL, *headExtraDesc = NULL;


  if (!srcExtraDesc) return NULL;

  while (srcExtraDesc)
  {
    newExtraDesc = new extraDesc;
    if (!newExtraDesc)
    {
      cout << "\n\nError creating new extraDesc in copyExtraDescs().  "
              "Out of memory.\n\n";

      return NULL;
    }

    memset(newExtraDesc, 0, sizeof(extraDesc));

    newExtraDesc->Last = prevExtraDesc;
//    newExtraDesc->Next = NULL;

    if (!headExtraDesc) headExtraDesc = newExtraDesc;

    if (prevExtraDesc) prevExtraDesc->Next = newExtraDesc;
    prevExtraDesc = newExtraDesc;

    newExtraDesc->keywordListHead =
           copyStringNodes(srcExtraDesc->keywordListHead);
    newExtraDesc->extraDescStrnHead =
           copyStringNodes(srcExtraDesc->extraDescStrnHead);


    srcExtraDesc = srcExtraDesc->Next;
  }

  return headExtraDesc;
}


//
// deleteExtraDescs : Deletes a list of extraDescs
//
//   *srcExtraDesc : head of list to delete
//

void deleteExtraDescs(extraDesc *srcExtraDesc)
{
  extraDesc *nextExtraDesc;


  while (srcExtraDesc)
  {
    nextExtraDesc = srcExtraDesc->Next;

    deleteStringNodes(srcExtraDesc->keywordListHead);
    deleteStringNodes(srcExtraDesc->extraDescStrnHead);

    delete srcExtraDesc;

    srcExtraDesc = nextExtraDesc;
  }
}


//
// copyOneExtraDesc : Copies just the specified extraDesc, returning the
//                    address of the copy
//
//   *srcExtraDesc : source to copy from
//

extraDesc *copyOneExtraDesc(const extraDesc *srcExtraDesc)
{
  extraDesc *newExtraDesc;


  if (!srcExtraDesc) return NULL;

  newExtraDesc = new extraDesc;
  if (!newExtraDesc)
  {
    cout << "\n\nError creating new extraDesc in copyOneExtraDesc().  "
            "Out of memory.\n\n";

    return NULL;
  }

  memcpy(newExtraDesc, srcExtraDesc, sizeof(extraDesc));

  newExtraDesc->keywordListHead =
         copyStringNodes(srcExtraDesc->keywordListHead);
  newExtraDesc->extraDescStrnHead =
         copyStringNodes(srcExtraDesc->extraDescStrnHead);

  return newExtraDesc;
}


//
// deleteOneExtraDesc : As you might guess, deletes just the specified
//                      extraDesc
//
//   *extraDescNode : extraDesc to delete
//

void deleteOneExtraDesc(extraDesc *extraDescNode)
{
  if (!extraDescNode) return;

  deleteStringNodes(extraDescNode->keywordListHead);
  deleteStringNodes(extraDescNode->extraDescStrnHead);

  delete extraDescNode;
}


//
// compareExtraDescs : Compares two lists of extra descs - returns TRUE if
//                     they match
//
//  *list1 : the first list
//  *list2 : take a guess, I'm sure you'll be pretty close..
//

char compareExtraDescs(extraDesc *list1, extraDesc *list2)
{
  if (list1 == list2) return TRUE;
  if (!list1 || !list2) return FALSE;

  while (list1 && list2)
  {
    if (!compareStringNodes(list1->keywordListHead,
                            list2->keywordListHead)) return FALSE;

    if (!compareStringNodes(list1->extraDescStrnHead,
                            list2->extraDescStrnHead)) return FALSE;

    list1 = list1->Next;
    list2 = list2->Next;
  }

  if ((!list1 && list2) || (list1 && !list2)) return FALSE;

  return TRUE;
}


//
// compareOneExtraDesc : Compares two extra desc nodes - returns TRUE if
//                       they match
//
//  *node1 : the first list
//  *node2 : take a guess, I'm sure you'll be pretty close - well, maybe
//

char compareOneExtraDesc(extraDesc *node1, extraDesc *node2)
{
  if (node1 == node2) return TRUE;
  if (!node1 || !node2) return FALSE;

  if (!compareStringNodes(node1->keywordListHead,
                          node2->keywordListHead)) return FALSE;

  if (!compareStringNodes(node1->extraDescStrnHead,
                          node2->extraDescStrnHead)) return FALSE;


  return TRUE;
}


//
// getEdescinList
//

extraDesc *getEdescinList(extraDesc *descHead, const char *keyword)
{
  extraDesc *descNode = descHead;

  if (!descHead) return NULL;

  while (descNode)
  {
    if (scanKeyword(keyword, descNode->keywordListHead)) return descNode;

    descNode = descNode->Next;
  }

  return NULL;
}
