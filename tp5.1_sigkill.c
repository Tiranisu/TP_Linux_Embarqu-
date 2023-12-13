#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){

	// Création d'un long signé (possibilité d'avoir des valeurs négatives)
	pid_t pidFork;

	// Récupération du PID du processus ainsi que la création du processus fils
	pidFork = fork();


	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		printf("Je suis dans le fils \n");
		for(int i = 0; i <= 20; i = i +2){
			printf("%d\n", i); // Affiche les valeurs pairs
			sleep(1);
		
		}
		printf("\n");
		// -------- FIN PROGRAMME FILS --------


	}else{ // Sinon, nous sommes dans le père
		printf("Je suis dans le père \n");
		for(int i = 1; i <= 19; i = i +2){
			sleep(1); 
			printf("%d\n", i); // Affiche les valeurs impairs

			// Si nous arrivons à la valeur 9, alors on arrête le programme fils
			if(i == 9){
				kill(pidFork, 9);
			}
		}
		printf("\n");
		// -------- FIN PROGRAMME PERE --------
	}

	wait(NULL); // Attente de la fin du processus fils
	return (0);
}
