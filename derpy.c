/*
 Copyright 2015 Bruno Marie

 The license only covers the files derpy.c, levels.h and menu_selection.h.
 Everything else belongs to their respective owners.
 
 
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004

Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <os.h>
#include "title_img.h"
#include "game_img.h"
#include "levels.h"
#include "menu_selection.h"

#include "n2DLib.h"

unsigned char level = 0;
unsigned char valid = 0;
unsigned char muffins[4];
unsigned char derpyfound = 0;
short sx = 0, sy = 0;
unsigned char timer = 20;
short timerest = 0;
short gameisover = 0;
short ytext = -64;
short gameoverwait = 0;
unsigned char menu = 0;

Rect mousePOS , textPOS, backsPOS;
Rect selectPOS[5];

void show_level(int level);
void controls();
void SHOWspriteslevel();
void gameoverorwin(void);
void gestionlevel();
void GamePlay(unsigned char level);
int thegame(void);
void Menu_Choose();

int main(void) 
{
	thegame();
    return EXIT_SUCCESS;
}

int thegame(void)
{
	unsigned char time_enter = 0;
	
	backsPOS.x = 0;
	backsPOS.y = 152+24;
	mousePOS.x = 150;
	mousePOS.y = 200;
	textPOS.x = 95;
	textPOS.y = 280;
	
    initBuffering();
	
	while(!isKeyPressed(KEY_NSPIRE_ESC))
    {
		switch(menu)
		{
			case 0:
				switch(level)
				{
					case 0:
						drawSprite(degrade_img, 0, 0);
						drawSprite(derpy, 0, 64);
						drawSprite(logo_img, 43, 6);
						
						time_enter++;
						if (time_enter < 30)
						{
							drawSprite(start_img, 74, 193);
						}
						else if (time_enter > 59)
						{
							time_enter = 0;
						}

						if (isKeyPressed(KEY_NSPIRE_VAR) || isKeyPressed(KEY_NSPIRE_ENTER))
						{
							menu = 1;
						}
					break;
					default:
						show_level(level);
						drawSprite(back_img, backsPOS.x, backsPOS.y);
						SHOWspriteslevel();
						gameoverorwin();
						GamePlay(level);
						if (gameisover == 0)
						{
							controls();
							gestionlevel();
						}	
					break;
				}
			break;
			
			case 1:
				controls();
				if (valid)
				{
					Menu_Choose();
					valid = 0;
				}
				drawSprite(menu_img, 0, 0);
				drawSprite(Mouse_img, mousePOS.x, mousePOS.y);
				
			break;
		}
		
		updateScreen();
	}
	deinitBuffering();
    return EXIT_SUCCESS;
};


void show_level(int level)
{
	switch(level)
	{
		case 1:
			drawSprite(level1_img, 0, 0);
		break;
		case 2:
			drawSprite(level2_img, 0, 0);
		break;
		case 3:
			drawSprite(level3_img, 0, 0);
		break;
		case 4:
			drawSprite(level4_img, 0, 0);
		break;
		case 5:
			drawSprite(level5_img, 0, 0);
		break;
		case 6:
			drawSprite(level6_img, 0, 0);
		break;
		case 7:
			drawSprite(level7_img, 0, 0);
		break;
		case 8:
			drawSprite(level8_img, 0, 0);
		break;	
		case 9:
			drawSprite(level9_img, 0, 0);
		break;
		case 10:
			drawSprite(level10_img, 0, 0);
		break;
		case 11:
			drawSprite(level11_img, 0, 0);
		break;
		case 12:
			drawSprite(level12_img, 0, 0);
		break;
		case 13:
			drawSprite(level13_img, 0, 0);
		break;
		case 14:
			drawSprite(level14_img, 0, 0);
		break;
		case 15:
			drawSprite(level15_img, 0, 0);
		break;
		case 16:
			drawSprite(level16_img, 0, 0);
		break;
		case 17:
			drawSprite(level17_img, 0, 0);
		break;
		case 18:
			drawSprite(level18_img, 0, 0);
		break;
		case 19:
			drawSprite(level19_img, 0, 0);
		break;
		case 20:
			drawSprite(level20_img, 0, 0);
		break;
	}
	
}

void Menu_Choose()
{
	unsigned char i;
	unsigned char lev;
	for(i=0;i<20;i++)
	{
		if (sx > menu_data[i][0] && sx < menu_data[i][1] && sy > menu_data[i][2] && sy < menu_data[i][3])
		{
			lev = i; 
			timer = 30;
			gameisover = 0;
			gameoverwait = 0;
			derpyfound = 0;
			muffins[0] = 0;
			muffins[1] = 0;
			muffins[2] = 0;
			
			if (lev+1 == 20) 
			backsPOS.y = 152;
			else
			backsPOS.y = 152+24;
			
			textPOS.y = 280;
			
			mousePOS.x = 150;
			mousePOS.y = 200;
			for (i=0;i<4;i++)
			{
				selectPOS[i].x = 400;
				selectPOS[i].y = 0;
			}
			menu = 0;
			level = lev+1;
			break;
		}
	}	
}

void gestionlevel() // Manage if you can win if you found derpy and manage the timer
{ 
	if ((derpyfound == 1 && muffins[0] == 1 && muffins[1] == 1 && muffins[2] == 1)) 
	{
		gameisover = 2;
		timerest = 0;
	}
	else if (timer < 1)
	{
		gameisover = 1;
	}
					
	if (timerest > 58)
	{
		timer = timer - 1;
		timerest = 0;
	}
	
	timerest++;			
}

void gameoverorwin(void) // This "function" sends you to the menu if you lose or win
{
	switch(gameisover)
	{		
		case 2:
			if (textPOS.y < 140)
			{
				gameoverwait++;
			}
			else
			{
				textPOS.y--;
			}
								
			if (gameoverwait > 80)
			{
				mousePOS.x = 150;
				mousePOS.y = 200;
				menu = 1;
				valid = 0;
			}		
			drawSprite(win_img, textPOS.x, textPOS.y);		
		break;
		case 1:
			if (textPOS.y < 140)
			{
				gameoverwait++;
			}
			else
			{
				textPOS.y--;
			}
								
			if (gameoverwait > 80)
			{
				mousePOS.x = 150;
				mousePOS.y = 200;
				menu = 1;
				valid = 0;
			}
			drawSprite(gameover_img, textPOS.x, textPOS.y);		
		break;
	}

}

void SHOWspriteslevel()  // Shows the sprites on dah screen
{
	if (timer > 9)
	{
		drawDecimal(152, 205, (timer/10)%10, 65000, 0);
		drawDecimal(162, 205, (timer)%10, 65000, 0);
	}
	else
	{
		drawDecimal(152, 205, (timer/10)%10, ((255 >> 3) << 11) | ((0 >> 2) << 5) | (0 >> 3), 0);
		drawDecimal(162, 205, (timer)%10, ((255 >> 3) << 11) | ((0 >> 2) << 5) | (0 >> 3), 0);
	}
	drawSprite(sel_img, selectPOS[0].x, selectPOS[0].y);	
	drawSprite(sel_img, selectPOS[1].x, selectPOS[1].y);	
	drawSprite(sel_img, selectPOS[2].x, selectPOS[2].y);	
	drawSprite(sel_img, selectPOS[3].x, selectPOS[3].y);	
	drawSprite(Mouse_img, mousePOS.x, mousePOS.y);
}

void controls() // Used for controlling the cursor
{ 
			if (mousePOS.x > 310)
			{
				mousePOS.x = 310;
			}
			else if (mousePOS.x < 0)
			{
				mousePOS.x = 0;
			}
			
			if (mousePOS.y > 220)
			{
				mousePOS.y = 220;
			}
			else if (mousePOS.y < 0)
			{
				mousePOS.y = 0;
			}
			
			if (isKeyPressed(KEY_NSPIRE_LEFTUP) || isKeyPressed(KEY_NSPIRE_7))
			{
				mousePOS.x = mousePOS.x - 2;
				mousePOS.y = mousePOS.y - 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_UPRIGHT) || isKeyPressed(KEY_NSPIRE_9))
			{
				mousePOS.x = mousePOS.x + 2;
				mousePOS.y = mousePOS.y - 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_RIGHTDOWN) || isKeyPressed(KEY_NSPIRE_3))
			{
				mousePOS.x = mousePOS.x + 2;
				mousePOS.y = mousePOS.y + 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_DOWNLEFT) || isKeyPressed(KEY_NSPIRE_1))
			{
				mousePOS.x = mousePOS.x - 2;
				mousePOS.y = mousePOS.y + 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_LEFT) || isKeyPressed(KEY_NSPIRE_4))
			{
				mousePOS.x = mousePOS.x - 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_6))
			{
				mousePOS.x = mousePOS.x + 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_8))
			{
				mousePOS.y = mousePOS.y - 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5))
			{
				mousePOS.y = mousePOS.y + 2;
			}
			else if (isKeyPressed(KEY_NSPIRE_DOC) && valid == 0)
			{
				sx = mousePOS.x;
				sy = mousePOS.y;
				valid = 1;
			}
			
	
}


void GamePlay(unsigned char level)
{
	if (valid == 1)
	{
		if (sx > level_data[level-1][0] && sx < level_data[level-1][1] && sy > level_data[level-1][2] && sy < level_data[level-1][3] && derpyfound == 0)
		{
			derpyfound = 1;
			selectPOS[0].x = sx-16;
			selectPOS[0].y = sy-16;
		}
		else if (sx > level_data[level-1][4] && sx < level_data[level-1][5] && sy > level_data[level-1][6] && sy < level_data[level-1][7] && muffins[0] == 0)
		{
			muffins[0] = 1;
			selectPOS[1].x = sx-16;
			selectPOS[1].y = sy-16;
		}
		else if (sx > level_data[level-1][8] && sx < level_data[level-1][9] && sy > level_data[level-1][10] && sy < level_data[level-1][11] && muffins[1] == 0)
		{
			muffins[1] = 1;
			selectPOS[2].x = sx-16;
			selectPOS[2].y = sy-16;
		}
		else if (sx > level_data[level-1][12] && sx < level_data[level-1][13] && sy > level_data[level-1][14] && sy < level_data[level-1][15] && muffins[2] == 0)
		{
			muffins[2] = 1;
			selectPOS[3].x = sx-16;
			selectPOS[3].y = sy-16;
		}
		valid = 0;
	}			
	
}
