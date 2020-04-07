#include <iostream>
#include <vector>
#include <cstdint>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> cimletek;
unsigned int nulla;

unsigned  int meddig(vector<vector< uint_fast32_t>> & remainder, unsigned int count_and_divisor){
    unsigned  int osszeg =0;
    unsigned  int fele =0;
    for (unsigned int i =0; i < remainder.size(); i++){
        for(unsigned int k =0; k < remainder[remainder.size()-1-i].size(); k++){
            osszeg+= remainder.size()-1-i;
            fele++;
            if (fele == count_and_divisor){break;}
        }
        if (fele == count_and_divisor){break;}
    }
    return (osszeg-(osszeg % count_and_divisor))/count_and_divisor;
}

void cimletcsinalo(vector<vector< uint_fast32_t>> & remainder){
    for(unsigned int i =1; i<remainder.size(); i++){
        if(!remainder[i].empty()){
            cimletek.push_back(i);
        }
    }
}

bool vizsgalo2(vector<unsigned int> & fiz,  vector<vector< uint_fast32_t>> & remainder, unsigned int & i ){
    return (remainder[cimletek[i]].size() > fiz[i]);

}

void vizsgalo(vector<unsigned int> fiz, vector<uint_fast32_t >& count,  vector<vector< uint_fast32_t>> & remainder,unsigned int & n){
    bool exist = true;
    vector<uint_fast32_t > tarolo;
    for(unsigned  int i=0; i < cimletek.size(); i++) {
        //if(remainder[cimletek[i]].size() >= fiz[i] ){
        for (unsigned int k = 0; k < fiz[i]; k++) {
            tarolo.push_back(remainder[cimletek[i]][k]);
        }
    }
    for(unsigned int i : tarolo){
        cout<< i << endl;
    }
        /*}
        else  {
            exist =false;
            return;
        }

    }
    if (exist){*/
        if( tarolo.size() < n ){
            int k = 0;
            while(tarolo.size() != n){
                tarolo.push_back(remainder[0][k]);
                k++;
            }
        }
        count = tarolo;

        return;
    }



void fizet (unsigned int osszeg, vector< unsigned int> fiz, unsigned int n, vector<uint_fast32_t >& count,  vector<vector< uint_fast32_t>> & remainder){
    if (count.empty()){

        unsigned int reszosszeg =0;
        unsigned int szamlalo=0;

        for(unsigned int i=0; i<cimletek.size();i++){
            reszosszeg += fiz[i]*cimletek[i];
        }

        for (unsigned int i : fiz){
            szamlalo += i;
        }
        if(szamlalo > n ) {return;}
/*
        cout << endl << szamlalo << endl;
        for( unsigned int j =0; j < cimletek.size();j++){
            cout << fiz[j] << " szer " << cimletek[j] << "  ";

        }cout << endl;*/


        if (reszosszeg != 0) {
            if ((reszosszeg % n == 0) && (szamlalo <= n) && ((n - nulla) <= szamlalo)){

                vizsgalo(fiz, count, remainder, n);
                if (!count.empty()) {return;}
                //bele kell a fizbe egy szamlalot epiteni, ogy csak azt returnolje, ami port n darab cimletbol all
            }
        }

        for(unsigned int i = (cimletek.size()-1); i >= 0 ; i--){
            if(!count.empty()){return;}
            else if((reszosszeg+cimletek[i] <= osszeg )&& vizsgalo2(fiz, remainder, i) && (szamlalo <= n)){
                vector<unsigned int> fiz2 = fiz;
                fiz2[i]++;
                fizet(osszeg, fiz2, n, count, remainder);

            }

        }
    }
    else{return;}
}


vector<uint_fast32_t> select_cubes( vector<uint_fast32_t>&& cubes,  uint_fast32_t count_and_divisor){
    // TODO return 'count' count number from 'cubes'
    // whose sum can be divided by 'divisor' with zero remainder

    vector<uint_fast32_t> count; // ez lesz a végeredmény
    vector< uint_fast32_t> v; // ebbe  mennek a megfelelő maradékot adó számok
    vector<vector< uint_fast32_t>> remainder(count_and_divisor, v); //maradékok alapján vectorokba

    for(int aktuell : cubes){
        remainder[(aktuell % count_and_divisor)].push_back(aktuell);
    }
    nulla=remainder[0].size();

    /* if(nulla >= count_and_divisor){
         for(unsigned int k =0; k < count_and_divisor ; k++){
             count.push_back(remainder[0][k]);
         }
         return count;
     }*/

    for(unsigned int k = 0; k <remainder.size(); k++){
        if(remainder[k].size() >= count_and_divisor ){
            for(unsigned int l =0; l < count_and_divisor ; l++){
                count.push_back(remainder[k][l]);
            }
            return  count;
        }
    }

    cimletcsinalo( remainder);
    vector<unsigned int> a (cimletek.size(), 0);
    vector<unsigned int> b (cimletek.size(), 0);
    unsigned  int  m = meddig(remainder, count_and_divisor);

    fizet((count_and_divisor*m), a, count_and_divisor, count, remainder); //ide kell egy osszeegyezteto fv szeru cucc, ami megnezi h vannak e olyan szamaim igazabol


    return count;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    uint_fast32_t boxA, boxB, boxC;
    //cin >> boxA >> boxB >> boxC;
    boxA = 3;
    vector<uint_fast32_t> cubes;
    //for (auto& cube : cubes) cin >> cube;
    srand (time(NULL));
    boxB = 20;
    boxC = 1;
    for(unsigned int i =0; i< (2*boxA*boxB*boxC); i++){
        cubes.push_back(rand() % 1000);
    }
/*for(unsigned int i =0; i < cubes.size(); i++){
    cout<< cubes[i] << "   ";
}cout << endl;*/
    auto N =  boxA * boxB * boxC;

/* cubes.push_back(12);
cubes.push_back(2);
cubes.push_back(3);
cubes.push_back(0);
cubes.push_back(7);
cubes.push_back(0);
cubes.push_back(0);
cubes.push_back(0);
*/


/*    if (auto && result = select_cubes(move(cubes), N); result.size() == N)
      for (auto& cube : result) cout << cube << " ";
    else
        cout << "****";

    endl(cout);*/

    vector<uint_fast32_t> count = select_cubes(move(cubes), N);
    if(count.empty()){cout<< "****";}
    else{
        for(unsigned int i : count){
            cout<< i << "  ";
        }
    }
}
