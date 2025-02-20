#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUMSNAILS 15
#define CLEARSCREEN printf("\e[2;1H\e[2J");

extern const char medal[15][91];
extern const char loser[8][49];

enum trackLength {
	SPRINT = 1000,
	SHORT = 2000,
	MEDIUM = 4000,
	LONG = 10000,
	MARATHON = 100000
};

typedef struct {
	int speed;
	float luck;
	char breed[50];
	int chosen; // if snail is chosen by user
	char bestRace[8];
	int bestTrackInt;
} snail;

float finishTime(snail snail, int trackLength, int trackType);
void makeFinishOrder(snail snails[], int finishOrder[NUMSNAILS][2], int trackLength, int trackType);

int main() {
	int playAgain = 1;
	while (playAgain == 1) {	
		
		CLEARSCREEN

		// time seed or something i dont understand it
		srand((time(NULL)));

		// list of premade names for snails
		char names[38][15] = {"Primous", "Sparsimus", "Variorumus", "Imprimisus", "Primous", "Ultimous", "Gregatimus", "Itemus", "Sparsimus", "Literatimus", "Paceus", "Gratisus", "Tantius", "Ubiqueus", "Sparsimus", "Stillatimus", "Partimus", "Interimus", "Secundumus", "Quaus", "Tantius", "Statimus", "Viceus", "Interimus", "Quatenusus", "Alternatimus", "Videlicetus", "Guttatimus", "Ergous", "Solus", "Circiterus", "Quasius", "Ergous", "Viceus", "Versusite", "Syllabatimusus", "Vulgousus", "Quasius"};
		
		// prefix to the snail names. i'm sure there's a better way to do this but this works for now
		char classification[32] = "Snailus ";
		
		// create multiple snails & value  for name
		snail snail[NUMSNAILS];
		int randomNameVal;

		// assign values to snails, probably should make it a function
		for (int i = 0; i < NUMSNAILS; i++) {
			randomNameVal = (rand() % 38);
			snail[i].speed = (rand() % 10) + 1;
			snail[i].luck =  (rand() % 10 + 1);
			strcpy(snail[i].breed, (strcat(classification, names[randomNameVal % 41])));
			strcpy(classification, "Snailus ");
			int trackPerformance = 0;
			snail[i].bestTrackInt = ((rand() % 5) + 1);
			if (snail[i].bestTrackInt == 1) {
				strcpy(snail[i].bestRace, "Sprint");
			} else if (snail[i].bestTrackInt == 2) {
				strcpy(snail[i].bestRace, "Short");
			} else if (snail[i].bestTrackInt == 3) {
				strcpy(snail[i].bestRace, "Medium");
			} else if (snail[i].bestTrackInt == 4) {
				strcpy(snail[i].bestRace, "Long");
			} else if (snail[i].bestTrackInt == 5) {
				strcpy(snail[i].bestRace, "Marathon");
			}
		}

		// user decides what track they want (note that this is done BEFORE the snail is chosen.)
		int userTrack;
		printf("What track size do you want to run on?\n(1) Sprint, 100m\n(2) Short, 200m\n(3) Medium, 400m\n(4) Long, 1KM\n(5) Marathon, 10KM\nEnter (1-5): ");
		scanf("%d", &userTrack);
		int trackType = userTrack;
		
		// determine track length.
		switch(userTrack) {
			case 1:
				userTrack = SPRINT;
				printf("You have chosen the Sprint!\n");
				break;
			case 2:
				userTrack = SHORT;
				printf("You have chosen the Short race!\n");
				break;
			case 3:
				userTrack = MEDIUM;
				printf("You have chosen the Medium race!\n");
				break;
			case 4:
				userTrack = LONG;
				printf("You have chosen the Long race!\n");
				break;
			case 5:
				userTrack = MARATHON;
				printf("You have chosen the Marathon!\n");
				break;
		}

		CLEARSCREEN

		// print out the different snails, user chooses what snail they want
		for (int i = 0; i < NUMSNAILS; i++) {
			printf("\nSnail %d (%s)\nSpeed: %d/10\nBest race: %s\n",(i + 1), snail[i].breed, snail[i].speed, snail[i].bestRace);
			sleep(1);
		}

		int userSnail;
		printf("\nWhich snail do you want choose? (Enter 1-%d):",NUMSNAILS);
		scanf("%d", &userSnail);
		snail[userSnail - 1].chosen = 1;

		CLEARSCREEN

		printf("You have chosen snail %d!\n", userSnail);
		
		// "wait" for snails to finish racing
		fflush(stdout);
		printf("Waiting for snails to finish racing");
		fflush(stdout);
		sleep(4);
		printf(".");
		fflush(stdout);
		sleep(4);
		printf(".");
		fflush(stdout);
		sleep(4);
		printf(".");
		fflush(stdout);
		sleep(4);
		printf(".");
		fflush(stdout);
		sleep(4);
		printf(".\n");
		fflush(stdout);

		// calculate finishing times and finishing orders.
		int finishTimes[NUMSNAILS][2];
		int finishOrders[NUMSNAILS][2];
		makeFinishOrder(snail, finishOrders, userTrack, trackType);
		for (int i = 0; i < NUMSNAILS; i++) {
			finishTimes[i][1] = finishTime(snail[i], userTrack, trackType); } printf("Here are the Finishing Times:\n");
		for(int i = 0; i < NUMSNAILS; i++) {
			printf("Snail %d:\tTime: %d\n",i+1,finishTimes[i][1]);
		}
		for(int i = 1; i <= NUMSNAILS; i++) {
			finishOrders[i-1][1] = i;
		}

		int place;
		for(int i = 0; i < NUMSNAILS; i++) {
			if (finishOrders[i][0] == (userSnail)) {	
				place = finishOrders[i][1];
				break;
			}
		}

		switch (place) {
			case 1:
				for(int i = 0; i < 15; i++) {
					printf("%s\t%s\t%s\n", medal[i], medal[i], medal[i]);
				}
				printf("\n\n\nYou came first! Well done!\n");
				break;
			case 2:
				for(int i = 0; i < 15; i++){
					printf("%s\t%s\n", medal[i], medal[i]);
				}
				printf("\n\n\nYou came Second! Can you get first place next time?!\n");
				break;

			case 3:
				for(int i = 0; i < 15; i++){
					printf("%s\n",medal[i]);
				}
				printf("\n\n\nYou came Third. Maybe try a different snail next time!\n");
				break;
			
			case 4:
				printf("\n");
				for(int i = 0; i < 8; i++){
					printf("%s\n",loser[i]);
				}
				printf("\n\n\nYou came Fourth.One place away from the podium!\n");
				break;
			
			case 5:
				printf("\n");
				for(int i = 0; i < 15; i++){
					printf("%s\n",loser[i]);
				}
				printf("\n\n\nYou came %d.You can only go up from here!\n",place);
				break;

		};
		printf("\nDo you want to play again?\n(1) Yes\n(0) No\n");
		scanf("%d", &playAgain);
	}

}

float finishTime(snail snail, int trackLength, int trackType) {
		float trackPerformance = 1;
		if (trackType == snail.bestTrackInt) {
			trackPerformance = 1.5;
		} else if ((trackType == snail.bestTrackInt + 1) || (trackType == snail.bestTrackInt - 1)) {
			trackPerformance = 0.75;
		} else if ((trackType == snail.bestTrackInt + 2) || (trackType == snail.bestTrackInt - 2)) {
			trackPerformance = 0.25;
		}
	int performance = (rand() % 10 );
	return trackLength / (trackPerformance * snail.speed * snail.luck);
}

void makeFinishOrder(snail snails[], int finishOrder[NUMSNAILS][2], int trackLength, int trackType) {
    for (int i = 0; i < NUMSNAILS; i++) {
        finishOrder[i][0] = i + 1;
        finishOrder[i][1] = finishTime(snails[i], trackLength, trackType);
    }
    // basic bubble sort
    for (int i = 0; i < NUMSNAILS; i++) {
        for (int j = i + 1; j < NUMSNAILS; j++) {
            if (finishOrder[i][1] > finishOrder[j][1]) {
                int tempTime = finishOrder[i][1];
                finishOrder[i][1] = finishOrder[j][1];
                finishOrder[j][1] = tempTime;
                int tempSnail = finishOrder[i][0];
                finishOrder[i][0] = finishOrder[j][0];
                finishOrder[j][0] = tempSnail;
            }
        }
    }
}
