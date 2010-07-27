// Venthix's procs

#include <ctype.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <list>
#include <vector>
using namespace std;

#include "comm.h"
#include "db.h"
#include "events.h"
#include "interp.h"
#include "prototypes.h"
#include "spells.h"
#include "specs.prototypes.h"
#include "structs.h"
#include "utils.h"

int roulette_pistol(P_obj obj, P_char ch, int cmd, char *arg)
{
  int position; //The local of the live round in the pistol, 0 if none exist (fired)
  int dieval = 0;
  
  if (cmd == CMD_SET_PERIODIC)
    return FALSE;

  if (!obj || !ch)
    return FALSE;

  if (arg && ((cmd == CMD_RELOAD) || (cmd == CMD_FIRE)) && isname(arg, obj->name))
  {
    if (ch->equipment[HOLD] != obj)
    {
      act("You must be holding the pistol to use it.", FALSE, ch, obj, 0, TO_CHAR);
      return TRUE;
    }
  } 

  if (arg && (cmd == CMD_RELOAD) )
  {
    if (isname(arg, obj->name))
    {
    
      // Does the pistol still have a live round?
      if (obj->value[0])
      {
        act("&+yA live round is still loaded.  You spin the chamber and lock it.&n", FALSE, ch, obj, 0, TO_CHAR);
        //  Uhh how do I make $e show as uppercase?
        act("&+y$n opens the chamber and notices a live round already chambered.&L$e spins the chamber and locks it back.&n", FALSE, ch, obj, 0, TO_ROOM);
      }

      // If no live round is found in the pistol...
      if (!obj->value[0])
      {
        act("&+y$n quickly reloads $p &+ywith a live round.", FALSE, ch, obj, 0, TO_ROOM);
        act("&+yYou quickly reload $p &+ywith a live round.", FALSE, ch, obj, 0, TO_CHAR);
      }
      
      // Randomize the live round...  
      obj->value[0] = number(1,6);
  
      return TRUE;
    }
  }
  
  if (arg && (cmd == CMD_FIRE) )
  {
    if (isname(arg, obj->name))
    {
      if (!obj->value[0])
      {
        // Gun is empty, no live round.  Reload before playing...
        act("&+WClick!  &+yThere is no live round in the gun, reload you dummy!", FALSE, ch, obj, 0, TO_CHAR);
        act("&+WClick!  &+y$n&+y tries to play roulette with an empty gun.", FALSE, ch, obj, 0, TO_ROOM);
        return TRUE;
      }
      else
      {
        if ((obj->value[0] > 6) || (obj->value[0] < 0))
        {
          //debug issue with code. Value out of acceptable parameters.
          return TRUE;
        }
        if (obj->value[0] != 1)
        {
          // CLICK, nothing happened, wew!
          act("&+WClick! &+yNothing happened... &+Lweeew!&n", FALSE, ch, obj, 0, TO_CHAR);
          act("&+WClick! &+y$n&+y pulled the trigger, but nothing happened.", FALSE, ch, obj, 0, TO_ROOM);
        }
        else
        {
          // BANG, your dead!
          act("&-RBANG!&n &+WYou're dead!&n", FALSE, ch, obj, 0, TO_CHAR);
          act("&-RBANG!&n &+W$n&+W shot himself... What a loser!", FALSE, ch, obj, 0, TO_ROOM);
          if (!IS_TRUSTED(ch))
          {
            
            //obj_from_char(unequip_char(ch, HOLD), TRUE);
            //obj_to_room(obj, ch->in_room);
            //act("$p&+y drops to the floor.", FALSE, ch, obj, 0, TO_ROOM);
            GET_HIT(ch) = (-100);
          }
          else
          {
            act("&+yThe bullet simply bounces off $n&+y's head.", FALSE, ch, obj, 0, TO_ROOM);
            send_to_char("You can't die!\n", ch);
          }
        }
        obj->value[0]--;

        return TRUE;
      }
    }
  }
  return FALSE;
}

// 67282 &+mt&+Mh&+me &+Mo&+mr&+Mb &+mo&+Mf &+md&+Me&+mc&+Me&+mp&+Mt&+mi&+Mo&+mn
int orb_of_deception(P_obj obj, P_char ch, int cmd, char *arg)
{
  int curr_time = time(NULL);

  if (cmd == CMD_SET_PERIODIC)
    return FALSE;

  if (!obj || !ch)
    return FALSE;

  if (arg && (cmd == CMD_SAY))
  {
    if (isname(arg, "mirage"))
    {
      if (((ch->equipment[WEAR_EARRING_L] == obj) ||
           (ch->equipment[WEAR_EARRING_R] == obj)) &&
          ((obj->timer[0] + 180) <= curr_time))
      {
        act("&+L$n&+L's $p &+Lbegins to vibrate.", FALSE, ch, obj, 0, TO_ROOM);
        act("&+LYour $p &+Lbegins to vibrate.", FALSE, ch, obj, 0, TO_CHAR);
        spell_mirage(51, ch, 0, SPELL_TYPE_SPELL, ch, 0);
        obj->timer[0] = time(NULL);
        return TRUE;
      }
    }
  }
  return FALSE;
}
