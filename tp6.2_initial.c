#include <stdio.h>
#include <pthread.h>

#define N 6

// Fonction qui sera exécutée par les threads spectateurs
void *spectateur(void *arg){ 
	sleep(5); // Temps d'attente avant de sortir de la salle de concert
	int *id = (int*)arg; // Récupération de l'id du spectateur
	printf("Spectateur %d sort de la salle de concert\n", *id);
	pthread_exit(NULL);
}

// Fonction qui sera exécutée par le thread orchestre
void *orchestre(void *arg){
	sleep(10); // Temps d'attente avant la fin du concert
	printf("Orchestre à fini de jouer\n");
	pthread_exit(NULL);
}

int main(){
	pthread_t thread[N]; // Tableau contenant les threads
	int id[N]={1,2,3,4,5,6}; // Tableau contenant les id des spectateurs et de l'orchestre

	printf("Orchestre commence a jouer \n");
	pthread_create(&thread[N], NULL, orchestre, NULL); // Création du thread orchestre

	for(int i=0; i < N; i++){ // Boucle qui permet de créer les threads spectateurs en fonction du nombre de spectateurs (N)
		printf("Spectateur %d entre dans la salle de concert\n",i + 1);
		pthread_create(&thread[i], NULL, spectateur, (void *)&id[i]); // Création des threads spectateurs
		sleep(1);
	}

	for (int i=0; i <= N; i++){
		pthread_join(thread[i], NULL); // Attente de la fin des threads
	}

	return 0;
}