#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Variables globales ATTENTE_PERE
int ATTENTE_PERE = 1;
int ATTENTE_FILS = 0;

// Change la valeur de la variable globale
void sigUsr1(int sig){
	ATTENTE_PERE = 0;
}

// Change la valeur de la variable globale
void sigUsr2(int sig){
	ATTENTE_FILS = 0;
}



int main(){
	// Si le signal reçu est SIGUSR1 alors aller dans le fonction sigUsr1
	signal(SIGUSR1, sigUsr1);
	// Si le signal reçu est SIGUSR2 alors aller dans le fonction sigUsr2
	signal(SIGUSR2, sigUsr2);

	// Création d'un long signé (possibilité d'avoir des valeurs négatives)
	pid_t pidFork;

	// Récupération du PID du processus ainsi que la création du processus fils
	pidFork = fork();


	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		printf("Je suis dans le fils \n");
		for(int i = 0; i <= 20; i = i +2){
			while(ATTENTE_FILS); // Bloquer le fils tant que la variable ATTENTE_FILS est égale à 1
			printf("%d\n", i); // Affiche les valeurs pairs
			ATTENTE_FILS = 1;
			kill(getppid(), SIGUSR1); // Envoie du signal SIGUSR1 au père
		}
		// -------- FIN PROGRAMME FILS --------


	}else{ // Sinon, nous sommes dans le père
		printf("Je suis dans le père \n");
		for(int i = 1; i <= 19; i = i +2){
			while(ATTENTE_PERE); // Bloquer le père tant que la variable ATTENTE_PERE est égale à 1
			printf("%d\n", i); // Affiche les valeur impair
			ATTENTE_PERE = 1;
			// Envoie du signal SIGUSR2 au fils
			kill(pidFork, SIGUSR2); // Envoie du signal SIGUSR2 au fils
		}
	}
	// -------- FIN PROGRAMME PERE --------

	wait(NULL); // Attente de la fin du processus fils
	return (0);
}