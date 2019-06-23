#include "prim.c"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){

	FILE *fp, *fs;
	grafo *G;
	int vertices[MAX];
	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0, sflg = 0;
	char *arquivo = NULL;
	int agm = 0;

	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:ms:")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados\n");
				printf("-o : indica o arquivo de saida para os dados\n");
				printf("-s : mostra a solucao (em ordem crescente)\n");
				printf("-m : entrada e uma matriz\n");
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

				agm = prim(G, G->vertices, vertices);
				printf("%d\n", agm);

				fclose(fp);
				
				fflg = 1;
				break;
			}
			case 'o':{
				
				fs = fopen(optarg, "w");

				fprintf(fs, "%d", agm);

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

				agm = prim(G, G->vertices, vertices);
				printf("%d\n", agm);
	
				fclose(fp);
				
				mflg = 1;
				break;
			}
			case 's':{

				printf("\n");
				
				mflg = 1;
				break;
			}
			case '?':{
				if(optopt == 'f' || optopt == 'o')
					fprintf(stderr, "Exemplo: -%c arquivo-entrada.txt\n", optopt);

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

