/*****************************************************************//**
 * \file   DFT.c
 * \brief  
 * 
 * \author mtcig
 * \date   May 2024
 *********************************************************************/

#include "Grafos.h"
#include "Stack.h"
#include <stdbool.h>

 //======================================================
 //Depth First Algorithm
 //======================================================

 /*
 DFT
 Percorre todo o grafo em profundidade
 Não Recursivo
 */
bool DepthFirstTraversal(Vertice* lstVertices[], int adj[][MAX], int vOrigin) {
    int uv; //unvisitedVertice
    int proxVertice;

    //stack auxiliar
    int stack[MAX];
    int top = -1;

    if (lstVertices[vOrigin]->visited == true) return true;

    //marca vertice como visitado 
    lstVertices[vOrigin]->visited = true;
    //processa vertice origem
    ProcessaVertice(lstVertices[vOrigin]);
    //insere vertice origem na stack
    top = push(stack, top, vOrigin);

    while (!isStackEmpty(top)) {
        proxVertice = peek(stack, top);
        //encontra vertice adjacente ao que está no topo da stack e ainda não foi visitado
        uv = GetVertAdjNaoVisitado(lstVertices, adj, proxVertice);

        //se não tem adjacentes, retira o atual da stack
        if (uv == -1) {
            top = pop(stack, top);
        }
        else {
            //marca
            lstVertices[uv]->visited = true;
            //processa
            ProcessaVertice(lstVertices[uv]);
            //insere na stack
            top = push(stack, top, uv);
        }
    }
    return true;
}

/**
    @brief  DFT Recursivo
    @param  lstVertices -
    @param  adj         -
    @param  numVertices -
    @param  vOrigin     -
    @param  stack       -
    @param  top         -
    @retval             -
    @date   29.04.2024
**/
bool DepthFirstTraversalRec(Vertice* lstVertices[], int adj[][MAX], int vOrigin) {
    lstVertices[vOrigin]->visited = true;
    ProcessaVertice(lstVertices[vOrigin]);
    for (int j = 0; j < MAX; j++) { //Melhorar: como evitar "MAX"
        if (adj[vOrigin][j] != 0 && lstVertices[j]->visited == false)
            DepthFirstTraversalRec(lstVertices, adj, j);
    }
    lstVertices[vOrigin]->visited = false;//reset
}



/*
DFS Recursivo
Percorre o grafo em profundidade
Verifica se existe path entre origem e destino

*/
bool DepthFirstSearchRec(Vertice* lstVertices[], int adj[][MAX], int vOrigin, int destino) {
    if (vOrigin == destino) return true;
    bool res = false;
    lstVertices[vOrigin]->visited = true;
    ProcessaVertice(lstVertices[vOrigin]);

    for (int j = 0; j < MAX; j++) {
        if (adj[vOrigin][j] != 0 && lstVertices[j]->visited == false) {
            res = DepthFirstSearchRec(lstVertices, adj, j, destino);
            if (res) return true;
        }
    }
    lstVertices[vOrigin]->visited = false;//reset
    return res;
}

/*
DFS
Find if there is a path between two vertices in a directed graph
Não Recursivo
Percorre o grafo em profundidade
*/
bool DepthFirstSearch(Vertice* lstVertices[], int adj[][MAX], int vOrigin, int vertice) {
    int i;
    int uv; //unvisitedVertice
    int proxVertice;

    //stack auxiliar
    int stack[MAX];
    int top = 0;

    //validações
    if (lstVertices[vOrigin]->visited == true)
        if (vOrigin == vertice) return true;
        else
            return false;

    if (vOrigin == vertice) return true;

    //marca vertice como visitado 
    lstVertices[vOrigin]->visited = true;
    //processa vertice
    ProcessaVertice(lstVertices[vOrigin]);
    //insere vertice na stack
    top = push(stack, top, vOrigin);

    while (!isStackEmpty(top)) {
        proxVertice = peek(stack, top);
        //encontra vertice adjacente ao que está no topo da stack e ainda não foi visitado
        uv = GetVertAdjNaoVisitado(lstVertices, adj, proxVertice);

        if (uv == vertice) return true;

        //se não tem adjacentes, retira o atual da stack
        if (uv == -1) {
            top = pop(stack, top);
        }
        else {
            //marca
            lstVertices[uv]->visited = true;
            //processa
            ProcessaVertice(lstVertices[uv]);
            //insere na stack
            top = push(stack, top, uv);
        }
    }
    return false;
}


#pragma endregion

