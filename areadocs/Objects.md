The #OBJECT block
=================

Last Modified by Samson, Nov. 26, 2014

Objects add life to an otherwise boring place. Afterall, people came to this place to loot!
A well constructed area should have several objects available in it. Whether they are available
as loot, used by the Mobiles in the area, or just purely decorative, is entirely up to you.

You may have as many objects as you like, within the assigned vnum range of the area.
They can be placed in any order you wish in the file, but each section must obey the syntax.

The syntax of an #OBJECT block is:

#OBJECT
-------
String literal. This is required to mark the beginning of an object block.

Vnum         <#>
----------------
An integer value > 0. This value must fall within the range assigned to the builder who owns this area, or in the event
that this area is installed, it must fall within the vnum range specified in the #AREAHEADER section of the file.

Keywords     <string>~
----------------------
A set of words which will be used to interact with this object. They can be practically anything you want, but they
should also make sense. The use of color codes in keywords is inadvisable since it will not be obvious to players.

Type         <string>~
----------------------
The typoe of object this instance represents.
Choose from the following table:

   "NONE", "light", "scroll", "wand", "staff", "weapon", "scabbard", "puddle",
   "treasure", "armor", "potion", "clothing", "furniture", "trash", "journal",
   "container", "drinkcon", "key", "food", "money", "pen", "boat",
   "corpse", "corpse_pc", "fountain", "pill", "blood", "bloodstain",
   "scraps", "pipe", "herbcon", "herb", "incense", "fire", "book", "switch",
   "lever", "pullchain", "button", "rune", "runepouch", "match", "trap",
   "map", "portal", "paper", "tinder", "lockpick", "spike", "disease", "oil",
   "fuel", "piece", "tree", "missileweapon", "projectile", "quiver", "shovel",
   "salve", "cook", "keyring", "odor", "campgear", "drinkmix", "instrument", "ore"

The "none" type is a placeholder and probably should not be used for anything.
( Be aware that not all of the item types are working )

Short        <string>~
----------------------
The one or two word "name" this object is displayed as in inventory and equipment lists.

Long         <string>~
----------------------
The long-description is the description used when a character walks in the
room and the object is visible.

Action       <string>~
----------------------
A message this object should display when used or otherwise activated.
This feature is not fully supported.

Flags        <string>~
----------------------
A space separated list of flags this object has.
Choose from the following table:

Flag          | Details
--------------|-------------------------------------------------------
glow          | Reveals objects in dark rooms. Also nullifies invisibility.
hum           | Object hums. Overrides darkness and invisibility.
metal         | The object is 20% more resistant to damage.
bless         | The object is 20% more resistant to damage. This will stack with the metal flag.
organic       | The object is 20% more susceptible to damage.
resistant     | Currently unused.
immune        | Currently unused.
brittle       | Currently unused.
mineral       | Currently unused.
evil          | Currently does nothing other than display a red aura in lists.
loyal         | The object cannot be separated from its owner in combat.
invis         | The object is invisible. It will not be detectable without magic or one of the overriding flags. 
hidden        | An object that can be revealed by searching a room.
covering      | This object is covering other objects.
buried        | An object buried in the ground. Must be dug up.
poisoned      | A poisoned weapon. Inflicts poison damage on its victim.
twohand       | An object requiring two free hands before it can be equipped.
mustmount     | An object that requires being mounted before it can be worn.
thrown        | An object that can be thrown, such as a throwing dagger.
magic         | Object is enchanted and cannot be further enchanted.
nodrop        | A cursed object. It cannot be dropped normally.
noremove      | A cursed object. It cannot be unequipped normally if worn.
nolocate      | The object will not be revealed by locate spells.
noauction     | This object cannot be auctioned.
antigood      | Cannot be used by good aligned players.
antievil      | Cannot be used by evil aligned players.
antineutral   | Cannot be used by neutral aligned players.
anticleric    | Cannot be used by clerics.
antimage      | Cannot be used by mages.
antirogue     | Cannot be used by rogues.
antiwarrior   | Cannot be used by warriors.
antibard      | Cannot be used by bards.
antidruid     | Cannot be used by druids.
antimonk      | Cannot be used by monks.
antiranger    | Cannot be used by rangers.
antipaladin   | Cannot be used by paladins.
antiapal      | Cannot be used by antipaladins.
antinecro     | Cannot be used by necromancers.
antimen       | Cannot be used by males.
antiwomen     | Cannot be used by females.
antineuter    | Cannot be used by neuters.
antiherma     | Cannot be used by hermaphrodites.
antisun       | Currently unused.
onlycleric    | Only clerics can use this.
onlymage      | Only mages can use this.
onlyrogue     | Only rogues can use this.
onlywarrior   | Only warriors can use this.
onlybard      | Only bards can use this.
onlydruid     | Only druids can use this.
onlymonk      | Only monks can use this.
onlyranger    | Only rangers can use this.
onlypaladin   | Only paladins can use this.
onlyapal      | Only antipaladins can use this.
onlynecro     | Only necromancers can use this.
permanent     | Once acquired, this object can never be removed. Suitable for use as a tattoo or a branding etc.
nofill        | Object cannot be used as a source to fill liquid containers.
personal      | Only the item's designated owner can use it. May not be auctioned or sold. Cannot be looted by others if dropped.
deathrot      | This object will disintegrate when its owner is killed.
deathdrop     | This object will fall to the ground when its owner is killed.
groundrot     | This object will disintegrate if left on the ground too long.
inventory     | Store inventory. Has an additional 20% resistance to damage while still owned by a shopkeeper. When killed, if the object is still on the shopkeeper, it will disintegrate.
lodged        | Set when a projectile becomes lodged in a target. Additional damage is done when the victim dislodges it.
sindhae       | Set on a prize item redeemed in the Sindhae Challenge.
auction       | Set when an item is currently being bid on in an auction.
donated       | Set when an object is dropped in a donation room. Prevents the object from being auctioned by players or sold to shopkeepers.
clanobject    | Set when a clan/guild leader creates one of their designated objects. When a weapon has this flag, it cannot be poisoned.
clancorpse    | Designates the corpse of a clan member killed during PK. Prevents various actions from being performed by someone other than the person who killed them.
onmap         | Set when the object is on an overland map.
proto         | An unfinished object.

WFlags       <string>~
----------------------
A space separated list of body locations the object can be worn on.
Choose from the following table:

Flag   | Details
-------|------------------------------------------
take   | The item can be picked up.
finger | Worn on the fingers. (2 slots)
neck   | Worn around the neck. (2 slots)
body   | Worn on the body.
head   | Worn on the head.
legs   | Worn on the legs.
feet   | Worn on the feet.
hands  | Worn on the hands.
arms   | Worn on the arms.
shield | Equipped as a shield.
about  | Worn around the body. Like a cloak.
waist  | Worn around the waist.
wrist  | Worn on the wrists. (2 slots)
wield  | Wielded as a weapon.
hold   | Held in a hand. Like a torch etc.
ears   | Worn on the ears.
eyes   | Worn over the eyes.
back   | Worn on the back.
ankle  | Worn around the ankles. (2 slots)
face   | Worn on the face.
hooves | Worn on the hooves.
tail   | Worn on the tail.

Values         <#0> <#1> <#2> <#3> <#4> <#5> <#6> <#7> <#8> <#9> <#10>
----------------------------------------------------------------------
Object values which determine characteristics of the object when applied.
Each value has meaning based on what object type is being affected, and not
all objects require all 11 values to be specified. Due to how the code works
the values begin counting up from 0, so value[0] is valid.

If there are unused values listed prior to a used value, those unused slots
need to be occupied with zeros. 

A value listed as "sn #" requires a slot number from the game's spell tables.
These values are covered in the Values.txt file. A 0 or negative number in these
types of positions means no spell is applied.

Choose the values based on the following table:

Item type: light
   value[0] unused
   value[1] unused
   value[2] hours of light available, 0 is dead, -1 is infinite

Item type: scroll
   value[0] level
   value[1] sn 1
   value[2] sn 2
   value[3] sn 3

Item type: wand
   value[0] level
   value[1] max charges
   value[2] current charges
   value[3] sn

Item type: staff
   value[0] level
   value[1] max charges
   value[2] current charges
   value[3] sn

Item type: weapon/missileweapon
   value[0] base condition
   value[1] number dice	  v1 and v2 are optional and will be
   value[2] size dice	  autogenerated if set to 0
   value[3] damage type ( Not relevant to missile weapons ):
      01 slash
      02 stab
      03 hack
      04 crush
      05 lash
      06 pierce
      07 thrust
   value[4] weapon skill:
      00 barehand
      01 sword
      02 dagger
      03 whip
      04 talon ( talonous arms )
      05 mace ( includes hammers )
      06 archery ( bows and crossbows )
      07 blowgun ( missileweapon )
      08 sling ( missileweapon )
      09 axe
      10 spear
      11 staff
   value[5] projectile type ( for missile weapons only ):
	( Determines the type of projectile this weapon can fire )
	00 bolt
	01 arrow
	02 dart
	03 stone
   value[6] current condition
   value[7] available rune/gem sockets

   The following 3 settings override most of the above. See Itemgen.txt for details.
   value[8] Weapon type
   value[9] Weapon material
   value[10] Weapon quality

Item type: projectile
   value[0] base condition
   value[1] number dice	  v1 and v2 are optional and will be
   value[2] size dice	  autogenerated if set to 0
   value[3] damage type:
      01 slash
      02 stab
      03 hack
      04 crush
      05 lash
      06 pierce
      07 thrust
   value[4] projectile type:
      00 bolt
      01 arrow
      02 dart
      03 stone
   value[5] current condition

Item type: treasure ( This type uses no values )

Item type: armor
   value[0] AC adjust/current condition
   value[1] Original AC
   value[2] available rune/gem sockets

   The v3 and v4 settings override much. See Itemgen.txt for details.
   value[3] Armor type
   value[4] Armor material

Item type: potion
   value[0] level
   value[1] sn 1
   value[2] sn 2
   value[3] sn 3

Item type: furniture
   value[0]  unused
   value[1]  unused
   value[2]  See below. Add the BV values to get the value of value[2].

FLAG     -     BV  - DESCRIPTION
------------------------------------------------------------
NORMAL   -       0 - Just a regular piece of furniture.
SIT_ON   -       1 - Can be sat on.
SIT_IN   -       2 - Can be sat in.
SIT_AT   -       4 - Can be sat at.
STAND_ON -       8 - Can be stood on.
STAND_IN -      16 - Can be stood in.
STAND_AT -      32 - Can be stood at.
SLEEP_ON -      64 - Can be slept on.
SLEEP_IN -     128 - Can be slept in.
SLEEP_AT -     256 - Can be slept at.
REST_ON  -     512 - Can be rested on.
REST_IN  -    1024 - Can be rested in.
REST_AT  -    2048 - Can be rested at.

Item type: trash ( This type uses no values )

Item type: container
   value[0] weight capacity
   value[1] flags: 1 closeable, 2 pickproof, 4 closed, 8 locked, 16 eatkey
   value[2] key vnum
   value[3] durability
   value[4] unused
   value[5] identifies matching key on value[5] of a key.
		If these values do not match, the key will not open the lock.
		Primarily used with the camping system to safeguard the strongbox.

Item type: drinkcon
   value[0] capacity
   value[1] current quantity
   value[2] liquid number (see 'liquids table' in values.txt)
   value[3] if non-zero, drink is poisoned

Item type: key
   value[0] unused
   value[1] unused
   value[2] unused
   value[3] unused
   value[4] Number of retries before key breaks if used in wrong lock.
   value[5] identifies matching lock on value[5] of a container.
		If these values do not match, the key will not open the lock.
	
Item type: food
   value[0] hours of food value
   value[1] (condition)
   value[2] unused
   value[3] if non-zero, food is poisoned

Item type: money
   value[0] value in gold pieces

Item type: boat ( This type uses no values )

Item type: fountain
   value[0] unused
   value[1] Number of drinks (any value = infinite )

Item type: pill
   value[0] level of spells
   value[1] sn 1
   value[2] sn 2
   value[3] sn 3

Item type: switch
   value[0] flags
   value[1] vnum or sn
   value[2] vnum
   value[3] vnum/value
   ( See lever flags in values.txt for switches, levers, pullchains, and buttons )

Item type: lever
   value[0] flags
   value[1] vnum or sn
   value[2] vnum
   value[3] vnum/value

Item type: pullchain
   value[0] flags
   value[1] vnum or sn
   value[2] vnum
   value[3] vnum/value

Item type: button
   value[0] flags
   value[1] vnum or sn
   value[2] vnum
   value[3] vnum/value

Item type: trap
   value[0] charges
   value[1] type
   value[2] level
   value[3] flags ( See Trap Flags and types in values.txt )
   value[4] minimum damage
   value[5] maximum damage

Item type: campgear
   value[0] Type of camping gear:
     1 - Bedroll. Used to sleep on while camped.
     2 - Gear. Miscelaneous things such as utensils etc.
     3 - Firewood. Required to light the campfire.

Item type: ore
   value[0] Type of ore material:
     1 - Iron
     2 - Gold
     3 - Silver
     4 - Adamantine
     5 - Mithril
     6 - Blackmite*
     7 - Steel
     8 - Bronze
     9 - Titanium
    10 - Dwarven Steel
    11 - Elven Steel

     * - Magical ore found only in Arthmoor's palace.

   value[1] Purity of the ore from 1-100%, affects cost/skill roll for forging weapons and armor.

Item type: piece
   value[0] Vnum of other half of the object.
   value[1] Vnum of the combined object.

Item type: journal
   value[0] Number of pages the journal has. Has a limit of 50 pages.

Stats       <#1> <#2> <#3> <#4> <#5> <string1> <string2> <string3>
------------------------------------------------------------------
Other statistics which affect this object.

#1 = Weight. How much this object weighs in pounds.
#2 = Cost. What this object costs in gold pieces.
#3 = Ego. The relative power or personality this item holds. Set to -2 to have this calculated automatically.
#4 = Limit. The hard limit of how many copies of this object are allowed to exist in play.
     This limit is enforced even with players who are logged off if the item's "ego" value
     is over 25. For non-limited items, specify 9999 here.
#5 = Layers. The layer number this object operates in.
     Code for this is not working properly so this could be unpredictable.
String1, String2, and String3 are for socketed items.
If this item is not intended to be socketed when it loads, then all three of these values
should read "None". See Runes.txt for more information on rune names and socketed items.

Affect      <Format varies>
---------------------------
Affects will be listed based on location, types, and other data associated with them.
These are best left to handle via the OLC as the format is different depending on the
location of the particular affect. An object can have as many affect sections as are
appropriate, but should be kept within reason or the object could be overbalanced.

Spells      '<string>' '<string>' '<string>'
--------------------------------------------
Spell names are added based on the object type.

A pill, potion or scroll should contain 3 strings. Specify "none" if one or more need to be left empty.
A staff or wand uses only the first string. Extras will be ignored.
A salve uses the first two slots. The third is ignored.

The single quotes around the spell names are required.

#EXDESC
#ENDEXDESC
----------
See the Misc.txt file for the format of Extra Description blocks. These are optional.

#MUDPROG
#ENDPROG
--------------
See the Misc.txt file for the format of Mudprog blocks. These are optional.

#ENDOBJECT
----------
String literal. This ending tag is required to mark the end of an #OBJECT block.
If it is left out, the file will be assumed to be corrupt.

=============================================================================================

An example of a completed object follows:

#OBJECT
Vnum      11028
Keywords  firewood pile twigs~
Type      tinder~
Short     Some dry twigs and firewood~
Long      A pile of dry twigs lies in a heap.~
WFlags    take~
Values    3 0 0 0 0 0 0 0 0 0 0
Stats     2 0 50 9999 0 None None None
#EXDESC
ExDescKey    firewood pile twigs~
ExDesc       A rather unimpressive heap of dry twigs and leaves. It appears to be
useful if you wanted to start a fire going.
 
To build a fire, follow the steps below:
1) Drop the firewood onto the ground where you want to build the fire.
2) Say "strike flint" to strike the tinder with some small flint stone.
3) Enjoy the warmth and light of your newly built fire.
~
#ENDEXDESC

#MUDPROG
Progtype  speech_prog~
Arglist   p strike flint~
Comlist   mpechoat 0.$n You strike the tinder with the flint and sparks fly...
mpechoat 0.$n The twigs catch fire and soon, you have a fire cackling.
mpechoat 0.$n The tinder and flint is consumed in building the fire.
mpoload 11002
mposet fire timer 15
mppurge firewood-pile-twigs
~
#ENDPROG

#ENDOBJECT

This completes an #OBJECT block.
Refer to Rooms.txt to continue building your area file.
