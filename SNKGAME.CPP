#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// mouse handel function
union REGS in,out;
void status();
void position(int* ,int* ,int*);
void show();
void hide();
void setpos();

// main screen functions
void game_scr();
void win_todo();
void UpdPos();
void ShowSnk();
void Gener_Food();
int isSelfBite();
void showFood();

void save_score();
void show_hs(struct hscore);
void save_scr_scn();

void show_help();

struct snak
{
	int x;
	int y;
	char pdir[6];
	char ndir[6];


}stl[400];

struct food
{
	int x;
	int y;
	time_t vTm;
	int avil;
	
}Fod;

struct hscore
{
	char p_name[50];
	long scr;
}hs;

struct hepls
{
	char command[40];
	char desc[300];
}hlp;


//some global variables
long SCORE=0,SLEN=0;
int Spd=400,TA=0,aD=0;


void main()
{
	int x,y,m,i,j;
	char qu,pos[50];
	int pus=1,Bt;
	int kstr;
	int gdriver = DETECT, gmode, errorcode;
	FILE *f1;
	
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	
RESTART:
{
	stl[0].x=10;
	stl[0].y=70;
	strcpy(stl[0].pdir,"right");
	strcpy(stl[0].ndir,"right");
	SLEN=0;
	SCORE=0;
	Spd=400;
	
	Fod.x=10;
	Fod.y=70;
	Fod.vTm=time(NULL);
	Fod.avil=0;
};
START:
{
	hide();
	cleardevice();
	game_scr();
	show();
	setpos();
	position(&x,&y,&m);
};
	
	while(1)
	{
		if(pus==1)
		{
			show();
			position(&x,&y,&m);
			if(x>=350 && x<=400 && y>=0 && y<=40)
			{
				if(m==1)
				{
					setcolor(RED);
					settextstyle(7,0,3);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(20,150,380,300);
					outtextxy(200,225,"Do you want to exit (Y/N)?");
					qu=getch();
					if(qu=='y' || qu=='Y')
					{
						exit(0);
					}
					cleardevice();
					game_scr();
				}
			}
			
			if(x>=0 && x<=100 && y>=40 && y<=60)
			{
				if(m==1)
				{
					goto TODO_COMM;
				}
			}
		}
		else if(pus==0)
		{
			
			delay(Spd);
			UpdPos();
			ShowSnk();
			Gener_Food();
			Bt=isSelfBite();
			if(Bt==1)
			{
				
				show();
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,190,"You have bite yourself.");
				delay(2000);
				getch();
				
				save_score();

				hide();
				cleardevice();
				game_scr();

				pus=1;
				show();
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					exit(0);
				}

				goto RESTART;
			}

			if(kbhit())
			{
				kstr=getch();
				if(pus==1 && kstr==32)
				{
					pus=0;
					hide();
				}
				else if(pus==0 && kstr==32)
				{
					pus=1;
					show();
				}
				else if((kstr==105 || kstr==73) && ((strcmp(stl[0].ndir,"down"))!=0))// PRESS I
				{
					strcpy(stl[0].ndir,"up");
				}
				else if((kstr==106 || kstr==74) && ((strcmp(stl[0].ndir,"right"))!=0))// PRESS j
				{
					strcpy(stl[0].ndir,"left");
				}
				else if((kstr==107 || kstr==75) && ((strcmp(stl[0].ndir,"left"))!=0))// PRESS k
				{
					strcpy(stl[0].ndir,"right");
				}
				else if((kstr==109 || kstr==77) && ((strcmp(stl[0].ndir,"up"))!=0))// PRESS m
				{
					strcpy(stl[0].ndir,"down");
				}
				else
				{
					;
				}
			}
		}
		else
		{
			;
		}
		if(kbhit())
		{

			kstr=getch();
			if(pus==1)
			{
				pus=0;
				hide();
			}
			else if(kstr==32)
			{
				pus=1;
			}
			else
			{
				;
			}
		}
	}

TODO_COMM:
{
	hide();
	cleardevice();
	game_scr();
	win_todo();
	show();
	setpos();
	delay(100);
	while(1)
	{
		position(&x,&y,&m);
		if(x>=0 && x<=180 && y>60 && y<=100)
		{
			if(m==1)
			{
				goto RESTART;
			}
		}
		else if(x>=0 && x<=180 && y>100 && y<=140)
		{
			if(m==1)
			{
				goto HIGH_SCORE;
			}
		}
		else if(x>=0 && x<=180 && y>140 && y<=180)
		{
			if(m==1)
			{
				goto HELP;
			}
		}
		else
		{
			if(m==1)
			{
				goto START;
			}
		}
	}
};

HIGH_SCORE:
{
	if((f1=fopen("Snack\\GameData\\SCR_DAT.dat","r"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,400,300);
		settextstyle(7,0,2);
		outtextxy(200,200,"SCORE FILE NOT FOUND");
		getch();
	}
	else
	{
		fread(&hs,sizeof(hs),1,f1);
		fclose(f1);
		show_hs(hs);
	}
	fclose(f1);
	goto START;
};

HELP:
{
	hide();
	cleardevice();
	show_help();
	goto START;
};

}

void game_scr()
{
	setbkcolor(CYAN);
	setfillstyle(SOLID_FILL,9);
	bar(0,0,400,460);

	//title bar
	setcolor(getmaxcolor());
	settextjustify(1,1);
	settextstyle(7,0,4);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,400,40);
	outtextxy(200,15,"SNAKE GAME");
	setfillstyle(SOLID_FILL,RED);
	settextstyle(0,0,4);
	bar(350,0,400,40);
	setcolor(GREEN);
	outtextxy(375,20,"X");
	//main menu bar

	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(7,0,3);
	bar(0,40,400,60);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,40,100,60);
	setcolor(BLUE);
	outtextxy(50,45,"MENU");

	setfillstyle(SOLID_FILL,YELLOW);
	settextstyle(7,0,3);
	bar(405,0,635,460);
	setcolor(RED);
	outtextxy(520,30,"TOTAL SCORE :");
	char trb[10];
	sprintf(trb,"%d",SCORE);
	outtextxy(520,60,trb);
	setcolor(GREEN);

}

void win_todo()
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,60,180,180);
	setcolor(BLUE);
	settextstyle(1,0,2);
	line(0,100,180,100);
	line(0,140,180,140);
	outtextxy(90,80,"RESTART");
	outtextxy(90,120,"HIGH_SCORE");
	outtextxy(90,160,"HELP");
	
}

void ShowSnk()
{

	int i=0,x,y;

	showFood();
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);

	while(i<=SLEN)
	{
		if(i==0)
		{
			if((strcmp(stl[i].ndir,"right"))==0)
			{
				sector(stl[i].x,stl[i].y, 30,330, 10,10);
			}
			else if((strcmp(stl[i].ndir,"left"))==0)
			{
				sector(stl[i].x,stl[i].y, 0, 150, 10,10);
				sector(stl[i].x,stl[i].y, 210,360, 10,10);
			}
			else if((strcmp(stl[i].ndir,"up"))==0)
			{
				sector(stl[i].x,stl[i].y,120,360, 10, 10);
				sector(stl[i].x,stl[i].y,0,60, 10, 10);

			}
			else if((strcmp(stl[i].ndir,"down"))==0)
			{
				sector(stl[i].x,stl[i].y,300,360, 10, 10);
				sector(stl[i].x,stl[i].y,0,240, 10, 10);
			}
			else
			{
				;
			}
		}
		else
		{
			fillellipse(stl[i].x,stl[i].y,10,10);
		}
		if(i==SLEN)
		{
			setcolor(9);
			setfillstyle(SOLID_FILL,9);
			x=stl[i].x;
			y=stl[i].y;


			if((strcmp(stl[i+1].ndir,"right"))==0)
			{
				x=x-20;
				if(x<10)
				{
					x=390;
				}
			}
			else if((strcmp(stl[i+1].ndir,"left"))==0)
			{
				x=x+20;
				if(x>390)
				{
					x=10;
				}
			}
			else if((strcmp(stl[i+1].ndir,"up"))==0)
			{
				y=y+20;
				if(y>450)
				{
					y=70;
				}
			}
			else if((strcmp(stl[i+1].ndir,"down"))==0)
			{
				y=y-20;
				if(y<70)
				{
					y=450;
				}
			}
			else
			{
				;
			}
			fillellipse(x,y,10,10);
		}
		i++;
	}
}

void UpdPos()
{
	int i=0;
	char todir[5];
	while(i<=SLEN)
	{
		if((strcmp(stl[i].ndir,"right"))==0)
		{
			stl[i].x=stl[i].x+20;

			if(stl[i].x>=400)
			{
				stl[i].x=10;
			}
		}
		else if((strcmp(stl[i].ndir,"left"))==0)
		{
			stl[i].x=stl[i].x-20;
			if(stl[i].x<=0)
			{
				stl[i].x=390;
			}
		}
		else if((strcmp(stl[i].ndir,"up"))==0)
		{
			stl[i].y=stl[i].y-20;
			if(stl[i].y<70)
			{
				stl[i].y=450;
			}
		}
		else if((strcmp(stl[i].ndir,"down"))==0)
		{
			stl[i].y=stl[i].y+20;
			if(stl[i].y>=460)
			{
				stl[i].y=70;
			}
		}
		else
		{
			;
		}

		strcpy(stl[i+1].ndir,stl[i].pdir);
		strcpy(stl[i].pdir,stl[i].ndir);
		
		if(i==SLEN)
		{
			strcpy(stl[i+1].ndir,stl[i].pdir);
		}
		i++;
	}
	if(TA==1)
	{
		if(aD==0)
		{
			TA=0;
			SLEN++;
			SCORE=SCORE+100;
			stl[i].x=Fod.x;
			stl[i].y=Fod.y;
			strcpy(stl[i].pdir,stl[i-1].pdir);
			strcpy(stl[i].ndir,stl[i-1].pdir);
			if(Spd>40)
			{
				Spd=Spd-20;
			}
			Fod.avil=0;
			cleardevice();
			game_scr();
		}
		else
		{
			aD--;
		}
	}
	if((stl[0].x==Fod.x) && ((stl[0].y==Fod.y)))
	{
		TA=1;
		aD=SLEN;
	}
}

void Gener_Food()
{
	time_t etm;
	double difr;
	int t=0,x,y,i=0;
	etm=time(NULL);
	difr=difftime(etm,Fod.vTm);
	if((Fod.avil==0) && (difr>0))
	{
		randomize();
		while(t==0)
		{
			i=0;
			x=((random(19))*20)+10;
			y=((random(21))*20)+70;
			for(int j=0;j<=SLEN;j++)
			{
				if(x==stl[j].x && y==stl[j].y)
				{
					i++;
					break;
				}
			}
			if(i==0)
			{
				t=1;
			}
		}
		Fod.x=((random(20))*20)+10;
		Fod.y=((random(20))*20)+70;
		Fod.vTm=etm;
		Fod.avil=1;
		
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,GREEN);
		fillellipse(Fod.x,Fod.y,10,10);
		
	}
}

void showFood()
{
	if(Fod.avil==1)
	{
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,GREEN);
		fillellipse(Fod.x,Fod.y,10,10);
	}

}

int isSelfBite()
{
	int i=0;
	for(int j=1;j<=SLEN;j++)
	{
		if(stl[0].x==stl[j].x && stl[0].y==stl[j].y)
		{
			i++;
			break;
		}
	}
	return i;
}

void show_help()
{
	int x,y,rs,q=1;
	FILE *f1;
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,YELLOW);
	settextstyle(7,0,3);
	bar(0,50,250,450);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(1,0,2);
	bar(250,50,630,450);

	if((f1=fopen("Snack\\GameData\\help_cmd.dat","r+"))==NULL)
	{
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		settextstyle(7,0,3);
		bar(50,100,500,300);
		outtextxy(100,225,"FILE NOT FOUND TO READ DATA ");
		getch();
		exit(0);
	}
	else
	{
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,BROWN);
		settextstyle(1,0,3);
		bar(0,0,630,50);
		settextjustify(1,1);
		outtextxy(315,25,"HELP WINDOW");
		settextstyle(1,0,2);

		while(f1)
		{
			x=125;
			y=50+q*30;
			fread(&hlp,sizeof(hlp),1,f1);
			if(feof(f1))
			{
				break;
			}
			setcolor(RED);

			outtextxy(x,y,hlp.command);
			x=440;
			setcolor(BLUE);
			outtextxy(x,y,hlp.desc);
			q++;
		}
		fclose(f1);
		getch();
	}
}

char *char_inp(int cor[5])
{
	int h,q,l,i,t,cr;
	char inp[50];
	char chp[50],*endptr;
	char ch='0';
	char ap[50]="",bp[50],cp[50],dp[50];
	h=cor[0]+10;
	i=cor[1]+10;
	settextstyle(1,HORIZ_DIR,2);

	while(ch!='\r')
	{

		save_scr_scn();
		setcolor(YELLOW);
		setfillstyle(1,RED);
		h=cor[0]+10;
		i=cor[1]+10;
		settextstyle(1,HORIZ_DIR,2);
		bar(cor[0],cor[1],cor[2],cor[3]);
		outtextxy(h,i,ap);
		ch=getch();

			if(ch=='\b')
			{
				strcpy(bp,ap);
				strrev(bp);
				q=strlen(bp)-1;
				i=0;
				while(q>0)
				{
					cp[i]=bp[q];
					i++;
					q--;
				}
				cp[i]='\0';
				strcpy(ap,cp);
			}

			if(ch=='a' || ch=='b'|| ch=='c'|| ch=='d' || ch=='e' || ch=='f'|| ch=='g' || ch=='h'|| ch=='i'|| ch=='j' || ch=='k' || ch=='l' || ch=='m' || ch=='n'|| ch=='o'|| ch=='p' || ch=='q' || ch=='r'|| ch=='s' || ch=='t'|| ch=='u'|| ch=='v' || ch=='w' || ch=='x' || ch=='y' || ch=='z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}
			if(ch==' ' || ch=='A' || ch=='B'|| ch=='C'|| ch=='D' || ch=='E' || ch=='F'|| ch=='G' || ch=='H'|| ch=='I'|| ch=='J' || ch=='K' || ch=='L' || ch=='M' || ch=='N'|| ch=='O'|| ch=='P' || ch=='Q' || ch=='R'|| ch=='S' || ch=='T'|| ch=='U'|| ch=='V' || ch=='W' || ch=='X' || ch=='Y' || ch=='Z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}


	 }
	 strcpy(dp,ap);
	 return(dp);
}

void save_scr_scn()
{
	cleardevice();
	settextjustify(0,2);
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,BLUE);
	settextstyle(7,0,3);
	bar(100,100,500,300);
	outtextxy(110,130,"ENTER THE PLAYER NAME : ");
	bar(100,200,500,300);
}

void save_score()
{
	struct hscore ohs;
	FILE *f1,*f2;
	int cr[5],l;
	ohs.scr=0;
	if((f1=fopen("Snack\\GameData\\SCR_DAT.dat","r"))==NULL)
	{
		fclose(f1);
		if((f1=fopen("Snack\\GameData\\SCR_DAT.dat","w+"))==NULL)
		{
			hide();
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,3);
			outtextxy(300,200,"SCORE FILE NOT CREATED...");
			show();
			getch();

		}
		else
		{
			cr[0]=100;
			cr[1]=200;
			cr[2]=500;
			cr[3]=300;
			cr[4]=0;
			strcpy(hs.p_name,char_inp(cr));
			hs.scr=SCORE;
			fwrite(&hs,sizeof(hs),1,f1);
			fclose(f1);
			hide();
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,3);
			outtextxy(200,200,"SCORE SAVE ");
			show();
			getch();
			settextjustify(1,1);
		}
		fclose(f1);
	}
	else
	{
		fread(&ohs,sizeof(ohs),1,f1);
		if(ohs.scr<SCORE)
		{
			fclose(f1);
			if((f1=fopen("Snack\\GameData\\SCR_DAT.dat","w+"))==NULL)
			{
				hide();
				cleardevice();
				setbkcolor(CYAN);
				setcolor(RED);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(100,150,500,300);
				settextstyle(7,0,3);
				outtextxy(300,200,"SCORE FILE NOT CREATED...");
				show();
				getch();

			}
			else
			{
				cr[0]=100;
				cr[1]=200;
				cr[2]=500;
				cr[3]=300;
				cr[4]=0;
				strcpy(hs.p_name,char_inp(cr));
				hs.scr=SCORE;
				fwrite(&hs,sizeof(hs),1,f1);
				fclose(f1);
				hide();
				cleardevice();
				setbkcolor(CYAN);
				setcolor(RED);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(100,150,500,300);
				settextstyle(7,0,3);
				outtextxy(200,200,"SCORE SAVE ");
				show();
				getch();
				settextjustify(1,1);
			}
			fclose(f1);
		}
		else
		{
			;
		}
	}
	fclose(f1);
}

void show_hs(struct hscore th)
{
	char tm[10],tmt[10],p_n[50];
	hide();
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	settextjustify(1,1);
	setfillstyle(SOLID_FILL,BROWN);
	settextstyle(7,0,3);
	bar(100,20,500,70);
	outtextxy(300,30,"HIGH SCORE");
	settextjustify(0,2);
	setfillstyle(SOLID_FILL,BLUE);
	settextstyle(7,0,3);
	bar(100,70,500,310);
	outtextxy(110,70,"PLAYER NAME : ");
	strcpy(p_n,th.p_name);
	outtextxy(110,110,p_n);
	sprintf(tmt,"%d",th.scr);
	outtextxy(110,150,"SCORE : ");
	outtextxy(110,190,tmt);
	settextjustify(1,1);
	show();
	getch();
}

void status()
{
	in.x.ax=0;
	int86(51,&in,&out);
}
void hide()
{
	in.x.ax=2;
	int86(51,&in,&out);
}
void show()
{
	in.x.ax=1;
	int86(51,&in,&out);
}
void setpos()
{
	in.x.ax=4;
	in.x.cx=0;
	in.x.dx=0;
	in.x.bx=0;
	int86(0x33,&in,&out);
}
void position(int *x,int *y,int *m)
{
	in.x.ax=3;
	int86(0x33,&in,&out);
	*m=out.x.bx;
	*x=out.x.cx;
	*y=out.x.dx;
}