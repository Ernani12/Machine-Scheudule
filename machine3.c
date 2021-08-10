/*Ernani   branch in bound for  3 - parallel machines 
//na turma de 2021s1, com a ajuda dos alunos
//Ele resolve o escalonamento em 3 maquinas usando um 

Ernani-Batista-Serfaim 2017019950 - traballho 2

Utiliza-se  limite Superior
Qual seria o superior:???
•	Heurística e pega as  tarefas na ordem que foram  dadas e colocar na maquina menos carregada 
•	Coloca-se sempre na menos carregada 

Alem do Limite Inferior 
•	Imaginar  que pega-se  todas  as tarefas e  derrete-se elas, perfeitamente(soma da bigger maquina carregada)

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int heuristc(int n, int * t, int current_task, int m1,int m2, int m3, int * x, int * best_x, int * best_solution){
    
		for(int i = current_task; i < n; i++) {
				if (m1 <= m2 && m1 <= m3) {
				x[i] = 1;
                m1 += t[i];
				} else if (m2 <= m1 && m2 <= m3) {
				 x[i] = 2;
                 m2 += t[i];
				} 
				else {
				x[i] = 3;
                m3 += t[i];	
				}
    }

			int bigger =0;  ///  qual é bigger
			
			if (m1 >= m2 && m1 >= m3) {
			    bigger=m1;
			}
            else if(m2 >= m1 && m2 >= m3){
                bigger=m2;
            }  

            else {
                bigger=m3;
            }
		

    if(bigger < *best_solution){
        *best_solution = bigger;
        for(int i = 0; i < n; i++){
          best_x[i] = x[i];
        }  
        } 
    
   return bigger;
}


void schedule_branch_bound(int n, int * t, int current_task, int * x, int * best_x, int * best_solution){
    
    		if(current_task == n){
			//tenho uma solucao completa
			int m1 = 0;
			int m2 = 0;
			int m3 = 0;
			
			for(int i = 0; i < n; i++){
				if(x[i] == 1) {
				m1 += t[i];
				}
				if(x[i] == 2){
				m2 += t[i];
				}
				if(x[i] == 3){
				m3 += t[i];
				}
			}
			int bigger =0;  ///  qual é bigger
			
			if (m1 >= m2 && m1 >= m3) {
			    bigger=m1;
			}
            else if(m2 >= m1 && m2 >= m3){
                bigger=m2;
            }  

            else {
                bigger=m3;
            }


			
			if(bigger < *best_solution){
			//encontrei uma solucao melhor
				*best_solution = bigger;
				for(int i = 0; i < n; i++) best_x[i] = x[i];
			}
			return;
		}
		
		
			//lower  bound  faz o mesmo acima  a qualquer momento
			int m1 = 0;
			int m2 = 0;
			int m3 = 0;
			
			for(int i = 0; i < current_task; i++){
				if(x[i] == 1) {
				m1 += t[i];
				}
				if(x[i] == 2){
				m2 += t[i];
				}
				if(x[i] == 3){
				m3 += t[i];
				}
			}
			
			heuristc(n, t, current_task, m1, m2, m3, x, best_x, best_solution);
    
            int resto = 0;
            for(int i = current_task; i < n; i++) {
            resto += t[i];
            }
			
			int bigger =0;  ///  qual é bigger
			
			if (m1 >= m2 && m1 >= m3) {
			    bigger=m1;
			}
            else if(m2 >= m1 && m2 >= m3){
                bigger=m2;
            }  

            else {
                bigger=m3;
            }
            
            
            resto = resto- (bigger - m1);
    		resto = resto- (bigger - m2);
    		resto = resto- (bigger - m3);
        
            if(resto > 0) {
                bigger += ceil((double) resto / 3);
            }
			
			if(bigger >= *best_solution){
			//encontrei uma solucao melhor
				return;
			}
			
		
		

     //****************************************************
    //BRANCHING
    x[current_task] = 1; // resolve  para 1 se  nao der beleza
    schedule_branch_bound(n, t, current_task + 1, x, best_x, best_solution);
    x[current_task] = 2;
    schedule_branch_bound(n, t, current_task + 1, x, best_x, best_solution);  
    x[current_task] = 3;
    schedule_branch_bound(n, t, current_task + 1, x, best_x, best_solution);  
    
}



void solve_schedule(int n, int * t){
    //x[i] guarda a maquina em que a tarefa i estah guardada, 1, 2 ou 3
    
    int * x = (int*) malloc(sizeof(int) * n);  //  depende da maquina m1,m2 m3
    int * best_x = (int*) malloc(sizeof(int) * n);  //guarda  valor melhor solucao
    
    int best_solution = INT_MAX;  // comecou com  infinito
    
    schedule_branch_bound(n, t, 0, x, best_x, &best_solution);

    //quais  maquinas escalonadas cada solucao 
    //for(int i = 0; i < n; i++) 
    // printf("%d - ", best_x[i]);
    //printf("\n");
    printf("%d\n", best_solution);
    
    return;
}

int main(int argc, char * argv[]){
    //n eh o numero de tarefas e t[i] eh o tempo de processento da tarefa i
    int n;
    int * t;
  
    //lendo a instancia da entrada
    scanf("%d", &n);
	//printf("%d  \n",n);
  
    t = (int*) malloc(sizeof(int) * n);
  
    for(int i = 0; i < n; i++){
        scanf("%d", &(t[i]));
			//printf("%d  \n", t[i]);
    }
    

    solve_schedule(n, t);

    return 0;
}

