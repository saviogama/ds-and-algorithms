#include "kruskal.c"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){

	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0, sflg = 0;
	
	FILE *fp, *fs;
	grafo *G;
	conjunto saida;
	vetorA vf;
	int custo[1], s = 0;
	char *arquivo = NULL;
	
	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:sm")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados\n");
				printf("-o : indica o arquivo de saida para os dados\n");
				printf("-m : calcula o custo da arvore geradora minima\n");
				printf("-s : mostra a solucao em ordem crescente\n");
				break;
			}
			case 'f':{
				int v1, v2;
				float peso;
				int numVertice, numArestas;
				arquivo = optarg;
				fp = fopen(optarg, "r");			

				fscanf(fp, "%d", &numVertice);	
				fscanf(fp, "%d", &numArestas);
				G = inicializar(numVertice + 1, numArestas + 1, 1);

				while(fscanf(fp, "%d", &v1)!= EOF){
					fscanf(fp, "%d", &v2);
					fscanf(fp, "%f", &peso);
					inserirAresta(G, v1, v2, 0, peso);
				}	
			
				arestaMenor(G, &vf);
				saida = kruskal(G, &vf, 2, custo);

				fclose(fp);
				printf("%d\n", custo[0]);
				
				fflg = 1;
				break;
			}
			case 'o':{	

				fs = fopen(optarg, "w");				
				fprintf(fs, "%d\n", custo[0]);
				fprintf(fs, "\n");

				if(s == 1){
					for(int i = 0; i < saida.indice; i++){
						fprintf(fs, "(%d,%d) ", saida.lista[i].v1, saida.lista[i].v2);					
					}
				}
				fclose(fs);

				oflg = 1;
				break;
			}
			case 's':{
				s = 1;
				arestaMenor(G, &vf);
				saida = kruskal(G, &vf, 2, custo);
				ordenaArestas(&saida);
				printf("\n");
				
				for(int i = 0; i < saida.indice; i++){
					printf("(%d,%d) ", saida.lista[i].v1, saida.lista[i].v2);					
				}
				printf("\n");
				
				mflg = 1;
				break;
			}
			case 'm':{		
					
				int x, i = 1, j = 1;
				int v1, v2;
				float peso;
				int numVertice, numArestas;

				fp = fopen(arquivo, "r");
				fscanf(fp, "%d", &x);
				numVertice = x;
				
				G = inicializar(numVertice + 1, 10, 1);

				while(fscanf(fp, "%d", &x) != EOF){
					if(x != 0){
						inserirAresta(G, i, j, 0, x);
					}

					if(j == (numVertice+1)){
						i++;
						j = 1;
					}
					j++;
				}
	
				arestaMenor(G, &vf);
				saida = kruskal(G, &vf, 2, custo);

				fclose(fp);
				printf("%d\n", custo[0]);

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
