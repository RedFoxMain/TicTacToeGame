//Сделано RedFoxMain
//github https://github.com/RedFoxMain

//ВАЖНО: если вы работаете на Linux, то закомментируйте первую строку после этого комментария
const bool isWindows = true;

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cctype>

#ifdef isWindows
#include <windows.h>
#else
#include <unistd.h>
#endif


// переменные для игры
//длинна карты
const int length = 3;
//карта
char map[length][length] = {};
//чем заполнять карту
char mapSymbol = '#';
//иконки первого и второго игрока
char firstPlayerIcon = 'x';
char secondPlayerIcon = 'o';
//задержка для метода sleep()
int delayForSleep = 2;
int badPlace = 0;
//считает не занятые mapSymbol
int countEmptyCells = 0;
bool win = false;
char playerIcon;

int rowInput, colInput;
int row, col;


//отрисовать карту
void DrawBoard(){
	for(int i = 0; i < length; i++)
	    {
	   	 for(int j = 0; j < length; j++)
	   	 {
	   	 	std::cout << map[i][j];
	   	 }
	   	 std::cout << std::endl;
	    }
}
//заполняем карту
void FillMap(){
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		    {
		   	 map[i][j] = mapSymbol;
		    }
	}
}
void DrawPlaceForMenu(){
	FillMap();
	DrawBoard();
}
///////////////////
void RowInput(){
	do {
    		std::cout << "Введите номер строки: ";
    		std::cin >> rowInput;
    		if (!(std::cin.good())){
    		    std::cout << "\033[31m";
        		std::cout << "Неверно введен row"<<std::endl;
        		std::cout << "\033[0m";
    			std::cin.clear();
    			std::cin.ignore();
			}else{
				row = rowInput;
			}
		} while (!(std::cin.good()));
}
void ColInput(){
	do {
    		std::cout << "Введите номер столбца: ";
    		std::cin >> colInput;
    		if (!(std::cin.good())){
    		    std::cout << "\033[31m";
        		std::cout << "Неверно введен col" << std::endl;
        		std::cout << "\033[0m";
    			std::cin.clear();
    			std::cin.ignore();
			}else{
				col = colInput;
			}
		} while (!(std::cin.good()));
	
}
// очерёдность хода
int NextPlayer(int player){
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
		return player;
}
// ничья
bool NoBodyWin(){
	if(countEmptyCells == 8){
			//окрашиваем текст ничья
			printf("\033[31m");
			std::cout << "Ничья!" << std::endl;			printf("\033[0m");
			return true;
	}
	return false;
}
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
	 if ((map[0][0] == playerIcon && map[0][1] == playerIcon && map[0][2] == playerIcon)
    || (map[1][0] == playerIcon && map[1][1] == playerIcon && map[1][2] == playerIcon)
    || (map[2][0] == playerIcon && map[2][1] == playerIcon && map[2][2] == playerIcon)
    || (map[0][0] == playerIcon && map[1][0] == playerIcon && map[2][0] == playerIcon)
    || (map[0][1] == playerIcon && map[1][1] == playerIcon && map[2][1] == playerIcon)
    || (map[0][2] == playerIcon && map[1][2] == playerIcon && map[2][2] == playerIcon)
    || (map[0][0] == playerIcon && map[1][1] == playerIcon && map[2][2] == playerIcon)
    || (map[0][2] == playerIcon && map[1][1] == playerIcon && map[2][0] == playerIcon)) {
    std::cout << "\033[31m";
    std::cout << "Игрок номер " << player << " закончил партию быстрее!" << std::endl;
    std::cout << "Победа игрока номер " << player << std::endl;
    std::cout << "\033[0m";
    return true;
}
return false;
}

// Эта функция уже отрисовывает игровое поле
void DrawPlace(int player,char playerIcon, int row, int col){
	// Если row, col, которые указал пользователь равны mapSymbol, то игрок может может поставить туда x или o.
	if (map[row][col] == mapSymbol){
		map[row][col] = playerIcon;
	}else{ // иначе ход не засчитывается и активному пользователю нужно сделать ход.
		if (player == 1){
			badPlace = 1;
		}else{
			badPlace = 2;
		}
		//Окрашиваем текст "Клетка занята"
		printf("\033[31mКлетка занята!\n");
		sleep(delayForSleep);
		printf("\033[0m");
}
	// считаем сколько mapSymbol осталось. Это нужно для отслеживания ничьей
	countEmptyCells++;
	//обновляем карту
	#ifdef isWindows
		system("cls");
	#else
		system("clear");
	#endif
	DrawBoard();
}

int main(int argc, char *argv[])
{
	FillMap();
	DrawPlaceForMenu();
	bool checkIfWin;
	int player = 1;
	while(true){
		printf("Игрок #%i",player);
		std::cout << std::endl;
		//получаем row
    	RowInput();
    	//получаем col
    	ColInput();
	    // Проверяем, что клетка не заполнена
	    if (map[row][col] != mapSymbol){
	        std::cout << "\033[31m";
	        std::cout << "Клетка уже заполнена.\nПопробуйте еще раз." << std::endl;
	        std::cout << "\033[0m";
	        continue;
	    }
	    //ход активного игрока
	    //badPlace = 0;
		if(player == 1){
			DrawPlace(player,firstPlayerIcon, row, col);
		}
		else if(player == 2){
			DrawPlace(player, secondPlayerIcon, row, col);
		}
	
		// Отслеживаем победил первый или второй игрок.
		checkIfWin = WinState(player);
		if (checkIfWin){
			break;
		}
		//Если на поле остался всего лишь один mapSymbol
		bool noBodyWin = NoBodyWin();
		if(noBodyWin){
			break;
		}
		// Здесь контролируем очерёдность ходов
		player = NextPlayer(player);
	}
}
