	// File: Trivia
	// Author: Matthew leung
	// Description: Trivia game

	#include <allegro.h>
	#include <iostream>
	#include <fstream>
	#include <cstring>
	#include <string>
	#include <stdlib.h>

	using namespace std;

	int main()
	{
		enum dir{ DOWN, UP };
		//set up program
		allegro_init();
		install_keyboard();
		install_timer();

		//setup variables
		char answer;
		int ansCount = 1;
		SAMPLE *sample;
		SAMPLE *select;
		int playerAns = 0;
		int col = 15;
		const int questend = 1400;
		const int ansend = 500;

		// load all questions and answers into array
		//loop question file
		string temp;
		string quest[questend];
		int i = 0;
		ifstream openfile("Qsts.txt");
		//check for error

		if (openfile.is_open())
			while (!openfile.eof())
			{
				getline(openfile, temp);
				quest[i] = temp;
				cout << quest[i] << endl;
				i++;
			}
		openfile.close();
		openfile.clear();

		// Load all answers
		//loop answer text
		string temp2;
		string ans[ansend];
		i = 0;
		ifstream infile("Ans.txt");
		//check for error

		if (infile.is_open())
			while (!infile.eof())
			{
				getline(infile, temp2);
				ans[i] = temp2;
				cout << ans[i] << endl;
				i++;
			}
		infile.close();
		infile.clear();

		//display screen resolution
		int ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 500, 0, 0);

		if (ret != 0)
		{
			allegro_message(allegro_error);
		}
		//change text color
		textprintf_ex(screen, font, 5, 2, col, -1,
			"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
			SCREEN_W, SCREEN_H, sizeof(quest));
		textprintf_ex(screen, font, 5, 12, col, -1,
			"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
			SCREEN_W, SCREEN_H);
		textprintf_ex(screen, font, 5, 22, col, -1,
			"Press Enter to change color",
			SCREEN_W, SCREEN_H);

		//set up music
		int volume = 64;
		int pan = 128;
		int pitch = 1000;
		install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");

		//load some music
		sample = load_sample("downtown.wav");
		select = load_sample("button-30.wav");
		play_sample(sample, volume, pan, pitch, true);

		if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
			allegro_message("Sound Error: %s", allegro_error);
		}

		//set up variables
		int count = 0;
		int y = 100;
		//triangle(screen, 90, 160, 90, 168, 95, 164, 15);
		int erase = makecol(0, 0, 0);
		int up = -10;
		int down = 10;
		bool loop = true;
		int question = 1;
		int chapter = 1;
		bool esc = true;
		bool vol = true;
		//change volume

		textprintf_ex(screen, font, 50, 60 + (10 * 0), 15, 0, "volume MIN");
		for (int v=1; v<26; v++)
		{
			textprintf_ex(screen, font, 50, 60 + (10 * v), 15, 0, "volume %i",v*10);
		}

			textprintf_ex(screen, font, 50, 60 + (10 * 26), 15, 0, "volume MAX");

		
		while (vol){
			textprintf_ex(screen, font, 50, 50, 15, 0, "Change background volume level by pressing - or + then press enter");
			//Background music volume change
			if (key[KEY_UP] && y > 0)
			{
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, erase);
				//set volume down
				y += up;
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, 15);
				set_volume(y, -1);
				rest(75);
				vol = true;
			}
			if (key[KEY_DOWN] && y < 255)
			{
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, erase);
				y += down;
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, 15);
				set_volume(y, -1);
				rest(75);
				vol = true;
			}
			if (key[KEY_ENTER])
			{
				vol = false;
				rest(75);
			}
			if (key[KEY_LEFT])
			{
				col = 15;
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);

			}
			if (key[KEY_RIGHT])
			{
				col = makecol(255, 0, 0);
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);
			}
			if (key[KEY_ESC])
			{
				stop_sample(sample);
				destroy_sample(sample);

				//end program
				allegro_exit();
				return 0;
			}
			volume = y;
		}

		rectfill(screen, 10, 50, SCREEN_W, SCREEN_H, 0);
		y = 0;

		//select chapter
		for (int n = 0; n < 22; n++)
		{
			textprintf_ex(screen, font, 50, 60+(10*n), col, 0, "chapter %i", n+1);
		}
		triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, 15);
		while (esc){
			textprintf_ex(screen, font, 50, 50, col, 0, "select a chapter");
			
			//Keys response to chapters
			if (key[KEY_UP] && y > 0)
			{
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, erase);
				y += up;
				chapter--;
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, col);
				play_sample(select, 128, 128, 1000, false);
				rest(75);
				esc = true;
			}
			if (key[KEY_DOWN] && y < 209)
			{
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, erase);
				y += down;
				chapter++;
				triangle(screen, 40, 60 + y, 40, 68 + y, 45, 64 + y, col);
				play_sample(select, 128, 128, 1000, false);
				rest(75);
				esc = true;
			}
			if (key[KEY_ENTER])
			{
				esc = false;
				rest(75);
			}
			if (key[KEY_LEFT])
			{
				col = 15;
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);
			}
			if (key[KEY_RIGHT])
			{
				col = makecol(255, 0, 0);
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);
			}
			if (key[KEY_ESC])
			{
				stop_sample(sample);
				destroy_sample(sample);

				//end program
				allegro_exit();
				return 0;
			}
		}

		//update question and answer array
		count = 5 * 10 * (chapter-1);
		ansCount = 10*(chapter - 1)+1;
	
		rectfill(screen, 10, 50, SCREEN_W, SCREEN_H, 0);

		//Game starts
		textprintf_ex(screen, font, 100, 70, col, 0, "Chapter %i", chapter);
		esc = true;
		loop = true;
	while (esc)
	{
		//Load question from i array

		textprintf_ex(screen, font, 50, 100, col, 0, (char*)quest[count].c_str());
		
		//add new question
		textprintf_ex(screen, font, 50, 162, col, 0, (char*)quest[count + 1].c_str());
		textprintf_ex(screen, font, 50, 172, col, 0, (char*)quest[count + 2].c_str());
		textprintf_ex(screen, font, 50, 182, col, 0, (char*)quest[count + 3].c_str());
		textprintf_ex(screen, font, 50, 192, col, 0, (char*)quest[count + 4].c_str());
		y = 0;
		rest(75);
		//Loop game
		while (loop)
		{
			
			//Keys response		
			if ( key[KEY_UP] && y>0)
			{
				triangle(screen, 40, 160 + y, 40, 168 + y, 45, 164 + y, erase);
				y += up;
				triangle(screen, 40, 160 + y, 40, 168 + y, 45, 164 + y, col);
				play_sample(select, 128, 128, 1000, false);
				rest(75);
			}
			if (key[KEY_DOWN] && y<21)
			{
				triangle(screen, 40, 160 + y, 40, 168 + y, 45, 164 + y, erase);
				y += down;
				triangle(screen, 40, 160 + y, 40, 168 + y, 45, 164 + y, col);
				play_sample(select, 128, 128, 1000, false);
				rest(75);
			}
			if (key[KEY_ENTER])
			{
				loop = false;
				esc = true;
				rest(75);
			}
			if (key[KEY_LEFT])
			{
				col = 15;
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);
			}
			if (key[KEY_RIGHT])
			{
				col = makecol(255, 0, 0);
				//change text color
				textprintf_ex(screen, font, 5, 2, col, -1,
					"Trivia game from 'Game programming all in one 3rd edition by Jonathan S. Harbour' - %dx%d - Press ESC to quit ",
					SCREEN_W, SCREEN_H, sizeof(quest));
				textprintf_ex(screen, font, 5, 12, col, -1,
					"Use UP, DOWN, ENTER keys to answer questions; Use LEFT key to change font to white,and RIGHT key to change color to red then Press Enter to change color",
					SCREEN_W, SCREEN_H);
				textprintf_ex(screen, font, 5, 22, col, -1,
					"Press Enter to change color",
					SCREEN_W, SCREEN_H);
			}
			if (key[KEY_ESC])
			{
				stop_sample(sample);
				destroy_sample(sample);

				//end program
				allegro_exit();
				return 0;
			}
		
		}
		// Switch cases for answers
		switch (y){

			case 0: answer = 'A';
				break; 
		
			case 10: answer = 'B';
				break; 
				
			case 20: answer = 'C';
				break;
			
			case 30: answer = 'D';


				break;
				}
	
		// wait for key Enter, esc = true, and less than array size
		if (esc && key[KEY_ENTER] && count <= (sizeof(quest)-1) && ansCount <= (sizeof(ans)-1))
		{
			
				rectfill(screen, 0, 80, SCREEN_W, 300, 0);

				// match answer
				if (ans[ansCount].at(0) == answer)
				{
					textprintf_ex(screen, font, 250, 250, col, 0, "Nice answer");
					esc = true;
				}
				else
				{
					textprintf_ex(screen, font, 250, 250, col, 0, "Wrong answer, the answer is %c", ans[ansCount].at(0));
					textprintf_ex(screen, font, 250, 270, col, 0, "you answered %c",  answer);
					esc = true;
				}

				// next question
				count = count + 5;
				ansCount = ansCount + 2;
				question++;

				// change chapter
				if (question % 10 == 0)
				{
					chapter++;
				}
					textprintf_ex(screen, font, 100, 70, col, 0, "Chapter %i", chapter);
				

				//erase question and questions
				rectfill(screen, 0, 80, SCREEN_W, 249, 0);
				rest(100);
				loop = true;
				triangle(screen, 40, 160, 40, 168, 45, 164, col);
			//if all answers or questions are looped through
				if (count == questend || ansCount == ansend)
			{
				rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, 0);
				textprintf_ex(screen, font, 250, 250, col, 0, "Thats all the questions");
				textprintf_ex(screen, font, 250, 270, col, 0, "The game will exit by itself");
				//stop the music and destroy it
				rest(2000);
				stop_sample(sample);
				destroy_sample(sample);

				//end program
				allegro_exit();
				return 0;
			}
			}

		//end program if esc is pressed in the middle
		if (!esc)
		{
			stop_sample(sample);
			destroy_sample(sample);

			//end program
			allegro_exit();
			return 0;
		}
	}
	//stop the music and destroy it
	stop_sample(sample);
	destroy_sample(sample);

	//end program
	allegro_exit();
	return 0;

	}
	END_OF_MAIN()