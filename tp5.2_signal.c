#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Variable globale ATTENTE_PERE
int ATTENTE_PERE = 1;

// Change la valeur de la variable globale
void sigUsr1(int sig){
	ATTENTE_PERE = 0;
}

int main(){
	// Si le signal reçu est SIGUSR1 alors aller dans le fonction sigUsr1
	signal(SIGUSR1, sigUsr1);

	// Création d'un long signé (possibilité d'avoir des valeurs négatives)
	pid_t pidFork;

	// Récupération du PID du processus ainsi que la création du processus fils
	pidFork = fork();

	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		printf("Je suis dans le fils \n");
		// Affiche les valeurs pair
		for(int i = 0; i <= 20; i = i +2){
			printf("%d\n", i);
			sleep(1);
		}
		printf("\n");
		// Envoie du signal SIGUSR1 au père
		kill(getppid(), SIGUSR1);
		// -------- FIN PROGRAMME FILS --------


	}else{ // Sinon, nous sommes dans le père
		// Bloquer le père
		while(ATTENTE_PERE);

		printf("Je suis dans le père \n");
		// Affiche les valeur impair
		for(int i = 1; i <= 19; i = i +2){
			sleep(1);
			printf("%d\n", i);

			// Si nous arrivons à la valeur 9, alors on arrête le programme fils
			if(i == 9){
				kill(pidFork, 9);
			}
		}
		printf("\n");
	}
	// -------- FIN PROGRAMME PERE --------

	wait(NULL); // Attente de la fin du processus fils
	return (0);

}