#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*INTEGRANTES: BRUNO FERNANDO, VICTOR HUGO DE SOUSA LIMA */

struct aluno {
    char cpf[20];
    char nome[50];
    struct aluno *proximo;
};
struct historico {
    char cpf[20];
    char codigo_disciplina[10];
	char situacao_disciplina[5];	
    struct historico *proximo;
};
struct disciplinas{
	char codigo_disciplina[10];
	char nome_disciplina[50];
	struct disciplinas *proximo;
};

typedef struct aluno aln;
typedef struct historico hst;
typedef struct disciplinas dcp;
void cadastraHistorico(hst **lst, char *cpf, dcp *codigo);

//FUNÇÕES RELACIONADAS A ALUNOS

void carregaAlunos(aln **lst){
    aln *alnArq;
    FILE *ptArq;
    ptArq = fopen("Alunos.txt", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaAlunos).\n");
    }else{
        char linha[100];
        while(fgets(linha, 100, ptArq) != NULL){

            char *token;
            char valores[2][50];
            alnArq = (aln*)malloc(sizeof(aln));
			
			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ",");
            int i=0, j=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ",");
                i++;
            }
            strcpy(alnArq->cpf, valores[0]);
            strcpy(alnArq->nome, valores[1]);

            if(*lst == NULL){
                alnArq->proximo = NULL;
                *lst = alnArq;

            }else{
                aln *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            alnArq->proximo = NULL;
            aux->proximo = alnArq;
            }
        }
        fclose(ptArq);

    }

}

void salvaAluno(aln **lst){
    aln *alnArq;
    alnArq = (aln*)malloc(sizeof(aln));

    FILE *ptArq;
    ptArq = fopen("Alunos.txt", "w");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUVO (salvaAluno).\n");
    }else{
        aln *pt;
        pt = *lst;

        while(pt != NULL){

           fprintf(ptArq,"%s,%s\n", pt->cpf,pt->nome);
            pt = pt->proximo;
        }
    }
    fclose(ptArq);
}

void relatorioAluno(aln *lst){
    aln *alunos;
    alunos = lst;

    printf("----RELATORIO DE ALUNOS-----\n\n");
    while(alunos!= NULL){
        printf("CPF: %s\nNOME ALUNO %s\n",
               alunos->cpf,alunos->nome);
        alunos = alunos->proximo;
    }
    printf("---------------------------------\n\n");

}

int verificaAlunos(aln *lst, aln *novo){

    aln *p;
    p = lst;

    while(p != NULL){

        if(strcmp(p->cpf,novo->cpf) == 0){
            return 1;
        }
        p = p->proximo;
    }
    return -1;

}

void cadastraAluno(aln **lst){
    aln *novo;
    novo = (aln *)malloc(sizeof(aln));
    fflush(stdin);
    printf("DIGITE O CPF DO ALUNO\n");
    scanf("%[^\n]s", &novo->cpf);
    
    fflush(stdin);
    printf("DIGITE O NOME DO ALUNO\n");
    scanf("%[^\n]s", &novo->nome);
    novo->proximo = NULL;

    if(*lst == NULL){
        *lst = novo;
	}
    else{
        int verificaAln = verificaAlunos(*lst, novo);
        if(verificaAln == 1){
            printf("CPF INFORMADO JA EXISTE..\n\n");
            return;
        }else{
            aln *pt, *ptAux;
            pt = *lst;
            ptAux = NULL;
            
            while((pt!= NULL) && (strcmp(pt->cpf,novo->cpf) == -1 )){
                    ptAux = pt;
                    pt = pt->proximo;
            }
            if(pt== NULL){
                novo->proximo = NULL;
                ptAux->proximo = novo;
            }else if(ptAux == NULL){
                *lst = novo;
                novo->proximo = pt;
            }else{
                ptAux->proximo = novo;
                novo->proximo = pt;
            }
        }
    }
    printf("ALUNO CADASTRADO COM SUCESSO.\n\n");
}

void editaAluno(aln **lst){

    if(*lst == NULL){
        printf("NÃO EXISTEM ALUNOS A SEREM EDITADOS.\n\n");
        return;
    }

    char cpf[30];
    fflush(stdin);
    printf("POR FAVOR INSIRA O CPF DO ALUNO A SER EDITADO.\n");
    scanf("%[^\n]s", &cpf);

    aln *pt;
    pt = *lst;
    while(pt != NULL && (strcmp(pt->cpf,cpf) != 0) ){
        pt = pt->proximo;
    }
    if(pt == NULL){
        printf("O VALOR DIGITADO NAO CONSTA NOS ALUNOS.\n\n");
        return;
    }else{
        printf("----EDICAO DE ALUNOS----\n\n");
            fflush(stdin);
            printf("INFORME O NOVO NOME PARA O ALUNO.\n");
            scanf("%[^\n]s", &pt->nome);
            printf("NOME ALTERADO COM SUCESSO!\n");
        
        }
    }

void removeAluno(aln **lst){

    if(*lst == NULL){
        printf("NAO EXISTEM ALUNOS A SEREM REMOVIDOS.\n\n");
        return;
    }
    char cpf[20];
    fflush(stdin);
    printf("----REMOCAO DE ALUNOS----\n\n");
    printf("INFORME O CPF DO ALUNO A SER REMOVIDO\n");
    scanf("%[^\n]s", &cpf);
	aln *pt, *aux;		
    pt = *lst;
	aux = NULL;

    while(pt!= NULL && (strcmp(pt->cpf, cpf)) != 0){
        aux = pt;
        pt=pt->proximo;
    }
    if(pt == NULL){
        printf("ALUNO NÃO ENCOTRADO.\n\n");
        return ;
    }
    if(aux == NULL){
        *lst = pt->proximo;
        free(pt);
    }else{
        aux->proximo = pt->proximo;
        free(pt);
    }

    printf("ALUNO REMOVIDO COM SUCESSO.\n\n");
}

//FUNÇÕES RELACIONADAS A HISTORICO

void relatorioHistorico(hst *lst){
	char cpf[20];
	hst *historicos;
	historicos = lst;
	
	fflush(stdin);
	printf("INSIRA O CPF DO ALUNO QUE DESEJA CONSULTAR HISTORICO:\n");
	scanf("%[^\n]s", &cpf);
	
	while(historicos!= NULL){
		if(strcmp(historicos->cpf, cpf) == 0){
			printf("CPF: %s Disciplina: %s Situacao: %s\n", historicos->cpf, historicos->codigo_disciplina, historicos->situacao_disciplina);
		}
		historicos = historicos->proximo;
	}
	printf("---------------------------------\n\n");
}

void carregaHistorico(hst **lst){
	hst *hstArq;
    FILE *ptArq;
    ptArq = fopen("Historico.txt", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaHistorico).\n");
    }else{
        char linha[100];
        while(fgets(linha, 100, ptArq) != NULL){

            char *token;
            char valores[3][100];
            hstArq = (hst*)malloc(sizeof(hst));

			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ",");
            int i=0, j=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ",");
                i++;
            }
            strcpy(hstArq->cpf, valores[0]);
            strcpy(hstArq->codigo_disciplina, valores[1]);
            sprintf(hstArq->situacao_disciplina, "%s", valores[2]);


            if(*lst == NULL){
                hstArq->proximo = NULL;
                *lst = hstArq;

            }else{
                hst *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            hstArq->proximo = NULL;
            aux->proximo = hstArq;
            }
        }
        fclose(ptArq);

    }


}

void salvaHistorico(hst **lst){
    
    FILE *ptArq;
    ptArq = fopen("Historico.txt", "w");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUVO (salvaHistorico).\n");
    }else{
        hst *pt;
        pt = *lst;

        while(pt != NULL){
            fprintf(ptArq, "%s,%s,%s,\n", pt->cpf,pt->codigo_disciplina,pt->situacao_disciplina);
            pt = pt->proximo;
        }
    }
    fclose(ptArq);
}

int verificaHistoricos(aln *lst, char *cpf){

    aln *p;
    p = lst;

    while(p != NULL){

        if(strcmp(p->cpf, cpf) == 0){
            return 1;
        }
        p = p->proximo;
    }
    return -1;

}

int verificaCpfHistorico(hst *lst, char *cpf){

    hst *p;
    p = lst;

    while(p != NULL){

        if(strcmp(p->cpf, cpf) == 0){
            return 1;
        }
        p = p->proximo;
    }
    return -1;

}

void cadastraHistorico(hst **lst, char *cpf, dcp *codigo){
	hst *novo, *pt, *ptAux;
	ptAux = NULL;
	pt = *lst;
	
	novo = (hst *)malloc(sizeof(hst));
	sprintf(novo->cpf, "%s", cpf);
    sprintf(novo->codigo_disciplina, "%s", codigo->codigo_disciplina);
    sprintf(novo->situacao_disciplina, "%s", "FAC");
    novo->proximo = NULL;
        
    if(*lst == NULL){
    	*lst = novo;
	} else {
		while(pt != NULL){
			ptAux = pt;
			pt = pt->proximo;
		}
		if(pt == NULL){
			novo->proximo = NULL;
			ptAux->proximo = novo;
		} else {
			ptAux->proximo = novo;
			novo->proximo = pt;
		}
		
	}
	printf("HISTORICO CADASTRADO COM SUCESSO!\n");
}

void editaHistorico(hst **lst){
	char cpf[20], codigo[20];
	int ctrl = 0;
	
	if(*lst == NULL){
        printf("NÃO EXISTEM HISTORICOS A SEREM EDITADOS.\n\n");
        return;
    }
    
    fflush(stdin);
    printf("POR FAVOR INSIRA O CPF E O CODIGO DA DISCIPLINA QUE DESEJA ALTERAR A SITUACAO\n");
    printf("CPF: \n");
    scanf("%[^\n]s", &cpf);
    printf("CODIGO: \n");
    fflush(stdin);
    scanf("%[^\n]s", &codigo);

    hst *pt;
    pt = *lst;
    while(pt != NULL){
    	if((strcmp(pt->codigo_disciplina,codigo) == 0) && (strcmp(pt->cpf,cpf) == 0)){
    		int op;
        	fflush(stdin);
        	printf("----EDICAO DE HISTORICO----\n\n");
        	printf("INFORME A NOVA SITUACAO DO HISTORICO.\n");
        	printf("1 - CURSANDO.\n2 - APROVADO.\n3 - REPROVADO POR NOTA.\n4 - REPROVADO POR FALTA.\n");
        	printf("5 - FALTA CURSAR.\n");
            	scanf("%d", &op);
        	if(op == 1){
	        	strcpy(pt->situacao_disciplina, "CUR");
			}
			else if(op == 2){
				strcpy(pt->situacao_disciplina, "APR");
			}
			else if(op == 3){
				strcpy(pt->situacao_disciplina, "RPN");
			}
			else if(op == 4){
				strcpy(pt->situacao_disciplina, "RPF");
			}
			else if(op == 5){
				strcpy(pt->situacao_disciplina, "FAC");
			}
			
			ctrl = 1;
			printf("HISTORICO ALTERADO COM SUCESSO!\n\n");
		}
        pt = pt->proximo;
    }
    if(ctrl != 1){
    	printf("VALOR DIGITADO NAO CONSTA NOS HISTORICOS\n\n");
    	return;
	}
}

void removeHistorico(hst **lst){
	int ctrl = 0;
    if(*lst == NULL){
        printf("NAO EXISTEM HISTORICOS A SEREM REMOVIDOS.\n\n");
        return;
    }
    char cpf[30], codigo[15];
    fflush(stdin);
    printf("----REMOCAO DE HISTORICO----\n\n");
    printf("INFORME O CPF DO ALUNO:\n");
    scanf("%[^\n]s", &cpf);
    fflush(stdin);
    printf("INFORME O CODIGO DA DISCIPLINA:\n");
    scanf("%[^\n]s", &codigo);


    hst *pt = *lst, *aux=NULL;
    while(pt!= NULL){
    	if((strcmp(pt->codigo_disciplina,codigo) == 0) && (strcmp(pt->cpf,cpf) == 0)){	
    		if(aux == NULL){
        		*lst = pt->proximo;
        		free(pt);
    		}else{
        		aux->proximo = pt->proximo;
        		free(pt);
    		}
    		ctrl = 1;
 		}
        aux = pt;
        pt=pt->proximo;
    }
    if(ctrl != 1){
    	printf("ERRO AO REMOVER HISTORICO!\n\n");
    	return;
	} else {
		printf("HISTORICO REMOVIDO COM SUCESSO!\n\n");
	}
}

void carregaDisciplinas(dcp **lst){
	dcp *dcpArq;
    FILE *ptArq;
    ptArq = fopen("Disciplinas.txt", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO. (carregaDisciplinas)\n");
    }else{
        char linha[100];
        while(fgets(linha, 100, ptArq) != NULL){

            char *token;
            char valores[2][100];
            dcpArq = (dcp*)malloc(sizeof(dcp));

            token = strtok(linha, ",");
            int i=0, j=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ",");
                i++;
            }
            strcpy(dcpArq->codigo_disciplina, valores[0]);
            strcpy(dcpArq->nome_disciplina, valores[1]);

            if(*lst == NULL){
                dcpArq->proximo = NULL;
                *lst = dcpArq;

            }else{
                dcp *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            dcpArq->proximo = NULL;
            aux->proximo = dcpArq;
            }
        }
        fclose(ptArq);

    }
}

void relatorioOferta(hst *lst){
	int valores[10], i, total;
	for(i=0; i<10; i++){
		valores[i]=0;
	}
	total = 0;
	char fac[15];
	sprintf(fac, "%s", "FAC");
	hst *pt;
	pt = lst;
	
	while(pt != NULL){
		if(strcmp(pt->situacao_disciplina,fac) == 0){
			if(strcmp(pt->codigo_disciplina,"ALGI") == 0){
				valores[0] = valores [0] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"ALGII") == 0){
				valores[1] = valores [1] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"CALI") == 0){
				valores[2] = valores [2] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"ED") == 0){
				valores[3] = valores [3] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"ARQ") == 0){
				valores[4] = valores [4] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"ISD") == 0){
				valores[5] = valores [5] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"PRB") == 0){
				valores[6] = valores [6] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"BDI") == 0){
				valores[7] = valores [7] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"ENG") == 0){
				valores[8] = valores [8] + 1;
			}
			else if(strcmp(pt->codigo_disciplina,"COM") == 0){
				valores[9] = valores [9] + 1;
			}			
		}
		pt = pt->proximo;
	}
	
	for(i=0; i<10; i++){
		total = total + valores[i];
	}
	for(i=0; i<10; i++){
		valores[i] = (valores[i]*100)/total;	
	}
	printf("---PORCENTAGEM DE MATERIAS QUE FALTAM SER CURSADAS---\n\n");
	printf("Algoritmos I: %d%%\n", valores[0]);
	printf("Algoritmos II: %d%%\n", valores[1]);
	printf("Calculo I: %d%%\n", valores[2]);
	printf("Estrutura de dados: %d%%\n", valores[3]);
	printf("Arquitetura de computadores: %d%%\n", valores[4]);
	printf("Introducao a sistemas digitais: %d%%\n", valores[5]);
	printf("Probabilidade e Estatistica: %d%%\n", valores[6]);
	printf("Banco de Dados I: %d%%\n", valores[7]);
	printf("Engenharia de Software: %d%%\n", valores[8]);
	printf("Computacao e Sociedade: %d%%\n", valores[9]);
	printf("TOTAL DE MATERIAS PENDENTES: %d\n\n", total);
	printf("-----------------------------------------------------\n\n");
}

int main (void){
    int menuOp=-1;
    aln *listaA = NULL;
    char cpf[20];
    hst *listaH = NULL;
    dcp *listaD = NULL;
    carregaAlunos(&listaA);
    carregaHistorico(&listaH);
    carregaDisciplinas(&listaD);
    while(menuOp != 5){
        printf("---SELECIONE A OPCAO DESEJADA---\n\n");
        printf("1 - Cadastrar \n");
        printf("2 - Editar \n");
        printf("3 - Remover \n");
        printf("4 - Relatorios \n");
        printf("5 - Sair \n");
        scanf("%d", &menuOp);
        int op=-1;
        if(menuOp == 1){
        	printf("---CADASTRAR---\n");
            printf("1 - Aluno \n");
            printf("2 - Historico \n");
            printf("3 - Cancelar \n");
            scanf("%d", &op);
            if(op == 1){
                cadastraAluno(&listaA);
            }else if(op == 2){
            	dcp *aux = listaD;
            	
                fflush(stdin);
				printf("DIGITE O CPF DO ALUNO QUE DESEJA CADASTRAR HISTORICO:\n");
				scanf("%[^\n]s", &cpf);
				
				int verificaH= 0;
				int verifica = verificaHistoricos(listaA, cpf);
				
				if(verifica != 1){
					printf("ALUNO INEXISTENTE!\n\n");
				} else {
					verificaH = verificaCpfHistorico(listaH, cpf);
					
					if(verificaH == 1){
						printf("HISTORICO CADASTRADO COM SUCESSO!\n\n");
						continue;
					} else {
							while(listaD != NULL){
								cadastraHistorico(&listaH, cpf, listaD);
								listaD = listaD->proximo;
							}
							listaD = aux;
					} 
					
				}
            } else if(op == 3){
                continue;
            }else{
                printf("OPCAO INVALIDA! \n");
            }

        }else if(menuOp == 2){
        	printf("---EDITAR---\n\n");
            printf("1 - Aluno \n");
            printf("2 - Historico \n");
            printf("3 - Cancelar \n");
            scanf("%d", &op);
            if(op == 1){
                editaAluno(&listaA);
            }else if(op == 2){
               editaHistorico(&listaH);
            }else if(op == 3){
                continue;

            }else{
                printf("OPCAO INVALIDA! \n");
            }

        }else if(menuOp == 3){
        	printf("---REMOVER---\n\n");
            printf("1 - Aluno \n");
            printf("2 - Historico \n");
            printf("3 - CANCELAR \n");
            scanf("%d", &op);
            if(op == 1){
                removeAluno(&listaA);
            }else if(op == 2){
                removeHistorico(&listaH);
            }else if(op ==3){
               continue;
            }else{
                printf("OPCAO INVALIDA! \n");
            }

        }else if(menuOp == 4){
        	printf("---RELATORIOS---\n\n");
            printf("1 - Aluno \n");
            printf("2 - Historico Escolar \n");
            printf("3 - Oferta Disciplinas\n");
            printf("4 - CANCELAR \n");
            scanf("%d", &op);
            if(op == 1){
                relatorioAluno(listaA);
            }else if(op == 2){
                relatorioHistorico(listaH);
            }else if(op == 3){
                relatorioOferta(listaH);
            }else if(op == 4){
            	continue;
			}
			else{
                printf("OPCAO INVALIDA! \n");
            }

        }else if(menuOp == 5){
            salvaAluno(&listaA);
            salvaHistorico(&listaH);
        }else{
            printf("OPCAO INVALIDA! \n");
            continue;
        }
    }

    return 0;
}
