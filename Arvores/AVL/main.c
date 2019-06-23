#include <unistd.h>
#include <getopt.h>
#include "avl.c"

int main(int argc, char *argv[]){

	int c;
	int hflg = 0, fflg = 0, oflg = 0, mflg = 0, Mflg = 0, aflg = 0, sflg = 0;
	
	avl t;
	array saida;
	iniciar(&t);
	iniciarArray(&saida);

	while((c = getopt(argc, argv, "hf:o:mMa:s:")) != -1){
		
		switch(c){
			case 'h':{
				hflg = 1;
				printf("-h : mostra os comandos de ajuda\n");
				printf("-f : indica o arquivo que contem os dados a serem adicionados na AVL\n");
				printf("-o : indica o arquivo de saida para os dados a serem adicionados na AVL\n");
				printf("-m : imprime o menor elemento da AVL\n");
				printf("-M : imprime o maior elemento da AVL\n");
				printf("-a : imprime o antecessor do elemento na AVL\n");
				printf("-s : imprime o sucessor do elemento na AVL\n");
				break;
			}
			case 'f':{
				int x;

				FILE *fp;
				fp = fopen(optarg, "r");			

				while(fscanf(fp, "%d", &x) != EOF){
					inserir(&t, x);
				}
				printf("\n");				
				PercursoPreOrdem(t.raiz);
				printf("\n\n");
				arraySaida(t.raiz, &saida);
				fclose(fp);

				fflg = 1;
				break;
			}
			case 'o':{
				FILE *fs;

				fs = fopen(optarg, "w");

				for(int i =0; i<saida.indice; i++){
					fprintf(fs, "%d ", saida.lista[i].num);
				}

				fclose(fs);
				oflg = 1;
				break;
			}
			case 'm':{

				Menor(t.raiz);

				mflg = 1;
				break;
			}
			case 'M':{
				
				Maior(t.raiz);			
				Mflg = 1;
				break;
			}
			case 'a':{
				int x;

				x = atoi(optarg);

				antecessor(&t, x);
				
				mflg = 1;
				break;
			}
			case 's':{
				int x;

				x = atoi(optarg);
				sucessor(&t, x);				

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

