#include "floyd.c"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){

	FILE *fp, *fs;
	grafo *G;
	int dist[MAX];
	int inicial, final = 0;
	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0, iflg = 0, lflg = 0;
	char *arquivo = NULL;

	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:mi:l:")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados\n");
				printf("-o : indica o arquivo de saida para os dados\n");
				printf("-m : entrada e uma matriz\n");
				printf("-i : vertice inicial (obrigatorio)\n");
				printf("-l : vertice final (opcional)\n");
				break;
			}
			case 'f':{
				int x, i, j, arestas;
				arquivo = optarg;

				G = inicializar();

				fp = fopen(optarg, "r");
				fscanf(fp, "%d", &x);
				G->vertices = x;
				fscanf(fp, "%d", &x);
				arestas = x;

				while(fscanf(fp, "%d", &i) != EOF){
					fscanf(fp, "%d", &j);
					fscanf(fp, "%d", &x);
					inserirAresta(G, i, j, x);
				}
	
				fclose(fp);
				
				fflg = 1;
				break;
			}
			case 'o':{
				
				fs = fopen(optarg, "w");

				if(final != 0){

					fprintf(fs, "%d", dist[final-1]);

				} else{

					int i = 0, j = 1;
	
					while(i < G->vertices){
						fprintf(fs, "%d:%d   ", j, dist[i]);
						i++;
						j++;
					}
				}

				fclose(fs);

				oflg = 1;
				break;
			}
			case 'm':{
				int x, i = 1, j = 1;
				
				G = inicializar();
				fp = fopen(arquivo, "r");
				fscanf(fp, "%d", &x);
				G->vertices = x;

				while(fscanf(fp, "%d", &x) != EOF){
					if(x != 0){
						inserirAresta(G, i, j, x);
					}

					if(j == (G->vertices+1)){
						i++;
						j = 1;
					}
					j++;
				}
	
				fclose(fp);
				
				mflg = 1;
				break;
			}
			case 'i':{
				inicial = atoi(optarg);

				floyd(G, inicial, dist);
				imprimirFloyd(dist, G->vertices);
				printf("\n");
				
				mflg = 1;
				break;
			}
			case 'l':{
				final = atoi(optarg);
				
				floyd(G, inicial, dist);
				calcularFloyd(dist, final);
				printf("\n");
				
				mflg = 1;
				break;
			}
			case '?':{
				if(optopt == 'f' || optopt == 'o')
					fprintf(stderr, "Exemplo: -%c arquivo-entrada.txt\n", optopt);
				if(optopt == 'i' || optopt == 'l')
					fprintf(stderr, "Exemplo: -%c 1\n", optopt);
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

