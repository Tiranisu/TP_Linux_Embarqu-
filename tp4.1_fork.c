#include <stdio.h>
#include <unistd.h>

int main(){
	// Création d'un long signé (possibilité d'avoir des valeurs négatives)
	pid_t pidFork;

	// Récupération du PID du processus ainsi que la création du processus fils
	pidFork = fork();

	
	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		printf("Je suis dans le fils \n");
		for(int i = 0; i <= 20; i = i +2){
			printf("%d ", i); // Affichage des nombres pairs
		}
		printf("\n");
		//-------- FIN PROGRAMME FILS --------

	}else{ // Sinon, nous sommes dans le père
		printf("Je suis dans le père \n");
		for(int i = 1; i <= 19; i = i +2){
			printf("%d ", i); // Affichage des nombres impairs
		}
		printf("\n");
		//-------- FIN PROGRAMME PERE --------
	}

	printf("La valeur de retour de fork vaut %d\n", pidFork); // Affichage de la valeur de retour de fork
	printf("Le PID courant est : %d\n\n", getpid()); // Affichage du PID courant

	// Attente de la fin du processus fils
	wait(NULL);
	return (0);

}