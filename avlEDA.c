//ANNE CAROLINE - 470124
//LINK: https://youtu.be/ameYE8zfr4w

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define maximo 100000

struct no {
  int chave;
  int bal;
  struct no *esq,*dir;
};
typedef struct no NO;

void rotacaoDirInserir(NO **pt, int *h) {
  NO *ptv = NULL;
  NO *ptu = (*pt)->esq;
  if (ptu->bal == -1) {
    (*pt)->esq = ptu->dir;
    ptu->dir = *pt;
    (*pt)->bal = 0; 
    *pt = ptu;
   } else {
      ptv = ptu->dir;
      ptu->dir = ptv->esq;
      ptv->esq = ptu;
      (*pt)->esq = ptv->dir;
      ptv->dir = *pt;

      if (ptv->bal == -1) {
          (*pt)->bal = 1;
      } else {
          (*pt)->bal = 0;
      }

      if (ptv->bal == 1) {
        ptu->bal = -1;
      } else {
        ptu->bal = 0;
      }

      *pt = ptv;
   }
  

  (*pt)->bal = 0;
  (*h) = false;
}

void rotacaoEsqInserir(NO **pt, int *h) {
  NO *ptv = NULL;
  NO *ptu = (*pt)->dir;
  if(ptu->bal == 1) {
    (*pt)->dir = ptu->esq;
    ptu->esq = *pt;
    (*pt)->bal = 0;
    (*pt) = ptu;
   } else {
      ptv = ptu->esq;
      ptu->esq = ptv->dir;
      ptv->dir = ptu;
      (*pt)->dir = ptv->esq;
      ptv->esq = *pt;
       
      if (ptv->bal == 1) {
        (*pt)->bal = -1;
      } else {
        (*pt)->bal = 0;
      }

      if (ptv->bal == -1) {
        ptu->bal = 1;
      } else {
        ptu->bal = 0;
      }

    (*pt) = ptv;
  }
  (*pt)->bal =0;
  (*h) = false;
}

//alocar memoria para novo elemento
void iniciarNo(NO **pt, int chave) {
  NO* novo = (NO*)malloc(sizeof(NO));
  novo->esq = NULL;
  novo->dir = NULL;
  novo->bal = 0;
  novo->chave = chave;
  (*pt) = novo;
}

void inserir(int x, NO **pt, int *h) {
  if (*pt == NULL) {
    iniciarNo(pt, x);
    (*h) = true;
  } else {
    if (x == (*pt)->chave) {
      printf("\n\nElemento ja se encontra na arvore!\n");
      return;
    } else if (x < (*pt)->chave) {
      inserir(x, &(*pt)->esq, h);
      if((*h) == true) {
        switch((*pt)->bal) {
          case 1: 
            (*pt)->bal = 0; 
            (*h) = false;
            break;
          case 0: 
            (*pt)->bal = -1; 
            break;
          case -1: 
            rotacaoDirInserir(pt, h);
            break;
          default: printf("\n\nERRO!\n\n");
      }
    }
  } else {
    inserir(x, &(*pt)->dir, h);
    if((*h) == true) {
      switch((*pt)->bal){
        case -1: 
          (*pt)->bal = 0; 
          (*h)= false;
          break;
        case 0: 
          (*pt)->bal = 1; 
          break;
        case 1: 
          rotacaoEsqInserir(pt, h);
          break;
          default: printf("\n\nERRO!!\n\n");
      }
    }  
  }
 }
}

void rotacaoDirRemover(NO **pt, int *h){
  NO *ptu = (*pt)->esq;
  NO *ptv;
  if (ptu->bal <= 0) {
    (*pt)->esq = ptu->dir;
    ptu->dir =(*pt);
    (*pt)= ptu;
    if (ptu->bal == -1) {
        ptu->bal =(*pt)->dir->bal = 0;         
        (*h) = true;
    } else {
      ptu->bal = 1;
      (*pt)->dir->bal=-1;
      (*h) = false;
    }
  } else {
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    (*pt)->esq=ptv->dir;
    ptv->esq=ptu;
    ptv->dir=(*pt);
    (*pt)=ptv;

    switch (ptv->bal) {
      case -1:
        ptu->bal = 0; 
        (*pt)->dir->bal = 1;
        break;
      case 0: 
        ptu->bal = (*pt)->dir->bal = 0;
        break;
      case 1:
        ptu->bal = -1;
        (*pt)->dir->bal=0;
        break;
      default:
        printf("\nERRO!!");
        break;
    }

    (*pt)->bal = 0;
    (*h) = true;
  }
}

void rotacaoEsqRemover(NO **pt, int *h){
  NO *ptu = (*pt)->dir;
  NO *ptv;
  if (ptu->bal >= 0) {
    (*pt)->dir = ptu->esq;
    ptu->esq = (*pt);
    (*pt)= ptu;
    if (ptu->bal == 1) {
      ptu->bal=(*pt)->esq->bal = 0;
      (*h) = true;
    } else {
      ptu->bal = -1;
      (*pt)->esq->bal=1;
      (*h) = false;
    }
  } else {
      ptv = ptu->esq;
      ptu->esq = ptv->dir;
      (*pt)->dir=ptv->esq;
      ptv->dir=ptu;
      ptv->esq=(*pt);
      (*pt)=ptv;

      switch (ptv->bal) {
        case 1:
          ptu->bal = 0; 
          (*pt)->esq->bal = -1;
          break;
          case 0: 
            ptu->bal = (*pt)->esq->bal = 0;
            break;
          case -1:
            ptu->bal = 1; 
            (*pt)->esq->bal= 0;
            break;
          default:
            printf("\nERRO!!");
          break;
      }
      (*pt)->bal = 0;
      (*h) = true;
  }
}

void trocar(NO **x, NO **y){
  int aux = (*x)->chave;
  (*x)->chave = (*y)->chave;
  (*y)->chave = aux;
}

void balancear(NO **pt, char r, int *h)  {
  if ((*h) == true) {
    if (r == 'D') {
      switch((*pt)->bal){
          case 1: 
            (*pt)->bal = 0; 
            break;
          case 0: 
            (*pt)->bal = -1; 
            (*h) = false; break;
          case -1: 
            rotacaoDirRemover(&(*pt), h); 
            break;
          default: 
            printf("\nERRO!\n"); 
            break;
      }
    } else {
      switch ((*pt)->bal) {
        case -1:
          (*pt)->bal = 0; 
          break;
        case 0:
          (*pt)->bal = 1; 
          (*h) = false; 
          break;
       case 1: 
        rotacaoEsqRemover(&(*pt), h); 
        break;
       default: 
        printf("\nERRO!\n"); 
        break;
      }
   }
  }
}


void remover(int x, NO **pt, int *h) {
  NO** ptRaiz= pt;
  if ((*ptRaiz) == NULL) {
    printf("\nNo inexistente\n");
    return;
  } else {
    if (x < (*ptRaiz)->chave) {
      remover(x, &(*ptRaiz)->esq, h);
      balancear(&(*ptRaiz), 'E', h);
    } else {
      if (x > (*ptRaiz)->chave) {
        remover(x, &(*ptRaiz)->dir, h);
        balancear(&(*ptRaiz), 'D', h);
      } else {
        NO *aux = (*ptRaiz);
        if ((*ptRaiz)->esq == NULL) {
              (*ptRaiz) = (*ptRaiz)->dir;
              (*h) = true;
              free(aux);
        } else {
          if ((*ptRaiz)->dir == NULL) {
            (*ptRaiz) = (*ptRaiz)->esq;
            (*h) = true;
            free(aux);
          } else {
            NO* s = (*ptRaiz)->dir;
            if (s->esq == NULL) {
              (*ptRaiz)->dir = s->dir;
              s->esq = (*ptRaiz)->esq;
              s->bal = (*ptRaiz)->bal;
              (*ptRaiz) = s;
              *h = true;
              free(aux);
            } else {
              NO* paiS = s;

              while(s->esq != NULL) {
                paiS = s;
                s = s->esq; 
              }

              trocar(ptRaiz, &(paiS->esq));
              remover(x, &(*ptRaiz)->dir, h);
            }
            balancear(ptRaiz, 'D', h);
          }
        }
          
      }
    }
  }
}

int quantidadeNO(NO* pt) {
  if(pt == NULL){
     return 0;
  }
  return 1 + quantidadeNO(pt->esq) + quantidadeNO(pt->dir);
}


int altura(NO *pt) {
  if (!pt) {
   return 0;
  }

  int altEsq = altura(pt->esq);
  int altDir = altura(pt->dir);

  if (altEsq > altDir) {
    return altEsq + 1;
  } else {
    return altDir + 1;
  }
}

int verificaAVL(NO* pt){
  int verifica;
    
  if (pt != NULL) {
    int arvEsq = verificaAVL(pt->esq);
    int arvDir = verificaAVL(pt->dir);

    if(arvEsq == false || arvDir == false){
      return false;
    }

    int calcBal = (altura(pt->dir) - altura(pt->esq));
    if (calcBal >=-1 && calcBal <=1) {
      verifica = true;
    } else {
      verifica = false;
    }
        
    if (calcBal != pt->bal) {
      printf("Bal do no %d está errado, o bal eh: %d,mas o coreto seria o bal %d\n\n", pt->chave, pt->bal, calcBal);
      return  false;
    }
    return verifica;
  } 

  return true;
}

void infoAVL(NO* pt) {
  printf("\n");
  printf("Numero de nos: %d\n", quantidadeNO(pt));
  printf("Altura: %d\n", altura(pt));
  if (verificaAVL(pt) == true) {
    printf("EH AVL!\n");
  } else {
    printf("Nao eh AVL!\n");
  }
}

int preencher() {
  return (rand() % maximo) + 1;
}

NO* buscar(int x, NO* pt){
    while(pt != NULL && pt->chave != x){
        if(x > pt->chave){
            pt = pt->dir;
        }else{
            pt = pt->esq;
        }
    }

    return pt;
}

void desaloca(NO *pt){
  if(pt != NULL){
    desaloca(pt->dir);
    desaloca(pt->esq);
    free(pt);
  }
}

void infoArvore() {
  int contAvl = 0;
  int h = -2;
  int valores[1000];
  int verificarValor = 0;
  int contNO = 0;
  while(contAvl < 100) {
    NO* avl = NULL;
    contNO = 0;

    printf("\n******* Arvore numero %d *******\n\n", contAvl+1);
    while(contNO < 1000){
      h = -2;
      verificarValor = preencher();
      if (buscar(verificarValor, avl) == NULL) {
        valores[contNO] = verificarValor;
        inserir(verificarValor, &avl, &h);
        contNO++;
      }
    }

    infoAVL(avl);

    while(quantidadeNO(avl) != 900 && contNO > 0){
      h = -2;
      remover(valores[--contNO], &avl, &h);
    }

    infoAVL(avl);
    desaloca(avl);
    contAvl++;
  }
}


int main(int argc, char *argv[]){

  srand(time(NULL));
  infoArvore();

  return 0;
}