//Сделано RedFoxMain 
//Git hub: https://github.com/RedFoxMain

//Если вы используете Linux вам следует закомментировать 6 строку.
//Если работаете на Windows, то ничего трогать не надо.
#define WINDOWS

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>

#ifndef WINDOWS
#include<windows.h>
#else
#include<unistd.h>
#endif


using namespace std;

char map[3][3];
int badPlace = 0;
int partOfMap = 0;

// Эта функция отрисовывать поле(для красоты)
void DrawPlaceForMenu(){
	int length = 3;
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		    {
		   	 map[i][j] = '#';
		    }
	}
	for(int i = 0; i < length; i++)
	    {
	   	 for(int j = 0; j < length; j++)
	   	 {
	   	 	
	   	 	cout << map[i][j];
	   	 }
	   	 cout << endl;
	    }
}


///////////////////

//Я надеюсь вы ещё не повесились.
//Эта функция отслеживает в каких яцейках находится "х" и "о"
bool WinState(int player){
	bool win = false;
	char icon;
	if(player == 1){
		icon = 'x';
	}
	else{
		icon = 'o';
	}
	if((map[0][0] == icon && map[0][1] == icon && map[0][2] == icon) || (map[1][0] == icon && map[1][1] == icon && map[1][2] == icon) || (map[2][0] == icon && map[2][1] == icon && map[2][2] == icon) || (map[0][0] == icon && map[1][0] == icon && map[2][0] == icon) || (map[0][1] == icon && map[1][1] == icon && map[2][1] == icon) || (map[0][2] == icon && map[1][2] == icon && map[2][2] == icon) || (map[0][0] == icon && map[1][1] == icon && map[2][2] == icon) || (map[0][2] == icon && map[1][1] == icon && map[2][0] == icon)){
			
		    printf("\033[31m");
			cout << "Игрок номер "<< player<< " закончил партию быстрее!" << endl;
			cout << "Победа игрока номер "<< player << endl;
			printf("\033[0m\n");
			win = true;
		}
	return win;
}

// Эта функция уже отрисовывает игровое поле
void DrawPlace(int player,char icon, int x, int y){
	
	int length = 3;
	if (map[x][y] == '#'){
		map[x][y] = icon;
	}else{
		if (player == 1){
			badPlace = 1;
		}else{
			badPlace = 2;
		}
		//Окрашиваем текст
		printf("\033[31mКлетка занята!\n");
		sleep(2);
		printf("\033[0m\n");
}
	
	partOfMap += 1;
	#ifndef WINDOWS
		system("cls");
	#else
		system("clear");
	#endif
	for(int i = 0; i < length; i++)
	    {
	   	 for(int j = 0; j < length; j++)
	   	 {
	   	 	cout << map[i][j];
	   	 }
	   	 cout << endl;
	    }
}

int main(int argc, char *argv[])
{
	int length = 3;
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		    {
		   	 map[i][j] = '#';
		    }
	}
	int x,y;
	bool win;
	int player = 1;
	DrawPlaceForMenu();
	while(true){
		printf("Игрок #%i",player);
		cout << endl;
		cout << "Введите номер строки: ";
		cin >> x;
		cout << "Введите номер столбца: ";
		cin >> y;
		badPlace = 0;
		if(player == 1){
			DrawPlace(player,'x',x,y);
		}
		else if(player == 2){
			DrawPlace(player,'o',x,y);
		}
		win = WinState(player);
		if (win){
			break;
		}
		if(partOfMap == 8){
			//окрашиваем текст ничья
			printf("\033[31mНичья!\n");			printf("\033[0m\n");
			break;
		}
		
		if(badPlace == 1){
			player = 1;
		}
		else if(badPlace == 2){
			player = 2;
		}else{
			if (player == 2){
			player = 1;
		}else{
			player = 2;
		}
		}
	}
}
