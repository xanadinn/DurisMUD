      /* test proc for Ailvio */
#include <ctype.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <list>
using namespace std;

#include "comm.h"
#include "db.h"
#include "events.h"
#include "interp.h"
#include "prototypes.h"
#include "specs.prototypes.h"
#include "structs.h"
#include "utils.h"
#include "tradeskill.h"
#include "spells.h"

extern P_room world;
extern P_nevent get_scheduled(P_char ch, event_func func);
extern void event_bandage_check(P_char ch, P_char victim, P_obj, void *data);

int burbul_map_obj(P_obj obj, P_char ch, int cmd, char *arg)
{
   P_obj map;

  /*
     check for periodic event calls
   */
  if (cmd == CMD_SET_PERIODIC)
    return TRUE;

  if (!ch)
    return FALSE;

  if (((cmd == CMD_ASK) && arg) || ((cmd == CMD_TELL) && arg))
  {
    if (isname(arg, "burbul map"))
    {
      if((map = read_object(29201, VIRTUAL)))
      {
        act("&+GB&N&+gurbu&+Gl &N&+ythe halfling &Nsmiles and hands you &+wa map&N.", FALSE, ch, 0, 0, TO_CHAR);
        act("&+GB&N&+gurbu&+Gl &N&+ythe halfling &Nsmiles and hands $n &+wa map&N.", TRUE, ch, 0, NULL, TO_ROOM);
        obj_to_char(map, ch);
      }
      return TRUE;
    }
  }


  return FALSE;
}

int chyron_search_obj(P_obj obj, P_char ch, int cmd, char *arg)
{
   P_obj newobj = NULL;

  /*
     check for periodic event calls
   */
  if (cmd == CMD_SET_PERIODIC)
    return TRUE;

  if (!ch)
    return FALSE;

  if ((cmd == CMD_GET || cmd == CMD_TAKE) && arg)
  {
    if(!(obj = get_obj_in_list_vis(ch, arg, world[ch->in_room].contents))) 
    { 
      return FALSE; 
    }
    if (isname(arg, "box") || isname(arg, "salt") || isname(arg, "wood") || isname(arg, "wooden"))
    {
      if(!(newobj = read_object(29220, VIRTUAL)))
      {
        return FALSE;
      }
      act("You get &+wa s&+Wal&N&+wt box&N.", FALSE, ch, 0, 0, TO_CHAR);
      act("$n gets &+wa s&+Wal&N&+wt box&N.", TRUE, ch, 0, NULL, TO_ROOM);
    }
    else if (isname(arg, "vial") || isname(arg, "red") || isname(arg, "tear") || isname(arg, "tears") ||  isname(arg, "basilisk"))
    {
      if(!(newobj = read_object(29221, VIRTUAL)))
      {
        return FALSE;
      }
      act("You get &+Ra vial of ba&N&+rsili&+Rsk tears&N.", FALSE, ch, 0, 0, TO_CHAR);
      act("$n gets &+Ra vial of ba&N&+rsili&+Rsk tears&N.", TRUE, ch, 0, NULL, TO_ROOM);      
    }
    else if (isname(arg, "all"))
    {
      act("You try, but Ch&+wyr&N&+gon gets in your way and you drop everything you've picked up.&N", FALSE, ch, 0, 0, TO_CHAR);
      return TRUE;
    }
    if(newobj)
    {
      // char gets object in room;
      obj_from_room(obj);
      obj_to_char(obj, ch);
      // put the new object in there and hide it
      SET_BIT(newobj->extra_flags, ITEM_SECRET);
      obj_to_room(newobj, ch->in_room);
      return TRUE;
    }
  }
  return FALSE;
}

int bandage_mob(P_char ch, P_char pl, int cmd, char *arg)
{

  if (cmd == CMD_SET_PERIODIC)
  {
    return TRUE;
  }
  
  if(!(ch) ||
     IS_PC(ch))
  {
    return FALSE;
  }

  if ((GET_STAT(ch) > STAT_INCAP) &&
       !IS_FIGHTING(ch))
  {
    SET_POS(ch, POS_PRONE + STAT_INCAP);
    GET_HIT(ch) = 0;
    affect_from_char(ch, SKILL_BANDAGE);
    return false;
  }

  return FALSE;
}

/*int bandage_reward_mob(P_char ch, P_char tch, int cmd, char *arg)
{
   P_char next;

   if(!ch)
   {
     return FALSE;
   }
   
   if(cmd == CMD_SET_PERIODIC)
   {
     return TRUE;
   }

   for(tch = world[tch->in_room].people; tch; tch = tch->next_in_room)
   {
     if (!tch)
     {
       return FALSE;
     }
     if(IS_NPC(tch))
     {
       return FALSE;
     }
     if (IS_PC(tch) && get_scheduled(tch, event_bandage_check))
     {
        act("$n&+w's eyes well up with &+Ctears&N &+wat your generosity.\n&+W'&N&+wTHANK YOU!!!&+W'&N&+w, $e sobs.\n&+wAs $e composes $mself, you find a &+Lpackage&n &+wat your feet.&N", FALSE, tch, 0, NULL, TO_VICT);
        act("$n&+w's eyes well up with &+Ctears&N &+wat $N's generosity.\n&+W'&N&+wTHANK YOU!!!&+W'&N&+w, $e sobs.\n&+wAs $e composes $mself, $e gives a &+Lpackage&n &+wto $N&+w.&N", TRUE, ch, 0, NULL, TO_NOTVICT);
        act("&+wOverwhelmed by the act of selflessness, you sob openly.  You compose yourself and\n&+wreward $N &+was best you can.&n", FALSE, ch, 0, NULL, TO_CHAR);
     }
   }
}
*/
