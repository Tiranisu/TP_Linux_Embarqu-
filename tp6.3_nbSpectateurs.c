#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4

sem_t sem; // Création du sémaphore
int CPT = 0; // Variable globale CPT

// Fonction qui sera exécutée par les threads spectateurs
void *spectateur(void *arg){
	sleep(5); // Temps d'attente avant de sortir de la salle de concert
	int *id = (int*)arg; // Récupération de l'id du spectateur
	sem_wait(&sem);  // Attente de la libération du sémaphore et le met en état occupé
	CPT--; // Décrémentation du nombre de spectateurs
	sem_post(&sem); // Libération du sémaphore
	printf("Spectateur %d sort de la salle de concert (%d spectateur (s) dans la salle)\n", *id, CPT);
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
	int id[4]={1,2,3,4}; // Tableau contenant les id des spectateurs et de l'orchestre

	sem_init(&sem, 0, 1); // Initialisation du sémaphore en état libre par défaut

	printf("Orchestre commence a jouer \n");
	pthread_create(&thread[N], NULL, orchestre, NULL); // Création du thread orchestre

	for(int i=0; i < N; i++){
		pthread_create(&thread[i], NULL, spectateur, (void *)&id[i]); // Création des threads spectateurs
		sem_wait(&sem); // Attente de la libération du sémaphore et le met en état occupé
		CPT++;
		sem_post(&sem); // Libération du sémaphore
		printf("Spectateur %d entre dans la salle de concert (%d spectateur (s) dans la salle)\n",i + 1, CPT);
		sleep(1);
	}
	for (int i=0; i <= N; i++){
		pthread_join(thread[i], NULL); // Attente de la fin des threads
	}

	sem_destroy(&sem); // Destruction du sémaphore
	return (0);
}
