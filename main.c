#include <stdio.h>

#include <time.h>

#include <stdlib.h>

#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define sizeOfRoll 3
bool isJackPot(int * combination);
int getMoneyWon(int * combination);
bool isLoseRoll(int * combination);
void generateCombination(int * combination);
void printCombination(int * combination);

/*
	В начале игры пользователю выдаётся 5000 кредитов.
	Случайным образом на барабанчиках выпадает три значения от 0 до 7.
	Призовые комбинации: 0 0 0, 1 1 1, 2 2 2, 3 3 3, 4 4 4, 5 Х Х, 5 5 Х, 5 5 5, 7 Х Х, 7 7 Х, 7 7 7
	(на месте Х может быть любая цифра).
	Штрафная комбинация: 6 6 6.
	Все остальные комбинации нейтральные.
	В любом случае, за показ новой комбинации с игрового счёта пользователя снимается определённая
	фиксированная сумма денег. Необходимо назначить различные вознаграждения за выпадение призовых комбинаций.
	Комбинации можно показывать через MessageBox, например.
	Зациклить работу приложения. Игра заканчивается поражением, если деньги закончились.
	Игра заканчивается победой, если выпадает джек-пот (7 7 7).
*/

int main(int argc, char * argv[]) {
	srand(time(NULL));
	int money = 5000;
	const int costOfRoll = 150;
	int * combination = calloc(3,sizeof(int));
	if(combination == NULL){
		printf("Memory creation error!\n");
		return (-1);
	}
	int menu = 0;
	while(money > costOfRoll) {
		printf("----------------------------------------------\n");
		printf("1) Roll one time\n");
		printf("2) Roll multiple times\n");
		printf("3) Print win combinations\n");
		printf("--------------------------Your balance is %4d\n",money);
		scanf("%d",&menu);
		switch(menu) {
			case 1: {
//					if(money - costOfRoll <= 0){
//						printf("Not enough money!\n");
//						break;
//					}
				money-= costOfRoll;
				generateCombination(combination);
				printCombination(combination);
				if (isJackPot(combination) == true) {
					printf("You won in this game!");
					exit(0);
				}
				if (isLoseRoll(combination) == true) {
					printf("You lost!");
					exit(0);
				}
				int moneyWon = getMoneyWon(combination);
				printf("You won : %d $\n", moneyWon);
				money += moneyWon;
				break;
			}
			case 2: {
				int amountOfRolls = 0;
				printf("Enter amount of rolls: ");
				scanf("%d",&amountOfRolls);
				if(amountOfRolls * costOfRoll > money) {
					printf("Not enough money!\n");
				} else {
					for(int i = 0 ; i < amountOfRolls; i++) {
						money-= costOfRoll;
						//sleep(1); // compatibility problem
						generateCombination(combination);
						printCombination(combination);
						if (isJackPot(combination) == true) {
							printf("You won in this game!");
							exit(0);
						}
						if (isLoseRoll(combination) == true) {
							printf("You lost!");
							exit(0);
						}
						int moneyWon = getMoneyWon(combination);
						printf("You won : %d $\n", moneyWon);
						money += moneyWon;
					}
				}
				break;
			}
			case 3:{
				printf("000, 111, 222, 333, 444 = 250$\n");
				printf("5XX = 350$, 55X = 500$, 555 = 700$ \n");
				printf("7XX = 450$ , 77X = 700$\n");
				printf("777 = WIN\n");
				printf("666 = LOSE\n");
				break;
			}
			case 0: {
				scanf("%d",&combination[0]);
				scanf("%d",&combination[1]);
				scanf("%d",&combination[2]);
				money-= costOfRoll;
				printCombination(combination);
				if (isJackPot(combination) == true) {
					printf("You won in this game!");
					exit(0);
				}
				if (isLoseRoll(combination) == true) {
					printf("You lost!");
					exit(0);
				}
				int moneyWon = getMoneyWon(combination);
				printf("You won : %d $\n", moneyWon);
				money += moneyWon;
				break;
			}
			default: {
				printf("Unknown input!\n");
				break;
			}
		}
	}
	free(combination);
	return 0;
}

bool isJackPot(int * combination) {
	if (combination[0] == 7 && combination[1] == 7 && combination[2] == 7) {
		return true;
	}
	return false;
}

bool isLoseRoll(int * combination) {
	if (combination[0] == 6 && combination[1] == 6 && combination[2] == 6) {
		return true;
	}
	return false;
}

int getMoneyWon(int * combination) {
	int moneyWon = 0;

	// 0 0 0, 1 1 1, 2 2 2, 3 3 3, 4 4 4 route
	if(combination[0] == combination[1] && combination[1] == combination[2]) {
		moneyWon = 250;
	}

	// 5XX, 55X, 555 route
	if (combination[0] == 5) {
		// 5XX
		moneyWon = 350;
		// 55X
		if(combination[1] == 5) {
			moneyWon = 500;
		}
		// 555
		if(combination[1] == 5 && combination[2] == 5) {
			moneyWon = 700;
		}
	}
	// 7XX, 77X route
	if (combination[0] == 7) {
		// 7XX
		moneyWon = 450;
		// 77X
		if(combination[1] == 7) {
			moneyWon = 700;
		}
		// 777 ?
		if(combination[1] == 7 && combination[2] == 7) {
			printf("You should not be here!");
			exit(-1);
		}
	}

	return moneyWon;
}

void generateCombination(int * combination) {
	int i = 0;
	for (i = 0; i < 3; i++) {
		combination[i] = rand() % 8;
	}
}

void printCombination(int * combination) {
	printf("\n\t-------  o\n");
	printf("\t| ");
	for (int i = 0; i < sizeOfRoll; i++) {
		printf("%d", combination[i]);
	}
	printf(" |./\n");
	printf("\t-------\n");
	printf("\t|     |");
	printf("\n");
}
