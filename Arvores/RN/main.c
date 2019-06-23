#include <unistd.h>
#include <getopt.h>
#include "rn.c"

int main(int argc, char *argv[]){

	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0, Mflg = 0, aflg = 0, sflg = 0;
	FILE *fp, *fs;
	rn *raiz;

	printf("Digite -h para comandos de ajuda\n");
	while((c = getopt(argc, argv, "hf:o:mMa:s:")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados na Rubro-Negra\n");
				printf("-o : indica o arquivo de saida para os dados a serem adicionados na Rubro-Negra\n");
				printf("-m : imprime o menor elemento da Rubro-Negra\n");
				printf("-M : imprime o maior elemento da Rubro-Negra\n");
				printf("-a : imprime o antecessor do elemento na Rubro-Negra\n");
				printf("-s : imprime o sucessor do elemento na Rubro-Negra\n");
				break;
			}
			case 'f':{
				int x, i;

				FILE *fp;
				fp = fopen(optarg, "r");
				
				raiz = inicializar();

				while(fscanf(fp, "%d", &x) != EOF){
					i = inserirElemento(raiz, x);
				}
				
				percursoPreOrdem(raiz);

				printf("\n");
				fclose(fp);

				fflg = 1;
				break;
			}
			case 'o':{
				int x;
				
				fs = fopen(optarg, "w");
				

				fclose(fs);
				oflg = 1;
				break;
			}
			case 'm':{
				int y;
				printf("\n");
				y = buscarMenor(raiz);
				printf("%d\n", y);

				mflg = 1;
				break;
			}
			case 'M':{
				int y;
				printf("\n");
				y = buscarMaior(raiz);
				printf("%d\n", y);
			
				Mflg = 1;
				break;
			}
			case 'a':{
				int x, y;
				x = atoi(optarg);
				y = predecessor(raiz, x);
				printf("\n");
				printf("%d\n", y);

				mflg = 1;
				break;
			}
			case 's':{
				int x, y;
				x = atoi(optarg);
				y = sucessor(raiz, x);
				printf("\n");
				printf("%d\n", y);

				mflg = 1;
				break;
			}
			case '?':{
				if(optopt == 'f' || optopt == 'o')
					fprintf(stderr, "Exemplo: -%c arquivo-entrada.txt\n", optopt);
				if(optopt == 'a' || optopt == 's')
					fprintf(stderr, "Exemplo: -%c 10\n", optopt);
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

