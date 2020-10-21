#include<stdio.h>
#include<conio.h>
#include<string.h>

struct hepls
{
	char command[40];
	char desc[300];
}hlp;

void main()
{
	FILE *f1;
	clrscr();
	if((f1=fopen("Snack\\GameData\\help_cmd.dat","w"))==NULL)
	{
		printf("There is some errors :");
	}
	else
	{
		strcpy(hlp.command,"i key");
		strcpy(hlp.desc,"To make snack go UP side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"Shift + i");
		strcpy(hlp.desc,"To make snack go UP side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"j key");
		strcpy(hlp.desc,"To make snack go LEFT side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"Shift + j");
		strcpy(hlp.desc,"To make snack go LEFT side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"k key");
		strcpy(hlp.desc,"To make snack go RIGHT side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"Shift + k");
		strcpy(hlp.desc,"To make snack go RIGHT side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"m key");
		strcpy(hlp.desc,"To make snack go DOWN side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"Shift + M");
		strcpy(hlp.desc,"To make snack go DOWN side");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		strcpy(hlp.command,"Space bar key");
		strcpy(hlp.desc,"To make snack POUSE or GO");
		fwrite(&hlp,sizeof(hlp),1,f1);
		
		fclose(f1);
		
		printf("\nAll helps Saved...");
	}
	getch();
	
}