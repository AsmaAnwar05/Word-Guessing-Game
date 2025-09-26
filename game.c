/*
  Note: download provided wordlist.txt or make your own text file (one word per line without space use).
  Place wordlist.txt in the same directory where you run the program,
  make sure to write path location correctly according to your text file location
*/
#include <ctype.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

struct Player {
    char name[15];
    int score;
    double time_taken;
};

void setName(struct Player* p,char *n) {
    strcpy(p->name, n);
}

void setScore(struct Player* p,int s) {
    p->score = s;
}

void setTime(struct Player* p,double t) {
    p->time_taken = t;
}

void printPlayer(struct Player p) {
    printf("Your Name: %s\nScore: %d\nTime Taken: %.2f seconds\n",
           p.name, p.score, p.time_taken);
}
int getHideNo(int l) {
    if (l<5) {return 1;}
    else if (l<7 && l>=5) {return 2;}
    else if (l<9 && l>=7) {return 3;}
    else if (l<11 && l>=9) {return 4;}
    else if (l<13 && l>=11) {return 5;}
    else{return 6;}
}
void hides(char word[] ) {
    int l=strlen(word);
    int noOfHid=getHideNo(l);
    int hiddenindex[l];
    for (int i=0;i<l;i++) {
    hiddenindex[i]=0;
    }
    for (int i=0;i<noOfHid;i++) {
        int random=rand()%(l);
        if (hiddenindex[random]==0) {
            if (word[random]=='a'||word[random]=='e'||word[random]=='i'||word[random]=='o'||word[random]=='u' ){
                word[random]='*';
        }
            else {
                word[random]='_';
            }
            hiddenindex[random]=1;
        }
        else {
            i--;
        }
    }
printf("Guess the Word %s\n", word);
}

void gamefunction(struct Player* p){
    int chance=2;
    int quesNo=4;
    int point=0;
    char guessword[50];
    char word[50];
    char wordcpy[50];
    double totalTime=0;
    FILE *fptr;
    fptr = fopen("E:\\clion project\\sdp project\\wordlist.txt", "r");//change file location according to text file located in your pc
    char ch;
    int wordcount=0;
    char tempword[20];
    if (fptr == NULL) {
            printf("Unable to open the file.make sure a word file exist and file location using correctly\n");
        }
        else {
            for (int i=0;fscanf(fptr, "%s", tempword) != EOF;i++) {
                wordcount++;
            }
            rewind(fptr);
            char wordbank[wordcount][20];
            for (int j = 0; j < wordcount; j++) {
                fscanf(fptr, "%s", wordbank[j]);
            }
            int randworduse[wordcount];
            for (int i = 0; i < wordcount; i++) {
                randworduse[i] = 0;
            }
            for (int i=0;i<quesNo && chance>0;i++) {
                int randindex=rand()%wordcount;
                if (randworduse[randindex]==0){
                    strcpy(word, wordbank[randindex]);
                printf("Question %d: ",i+1 );
                    strcpy(wordcpy, wordbank[randindex]);
                    for (int j=0;wordcpy[j]!='\0';j++) {
                        wordcpy[j]=tolower(wordcpy[j]);
                        word[j]=tolower(word[j]);
                    }
                    hides(wordcpy);
                printf("Input your guess and press enter\n");
                clock_t start = clock();
                scanf("%s",guessword);
                clock_t end = clock();
                double timeTaken = (double)(end - start)/CLOCKS_PER_SEC;
                totalTime=totalTime+timeTaken;
                for (int j=0;guessword[j]!='\0';j++) {
                    guessword[j]=tolower(guessword[j]);
                }
                if(strcmp(guessword, "s") == 0) {
                    printf("moving to next question.Word was %s\n", word);
                    point--;
                    chance--;
                    printf("Your score now %d\n",point);
                    printf("You have %d chance\n\n",chance);
                }
                else {
                    if (strcmp(guessword,word)==0) {
                        printf("Correct Guess\n");
                        point++;
                        printf("Your score now %d\n\n",point);
                    }
                    else {
                        printf("Wrong Guess. Word was %s\n", word);
                        point--;
                        chance--;
                        printf("Your score now %d\n",point);
                        printf("You have %d chance\n\n",chance);

                    }
                }
                    randworduse[randindex]=1;
            }
                else{i--;}
            }
    }
    p->score = point;
    p->time_taken = totalTime;
    printPlayer(*p);

}
void welcome() {
    printf("Welcome to Word Guessing Game\n"
       "Game rules:\n1.Maximum player: 3.\n"
       "2. There are 4 question to answer.\n"
       "3.you have 2 chance for wrong guess. if you guess wrong or want to skip a question than 1 point decress\n"
       "4.If player more than one,there are one winner who score most. "
       "if there are draw than compare who took less time\n\n");

}
int main() {
    srand(time(NULL));
    char name[20];
    welcome();
    int playerno;
    printf("Input player number\n");
    scanf("%d",&playerno);
    if (playerno<=4 && playerno>0) {
        struct Player players[playerno];
        for (int i=0;i<playerno;i++) {
        printf("\n\n Enter name of player no %d\n",i+1);
            scanf("%s", players[i].name);
            players[i].score = 0;
            players[i].time_taken = 0;
            printf("Game started for %s\n", players[i].name);
            gamefunction(&players[i]);
        }

        printf("\nAll players finished and Results:\n");

        int winnerNum = 0;
        for (int i = 0; i < playerno; i++) {
            if (players[i].score > players[winnerNum].score) {
                winnerNum = i;
            }
            else if (players[i].score == players[winnerNum].score) {
                if (players[i].time_taken < players[winnerNum].time_taken) {
                    winnerNum = i;
                }
            }
        }

        printf("Winner is %s with score %d and time %.2f seconds\n",
               players[winnerNum].name,
               players[winnerNum].score,
               players[winnerNum].time_taken);
    }
    else {
        printf("You must enter a number between 1 and 4\n");
    }

    return 0;
}
