Using Mob_progs
===============

Ahh, you say.. mob progs. WTF? Well I will answer that.
Mop Progs give life to your mobs. Instead of sitting around
waiting to be slaughtered, they can give advice, hints, give money,
accept bribes, smile, go down on someone. There are other things 
that mob-progs can do but this is good for now.  

How to make mob_progs?
--It's Alive, Alive! (Dr. Frankstein)

	First things first Create your Mob!
	--Zaaaap! (Me)

	Second Things second: Mset all the stats.
	--Ack! (Countless Mudders)

	Third ADD in Mob_progs. 
	--WTF? (Countless Immorts)

        A MUDPROG section of a Mob, Object, or Room is constructed with a simple block in their data.
        These should be inserted before the #ENDMOBILE, #ENDOBJECT, or #ENDROOM markers depending on
        what you are applying them too.

So. Lets say Bill Gates has a fight program attached that goes off 40% of the time while in combat.
This is what that should look like:

#MUDPROG
Progtype fight_prog~
Arglist  40
Comlist  say I will purchase you~
#ENDPROG

	Get it?
	That is how you add mob_progs. Now I know you are thinking
	WTF is fight_prog 40 mean?
	Well I'll get into that right now.

	TRIGGERS
	"Pounce Session, all right sir. ... Wait NO!!! Mufasa?" --Zazzo
	
	Triggers are what get this, trigger your mob_prog.
	
	So can I have just _any_ trigger?
 	_NO!_
	But here is a list of the ones that are built into Smaug:

------------------------------------------------------------------------
act_prog	syntax: act_prog [p] <Argument>

What Does it do: This makes the Mob listen to what a character is saying
or doing. So if the character says, Fred tell me about my mother. Fred 
will listen. The Argument is the list of keywords that fred is listening
for.
  
Example:

act_prog mother lazy kitten
say It's okay I heard you the first time

What's that mean: If someone says mother, lazy, or kitten Fred will
reply, "It's okay I heard you the first time".

You can get specific and they have to say a key phrase to say get
in to an elite club.

Example:
	
act_prog [p] p My password is: Jerry
say alright

What's that mean: When someone says, My password is: Jerry
Fred will say, "alright".

This trigger can also read anything that happens in the room. For
example if a char "pokes you in the ribs" can be a trigger. Or a
certain emote. In these cases remember the preceding p.
	
		NOTE:  NONE OF THESE MOB_PROG'S ARE CASE SENSITIVE

------------------------------------------------------------------------
bribe_prog      Syntax: bribe_prog <NUMBER>

Ahah. Corrupt Officails? Selling certain Items that are 'blackmarket?' 
Uhuh this is a good one to use if you want to get a corrupt or devious
feeling. What Does it DO: It is activated when an amountt of coins is
given to the mob in a number equal to or greater than the NUMBER.
NOTE: This cash does NOT go into mob->gold. It is seperate. To really 
get life like the mob can now with a combo of other triggers purchase 
food, or weapons or whatever with this money.
			
Example:

bribe_prog 5000
grin
say thanks sir

What's that mean: When someone types give Fred 5000
Fred grins and says "thanks sir".  

------------------------------------------------------------------------
entry_prog      Syntax: entry_prog <PERCENT>

Okay this is a neat one. What does a gentleman do when he enters a room?
Right, he tips his hat. So what entry_prog allows us to do is set up a 
chance that Fred is going to say Hi! or tip his hat or wave or whatever
we want him to do. NOTE: it is a percent so unless you set it to 100 it
won't happen all the time.

Example:

entry_prog 50
tip
say Hello, how are you doing this morn?

What's this mean: When Fred walks into a room he has 50/50 chance of
tipping his hat and saying hello otherwise he won't do anything.

NOTE: Please ONLY use this on wandering MOB's It does no good to use it
on stationary MOB's. It is only for when they enter a room.

------------------------------------------------------------------------
give_prog       Syntax: give_prog <ARGUMENT>

Need someone to find a lost ring? Or return a stolen purse? Well that's 
what this prog is for. This prog is activated when ARGUMENT is given to 
Fred. The ARGUMENT has to be the complete name, or it can be all. 
Complete names are like : "Sword shiny magic" vs "sword" or what ever is 
on the line of the object section following the VNUM.
			
Example:

give_prog light saber
pout
say darn it Jim, I'm a coder not a Jedi

What's this Mean:  When Joe Blow Character gives Fred his light saber 
Fred pouts and say darn it jim, I'm a coder not a jedi.

------------------------------------------------------------------------
 greet_prog      Syntax: greet_prog <PERCENT>

"Ho, what can I sell you?" the mechant asks. Aggromonsters attack, is what
this prog is for. What it does is detect someone entering the room they 
are in and gets a percentage of doing whatever it is it does. Remember 
it is a percent so If you want the merchant/shopkeeper to always say Hi 
set it to 100.

Example:
greet_prog 25 
drop 100 gold

What's this Mean: When Joe Blow walks into the room Fred has a 1/4
chance of dropping some cash. WoooHooo Joe Blow thinks. He comes back and
Fred thinks about it, but doesn't. Joe Blow sulks.	

------------------------------------------------------------------------
all_greet_prog	syntax: all_greet_prog <PERCENT>

This is greet except it detects, invis, sneak, hide and all those devious
cloak and dagger skills. Good use for creatures that should see invis.

Example:
	
all_greet_prog 100
say aha trying to get pass me?

What's this mean: When an invisible Joe Blow walks in Fred says aha,
trying to get pass me?

*************NOTE:  THE GREET PROGRAMS DO NOT WORK WHEN THE MOB IS FIGHTING*****************

------------------------------------------------------------------------
fight_prog      Syntax: fight_prog <PERCENT>

Evil Doer!!!! CHARGE!!!! -Cityguards. This prog is to give mob personalities
when fighting. A mercanary that complains he's not getting paid enough. 
It checks the percent every combat round. But, if it is successful it won't
execute again. SO: IT ONLY CHECKS EACH COMBAT IF IT HAS FAILED.
			
Example:
	
fight_prog 35
cast fireball

What it means: When combat is initiated the prog checks to see if it
can cast fireball, then continues to check until it can. 

NOTE: FOR EACH SPELL OR SKILL A MOB CAN USE CREATE A FIGHT_PROG for it.

------------------------------------------------------------------------
hitprcnt_prog   Syntax: hitprcnt_prog <PERCENT>

Run away! Run away! This prog activates when the mob's hp drop to
the percentage given. So if a Mob drops to 50% hp he tries to cast 
fireball or lightning or flees.

Example:

hitprcnt_prog 20
say Darn it I'm going to DIE!

What it means: When a 100hp Mob drops to 20Hp or Below, the MOB says 
'Darn it I'm going to DIE!

------------------------------------------------------------------------
death_prog      Syntax: death_prog <PERCENT>

'Tis a shame that I have but one life to live for my country. One last 
quote or action. His last gasp! If the random Percent is below the given
percent then the action happens.

Example:
	
death_prog 100
smile
chat Alas, I have been Slain
		
What it means: When poor Fred Dies, he smiles and chats Alas, I have been Slain.

------------------------------------------------------------------------
rand_prog       Syntax: rand_prog <PERCENT>

Ahh, this one is sweet. Basically what it does is check the percent every 
heartbeat [rd] and if the percent is less then the one given then the action 
happens. This is a catchall. If you want a mayor who wanders around and does 
weird things almost absent mindedly then this is the one you want.

Example:

rand_prog 50
drool
dance
sing

What it means: When poor Fred the Mayor is wondering around he has a 50/50 
chance of drooling, dancing and singing all at the same time.

------------------------------------------------------------------------
speech_prog 	Syntax: speech_prog [p] <ARGUMENT>

"What's that Whipper-snapper?" This prog is triggered only by messages 
other wise it works just like act_prog.
				
Example:

speech_prog p Hey old man.
say Huh whipper snapper? My time's almost up.
		
What it means: Fred is out of time, he hears a char say Hey old man, or 
is told Hey old man. He replies Huh whipper snapper? My time's almost up.

------------------------------------------------------------------------
BIG NOTE:  NONE. NOT A SINGLE MOB_PROG WORKS WHEN A MOB IS CHARMED.  
I REPEAT NO MOB PROGS WORK WHEN THE MOB IS CHARMED.

Now for your Test:

Create a mob that wonders around, and when he enters a room say hello all.  
When he dies he chat's fair well world. And when he's given a sword he drops gold.

Test 2

Create a mob that when given money babbles something at a char. If asked to 
return it gives it back.

*A MOB THAT IS CHARMED DOES NOT USE MOB_PROGS*

Part 2
======

Now that your MOB is alive, well sort of. Fred does all kind of neat 
things, but you know what?

Yes, Johnny?
Um, teacher can I go to the bathroom?
I don't know, but you may go if you need to.

Fred can't address Johnny or teacher yet. Here's a secret: In this section 
we will learn how to do this, and many other cool things.

--No master, I will take Care of Him.(Darth Vader)


Now, not coincidentally, the variables in MOB_PROG are addressed the same 
way that social's are addressed. If you're already coding social's, then 
WTF are you doing reading this? This is for builders, dammit. To address a 
variable you use the $ sign and then the variable whatever it is.

NOTE: The Syntax listed is on the line following the mob_prog call.
NOTE: Mob's _CAN_ activate Trigger's on other Mobs.
NOTE: If You have used Mob_Progs or Read the Help files you might notice 
some of the Variables missing. The Author (me) decided to include those 
Variables in another section because he wrote these things on whim.  
So cut me some flak, okay?

------------------------------------------------------------------------
Example:

rand_prog(100)
say $Variable <msg>

or

rand_prog(100)
kiss $Variable

Get it?
Got it?
Good!
------------------------------------------------------------------------
NOTE: For the sake of Flow, and because I'm lazy, the Syntax will contain: 
say $$ <msg>. Be aware though _ANY_ social may go in place of say.  
So you can use run, or laugh, or rofl or whatever. You can also instead 
of using say, use any of the channels that the mob would be able to use.
Race channels, chat, barter, whatever.

$i	Syntax: say $i likes to eat things

So you want your mob to be a little crazy? What better way then to have him 
talk in third person or use socials on himself.
 
So In other words: $i calls the first name of the mob itself.

	Example:
	rand_prog 50
	say $i was crazy once.
	bonk $i
	Snicker

What it does: There is a 50/50 chance of Fred saying, Fred was crazy once.
Bonk fred, and snicker.

------------------------------------------------------------------------
$I	Syntax: say $I is really kind of wierd.

Well, well we have gotten really formal haven't we? This gets even a crazier
response. So in other words: $I calls the short description of the mobile.
This would be used mostly for says or tells, It's hard to use bonk Fred, 
the blond male vampire is standing here. 
--Bet you didn't know Fred was blonde or a vampire did you?

	Example:
	rand_prog 50
	say $I is pretty funny isn't he?

What it does: 50/50 chance that Fred says, Fred, the blonde male is pretty 
funny	isn't he?

------------------------------------------------------------------------
$r	Syntax: say Hi $r

Doctor! Doctor! Doctor! Doctor! Doctor! Cut that OUT! (3 Stooges)
So in other words: $r chooses the name of a random char/mob in the room 
with the mob(FRED). But $r will never be the name of the mob(Fred).
NOTE:  mob(FRED) is used to differentiate between The mob with the mob_prog 
andanother random mob in the room. (FRED) has the mob_prog.

	Example:
	greet_prog 100
	say Hi $n
	bite $r

What it does: Whenever someone enter's the room Fred will greet them.  
But then he	will turn around and bite a random person/mob in the room.

------------------------------------------------------------------------
$R	Syntax: say Hello $R

Doctor Livingston, I persume. (Doctor Watson)
So in other words: $R chooses a random char/mob other than the one with 
the mob_prog and address it by it's title/short description.

	Example:
	rand_prog 50
	say $R you are smashing today, mind helping out an old beggar?

What it does: Each Heartbeat there is a 50/50 chance of Fred telling
Joe Blow the Immortal, you are smashing today, mind helping out an old beggar?

------------------------------------------------------------------------
$n	Syntax: say $n is really kind of neat

Hello, Joe Blow, welcome to my humble abode. I hope you enjoy your stay, Joe.
Have fun Joe.
So in other words: $n is the variable that calls the name of a character that
triggered an event. This is probably the one to use most of the time.

	Example:
	greet_prog 100
	say welcome back $n
	cast Sanc $n

What it does: Whenever someone comes into this room, Fred greets them with 
Welcome back Joe. And then being the nice guy he is, Fred cast Sanctuarary 
on Joe.
NOTE:  $n --CAN-- be another MOB

------------------------------------------------------------------------
$N	Syntax: say $N I'm humbled

Once again Fred is being formal. Awfully nice of him isn't it?
So in other words: $N is the variable that calls the name and title of a 
char that activates a trigger.
NOTE: $N --CAN-- be another MOB

	Example:
	greet_all_prog 100
	say $N ! I wasn't Expecting you!!!!

What it does: Whenever ANYONE(greet_all_prog [lesson 1]) comes into the 
room Fred say's Joe Blow the Immortal! I wasn't expecting you!!!!
NOTE: Since this does use Titles it's is probably _NOT_ a good Idea to use 
it for socials( pounce, giggle, bite ).

------------------------------------------------------------------------
$o	Syntax: get $o

Ah, ha, Now we can have Real Janitors! No more dropped items sitting around.
And heck if we combine this with speech_prog we can have a janitor that people
bully	around to clean things up!
So in other words: $o is the name of an object.

	Example:
	act_prog drops
	get $o

What it does: Whenever the terminal prints out Someone drops something, 
Fred our faithful Janitor is going to pick it up. Evil huh?
 
------------------------------------------------------------------------
$O	Syntax: say $n dropped the $O

Now Fred the Janitorial Mayor can yell at you for dropping an object before 
he picks it up. Fred can get very mean when you dirty up his town.
So in other words: $O is the long name of an object.

	Example:
	act_prog drops
	say $n you BASTARD I'm Going to fine you 1000 Gold for dropping $O

What it does: Whenever Joe Blow drops ANYTHING, Fred is going to say, 
Joe you BASTARD I'm going to fine you 1000 Gold for dropping your POT PIE.

------------------------------------------------------------------------
$a	Syntax: say $n dropped $a $o

A+ in English? Wooohooo! Now I can write good room descriptions!!!
So in other words: $a checks the first letter of $o. If it is a,e,i,o,u it 
replaces $a with an, but if it starts with a constanant(sp?) it replaces $a 
with a.

	Example:
	act_prog drops
	say Wow, $n dropped $a $o

What it does: Whenever someone drops something, Fred is going to say, 
"Joe dropped a pear" or "Joe dropped an apple".

------------------------------------------------------------------------
These are Grammatical Variables

He, She, it Based upon Sex.
NOTE: There is no Syntax included because this is a very base-by-base case 
of using these. So BE CAREFUL to use them _CORRECTLY_.

$j	he, she, it based on sex of $i.
$e	he, she, it based on sex of $n.
$J	he, she, it based on sex of $r.

Him, Her, it based upon Sex.
NOTE: There is no Syntax included because this is a very base-by-base case
of using these. So BECAREFUL to use them _CORRECTLY_.

$k	him, her, it based on sex of $i.
$m	him, her, it based on sex of $n.
$K	him, her, it based on sex of $r.

his, hers, its based upon Sex.
NOTE: There is no Syntax included because this is a very base-by-base case 
of using these. So BECAREFUL to use them _CORRECTLY_.

$l	his, hers, its based on sex of $i.
$s	his, hers, its based on sex of $n.
$L	his, hers, its based on sex of $r.

------------------------------------------------------------------------

Ah Hah, Now you know how to get Your Mob to interact with what players do.  
No longer is it that the players trigger a response. That response can be 
made at a specific, char or obj or even mob!!! Wooohooo!

Now For the Tutorial Part: (or Pop Quiz Time)

Create a Janitor, that mumbles arcane curses at people who drop things.
Bonus pts, if he gives the obj back to the person who dropped it.

Create a Woman who is in awe of a man who likes to show off his muscles 
(flex) or likes to change weapons.

Create a corruptable Mayor that goes around kissing people.

Part 3
======

MudProg Keyword Trigger
-----------------------

This small snippet allows you to create what I call 'keyword' programs.
In essence, you can create a program on a room, mobile, or object that
is triggered by what a player would consider a command.

Here's an example:

   >rpedit add keyword Xorith is god
   >mea $n I do agree!
   >/s

Typing that into a room will yield this under rpstat:

   <1000hp 1000m 1000mv> rpstat
   Name: The Parlour of the Immortals.  Vnum: 1200.
   >keyword_prog Xorith is god
   mea $n I do agree!

Now watch the game:

   <1000hp 1000m 1000mv> xorith is god
   I do agree!

   <1000hp 1000m 1000mv> XORITh is GOD
   I do agree!

   <1000hp 1000m 1000mv> say Xorith is god
   You say 'Xorith is god'

   <1000hp 1000m 1000mv> 'Xorith is god
   You say 'Xorith is god'

   <1000hp 1000m 1000mv> xorith is
   Huh?

   <1000hp 1000m 1000mv> xorith is god!!
   Huh?

   <1000hp 1000m 1000mv> xorith is god --
   Huh?

   <1000hp 1000m 1000mv> 

As you can see, the program was triggered only when I typed the whole text.
It is case insensitive as well.

You can place a trigger on objects and mobiles, as well as rooms. They operate
in the same fashion, however objects have a few more options:

Adding r) before the trigger text requires the object to be in the room.
Adding i) before the trigger text requires the object to only be in the player's inventory.
Adding e) before the trigger text requires the object to only be equipped.
Adding c) before the trigger text requires the object to be in inventory or equipped.


Here's an example:

I added four programs to a sword.

   opedit sword add keyword wave sword
   opedit sword add keyword r)grin sword
   opedit sword add keyword i)kiss sword
   opedit sword add keyword e)grip sword
   opedit sword add keyword c)hug sword

Here's the OPSTAT:
   <1000hp 1000m 1000mv> opstat sword
   Name: sword academy.  Vnum: 10313.
   Short description: a finely honed sword.
   >keyword_prog wave sword
   mea $n Wave your sword? HA!
   
   >keyword_prog r)grin sword
   mea $n Grinning at a sword, eh? Riiiight...
   
   >keyword_prog i)kiss sword
   mea $n You're truely nuts, you know this right?
   
   >keyword_prog e)grip sword
   mea $n You DO know you're wielding it already, right?
   
   >keyword_prog c)hug sword
   mea $n Get a room, mate.
   
And here's the game log of me interacting with it:
   
   <1000hp 1000m 1000mv> l
   The Parlour of the Immortals
   You are lounging in a quiet cosy parlour, warmed by a gentle magical fire
   which twinkles happily in a warm fireplace. 
 
   Exits: none.
   Mystical sparkling colors converge here to form arcane runes...

In my inventory...
   <1000hp 1000m 1000mv> i
   You are carrying:
        (PROTO) a finely honed sword
   
   <1000hp 1000m 1000mv> wave sword
   Wave your sword? HA!
   
   <1000hp 1000m 1000mv> grin sword
   They aren't here.
   
   <1000hp 1000m 1000mv> kiss sword
   You're truely nuts, you know this right?
   
   <1000hp 1000m 1000mv> grip sword
   They aren't here.
   
   <1000hp 1000m 1000mv> hug sword
   Get a room, mate.

In the room....   
   <1000hp 1000m 1000mv> drop sword
   You drop a finely honed sword.
         
   <1000hp 1000m 1000mv> wave sword
   Wave your sword? HA!

   <1000hp 1000m 1000mv> grin sword
   Grinning at a sword, eh? Riiiight...

   <1000hp 1000m 1000mv> kiss sword
   They aren't here.

   <1000hp 1000m 1000mv> grip sword
   They aren't here.
   
   <1000hp 1000m 1000mv> hug sword
   They aren't here.

Wielded...
   <1000hp 1000m 1000mv> get sword
   You get a finely honed sword.

   <1000hp 1000m 1000mv> wield sword
   You wield a finely honed sword.

   <1000hp 1000m 1000mv> wave sword
   Wave your sword? HA!

   <1000hp 1000m 1000mv> grin sword
   They aren't here.

   <1000hp 1000m 1000mv> kiss sword
   They aren't here.

   <1000hp 1000m 1000mv> grip sword
   You DO know you're wielding it already, right?
   
   <1000hp 1000m 1000mv> hug sword
   Get a room, mate.

As you can see, due to the different trigger types it reacted differently.

--Xorith



