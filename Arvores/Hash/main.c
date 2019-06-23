#include "hash.c"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){

	int tamanho = 0;
	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0;
	hash *h[SIZE];

	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:m:")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados na Hash\n");
				printf("-o : indica o arquivo de saida para os dados a serem adicionados na Hash\n");
				printf("-m : indica o tamanho da Hash\n");
				break;
			}
			case 'f':{
				int x;
				if(tamanho <= 0){
					FILE *fp;
					fp = fopen(optarg, "r");
				
					inicializarHash(h);

					while(fscanf(fp, "%d", &x) != EOF){
						inserirHash(h, x);
					}

					imprimirHash(h);
					fclose(fp);
				}
				else{
					FILE *fp;
					fp = fopen(optarg, "r");
				
					inicializarHash2(h, tamanho);

					while(fscanf(fp, "%d", &x) != EOF){
						inserirHash2(h, x, tamanho);
					}

					imprimirHash2(h, tamanho);
					fclose(fp);
				}

				fflg = 1;
				break;
			}
			case 'o':{
				int i;

				if(tamanho <= 0){
					FILE *fs;
					fs = fopen(optarg, "w");
					
					hash* aux;

					for(i = 0; i < SIZE; i++){

						aux = h[i];
						fprintf(fs, "%d: ", i);
						while(aux != NULL){
			
							fprintf(fs, "%d ", aux->dado);
							aux = aux->prox;
						}
						fprintf(fs, "\n");
					}

					fclose(fs);
				}
				else{
					FILE *fs;
					fs = fopen(optarg, "w");
					
					hash* aux;

					for(i = 0; i < tamanho; i++){

						aux = h[i];
						fprintf(fs, "%d: ", i);
						while(aux != NULL){
			
							fprintf(fs, "%d ", aux->dado);
							aux = aux->prox;
						}
						fprintf(fs, "\n");
					}

					fclose(fs);
				}

				oflg = 1;
				break;
			}
			case 'm':{
				tamanho = atoi(optarg);
				
				mflg = 1;
				break;
			}
			case '?':{
				if(optopt == 'f' || optopt == 'o')
					fprintf(stderr, "Exemplo: -%c arquivo-entrada.txt\n", optopt);
				if(optopt == 'm')
					fprintf(stderr, "Exemplo: -%c 13\n", optopt);
				else
					fprintf(stderr, "Opcao invalida -%c\n", optopt);
				break;
			}
			default:
				fprintf(stderr, "getopt");
		}
	}

	return 0;
}

