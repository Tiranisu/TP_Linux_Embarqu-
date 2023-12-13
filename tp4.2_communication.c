#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

	pid_t pidFork; // Création d'un long signé (possibilité d'avoir des valeurs négatives)
	char buffer[BUFSIZ]; // Création du buffer

	int  pfd1[2]; // Création du tube 1
	// Verification de la création du tube 1
	if(pipe(pfd1) == -1){
		printf("pipe 1 failed\n");
		return 1;
	}

	int  pfd2[2]; // Création du tube 2
	// Verification de la création du tube 2
	if(pipe(pfd2) == -1){
		printf("pipe 2 failed\n");
		return 1;
	}

	// Récupération du PID du processus ainsi que la création du processus fils
	pidFork = fork();

	if(pidFork == 0){ // Si le PID est égal à 0, cela signifie que nous sommes dans le fils
		printf("Je suis dans le fils \n");

		for(int i = 0; i <= 4; i++){
			printf("%d ", i); // Affichage de 0 - 4 
		}
		printf("\n");

		strcpy(buffer, "4"); // Copie de la valeur 4 dans le buffer
		close(pfd1[0]); // Fermeture pipe read
		write(pfd1[1], buffer, strlen(buffer)+1); // Ecriture dans le pipe 1
		close(pfd1[1]); // Fermeture pipe write


		close(pfd2[1]); // Fermeture pipe write
		while (read(pfd2[0], buffer, BUFSIZ) != 0); // Lecture du pipe 2
		close(pfd2[0]); // Fermeture pipe read

		printf("Je suis dans le fils 2\n");

		if(strcmp(buffer, "10") == 0){
			for(int i = 11; i <= 15; i++){
				printf("%d ", i); // Affichage de 11 - 15
			}
		}

		printf("\n");
		//-------- FIN PROGRAMME FILS --------


	}else{ // Sinon, nous sommes dans le père
		close(pfd1[1]); // Fermeture pipe write
		while (read(pfd1[0], buffer, BUFSIZ) != 0); // Lecture du pipe 1
		close(pfd1[0]); // Fermeture pipe read

		printf("Je suis dans le père\n");

		if(strcmp(buffer, "4") == 0){ // Si la valeur du buffer est égale à 4 afficher 5 - 10
			for(int i = 5; i <= 10; i++){
				printf("%d ", i);
			}
		}
		printf("\n");

		strcpy(buffer,"10"); // Copie de la valeur 10 dans le buffer
		close(pfd2[0]); // Fermeture pipe read
		write(pfd2[1], buffer, strlen(buffer)+1); // Ecriture dans le pipe 2
		close(pfd2[1]); // Fermeture pipe write

		wait(NULL); // Attente de la fin du processus fils
		printf("Je suis dans le père 2\n");

		for(int i = 16; i <= 21; i++){
			printf("%d ", i); // Affichage de 16 - 21
		}
		printf("\n");
		//-------- FIN PROGRAMME PERE --------
	}
	return (0);
}

