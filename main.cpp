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
// переменные для игры
//длинна карты
int length = 3;
//карта
char map[3][3];
//чем заполнять карту
char mapSymbol = '#';
//иконки первого и второго игрока
char firstPlayerIcon = 'x';
char secondPlayerIcon = 'o';
int badPlace = 0;
int countPartOfMap = 0;
bool win = false;
char playerIcon;
int player = 1;
int row,col;
bool ckeckIfWin;

// Эта функция отрисовывать поле(для красоты)
void DrawPlaceForMenu(){
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		    {
		   	 map[i][j] = mapSymbol;
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
	if(player == 1){
		playerIcon = firstPlayerIcon;
	}
	else{
		playerIcon = secondPlayerIcon;
	}
	//Здесь происходит очень важная проверка, но как она работает долго рассказывать.
	if((map[0][0] == playerIcon && map[0][1] == playerIcon && map[0][2] == playerIcon) || (map[1][0] == playerIcon && map[1][1] == playerIcon && map[1][2] == playerIcon) || (map[2][0] == playerIcon && map[2][1] == playerIcon && map[2][2] == playerIcon) || (map[0][0] == playerIcon && map[1][0] == playerIcon && map[2][0] == playerIcon) || (map[0][1] == playerIcon && map[1][1] == playerIcon && map[2][1] == playerIcon) || (map[0][2] == playerIcon && map[1][2] == playerIcon && map[2][2] == playerIcon) || (map[0][0] == playerIcon && map[1][1] == playerIcon && map[2][2] == playerIcon) || (map[0][2] == playerIcon && map[1][1] == playerIcon && map[2][0] == playerIcon)){
		    printf("\033[31m");
			cout << "Игрок номер "<< player<< " закончил партию быстрее!" << endl;
			cout << "Победа игрока номер "<< player << endl;
			printf("\033[0m");
			win = true;
		}
	return win;
}

// Эта функция уже отрисовывает игровое поле
void DrawPlace(int player,char playerIcon, int row, int col){
	if (map[row][col] == mapSymbol){
		map[row][col] = playerIcon;
	}else{
		if (player == 1){
			badPlace = 1;
		}else{
			badPlace = 2;
		}
		//Окрашиваем текст
		printf("\033[31mКлетка занята!\n");
		sleep(2);
		printf("\033[0m");
}
	
	countPartOfMap += 1;
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
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		    {
		   	 map[i][j] = mapSymbol;
		    }
	}
	
	DrawPlaceForMenu();
	while(true){
		printf("Игрок #%i",player);
		cout << endl;
		cout << "Введите номер строки: ";
		cin >> row;
		cout << "Введите номер столбца: ";
		cin >> col;
		badPlace = 0;
		if(player == 1){
			DrawPlace(player,firstPlayerIcon, row, col);
		}
		else if(player == 2){
			DrawPlace(player, secondPlayerIcon, row, col);
		}
		ckeckIfWin = WinState(player);
		if (ckeckIfWin){
			break;
		}
		if(countPartOfMap == 8){
			//окрашиваем текст ничья
			printf("\033[31m");
			cout << "Ничья!" << endl;			printf("\033[0m");
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


