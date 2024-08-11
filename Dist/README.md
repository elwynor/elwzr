<pre>
    _____                       ____  ___    ________  __________  _____ __
   /__  /  ____  ____  ___     / __ \/   |  /  _/ __ \/ ____/ __ \/ ___// /
     / /  / __ \/ __ \/ _ \   / /_/ / /| |  / // / / / __/ / /_/ /\__ \/ /
    / /__/ /_/ / / / /  __/  / _, _/ ___ |_/ // /_/ / /___/ _, _/___/ /_/
   /____/\____/_/ /_/\___/  /_/ |_/_/  |_/___/_____/_____/_/ |_|/____(_)
                                                                             
                                 version 3.1
                     Copyright (c) 2024 Elwynor Technologies
</pre>

## WHAT IS ZONE RAIDERS?

 Zone RAIDERS! is a multi-player combat game originally based on the
 "survivalist" camps popular in the early 80's.  Players here are given the
 opportunity to be really hostile to each other with no real-life side effects.

## GAMEPLAY
 
 Zone RAIDERS! takes place in REAL TIME, on a 50 by 50 square grid. Each grid
 position is a place you can stand, so there are 2500 different locations in
 the game.  Everyone has HEALTH and ENERGY POINTS.  As you are attacked, your
 health decreases.  You never heal (without assistance) in Zone RAIDERS!,
 because the time span of the game is too short to allow it to happen in real
 life.  If your health goes below zero, you die, and are out of the game.

 A player may carry up to 10 items, including one gun-type weapon. Everyone has
 a knife, even though it does not appear on the inventory.

 EP is short for ENERGY POINTS.  When you fire your weapon, it uses up energy.
 Energy points regenerate, 1 every 2 seconds.  The number of EP used when you
 fire depends on your weapon, and ranges from 3 to 16 per shot.  It is best to
 be judicious with your weapon, or you will run out of EP very quickly.

 In Zone RAIDERS, you can move and fire in 8 different directions. These are:
 N, NW, W, SW, S, SE, E and NE.

 When you move, you make noise.  That noise can and will be heard by any player
 close enough to hear it.  You can move by RUNNING (very loud), WALKING (fairly
 quiet) or CRAWLING (nearly silent).  You can also make yourself heard bu
 speaking.  You have a choice of three speaking volumes. You can YELL, TALK or
 WHISPER.
         
 Everyone has a two-channel radio.  You can use the "General" channel which
 everyone can hear, or the "Loyal" channel, which only people on your side can
 hear.  Remember: Speaking into your radio can ALSO be heard.

 Everyone starts the game with the Basic weapon (pulse pistol).  Every shot you
 score on someone, you earn 3 "bux".  If you kill someone, you earn 15 "bux".
 You can go to the supply depots (located at 00 W10 and 00 E10) to purchase
 various items with your bux, like better weapons, medikits and the like.
 Better weapons can fire with more power (using more EP per shot) and do more
 damage.  Better weapons also are quieter (weapon fire can be heard), but have
 a shorter range.

 There are two sides: ALPHA and BRAVO.  You choose which side you want to play
 when you enter the game.  It makes no difference in the game who you shoot,
 indeed, if you are playing teams, you MUST use your loyal radio and whispering
 to make sure you don't shoot an ally!

 You can play the game any number of ways:  As a two-sided war.  As a everyman-
 for-himself free-for-all.  You can even challenge someone to a duel.  However,
 the game knows nothing of HOW you play it, it just keeps track of two sides,
 with a loyal radio channel exclusive to that.  It's up to YOU to create the
 scenario you want to play --- Zone RAIDERS enables you to be very creative in
 your game play.

 The reason all this is based on "sound" as it were, is that the game is played
 at night, in a lightly wooded forest.  Ergo, running is very loud as the
 player trips over bushes, runs into branches, etc.

 Also, while "sound levels" were mentioned, and "ranges" for weapons, you were
 NOT told what these were.  You have to discover all these factors for
 yourself.  That is what separates the beginner from the expert Zone
 RAIDERS! player.

 When you exit the game, no matter how, you are assigned a score. Depending on
 how you exit the game, you're assigned a "status".  If you left the game
 before all the players on the other team were dead, you are "AWOL", and your
 score is divided by three.  If you die, you are "Killed in Service" and
 receive your full score.  If you exit the game, but there are no players on
 the other team, you receive an "Honorable Discharge," and your full score.
 
 TIPS FOR PLAYING
<pre>
 1) Nothing is printed to your screen for "fun."  Every message you see
    has some meaning.  Don't ignore any part of the text display.

 2) Weapons can jam.

 3) If you're LOOKING, and get shot, you won't see anything.

 4) Usage of landmines:  Just <U>se them.  They rest on the current
    square.  It won't go off until someone moves onto the square.

 5) Usage of grenades:  <U>se it, then <T>hrow it.  If you don't throw
    it, it will blow up in the square you're in.

 6) You receive no bux or score for using landmines or grenades.

 7) Alpha players start out near 15N 0E, Bravo near 15S 0E.

 8) Landmines go dud in 10 minutes.
</pre> 
## OTHER CONSIDERATIONS
 
 The algorithm for deriving a user's score is annoying at best.  There's a lot
 of factors that are used with varying wieghts to create the score.  Take a
 peek in the c-source for the formula itself.

 Loreli, the original BBS, liked to hold Zone RAIDERS! competitions. These are
 a lot of fun! They set them up in a round-robin competition. Two players at a
 time enter Zone Raiders, while a Sysop moderator remains at 0,0 to direct the
 game.  The person who survives 2 out of 3 games moves to the next round.

## SYSOP COMMANDS
 
 Zone RAIDERS! has two hidden commands.  The first, usable only by the SYSOP
 flagged user, is CONTEST.  Use it like this:
<pre>
 CONTEST <user-id>
</pre>
 This will give that user 24 health points, 100 energy points, and 100 bux. We
 use this option at the beginning of our competitions.

 The second command, known informally as the CHEAT button, is typed like this:
<pre>
    !depot!
</pre>
 This command takes give you 5000 bux and drops you into the ZR Depot.  DON'T
 GIVE THIS COMMAND OUT TO JUST ANYONE! It's there for testing/debugging of the
 game.  You can use it to purchase a lot of firepower for managing the ZR
 competitions.

## INSTALLATION AND CONFIGURATION
 
 Simply unzip the archive to your BBS server directory, add it to your menu,
 configure the MSG file to your liking, and start the BBS! It's that easy!

 Zone RAIDERS! has one MSG file. Within it, you can define the key required 
 to play the game, and decide whether to show a message advertising the game 
 when users log-on. You can also set credit consumption rate, but normally
 on modern systems you leave it set to 1. You can also set the key required
 to use the SysOp commands described above.
 
 There are text blocks to configure to your liking, though! For speed, much
 of the game short text is embedded within the game.
 
## MODULE HISTORY
 
 Zone RAIDERS! was one of the very earliest multi-user combat games written
 for The Major BBS. It was designed and developed by Sean M. Puckett of 
 Codesmiths in 1989.
 
 In 1992, Skip Potter of Crystal Vision Inc. (CVI) upgraded the game to 
 work on The Major BBS v6.  
 
 There was mention of a Zone Raiders II, which included computer-controlled
 players. We do not have the source to that, and don't know if it was ever
 completed for full release. 
 
 Zone RAIDERS! was upgraded to Worldgroup 3.2 in 2023, and The Major BBS v10
 at the same time in April 2023. In August 2024, it was released on a single
 code base to Elwynor's github!
 
## LICENSE

 This project is licensed under the AGPL v3. Additional terms apply to 
 contributions and derivative projects. Please see the LICENSE file for 
 more details.

## CONTRIBUTING

 We welcome contributions from the community. By contributing, you agree to the
 terms outlined in the CONTRIBUTING file.

## CREATING A FORK

 If you create an entirely new project based on this work, it must be licensed 
 under the AGPL v3, assign all right, title, and interest, including all 
 copyrights, in and to your fork to Rick Hadsall and Elwynor Technologies, and 
 you must include the additional terms from the LICENSE file in your project's 
 LICENSE file.

## COMPILATION

 This is a Worldgroup 3.2 / Major BBS v10 module. It's compiled using Borland
 C/C++ 5.0 for Worldgroup 3.2. If you have a working Worldgroup 3.2 development
 kit, a simple "make -f ELWZR" should do it! For Major BBS v10, import this
 project folder in the isv/ subtree of Visual Studio 2022, right click the
 project name and choose build! When ready to build for "release", ensure you
 are building for release.

## PACKING UP

 The DIST folder includes all of the items that should be packaged up in a 
 ELWZR.ZIP. When unzipped in a Worldgroup 3.2 or Major BBS V10 installation 
 folder, it "installs" the module.
