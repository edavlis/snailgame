#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUMSNAILS 5

extern const char medal[15][91];

enum trackLength {
	SPRINT = 100,
	SHORT = 200, MEDIUM = 400,
	LONG = 1000,
	MARATHON = 10000
};

typedef struct {
	int speed;
	float luck;
	char breed[50];
	int chosen; // if snail is chosen by user
} snail;

unsigned int finishTime(snail snail, int trackLength) {
	int performance = (rand() % 9 );
	return trackLength / (snail.speed * (snail.luck * 10) / 10);
}

void makeFinishOrder(snail snails[], int finishOrder[5][2], int trackLength) {
    for (int i = 0; i < 5; i++) {
        finishOrder[i][0] = i + 1;
        finishOrder[i][1] = finishTime(snails[i], trackLength);
    }

    // basic bubble sort
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
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

int main() {
	srand((time(NULL)));
	char names[40][15] = {"Primous", "Sparsimus", "Variorumus", "Imprimisus", "Primous", "Ultimous", "Gregatimus", "Itemus", "Sparsimus", "Literatimus", "Paceus", "Gratisus", "Tantius", "Ubiqueus", "Sparsimus", "Stillatimus", "Partimus", "Interimus", "Secundumus", "Quaus", "Tantius", "Statimus", "Viceus", "Interimus", "Quatenusus", "Alternatimus", "Videlicetus", "Guttatimus", "Ergous", "Solus", "Circiterus", "Quasius", "Ergous", "Viceus", "Versusite", "Syllabatimusus", "Vulgousus", "Quasius"};
	
	// prefix to the snail names. i'm sure there's a better way to do this but this works for now
	char classification[32] = "Snailus ";
	// create multiple snails
	snail snail[5];

	int randomNameVal;

	// assign values to snails
	for (int i = 0; i < 5; i++) {
		randomNameVal = (rand() % 38);
		snail[i].speed = (rand() % 10);
		snail[i].luck =  (float) ((float) (rand() % 11) / 10 + 1);
		snail[i].chosen = 0;
		strcpy(snail[i].breed, (strcat(classification, names[randomNameVal % 41])));
		strcpy(classification, "Snailus ");
	}

	// clear screen
	//printf("\e[1;1H\e[2J");

	// print out the different snails
	for (int i = 0; i < 5; i++) {
		printf("\nSnail %d:\nSnail Species: %s\nSpeed: %d\nLuck: %.1f\n",(i + 1), snail[i].breed, snail[i].speed, snail[i].luck);
	}


	int userSnail;
	printf("\nWhich snail do you want choose? (Enter 1-5): " );
	scanf("%d", &userSnail);
	snail[userSnail - 1].chosen = 1;



	// clear screen
	printf("\e[1;1H\e[2J");

	printf("You have chosen snail %d!\n", userSnail);

	int userTrack;
	printf("What track size do you want to run on?\n(1) Sprint, 100m\n(2) Short, 200m\n(3) Medium, 400m\n(4) Long, 1KM\n(5)Marathon, 10KM\nEnter (1-5): ");
	scanf("%d", &userTrack);

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

	// clear screen
	printf("\e[1;1H\e[2J");

	int finishTimes[5][2];
	int finishOrders[5][2];
        makeFinishOrder(snail, finishOrders, userTrack);
	for (int i = 0; i < 5; i++) {
		finishTimes[i][1] = finishTime(snail[i], userTrack); } printf("Here are the Finishing Times:\n");
	for(int i = 0; i < 5; i++) {
		printf("Snail %d:\tTime: %d\n",i+1,finishTimes[i][1]);
	}
	for(int i = 1; i <= 5; i++) {
		finishOrders[i-1][1] = i;
	}

	printf("Here are the Finishing Places:\n");
	for(int i = 0; i < 5; i++) {
		printf("Snail %d:\tTime: %d\n",i+1,finishOrders[i][1]);
	}
	

	// clear screen
	printf("\n\n\n\n\n\n\n\n\n\n\n");

	switch (finishOrders[userSnail -1][1]) {
		case 1:
			for(int i = 0; i < 15; i++){
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
			printf("\n\n\nYou came Fourth. At least you're not last place!\n");
			break;
		
		case 5:
			printf("\n\n\nYou came Fifth.You can only go up from here!\n");
			break;

	};

}
