#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include <cassert>


std::vector<std::vector<int> > clausulas;
int qtdvar;
int qtdclausula;


//std::vector<std::vector<int> >
void ler(std::string arg){
    std::ifstream arq(arg.c_str());
    //std::vector <std::vector<int> > clausulas;
   // std::cout<<arq;
    while(arq){
        char ch;
        arq>>ch;
        if(ch == 'c'){
            std::string linha;
            std::getline(arq,linha);
            //std::cout<<linha;
        }else if(ch == 'p'){
            std:: string nf;
            int var, clausula;
            arq>>nf>>var>>clausula;
            clausulas.resize(clausula);
            qtdvar = var;
            qtdclausula = clausula;
            //printf("%d,%d", var,clausula);
            for(int i=0; i<=clausula; i++){
                // std::string linha;
                //std::getline(alinharq,linha);
                //std::cout<<linha<< "\n";
                int v;
                do{
                    arq>>v;
                   // std::cout<<v << " ";
                    if(v!=0){
                        clausulas[i].push_back(v);
                    }
                }while(v!=0);               
                    //std::cout<< "\n";
                
                //int v1, v2,v3;
               // arq>>v1>>v2>>v3;
                //std::cout<<v1<<" "<<v2<< " " <<v3<< "\n";
            }
            break;
        }
        
    }
    //return clausulas;
    
};




std::vector<int> sol_aleatoria (){
        std::vector<int> sol;
        sol.push_back(0);
        for(int i=1; i<=qtdvar; i++){
            sol.push_back(rand()%2);
        }
        return sol;
}

int coust(std::vector<int> sol){
    int count = 0;
    for(int i=0; i < clausulas.size(); i++){
        for(int j=0; j < clausulas[i].size(); j++){
            int aux = clausulas[i][j];
            if(aux < 0){
               aux = -aux;
            }
            if(clausulas[i][j] <0 && sol[aux]==0){
                count++;
                break;
            } else if(clausulas[i][j] >0 && sol[aux] == 1) {
                  count++;
                  break;
            }
       }
    }
    return count;
}


std::vector<int> buscagsat(std::vector<int> s){
    std::vector<int> melhorVizinho = s;
    int custoMelhorV = coust(s);
    int empate = 1;
    std::vector<int> aux = s;
    int custoaux = custoMelhorV;
    for(int i = 1; i <= qtdvar; i++){
      aux[i] = 1 - aux[i];
        custoaux = coust(aux);
        //std::cout << custoaux << std::endl;
        if(custoMelhorV == custoaux){
            empate++;
            if(rand()%empate == 0){
                melhorVizinho = aux;
                //custoMelhorV = custoaux;
            }
        }
        else if(custoMelhorV < custoaux){
          return aux;
        }
        aux[i] = 1 - aux[i];
    }
    return melhorVizinho;
}



std::vector<int> walksat(std::vector<int> s){
    std::vector<int> melhorVizinho = s;
    int custoMelhorV = coust(s);
    int empate = 1;
    std::vector<int> aux = s;
    int custoaux = custoMelhorV;
    for(int i = 1; i <= qtdvar; i++){
      aux[i] = 1 - aux[i];
        custoaux = coust(aux);
        //std::cout << custoaux << std::endl;
        if(custoMelhorV == custoaux){
            empate++;
            if(rand()%empate == 0){
                melhorVizinho = aux;
                //custoMelhorV = custoaux;
            }
        }
        else if(custoMelhorV < custoaux){
          return aux;
        }
        aux[i] = 1 - aux[i];
    }
    return melhorVizinho;
}

void gsat(){
    int custoMelhorS = 0;
    int coustaux = 0;
    std::vector<int> melhorSol;
    int  inter=0;
    while(custoMelhorS < qtdclausula){
        std::vector<int> sol = sol_aleatoria();
        for(int i=0; i< qtdvar*3; i++){

            sol =  buscagsat(sol);
            coustaux = coust(sol);
            if(custoMelhorS < coustaux){
                melhorSol = sol;
                custoMelhorS = coustaux;
            }
            if(custoMelhorS == qtdclausula){
                melhorSol =sol;
                custoMelhorS = coustaux;
                std::cout<< custoMelhorS << "\n";
                break;
            }
        }
        inter++;
        std::cout<< custoMelhorS << " interações: " << inter << "\n"; 
    }
};






int main(int argc, char **argv) {
    //std::vector<std::vector<int> > dados;
    //dados = 
  srand(0);
    ler("./flat100-1.cnf");    
    gsat();       
    /*for(int i=0; i<dados.size(); i++){
       for(int j=0; j<dados[i].size(); j++){
        std::cout<< dados[i][j]<< " ";
        }
      printf("\n");
   }*/
    

    return 0;
}
