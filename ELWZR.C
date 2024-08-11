/*****************************************************************************
 *                                                                           *
 *    Zone Raiders                                                     v3.1  *
 *                                                                           *
 *    zoneraid.c                                                             *
 *    the game ZONE RAIDERS!                                                 *
 *                                                                           *
 *    by Sean Puckett                                                        *
 *    for Codesmiths, Inc.                                                   *
 *                                                                           *
 *    December 1989                                                          *
 *                                                                           *
 *    v6 port: Skip Potter/CVI December 1992                                 *
 *    WG3.2 port: Rick Hadsall/ELW 2023 April 2023                           *
 *    V10 port: Rick Hadsall/ELW April 2023                                  *
 *    V10/WG32 single kit, updates: Rick Hadsall/ELW August 10 2024          *
 *                                                                           *
 * Copyright (C) 2024 Rick Hadsall.  All Rights Reserved.                    *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "elwzr.h"

typedef struct PYRO PYRO;
typedef struct TOPTEN TOPTEN;

SHORT zrlon(VOID);
SHORT crszr(VOID);
VOID hupzr(VOID);
VOID dfsthn(VOID);
VOID shtzr(VOID);
VOID zrtime(VOID);
SHORT fsign(SHORT a);
VOID inst10(SHORT awol);
VOID setzr(VOID);
struct ZRUSER *gtzrus(INT usrn);
VOID look(INT who, SHORT max, SHORT di);
VOID blast(PYRO *obj);
VOID lonzr(VOID);
VOID newgam(VOID);
VOID outnot(INT side, INT user);
VOID EXPORT newply(SHORT side);
VOID shwsta(VOID);
VOID shwhlp(VOID);
VOID EXPORT whoply(VOID);
VOID exitgm(SHORT qtdy);
SHORT getdir(CHAR *s);
SHORT dirfrom(SHORT xc, SHORT yc, SHORT x, SHORT y);
VOID hdlsndu(INT from, SHORT type, SHORT sndlvl);
VOID hdlsnd(SHORT xloc, SHORT yloc, SHORT type, SHORT sndlvl);
VOID hdlspk(SHORT xloc, SHORT yloc, SHORT type, SHORT sndlvl, CHAR *messg);
VOID depot(VOID);
VOID moveto(SHORT x, SHORT y);
VOID move(CHAR *whatd, SHORT option);
SHORT cantmove(VOID);
VOID talk(CHAR *msg, SHORT type);
VOID inflict(INT cre, INT who, SHORT damg);
VOID fire(CHAR *dir, SHORT power);
VOID radio(CHAR *msg, INT towho);
VOID inv(VOID);
VOID insertg(SHORT dmg);
VOID insertm(SHORT dmg);
VOID use(CHAR *what);
VOID throw(CHAR *d, SHORT dist);
VOID binox(CHAR *d);
VOID attack(CHAR *who);
VOID inpzr(VOID);
VOID prfwm(TOPTEN *tt);
VOID warmem(VOID);
VOID hdlmm(VOID);
VOID EXPORT ply(SHORT side);
VOID hdlsid(VOID);
SHORT haveweap(VOID);
VOID depzr(VOID);
SHORT getnum(CHAR *us);
SHORT spinpak(VOID);
VOID purch(VOID);
SHORT whereinpak(SHORT obj);
VOID sell(VOID);
VOID offer(VOID);
SHORT zrinj(VOID);
VOID zrdela(CHAR *userid);

static INT zrstt;
struct module modzr={         /* module interface block               */
     "",                      /*    name used to refer to this module */
     zrlon,                   /*    user logon supplemental routine   */
     crszr,                   /*    input routine if selected         */
     dfsthn,                  /*    status-input routine if selected  */
     zrinj,                   /*    "injoth" routine for this module  */
     NULL,                    /*    user logoff supplemental routine  */
     hupzr,                   /*    hangup (lost carrier) routine     */
     NULL,                    /*    midnight cleanup routine          */
     zrdela,                  /*    delete-account routine            */
     shtzr                    /*    finish-up (sys shutdown) routine  */
};


static
struct ZRUSER {
	SHORT xc;			/* x coord in grid */
	SHORT yc;			/* y coord in grid */
	SHORT side;		/* alpha = 0, bravo = 1 */
	SHORT timeout;	/* time remaining 'till user can move again */
	SHORT ep;			/* energy points */
	SHORT hp;			/* hit pointz */
	SHORT weapon;		/* weapon type 0-4 */
	SHORT dead;		/* flag if you dead */
	SHORT kills;		/* number of kills */
	SHORT shots;		/* shots fired */
	SHORT hits;		/* hits */
	LONG time;		/* time in game */
	SHORT bux;		/* bux */
	SHORT look;		/* how far to look when timeout runs out */
	SHORT lookd;		/* direction to look when timeout is over */
	SHORT lookrnd;	/* random factor in looks.. changes wen move */
	CHAR inv[10];	/* inventory */
	SHORT inpak;		/* buy/sell item */
} *zruser, *zrptr;

/*
User-ID                        Shots Hits  Pct. Kills Time     Overall Score
------------------------------ ----- ----- ---- ----- -------- ----------------
%-30.30s %5.5d %5.5d %3.3d%% %5.5d %3.3d:%2.2d %ld (%s)

"%-15.15s  %5.5d  %5.5d  %3.3d%%  %5.5d  %3.3dm %2.2ds  %ld (%s)\r"
*/

static
struct TOPTEN {
    CHAR name[UIDSIZ];    // 00-29
	SHORT shots;           // 30-31
	SHORT hits;            // 32-33
	SHORT pct;             // 34-35
	SHORT kills;           // 36-37
	SHORT min;             // 38-39
	SHORT sec;             // 40-41
	SHORT awol;            // 42-43
	LONG score;            // 44-47
} entry, *tt2; //, *tt1; //size:48 tt1 is alltime, tt2 is today

static
struct ZRSID {
	SHORT homx;		/* home x location */
	SHORT homy;		/* home y location */
	SHORT flgx;		/* flag x pos */
	SHORT flgy;		/* flag y pos */
	SHORT nply;		/* number of players */
} ab[2];

static
struct ZROBJ {
	CHAR *name;		/* obj name */
	CHAR *desc;		/* obj description  */
	SHORT price;		/* price */
} zobj[]={
{"Pulsegun","Standard Issue, Med range",10},
{"Disruptor","Good range, Better Damage, More Efficient",50},
{"Lasgun","Shorter range, More efficient, Quieter",110},
{"Laser-rifle","Better range, Less efficient than pistol, Noisy",170},
{"Phaser","Very good Damage, SHORT Range, Quiet",180},
{"Plasmagun","Shorter range, Efficient, Lots of damage",300},
{"Gaussrifle","Very powerful, Very loud, Very efficient",540},

{"Medikit","Heals 10 points",35},
{"Epak","200 EP",20},
{"Powercell","EP recovers 2x as fast",135},
{"Binoculars","Lets you look in a direction (LN for example)",85},
{"2kx Grenade","Small blast radius",5},
{"7kx Grenade","Medium blast radius",15},
{"15kx Grenade","Large blast radius",30},
{"Lm2 Landmine","Small blast radius",4},
{"Lm7 Landmine","Medium blast radius",12},
{"Lm15 Landmine","Large blast radius",24},
{"","",-1}};

static SHORT weapdm[]={1,2,3,3,4,5,8};/* max damage */
static SHORT weaprn[]={6,6,5,7,4,4,9};/* range */
static SHORT weapep[]={7,6,5,6,4,3,2};/* energy per point of damage */
static SHORT weapsn[]={7,7,6,8,5,5,14};/* sound when fired */
static SHORT weapjm[]={99,12,16,22,99,4,3};

#define IPUL 0
#define IDIS 1
#define ILAS 2
#define ILRI 3
#define IPHA 4
#define IPLA 5
#define IGAU 6
#define IMED 7
#define IEPA 8
#define IPOW 9
#define IBIN 10
#define I2KX 11
#define I7KX 12
#define I15K 13
#define ILM2 14
#define ILM7 15
#define ILM1 16

static
struct PYRO {
	SHORT x;
	SHORT y;
	SHORT time;
	SHORT damage;
} grenade[50],landmine[50];

/****************************************************************************/

static SHORT newst;
static SHORT sidecnt=0;
static SHORT dist;
static SHORT plsen=0;
static HMCVFILE zrmb;
static DFAFILE *zrdat;
static CHAR sel;
static SHORT zrcst;
static CHAR *zrkey;
static SHORT showzrlon;

/****************************************************************************/

static CHAR nschr[]={'N','0','S'};
static CHAR wechr[]={'W','0','E'};

static CHAR *dirxl[]={"N","NE","E","SE","S","SW","W","NW"};
static SHORT dlx[]={0,1,1,1,0,-1,-1,-1};
static SHORT dly[]={-1,-1,0,1,1,1,0,-1};
static SHORT mnoise[]={3,8,1};  /* noise factor WALK, RUN, CRAWL */
static SHORT mtime[]={3,1,5};/* time in secs WALK, RUN, CRAWL */
static SHORT spkvl[]={4,12,2};/* noise factor for TALK, YELL, WHISPER */

static CHAR *noiset[]={
"walking",
"running",
"crawling",
"explosions",
"howls of pain",
"shrieks...and a body hitting the ground",
"radio static",
"pulsegun whine",
"disruptor static",
"lasgun fire",
"laser fire",
"phaser bursts",
"plasma crackle",
"gaussrifle fire",
"parachute landing",
"thud"};

static CHAR *noisein[]={
"Distant",
"Faint",
"Quiet",
"You hear",
"Nearby",
"Close",
"Loud",
"Very loud"};

static CHAR *sndfmt={"%s %s from the %s.\r"};
static CHAR *ssndfmt={"%s %s.\r"};

static CHAR *diststr[10]={
"tremendously far away ",
"very far off ",
"far away ",
"fairly far off ",
"somewhat distant "
"distinct ",
"",
"near ",
"very near ",
"proximal "};

static CHAR *says[]={
"voice",
"yell",
"whisper"};

static CHAR *said[]={
"Uttered.\r",
"Yelled.\r",
"Whispered.\r"};

static CHAR *sayfmt={"A %s%s \"%s\" from the %s.\r"};
static CHAR *ssayfmt={"%s's %s: \"%s\"\r"};

static CHAR *rat[]={"K.I.A.","Honored","A.W.O.L.","Dishonored"};

#define VERSION "3.1"

/****** START OF SOURCE CODE ******/

VOID EXPORT
init__elwzr(VOID) /* init zone raider */
{
   stzcpy(modzr.descrp,gmdnam("ELWZR.MDF"),MNMSIZ);
   zrstt=register_module(&modzr);

   zrmb=opnmsg("elwzr.mcv");
   zrkey=stgopt(ZRKEY);
   zrcst=(SHORT)numopt(ZRCST,-32000,32000);
   showzrlon = ynopt(ZRLON);

   newgam();
   rtkick(1,zrtime);

   zruser=(struct ZRUSER *)alczer(nterms*sizeof(struct ZRUSER)); 
   tt2=(struct TOPTEN *)alczer(10*sizeof(struct TOPTEN)); // alczer(n)
   setmem(&entry,sizeof(struct TOPTEN),0);

   zrdat=dfaOpen("ELWZR.DAT",sizeof(struct TOPTEN),NULL);
   dfaSetBlk(zrdat);	

   shocst(spr("ELW Zone RAIDERS! v%s", VERSION), "(C) Copyright 2024 Elwynor Technologies - www.elwynor.com");
}

SHORT zrlon(VOID)
{
	// login
	if (showzrlon) {
		setmbk(zrmb);
		prfmsg(ZRLONMSG);
		outprf(usrnum);
		rstmbk();
	}
	return(0);
}

SHORT
crszr(VOID) /* cr terminated entry */
{
	setzr();
	sel=(CHAR)tolower(margv[0][0]);
	switch(newst=(SHORT)usrptr->substt) {
	case 0:
		prfmsg(newst=ZRM);
		break;
	case ZRM:
	case ZRP:
		hdlmm();
		break;
	case ZRSIDE:
		hdlsid();
		break;
	case PLYZR:
		if (zrptr->dead) {
			if (sameas(margv[0],"ok")) {
				exitgm(0);
			} else {
				prf("Type 'ok' and press RETURN.\r");
			}
		} else {
            inpzr();
		}
		break;
	case ZRH5:
		prfmsg(newst=ZRP);
		break;
	case ZRH1:
	case ZRH2:
	case ZRH3:
	case ZRH4:
		if (sel=='x') {
			prfmsg(newst=ZRP);
		} else {
			prfmsg(++newst);
		}
		break;
	case DEPOTM:
	case DEPOTP:
		depzr();
		break;
	case DPUR:
		purch();
		break;
	case DSELLIN:
		sell();
		break;
	case DOFFER:
		offer();
		break;
	default:
		newst=0;
		break;
	}

   usrptr->substt=newst;
	outprf(usrnum);
	if (!newst) return 0;
	return 1;
}

VOID
hupzr(VOID) /* user hangs up */
{
	if ((zrptr=gtzrus(usrnum))!=NULL) {
		exitgm(1);
	}
}

SHORT fsign(SHORT a)
{
	if (a<0) return 0;
	if (a==0) return 1;
	return 2;
}

VOID
shtzr(VOID)
{
	clsmsg(zrmb);
	dfaClose(zrdat);
}

VOID
zrtime(VOID)
{
    struct ZRUSER *zeep;
	SHORT a;

	if (++plsen==2) plsen=0;
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL) {
			if (zeep->timeout) {
				zeep->timeout--;
				if (!(zeep->timeout)) {
					if (zeep->look) {
						look(a,zeep->look,zeep->lookd);
					}
					zeep->look=0;
					prf("GO!\r");
					outprf(a);
				}
			}
			if (!plsen) {
				if (zeep->ep<100 && whereinpak(IPOW)!=-1) zeep->ep++;
				if (zeep->ep<100) zeep->ep++;
			}
			zeep->time++;
		}
	}
	for (a=0; a<50; a++) {
		if (grenade[a].damage) {
			if (!(--grenade[a].time)) {
				blast(&grenade[a]);
			}
		}
		if (landmine[a].damage) {
			if (!(--landmine[a].time)) {
				landmine[a].damage=0;
			}
		}
	}
    rtkick(1,zrtime);
}

VOID
inst10(SHORT awol)
{
   static TOPTEN him;
	SHORT a;

	strcpy(him.name,usaptr->userid);
	him.kills=zrptr->kills;
	him.shots=(zrptr->shots);
	him.hits=(zrptr->hits);
	him.pct=(SHORT)(((LONG)him.hits*100l)/(LONG)(max(1,him.shots)));
	him.sec=(SHORT)(zrptr->time % 60l);
	him.min=(SHORT)(zrptr->time / 60l);
	him.awol=awol;
	him.score=((((LONG)him.hits)*300L)/(LONG)(max(1,him.shots)))+1l;
	him.score+=250*him.kills;
	if (him.min>him.kills) {
		him.score*=((((LONG)him.kills)*10l)/(LONG)(max(1,him.min)))+1l;
	}
	if ((him.kills*10)>him.hits && awol==1) {
		awol=3;
	}
	if (awol>1) him.score/=3;

	dfaSetBlk(zrdat);
	dfaInsertDup(&him); // insert the user's game record into the data file
	// Today's Top 10
	for (a=0; a<10; a++) {
		if (tt2[a].score<=him.score) {
			if (a!=9) {
                memmove(&tt2[a+1],&tt2[a],(9-a)*sizeof(struct TOPTEN));
				strcpy(tt2[a].name,him.name);
				tt2[a].shots = him.shots;
				tt2[a].hits = him.hits;
				tt2[a].pct = him.pct;
				tt2[a].kills = him.kills;
				tt2[a].min = him.min;
				tt2[a].sec = him.sec;
				tt2[a].awol = him.awol;
				tt2[a].score = him.score;
				break;
			}
		}
	}
}

VOID
setzr(VOID)
{
	setmbk(zrmb);
	dfaSetBlk(zrdat);
	zrptr=&zruser[usrnum];
}

struct
ZRUSER *gtzrus(INT usrn)/* get address of valid zr player's data */
{
	if (usroff(usrn)->usrcls<=SUPIPG) return NULL;
    if (usroff(usrn)->state!=zrstt) return NULL;
	if (usroff(usrn)->substt!=PLYZR) return NULL;
    if (zruser[usrn].dead) return NULL;
    return &zruser[usrn];
}

VOID
look(INT who, SHORT max, SHORT di)
{
    struct ZRUSER *zeep,*zwho;
	INT a;
	SHORT dir, ms;

	if ((zwho=gtzrus(who))==NULL) return;
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && a!=who) {
			dir=dirfrom(zwho->xc,zwho->yc,zeep->xc,zeep->yc);
			ms=min(9,dist);
			ms=max(0,ms);
			if ((di==-1 || di==dir) && dist+(zwho->lookrnd)<max) {
				if (dist) {
					prf("> Someone %sto the %s.\r",diststr[9-ms],dirxl[dir]);
				} else {
                    prf("> %s is here.\r",uacoff(a)->userid);
				}
				outprf(who);
			}
		}
	}
	*prfptr=0;
}

VOID
blast(PYRO *obj)
{
	INT a;
	SHORT rng;
    struct ZRUSER *zeep;

	usrnum+=100;
	hdlsnd(obj->x,obj->y,3,(rng=obj->damage)/2+2);
	usrnum-=100;
	rng/=3;
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL) {
			dirfrom(obj->x,obj->y,zeep->xc,zeep->yc);
			if (dist<=rng) {
				inflict(-1,a,obj->damage-(dist*3));
			}
		}
	}
	obj->damage=0;
}

VOID
lonzr(VOID)
{
	setzr();
}

VOID
newgam(VOID) /* a new game */
{
	SHORT a;

	for (a=0; a<2; a++) {
		ab[a].homx=0;
		ab[a].nply=0;
	}
	ab[0].homy=-10;
	ab[1].homy=10;
}




VOID
outnot(INT side, INT user)/* outprf NOT to side and NOT to user */
{
    struct ZRUSER *zeep;
	INT a;

	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && a!=user && zeep->side!=side) {
			outprf(a);
		}
	}
	clrprf();
	*prfptr=0;
}



VOID EXPORT
newply(SHORT side)
{
	SHORT s,a;

	if (side==-1) {
		s=0;
		if (ab[0].nply==ab[1].nply) {
			s=(sidecnt=1-sidecnt);
		} else if (ab[0].nply>ab[1].nply) {
			s=1;
		}
	} else {
		s=side;
	}
	prf("You are %s\r",s?"Bravo":"Alpha");

	for (a=0; a<10; zrptr->inv[a++]=255);
	zrptr->xc=ab[s].homx+5-(rand()%11);
	zrptr->yc=ab[s].homy+5-(rand()%11);
	zrptr->side=s;
	zrptr->ep=10;
	zrptr->hp=24;
	zrptr->inv[0]=0;
	zrptr->weapon=0;
	zrptr->bux=0;
	ab[s].nply++;
	outprf(usrnum);
}



VOID
shwsta(VOID)
{
/*

* Location %u,%u  Loyalty %s
* Energy %u  Health %u
* Weapon %s

*/
    setzr();
	prf("* Location %c%d %c%d  Loyalty %s\r",nschr[fsign(zrptr->yc)],abs(zrptr->yc),wechr[fsign(zrptr->xc)],abs(zrptr->xc),zrptr->side ? "Bravo" : "Alpha" );
	prf("* Energy %u  Health %u  Bux %u\r",zrptr->ep,zrptr->hp,zrptr->bux);
	prf("* Weapon %s  Bagged %u\r",zrptr->weapon==-1 ? "None" : zobj[zrptr->weapon].name,zrptr->kills);
	look(usrnum,(SHORT)2,(SHORT) - 1);
}

VOID
shwhlp(VOID)
{
	prfmsg(ZRGHLP);
}


VOID EXPORT
whoply(VOID)
{
    struct ZRUSER *zeep;
	INT a;

	prf(" --- Current Players ---\r\r");
	prf("Alpha: ");
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && zeep->side==0) {
            prf("%s ",uacoff(a)->userid);
		}
	}
	prf("\r\rBravo: ");
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && zeep->side==1) {
            prf("%s ",uacoff(a)->userid);
		}
	}
	prf("\r");
}



VOID
exitgm(SHORT qtdy)
{
	INT a,s;

	s=zrptr->side;
	if (qtdy) {
		if (ab[1-s].nply==0) inst10(1); else inst10(2);
	} else {
		inst10(0);
	}
	ab[s].nply--;
	prf("Ally %s %s!\r",usaptr->userid,qtdy ? "quit" : "was killed");
	outnot(1-s,usrnum);
	prf("Enemy %s %s!\r",usaptr->userid,qtdy ? "quit" : "-- Terminated");
	if (ab[s].nply==0) {
		prf("No players on the enemy team!\r");
	}
	outnot(s,-1);
	prf("Exiting Zone RAIDERS!\r\r\r");
	newst=0;
	for (a=0; a<nterms; a++) {
		if (gtzrus(a)!=NULL) return;
	}
	for (a=0; a<50; a++) {
		grenade[a].damage=0;
		landmine[a].damage=0;
	}
}



SHORT
getdir(CHAR *s)
{
	SHORT a;

	for (a=0; a<8; a++) {
		if (sameas(s,dirxl[a])) {
			return a;
		}
	}
	return -1;
}



SHORT
dirfrom(SHORT xc, SHORT yc, SHORT x, SHORT y)/* return direction from center */
{
	SHORT xd,yd;

	xd=x-xc;
	yd=y-yc;

	dist=(abs(xd)+abs(yd)); /* cheap approximation of distance */
	if (abs(xd)*2<=abs(yd)) return yd<0 ? 0 : 4;  /* figure n/s */
	if (abs(yd)*2<=abs(xd)) return xd<0 ? 6 : 2;  /* figure w/e */
	if (xd<0) return yd<0 ? 7 : 5; else return yd<0 ? 1 : 3;
}


VOID
hdlsndu(INT from, SHORT type, SHORT sndlvl)/* handle noise made */
{
    struct ZRUSER *ze2,*zeep;
	SHORT a,dr,sndlv;

   // Rick: I added the && ze2!=NULL three lines below in the if because it was causing a GP when ge2 was NULL. It seems to play normally now?
	ze2=gtzrus(from);
	for (a=0; a<nterms; a++) {
		if (a!=from && (zeep=gtzrus(a))!=NULL && ze2!=NULL) {
			dr=dirfrom(zeep->xc,zeep->yc,ze2->xc,ze2->yc);
			sndlv=sndlvl-dist;
			sndlv=max(0,sndlv);
			sndlv=min(7,sndlv);
			if (sndlv--) {
				if (dist) {
					prf(sndfmt,noisein[sndlv],noiset[type],dirxl[dr]);
				} else {
					prf(ssndfmt,noisein[sndlv],noiset[type]);
				}
				outprf(a);
			}
		}
	}
}


VOID
hdlsnd(SHORT xloc, SHORT yloc, SHORT type, SHORT sndlvl)/* handle noise made */
{
    struct ZRUSER *zeep;
	INT a;
	SHORT dr, sndlv;

	for (a=0; a<nterms; a++) {
		if (a!=usrnum && (zeep=gtzrus(a))!=NULL) {
			dr=dirfrom(zeep->xc,zeep->yc,xloc,yloc);
			sndlv=min(8,max(0,sndlvl-dist));
			if (sndlv--) {
				if (dist) {
					prf(sndfmt,noisein[sndlv],noiset[type],dirxl[dr]);
				} else {
					prf(ssndfmt,noisein[sndlv],noiset[type]);
				}
				outprf(a);
			}
		}
	}
}

VOID
hdlspk(SHORT xloc, SHORT yloc, SHORT type, SHORT sndlvl, CHAR *messg)/* handle noise made */
{
    struct ZRUSER *zeep;
	INT a;
	SHORT dr, sndlv;

	for (a=0; a<nterms; a++) {
		if (a!=usrnum && (zeep=gtzrus(a))!=NULL) {
			dr=dirfrom(zeep->xc,zeep->yc,xloc,yloc);
			sndlv=min(9,max(0,sndlvl-dist));
			if (sndlv--) {
				if (dist) {
					prf(sayfmt,diststr[sndlv],says[type],messg,dirxl[dr]);
				} else {
					prf(ssayfmt,usaptr->userid,says[type],messg);
				}
				outprf(a);
			}
		}
	}
	prf("%s",said[type]);
}



VOID
depot(VOID)
{
	prfmsg(newst=DEPOTM);
}



VOID
moveto(SHORT x, SHORT y)
{
    struct ZRUSER *zeep;
	INT a;

	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && zeep->xc==x && zeep->yc==y && a!=usrnum) {
			prf("%s arrives!\r",usaptr->userid);
			outprf(a);
		}
	}
	*prfptr=0;
	zrptr->lookrnd=(rand()%5)-2;
	zrptr->xc=x;
	zrptr->yc=y;
	for (a=0; a<50; a++) {
		if (landmine[a].damage) {
			if (landmine[a].x==x && landmine[a].y==y) {
				blast(&landmine[a]);
			}
		}
	}
}



VOID
move(CHAR *whatd, SHORT option)
{
	SHORT dir,x,y;

	if (-1==(dir=getdir(whatd))) return;
	x=zrptr->xc+dlx[dir];
	y=zrptr->yc+dly[dir];
	if (x<-25 || x>25 || y<-25 || y>25) {
		prf("Can't move out of battle field.\r");
	} else {
		moveto(x,y);
		if (!(zrptr->dead)) {
			hdlsnd(x,y,option,mnoise[option]);
			zrptr->timeout=mtime[option];
			prf("At %c%d %c%d (%u sec)\r",nschr[fsign(y)],abs(y),wechr[fsign(x)],abs(x),mtime[option]);
			look(usrnum,(SHORT)2,(SHORT) - 1);
			if ((x==-10 || x==10) && y==0) {
				depot();
				zrptr->timeout=0;
			}
		}
	}
	outprf(usrnum);
	*prfptr=0;
}



SHORT
cantmove(VOID)
{
	if (zrptr->timeout) {
		prf("Last move still in progress!\r");
		return 1;
	}
	return 0;
}



VOID
talk(CHAR *msg, SHORT type)
{
	rstrin();
	hdlspk(zrptr->xc,zrptr->yc,type,spkvl[type],msg);
	prf("GO!\r");
}



VOID
inflict(INT cre, INT who, SHORT damg)
{
    struct ZRUSER *zeep,*cred;

	if (damg<=0) return;
	cred=gtzrus(cre); // Rick: If this is null I should check for it or it will GP
	if (cred == NULL) return; 
	if ((zeep=gtzrus(who))==NULL) return;
	if (cre>=0) {
		cred->hits++;
	}
	if (damg>zeep->hp) {
		hdlsndu(who,5,13);
		prf("You died.\rType 'ok' and press RETURN.\r");
		zeep->dead=1;
		outprf(who);

		if (cre>=0) {
            prf("\r\r   *** You killed %s!\r\r",uacoff(who)->userid);
			cred->kills++;
			cred->bux+=25;
		}
	} else {
		hdlsndu(who,4,5+(rand()%4));
		zeep->hp-=damg;
		zeep->timeout=min(3,zeep->timeout);
		zeep->look=0;
		prf("Damage for %u - %u left!\r",damg,zeep->hp);
		outprf(who);

		if (cre>=0) {
			cred->bux+=2;
		}
	}
	*prfptr=0;
}



VOID
fire(CHAR *dir, SHORT power)
{
    struct ZRUSER *zeep;
	SHORT pu, w, di;
	INT a;

	w=zrptr->weapon;
	if (w==-1) {
		prf("You don't have a weapon!\r");
		return;
	}
	if (power>weapdm[w] || power<1) {
		prf("Your weapon can only handle energy levels from 1 to %u\r",weapdm[w]);
		return;
	}
	pu=power*weapep[w];
	if (pu>zrptr->ep) {
		prf("Need %u EP to fire.\r",pu);
		return;
	}
	if ((di=getdir(dir))==-1) {
		prf("Unrecognizable direction.  Use FN FNE FE FSE FS FSW FW FNW\r");
		return;
	}
	if ((rand()%weapjm[w])==0) {
		zrptr->timeout=1;
		prf("Weapon jammed!\r");
		return;
	}
	hdlsnd(zrptr->xc,zrptr->yc,7+w,weapsn[w]);
	zrptr->ep-=pu;
	zrptr->shots++;
	prf("Firing (%u EP)...\r",pu);
	outprf(usrnum);
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL && a!=usrnum) {
			if (dirfrom(zrptr->xc,zrptr->yc,zeep->xc,zeep->yc)==di) {
				if (dist<weaprn[w]) {
					inflict(usrnum,a,power);
				}
			}
		}
	}
	*prfptr=0;
	zrptr->timeout=1;
}



VOID
radio(CHAR *msg, INT towho)
{
	rstrin();
	prf("%s radio: %s\r",towho==-1 ? "General" : "Loyal",msg);
	outnot(towho,usrnum);
	hdlsndu(usrnum,(SHORT)6,(SHORT)3);
	prf("Radioed.\rGO!\r");
}



VOID
inv(VOID)
{
	SHORT a;

	prf(">> %u Bux\r",zrptr->bux);

	for (a=0; a<10; a++) {
		if (zrptr->inv[a]!=255) prf(">> %s\r",zobj[zrptr->inv[a]].name);
	}
}



VOID
insertg(SHORT dmg)
{
	SHORT a;

	for (a=0; a<50; a++) {
		if (grenade[a].damage==0) {
			grenade[a].time=10;
			grenade[a].x=zrptr->xc;
			grenade[a].y=zrptr->yc;
			grenade[a].damage=dmg;
			return;
		}
	}
	prf("Tell Ingy there's not enough Grenade slots.\r");
}



VOID
insertm(SHORT dmg)
{
	SHORT a;

	if (abs(zrptr->xc)==10 && zrptr->yc==0) {
		prf("The Depot minesweep-robot removes the landmine as soon as you place it.\r");
		return;
	}
	for (a=0; a<50; a++) {
		if (landmine[a].damage==0) {
			landmine[a].time=600;
			landmine[a].x=zrptr->xc;
			landmine[a].y=zrptr->yc;
			landmine[a].damage=dmg;
			return;
		}
	}
	prf("Tell Ingy there's not enough Landmine slots.\r");
}



VOID
use(CHAR *what)
{
	SHORT is,pip,time;

	if ((is=getnum(what))==-1) {
		prf("You don't have a %s!\r",what);
		return;
	} else if ((pip=whereinpak(is))==-1) {
		prf("You don't have a %s!\r",what);
		return;
	}
	if (is<IMED) {
		prf("You're already using your weapon!\r");
		return;
	}
	time=0;
	switch (is) {
	case IMED:
		prfmsg(ZRIMED,zrptr->hp=min(24,zrptr->hp+10));
		time=10;
		break;
	case IEPA:
		prfmsg(ZRIEPA,zrptr->ep=zrptr->ep+200);
		time=2;
		break;
	case IPOW:
		prfmsg(ZRIPOW);
		return;
	case IBIN:
		prfmsg(ZRBINOX);
		return;
	case I2KX:
		prfmsg(ZRGREN);
		insertg(2);
		break;
	case I7KX:
		prfmsg(ZRGREN);
		insertg(7);
		break;
	case I15K:
		prfmsg(ZRGREN);
		insertg(15);
		break;
	case ILM2:
		prfmsg(ZRMINE);
		insertm(2);
		break;
	case ILM7:
		prfmsg(ZRMINE);
		insertm(7);
		break;
	case ILM1:
		prfmsg(ZRMINE);
		insertm(15);
		break;

	}
	if (time) {
		prf("(%u sec)\r",zrptr->timeout=time);
	}
	zrptr->inv[pip]=255;
}



VOID
throw(CHAR *d,SHORT throw_dist)
{
	SHORT a,dir;

	if (throw_dist <1 || throw_dist>6) {
		prf("Specify a distance (like TN 3) from 1 to 6.\r");
		return;
	} else if ((dir=getdir(d))==-1) {
		prf("Specify a direction (like TN TNE etc) and a range (i.e. TSW 4).\r");
		return;
	}
	zrptr->timeout=3;
	for (a=0; a<50; a++) {
		if (grenade[a].damage>0 && zrptr->xc==grenade[a].x && zrptr->yc==grenade[a].y) {
			grenade[a].x+= throw_dist *dlx[dir];
			grenade[a].y+= throw_dist *dly[dir];
			hdlsnd(grenade[a].x,grenade[a].y,15,2);
			prf("Threw a grenade %u to the %s! (3 sec)\r", throw_dist,dirxl[dir]);
			return;
		}
	}
	prf("Found nothing to throw. (3 sec)\r");
}



VOID
binox(CHAR *d)
{
	SHORT dir;

	if (whereinpak(IBIN)==-1) {
		prf("You don't have binoculars.\r");
	} else if ((dir=getdir(d))==-1) {
		prf("Unrecognizable direction.  Use LN LNW LW LSW LS LSE LE LNE.\r");
	} else {
		prf("Looking %s...(5 sec)\r",dirxl[dir]);
		zrptr->timeout=5;
		zrptr->look=8;
		zrptr->lookd=dir;
	}
}



VOID
attack(CHAR *who)
{
    struct ZRUSER *zeep;
	SHORT mn,dmg;
	INT a, t1=nterms;

	mn=0;
	for (a=0; a<nterms; a++) {
		if ((zeep=gtzrus(a))!=NULL) {
            if (sameto(who,(uacoff(a)->userid)) && zeep->xc==zrptr->xc && zeep->yc==zrptr->yc) {
				mn++;
				t1=a;
			}
		}
	}
	if ( (a == nterms) || (mn != 1) ) {
		prf("Attack who?\r");
		return;
	}
	if (t1==usrnum) {
		prf("No, you can't stab yourself.\r");
		return;
	}
	dmg=1+(rand()%3);
	zrptr->shots++;
	prf("%s knifed you!\r",usaptr->userid);
	outprf(t1);
	*prfptr=0;
	inflict(usrnum,t1,dmg);
    prf("Knifed %s for %u! (4 sec)\r",uacoff(t1)->userid,dmg);
	zrptr->timeout=4;
}



VOID
inpzr(VOID)
{
	CHAR op;
    struct ZRUSER *zeep;

	op=(CHAR)tolower(margv[0][0]);
	setmbk(zrmb);
	if (margc==0) {
		shwsta();
	} else if (sameas(margv[0],"?")) {
		shwhlp();
	} else if (sameas(margv[0],"who")) {
		whoply();
	} else if (sameas(margv[0],"x")) {
		exitgm(1);
	} else if (cantmove()) {
		return;
	} else if (margc==1) {
		if (sameas(margv[0],"l")) {
			prf("Looking... 5 sec...\r");
			zrptr->look=4;
			zrptr->lookd=-1;
			zrptr->timeout=5;
		} else if (sameas(margv[0],"lh")) {
			prf("Looking hard... 15 sec...\r");
			zrptr->look=7;
			zrptr->lookd=-1;
			zrptr->timeout=15;
		} else if (sameas(margv[0],"!depot!") && hasmkey(CHEATKEY)) {
			zrptr->bux=5000;
			depot();
		} else if (op=='l') {
			binox(margv[0]+1);
		} else if (op=='i') {
			inv();
		} else if (op=='r') {
			move(margv[0]+1,1);
		} else if (op=='c') {
			move(margv[0]+1,2);
		} else if (op=='f') {
			fire(margv[0]+1,1);
		} else {
			move(margv[0],0);
		}
	} else if (margc==2 && op=='f') {
		fire(margv[0]+1,(SHORT)atoi(margv[1]));
    } else if (margc==2 && sameas(margv[0],"contest") && hasmkey(CHEATKEY)) {
		if (onsys(margv[1]) && (zeep=gtzrus(othusn))!=NULL) {
			zeep->hp=24;
			zeep->ep=100;
			zeep->bux=100;
            prf("%s was set to 'contestant' level.\r",uacoff(othusn)->userid);
		}
	} else if (margc==2 && op=='u') {
		use(margv[1]);
	} else if (margc==2 && op=='a') {
		attack(margv[1]);
	} else if (op=='t' && strlen(margv[0])>1 && margc==2) {
		throw(margv[0]+1,(SHORT)atoi(margv[1]));
	} else if (sameas(margv[0],"t")) {
		talk(margv[1],0);
	} else if (sameas(margv[0],"y")) {
		talk(margv[1],1);
	} else if (sameas(margv[0],"w")) {
		talk(margv[1],2);
	} else if (sameas(margv[0],"g")) {
		radio(margv[1],-1);
	} else if (sameas(margv[0],"l")) {
		radio(margv[1],1-(zrptr->side));
	}
	rstmbk();
}


VOID
prfwm(TOPTEN *tt)
{
	if (tt->name[0]) {
        prfptr+=sprintf(prfptr,"%-30.30s %5.5d %5.5d %3.3d%% %5.5d %3.3d:%2.2d %ld (%s)\r",     /*sprintf(prfptr,"%-15.15s  %5.5d  %5.5d  %3.3d%%  %5.5d  %3.3dm %2.2ds  %ld (%s)\r",*/
			tt->name,
			tt->shots,
			tt->hits,
			tt->pct,
			tt->kills,
			tt->min,
			tt->sec,
			tt->score,
			rat[tt->awol]);
	}
}

VOID
warmem(VOID)
{
	SHORT a=0;
	GBOOL bOK;
	LONG lPos;

	setzr();
	prfmsg(WARM1);
	bOK=dfaQueryHI(1); // query by score, which is key 1 (userid is 0)
	while (bOK && (a<10)) {
     lPos=dfaAbs();
     dfaGetAbs(&entry,lPos,0);
     prf("%-30.30s %5.5d %5.5d %3.3d%% %5.5d %3.3d:%2.2d %ld (%s)\r",entry.name,entry.shots,entry.hits,entry.pct,entry.kills,entry.min,entry.sec,entry.score,rat[entry.awol]);
     bOK=dfaQueryPR(); a++;
	}
	if (!bOK && a==0) prf("No scores have been recorded yet.\r");
	
	prfmsg(WARM2);
	for (a=0; a<10; a++) {
		prfwm(&tt2[a]);
	}
}

VOID
zrdela(CHAR *userid)
{
  dfaSetBlk(zrdat);
  while (dfaAcqEQ(NULL,userid,0)) dfaDelete(); // delete all records associated with the user
}


VOID
hdlmm(VOID)
{
	switch(sel) {
	case 'h':
		prfmsg(newst=ZRH1);
		break;
	case 'p':
        if (!haskey(zrkey) && !usaptr->totcreds) {
			prfmsg(NONONL);
			prfmsg(newst=ZRP);
			break;
		}
		whoply();
		prfmsg(newst=ZRSIDE);
		break;
	case 's':
		whoply();
		prfmsg(newst=ZRP);
		break;
	case 'w':
		warmem();
		prfmsg(newst=ZRP);
		break;
	case 'x':
		prf("\rBye now...\r\r");
		newst=0;
		break;
	case '?':
		prfmsg(newst=ZRM);
		break;
	default:
		prfmsg(newst=ZRP);
		break;
	}
}




VOID EXPORT
ply(SHORT side)
{
	prfmsg(newst=PLYZR);
	newply(side);
	hdlsndu(usrnum,(SHORT)14,(SHORT)5);
	shwsta();
}



VOID
hdlsid(VOID)
{
	switch(sel) {
	case 0:
		ply(-1);
		break;
	case 'a':
		ply(0);
		break;
	case 'b':
		ply(1);
		break;
	case 'x':
		prfmsg(newst=ZRP);
		break;
	default:
		prfmsg(ZRSIVA);
		break;
	}
}



SHORT
haveweap(VOID)
{
	SHORT a;

	for (a=0; a<10; a++) {
		if (zrptr->inv[a]<IMED) return zrptr->inv[a];
	}
	return -1;
}



VOID
depzr(VOID)
{
	SHORT a;

	switch(sel) {
	case 0:
		prfmsg(newst=DEPOTP);
		break;
	case '?':
		prfmsg(newst=DEPOTM);
		break;
	case 'i':
		inv();
		prfmsg(newst=DEPOTP);
		break;
	case 'x':
		prfmsg(DRETURN);
		newst=PLYZR;
		zrptr->weapon=haveweap();
		shwsta();
		break;
	case 'c':
		prfmsg(DCAT);
		a=0;
		while (zobj[a].price!=-1) {
			prf("%5u %-12.12s %s\r",zobj[a].price,zobj[a].name,zobj[a].desc);
			a++;
		}
		prfmsg(DEPOTP);
		break;
	case 'p':
		prfmsg(newst=DPUR);
		break;
	case 's':
		prfmsg(newst=DSELLIN);
		break;
	default:
		prfmsg(newst=DEPOTP);
		break;
	}
}



SHORT getnum(CHAR *us)
{
	SHORT matches,matched,a;

	matches=matched=a=0;
	while (zobj[a].price!=-1) {
		if (sameto(us,zobj[a].name)) {
			matches++;
			matched=a;
		}
		a++;
	}
	if (matches==1) return matched;
	return -1;
}



SHORT spinpak(VOID)
{
	SHORT a;

	for (a=0; a<10; a++) {
		if (zrptr->inv[a]==255) return a;
	}
	return -1;
}



VOID
purch(VOID)
{
	SHORT catno,ptp;

	if (!sameas(margv[0],"x")) {
		if ((catno=getnum(margv[0]))==-1) {
			prfmsg(DNOSTOK,margv[0]);
		} else if ((ptp=spinpak())==-1) {
			prfmsg(DWFULL,margv[0]);
		} else if (zrptr->bux<zobj[catno].price) {
			prfmsg(DGYP,margv[0],zobj[catno].price,zrptr->bux);
		} else if (haveweap()!=-1 && catno<IMED) {
			prfmsg(DWSELL);
		} else {
			zrptr->inv[ptp]=(CHAR)catno;
			zrptr->bux-=zobj[catno].price;
			prfmsg(DYOUBUY,zobj[catno].name,zobj[catno].price,zrptr->bux);
		}
	}
	prfmsg(newst=DEPOTP);
}



SHORT whereinpak(SHORT obj)
{
	SHORT a;

	for (a=0; a<10; a++) {
		if (zrptr->inv[a]==obj) return a;
	}
	return -1;
}



VOID
sell(VOID)
{
	SHORT catno;

	if (!sameas(margv[0],"x")) {
		if ((catno=getnum(margv[0]))==-1) {
			prfmsg(DNOGOT,margv[0]);
		} else if ((zrptr->inpak=whereinpak(catno))==-1) {
			prfmsg(DNOGOT,margv[0]);
		} else {
			prfmsg(newst=DOFFER,(zobj[catno].price/2)+1,zobj[catno].name);
			return;
		}
	}
	prfmsg(newst=DEPOTP);
}



VOID
offer(VOID)
{
	SHORT catno;

	if (!sameas(margv[0],"x")) {
		if (sameto(margv[0],"no")) {
			prfmsg(DDENY);
		} else if (sameto(margv[0],"yes")) {
			catno=zrptr->inv[zrptr->inpak];
			zrptr->inv[zrptr->inpak]=255;
			zrptr->bux+=(zobj[catno].price/2)+1;
			prfmsg(DACCEPT,(zobj[catno].price/2)+1,zobj[catno].name,zrptr->bux);
		} else {
			catno = zrptr->inv[zrptr->inpak];
			prfmsg(DOFFER,(zobj[catno].price/2)+1,zobj[catno].name);
			return;
		}
	}
	prfmsg(newst=DEPOTP);
}

SHORT
zrinj(VOID)
{
    dftinj();
    return(1);
}
