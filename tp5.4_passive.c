#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigUsr1(int s){return;}
void sigUsr2(int s){return;}

int main(){
	// Création d'un long signé (possibilité d'avoir des valeurs négatives)
	pid_t pidFork;

	// Récupération du pid du processus
	pidFork = fork();

	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		signal(SIGUSR2, sigUsr2); // Si le signal reçu est SIGUSR2 alors aller dans le fonction sigUsr2

		sigset_t mask2; // creation du masque dinterruption
		sigfillset	(&mask2 ) ; // initialisation(toutes interruptions masquees )
		sigdelset(&mask2 , SIGUSR2) ; // demasquage de l interruption SIGUSR1

		printf("Je suis dans le fils \n");
		for(int i = 0; i <= 20; i = i +2){
			printf("%d\n", i); // Affiche les valeurs pairs
			// Envoie du signal SIGUSR1 au père
			kill(getppid(), SIGUSR1);
			// Attente de reception du signal SIGUSR2
			sigsuspend(&mask2);
		}
		kill(getppid(), SIGUSR1);
		// -------- FIN PROGRAMME FILS --------


	}else{ // Sinon, nous sommes dans le père
		// Si le signal reçu est SIGUSR1 alors aller dans le fonction sigUsr1
		signal(SIGUSR1, sigUsr1);

		sigset_t mask1; // creation du masque dinterruption
		sigfillset	(&mask1 ) ; // initialisation (toutes interruptions masquees )
		sigdelset(&mask1 , SIGUSR1) ; // demasquage de l interruption SIGUSR1

		// Attente de reception du signal SIGUSR1
		sigsuspend(&mask1);

		printf("Je suis dans le père \n");
		// Affiche les valeurs impaires
		for(int i = 1; i <= 19; i = i +2){
			printf("%d\n", i);
			// Envoie du signal SIGUSR1 au fils
			sleep(1);
			kill(pidFork, SIGUSR2); // Envoie du signal SIGUSR2 au fils
			sigsuspend(&mask1); // Attente de reception du signal SIGUSR1
		}
	}
	sleep(1); // Attente car sinon l'ordre des commandes n'est pas respecté
	kill(pidFork, SIGUSR2); // Envoie du signal SIGUSR2 au fils
	// -------- FIN PROGRAMME PERE --------

	wait(NULL); // Attente de la fin du processus fils
	return (0);
}

