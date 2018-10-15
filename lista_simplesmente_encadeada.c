#include <stdio.h>
#include <stdlib.h>

//O comando struct define um modelo de objeto em C.
//É similar a uma classe, em outras linguagens.
//Um struct define as regras de um objeto.
//Usamos para agruparmos certos padrões

//Todo objeto do tipo Lista, nesse caso, deve possuir um valor e um ponteiro
//para o seu vizinho

/* IMPORTANTE */
//Cada caracteristica de um objeto (como o valor, ou o endereço do vizinho) é
//chamada de atributo

//Aqui estamos definindo o modelo de objeto Lista
struct Lista {
  int valor; //O atributo valor está ligado a cada objeto Lista que for criado

  //Se estivermos acessando o atributo valor a partir do endereço do nosso objeto
  //"Lista" devemos usar Lista.valor

  //Para casos de ponteiros, acessamos atributos usando "->"
  //Dessa forma: ponteiro -> valor


  struct Lista *proximo; //Aqui temos como atributo, um ponteiro direcionado ao
  //proximo elemento da lista.

};

typedef struct Lista Lista; //Aqui estamos definindo um apelido para a struct Lista
// A partir de agora, acessamos esse modelo usando apenas o apelido Lista.
//Ex: Lista objeto;
//De outra forma, se não estivessemos dando um apelido, fariamos referencia a
//essa struct usando "struct Lista"
//Ex: struct Lista objeto;


// Essa funcao inclui um valor usando a técnica de passar o endereço do ponteiro
// Conhecida como ponteiro de ponteiro

// O ponteiro de ponteiro aponta para o local na memória em a variavel se encontra
// e não para o local em que o ponteiro está armazenado

//Chamamos a técnica de acessar esse local na memória de dereferenciando ponteiros

//Nesse caso, o paramentro **primeiro, recebe um ponteiro como argumento, mas imediatamente
//acessa o local na memoria para aonde esse ponteiro está apontando

//Em suma, dentro da funcao, primeiro faz referencia à variavel original.
Lista *inserirValorPP(Lista **primeiro, int valor)
//Essa funcao irá retornar um ponteiro do tipo Lista, que aponta ao objeto que será
//inserido no fim da lista
// Recebe um ponteiro de ponteiro do tipo lista, que representa o primeiro Elemento
// E recebe o valor que será inserido na lista
{
  Lista *novo, *auxiliar; //Aqui definimos dois ponteiros do tipo lista
  //novo irá apontar para o objeto que será criado, tendo como valor o valor
  //passado como argumento

  //Auxiliar irá iterar sobre a lista, até encontrar o último valor, caso a Lista
  //já possua objetos

  novo = (Lista *)malloc(sizeof(Lista)); //Aqui estamos definindo que o ponteiro
  //"novo" do tipo Lista, está apontando para um espaço na memória criado para
  //armazenar um objeto com o espaço necessário para um objeto Lista
  //O processo de alocação da memória necessária para um objeto é feito pela
  //funcão "malloc"

  //Setando os valores do atributos do objeto que será inserido no fim da lista
  novo -> valor = valor;
  novo -> proximo = NULL;

  //em "*ponteiro" estamos pegando o ponteiro do espaço na memoria que armazena o primeiro
  //objeto da lista

  //Caso não tenha um elemento no inicio da lista, logo, ela está vazia.
  //nosso novo elemento será o primeiro :)
  if (*primeiro == NULL) {
	    *primeiro = novo;
	    return novo;
  }

  //Não precisamos de um else, porque temos um return dentro do ultimo if

  //A variavel auxiliar será usada para iterar pela lista até achar o ultimo elemento
  auxiliar = *primeiro;
  while (auxiliar -> proximo != NULL){
    auxiliar = auxiliar -> proximo;
  }
  // Uma vez que o proximo elemento seja NULL, o nosso elemento atual é o ultimo da Lista

  auxiliar -> proximo = novo; //aqui colocamos o proximo elemento como o novo,
  //agora ele é o ultimo da lista :(
  return novo;
}


// Inserção do valor sem utilizar ponteiro de ponteiro
Lista *inserirValor(Lista *primeiro, int valor)
{
    Lista *novo, *auxiliar;
    novo = (Lista *)malloc(sizeof(Lista));
    novo -> valor = valor;
    novo -> proximo = NULL;

    //Nesse caso, já estamos usando o ponteiro, por isso, acessamos diretamente
    //a variavel primeiro, sem o "*"
    if (primeiro == NULL) {
      primeiro = novo
  		return novo;
    }
    auxiliar = primeiro; // aux recebe o endereço da cabeça da lista (primeiro)
    while (primeiro -> proximo != NULL){
      	auxiliar = auxiliar -> proximo;
    }
	auxiliar -> proximo = novo;
	return novo;
}


// Essa funcao irá apagar da memória todos os elementos da lista

void apagarLista(Lista *primeiro)
{
	Lista *auxiliar; //Esse objeto salva o proximo elemento da lista, tendo como
  //base o atual
  // Salvamos a referencia ao proximo, porque a cada loop estamos apagando o objeto atual
  //(Não apagamos de fato a variavel, mas limpamos o espaço na memória que contém o seu valor)
	while (primeiro != NULL)
	{
	   auxiliar = primeiro -> proximo;
	   free(primeiro);
	   primeiro = auxiliar;
    }
}

//Essa função imprime o valor de todos elementos, na ordem em que foram inseridos
void mostrarTodos(Lista *primeiro)
{
	while (primeiro != NULL)
	{
     printf("%d\n", primeiro -> valor);
	   primeiro = primeiro -> proximo;
    }
}

//Essa função encontra um valor na lista, e retorna o ponteiro a esse valor
Lista *encontrarValor(Lista *primeiro, int valor)
{

	if (primeiro == NULL){ //Caso a lista esteja vazia, retornamos null;
    return NULL;
  }
	while (primeiro != NULL){

	   if (primeiro -> valor == valor) {
          return primeiro;
     }
     primeiro = primeiro -> proximo
    }
	return NULL;
}

//Essa funcao atualiza o valor de um elemento na Lista
//a partir do valor antigo
void atualizarLista(Lista *primeiro, int valorAntigo, int valorNovo)
{
	Lista *ponteiroValorAntigo = encontrarValor(primeiro, valorAntigo); //Aqui usamos a função
  // encontrarValor() para sabermos se o valor existe na lista
	if (ponteiroValorAntigo == NULL) {
		printf("Valor %d não existe!\n", valorAntigo);
		return NULL;
	}
  //Caso o elemento exista, a função encontrarValor já nos retornou o seu ponteiro,
  //só nos atualizar o seu valor
	ponteiroValorAntigo -> valor = valorNovo;
}

//Essa função exclui um elemento da lista, com base na primeira ocorrencia do
//valor passado como paramentro
Lista *apagarValor(Lista *primeiro, int valor)
{
	Lista *anterior = NULL //Essa variavel ira armazena o elemento verificado anteriormente
  // e usada para caso o elemento atual tenha seu valor igual ao solicitado para exclusao
  // nesse caso, setamos o proximo elemento do elemento anterior como sendo o proximo do atual
  //Dessa forma, estamos "pulando o atual" na nossa lista

  Lista *atual = primeiro;
	if (primeiro == NULL || (encontrarValor(primeiro, valor) == NULL)) return NULL;
  // lista vazia ou numero não está presente na lista

	while (atual != NULL){
		if (atual-> valor == valor)
		{
			if (atual == primeiro) //se estivermos no primeiro elemento, ele ainda não
      //terá um anterior então damos retorno aqui mesmo
			{
				primeiro = atual -> proximo; //o segundo elemento da lista passa a ser o primeiro
				free(atual); //o elemento atual tem seu valor limpado da memoria
				return primeiro;
			}
			anterior -> proximo = atual -> proximo; //O uso da variavel anterior, como ja explicado
      //pulamos o elemento atual, e limpamos o seu valor na memoria
			free(atual);
			return primeiro;
	  } //caso nao encontremos o valor, vamos para o proximo
    //no proximo loop, o anterior sera o atual de agora
    //o atual sera o proximo
		anterior = atual;
		atual = atual -> proximo;
  }
}

int main()
{
    Lista *inciaLista = NULL, *primeiro=NULL;
    int operacao = 1, valor, valorAntigo, valorNovo;
    while (operacao != 0) {
		    printf("\n1 - Insere\n2 - Procura\n3 - Lista Todos\n4 - Limpa Lista\n5 - Atualiza\n6 - Exclui Elemento\n0 - Sai: ");
		    scanf("%d",&operacao);
		    if (operacao == 1) { //inserir valor na nlista
			       printf("Valor: ");
			       scanf("%d", &valorl);
			       inciaLista = inserValor(primeiro, valor);
			       if (primeiro == NULL){
               primeiro = inciaLista;
             }
			       continue;
		     }
		     if (operacao == 2)	{
			        printf("Valor: ");
			        scanf("%d",&vl);
			        if (encontrarValor(primeiro, valor) != NULL){
                  printf("Valor presente na lista!\n");
              }
			        else { printf("Valor não encontrado na lista!\n"); }
			        continue;
	         }
		     if (operacao == 3) {
		         mostrarTodos(primeiro);
		         continue;
		     }
		     if (operacao == 4) {
			        apagarLista(primeiro);
			        primeiro = NULL; // não esquecer de setar a lista para vazia
			        continue;
		          }
		     if (operacao == 5) {
			        printf("Valor antigo: ");
              scanf("%d",&valorAntigo);
			        printf("Valor   novo: ");
              scanf("%d",&valorNovo);
			        atualizarLista(primeiro, valorAntigo, valorNovo);
			        continue;
              }
    		 if (operacao == 6) {
              printf("Valor a ser excluído: ");
              scanf("%d",l&valor);
              primeiro = apagarValor(primeiro, valpr);
       		    continue;
           }
         }
    return 0;
}
