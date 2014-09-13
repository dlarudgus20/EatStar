// Copyright (c) 2014, 임경현 (dlarudgus20)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "MainFunc.h"
#include "Item.h"

void atexit_func()
{
	endwin();
}

int main(void)
{
	setlocale(LC_CTYPE, "");
	initscr();
	atexit(atexit_func);
	curs_set(0);

	maininit();
	while (1)
	{
		while (!gamestart)
		{
			loadscore();
			if (loadscore() == -1)
				savescore();
				
			mainprint();
		
			switch (getch())
			{
			case 'a':
				gamestart = TRUE;
				break;
			case 'b':
				setSettings();
				break;
			case 'c':
				clear();
				printw("\n ★ EatStar v0.0.5\n 별 먹기 게임!\n\n ⓒ 2014 Naissoft. All rights reserved.");
				usleep(1500);
				break;
			case 'd':
				shop();
				break;
			case 'e':
				exit(0);
				break;
			default:
				break;
			}
		}
	
		clear();
		setstar();
		while (!g_over)
		{
			print();
			keyproc();
			pausemenu();
			if (x == star_x && y == star_y)
			{
				printstar();
				usleep(5000);
				score += ADDSCORE;
				setstar();
				moved = 0;
			}
			if (moved >= MAXMOVED) break;
		}
		if (!g_over) 
			gameover();
		g_over = FALSE;
		gamestart = FALSE;
	}
	return 0;
}
