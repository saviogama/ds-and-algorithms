#include <getopt.h>
#include <unistd.h>
#include "heap.c"

int main(int argc, char *argv[]){

	int minima = 0;
	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0;
	heap h;

	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:m")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados na Heap\n");
				printf("-o : indica o arquivo de saida para os dados a serem adicionados na Heap\n");
				printf("-m : indica que a estrutura sera uma Heap minima\n");
				break;
			}
			case 'f':{
				int x;

				if(minima == 0){
					FILE *fp;
					fp = fopen(optarg, "r");
				
					inicializarHeap(&h);

					while(fscanf(fp, "%d", &x) != EOF){
						inserirHeap(&h, x);
					}
				
					imprimirHeap(&h);
					fclose(fp);
				}
				else{
					FILE *fp;
					fp = fopen(optarg, "r");
				
					inicializarHeap(&h);

					while(fscanf(fp, "%d", &x) != EOF){
						inserirHeap(&h, x);
					}

					heapSort(&h);
					imprimirHeap(&h);

					fclose(fp);
				}

				fflg = 1;
				break;
			}
			case 'o':{
				int i;

				FILE *fs;
				fs = fopen(optarg, "w");

				for(i = 1; i < h.indice; i++){	
					fprintf(fs, "%d	", h.heap[i].dado);
 				}
			
				fclose(fs);
				
				oflg = 1;
				break;
			}
			case 'm':{
				minima = 1;
				
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

