Miscelaneous blocks
===================

Exit block - Used inside of #ROOM blocks.

Rooms aren't of much value without exits. People don't like to be trapped.

The syntax of an #EXIT block is:

#EXIT
-----
String literal. Required to marke the beginning of the block.

Direction     <string>~
-----------------------
Name of the direction this exit points in.
Choose from the following table:

DIRECTION
---------
north
east
south
west
up
down
northeast
northwest
southeast
southwest
somewhere ( usually a portal type exit )

ToRoom        <#>
-----------------
Vnum of the target room for this exit. Obviously needs to exist.

Key           <#>
-----------------
Vnum of the key needed to unlock a door in the direction specified above.

ToCoords      <X> <Y>
---------------------
Overland map coordinates this exit will lead to if the exit has the EX_OVERLAND flag.
The actual map the coordinates to apply will be determined by which continent the
room's area belongs on. Setting coordinates on a room that's not flagged for overland
will have no affect.

Pull          <#1> <#2>
-----------------------
Uh....

Desc          <string>~
-----------------------
A one line descriptive message which is displayed if a user types "look direction".
This is optional.

Keywords      <string>~
-----------------------
A single keyword that can be used to manipulate the exit, such as "door" or "gate".
Somewhat misleading in that it will only support one word being there.

Flags         <string>~
-----------------------
A space separated list of attribute flags which affect this exit.
Choose from the following table:

Flag       | Details
-----------|---------------------------------------------
isdoor     | <direction> is a door. Can have several states. Defaults as open.
closed     | A closed door.
locked     | A closed and locked door. Can be unlocked with a lockpick.
pickproof  | A closed and locked door. Requires the key to be opened.
eatkey     | The key is consumed when this door is unlocked.
isbolt     | A door which can be bolted shut.
bolted     | A closed door that is currently bolted shut.
bashed     | A door which has been bashed open.
bashproof  | A door which cannot be bashed open.
nopassdoor | Passdoor cannot be used to bypass the door.
secret     | A secret exit. Will not be visible without being searched for.
hidden     | A hidden exit. Will not be revealed by search skill.
nomob      | NPCs may not use this exit.
fly        | Flight is required to use this exit.
climb      | Climbing skill is required to use this exit.
can_climb  | The climb command can be used to access this exit.
can_enter  | The enter command can be used to access this exit.
can_leave  | The leave command can be used to access this exit.
auto       | The exit's assigned keyword can be used to access it.
dig        | The exit must be dug out before it can be used.
window     | The exit is a window.
can_look   | A window exit which can be looked through.
overland   | The exit leads from a standard area on to an overland map.
arrowslit  | Only projectiles may be fired through this exit.
noflee     | This exit will not be used by fleeing opponents.
fortified  | An exit which has been fortified. *
heavy      | A fortified exit which must be attacked 4 times to clear it. *
medium     | A fortified exit which must be attacked 3 times to clear it. *
light      | A fortified exit which must be attacked 2 times to clear it. *
crumbling  | A fortified exit which must be attacked 1 time to clear it. *
destroyed  | A fortified exit where the fortifications have been destroyed. *
swim       | Swimming is required to use this exit. *
passage    | Flag set when mpopenpassage is called. Do not use.
portal     | Flag set when the portal spell is case. Do not use.

* These flags have not been completely implemented yet.

Attackable walls can only be damaged by siege engines - which don't yet exist in game.
Each grade of wall is stronger than the one below it. When setting wall flags, only
use one flag, combining them will only result in the greatest flag being acknowledged.


An Extra Description block:
---------------------------

Extra descriptions can be used to enhance the details of either objects or rooms in the same manner
that long descriptions provide descriptive details for Mobiles. These should be used where they make
sense. They should avoid substituting for real objects or mobiles if used in a room.

The format of an Extra Description block:

#EXDESC
-------
String literal required to mark the beginning of the block.

ExDescKey    <string>~
----------------------
The keywords used to display the description to players. Some sort of logical hint that this is possible
should be provided either by way of an object name or a subtle hint in a room description.

ExDesc       <string>~
----------------------
The detailed text displayed when a player uses the look command on one of the keywords associated with it.

#ENDEXDESC
----------
String literal required to mark the end of the block.

A Mudprog block:
----------------

Mudprogs can be used to further enhance the experience provided by mobiles, rooms, or objects.
Properly done they can be used to simulate crude AI behaviours, transportation tricks such
as boat rides, elevators, or other more complicated things that the standard tools don't allow.
Though not as powerful as true scripting languages, in the right hands a lot can be done with mudprogs.
For details of what types of progs are available and how to use them, refer to the Mudprog text files.

#MUDPROG
--------
String literal required to mark the beginning of the block.

Progtype      <string>~
-----------------------
Name of the type of mudprog this is.

Arglist       <string>~
-----------------------
Argument list which is fed to the specified program type. Can be something as simple as a number.
Can also be something more complex such as a specific trigger string to make it work.

Comlist       <string>~
-----------------------
The detailed list of commands the program is instructed to execute. This can be quite elaborate
with nested if/else blocks and other things.

#ENDPROG
--------
String literal required to mark the end of the block.
