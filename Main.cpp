#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <climits>



using namespace std;

class Sorts {
   int isInt;
   int aux = 0;
   string *temp;
public:
   long long *input;
   string *inputString;
   int siz;
   Sorts(long long *in, int s);
   Sorts(string *in, int s);
   void sortHeuristic();
private:
   void insertion(int esq, int dir);
   void quick(int esq, int dir);
   int partitionTest(int esq, int dir);
   void counting();
   void bucket();
   void radix();
   void radixString(int esq, int dir, int a);
};

Sorts::Sorts(long long *in, int s) {

   input = new long long[s];
   siz = s;
   for(int i = 0;i < siz; i++) {
      input[i] = in[i];
   }
   isInt = 1;
}

Sorts::Sorts(string *in, int s) {

   inputString = new string[s];
   temp = new string[s];
   siz = s;
   for(int i = 0;i < siz; i++) {
      inputString[i] = in[i];
   }
   isInt = 0;
}
void Sorts::insertion(int esq, int dir) {
   long long x;

	for(int j = esq + 1; j < dir + 1; ++j) {
		x = input[j];
		int i = 0;
		for(i = j-1; i>=0 && input[i] > x; i--) {
			input[i+1] = input[i];
		}
		input[i+1] = x;
	}
}

void Sorts::quick(int esq, int dir) {
	int p;

	if(esq < dir) {
       if(9 > (dir-esq)) {
          insertion(esq, dir);
       }
      else {
         p = partitionTest(esq, dir);
         quick(esq, p - 1);
         quick(p+1, dir);
       }
	}

}

int Sorts::partitionTest(int esq, int dir) {
	int indicePivo;
   long long pivo;
   long long aux;
	indicePivo = (int) (dir);
	pivo = input[indicePivo];
	dir--;
	while(esq <= dir) {
		for(;input[esq] < pivo; ++esq) {}
		for(;dir >= 0 && (input[dir] >= pivo); --dir) {}
		if(esq >= dir) {
			break;
		}
		else {
			aux = input[esq];
			input[esq] = input[dir];
			input[dir] = aux;
		}
	}
	aux = input[esq];
	input[esq] = input[indicePivo];
	input[indicePivo] = aux;
	return esq;

}

void Sorts::counting() {

   long long minimo = LLONG_MAX;
   int maximo = 0;
   long long dif = LLONG_MAX;
   int aux = 0;

   for(int i = 0; i < siz; i++ )
	{
	    if( input[i] > maximo ){
         maximo = input[i];
	    }
	    if( input[i] < minimo ){
         minimo = input[i];
	    }
	}

	dif = (maximo - minimo) + 1;
	long long *help = new long long[dif];
	memset( help, 0, dif*sizeof(long long));

	for( int i = 0; i < siz; i++ ){
      help[input[i] - minimo]++;
	}

	for(long long i = minimo;i <= maximo;i++ )
	{
      while(help[i - minimo] )
      {
         input[aux++] = i;
         help[i - minimo]--;
	   }
	}
	free(help);
}

void Sorts::radixString(int esq, int dir, int a) {
	if(dir <= esq) {
		return;
	}
	int count[258] = {0};
	for(int i = esq; i < dir; ++i) {
		count[inputString[i].at(a) + 2]++;
	} 
	for(int k = 0; k < 257; k++) {
		count[k+1] += count[k];
	}
	for(int i = esq; i < dir; i++) {
		temp[count[inputString[i].at(a)+1]++] = inputString[i];
	}
	for(int i = esq; i < dir; i++) {
		inputString[i] = temp[i-esq];
	}
	for(int i = 0; i < 256; i++) {
		radixString(esq+count[i], esq+count[i+1] - 1, a+1);
	} 
}

void Sorts::sortHeuristic() {
   int ord = 0;
   int cond = 0;
   long long maximo = LLONG_MIN, minimo = LLONG_MAX;


   if(isInt) {
      for(int i = 0; i < siz; ++i) {
         if(ord != 1 && i != (siz-1) && input[i] > input[i + 1]) {
            ord = 1;
         }
         if(maximo < input[i]) {
         	maximo = input[i];
         }
         if(minimo > input[i]) {
         	minimo = input[i];
         }
      }
      
      if((long long)((maximo - minimo)/(long long)log10(siz)) >= (long long)(siz)){
      	cond = 3;
      }

      if(ord == 0) {
      	cond = 1;
      }

      switch(cond) {
      case 0:
      	cout << "Usando counting sort" << endl;
        counting();
        break;
      case 1:
      	cout << "Dados ja ordenados" << endl;
        break;
      case 2:
      	cout << "Usando Quick Sort" << endl;
      	quick(0, siz-1);
        break;
      case 3:
      	cout << "Usando Quick Sort" << endl;
        quick(0, siz-1);
        break;
      default:
        break;
      }

   }
   else {
   		cout << "Using radix sort" << endl;
   		radixString(0, siz-1, 0);
   }
}

int main(int argc, char* argv[]) {

   int siz, aux = 0;
   long long taxableIncome;
   int isInt = 0;
   cin >> siz;
   long long*input = new long long[siz];
   string *inputString = new string[siz];

   for(int i = 0; i < siz; i++) {
      cin >> inputString[i];
      if(aux == 0) {
         stringstream myStream(inputString[i]);
         if ( (myStream >> taxableIncome) ) {
            isInt = 1;
         }
         aux = 1;
      }

      if(isInt == 1) {
         input[i] = atoll(inputString[i].c_str());
      }
   }

	Sorts *sorts;
   clock_t startTime, endTime;

	if(isInt) {
      sorts = new Sorts(input, siz);
      startTime = clock();
      sorts->sortHeuristic();
      endTime = clock();

      for(int i = 0; i < siz; i++) {
         if(i != (siz - 1)) {
            cout << sorts->input[i] << endl;
         }
         else {
            cout << sorts->input[i];
         }
      }
	}
	else {
      sorts = new Sorts(inputString, siz);
      startTime = clock();
      sorts->sortHeuristic();
      endTime = clock();

      for(int i = 0; i < siz; i++) {
         if(i != (siz - 1)) {
            //cout << sorts->inputString[i] << endl;
         }
         else {
            //cout << sorts->inputString[i];
         }
      }
	}

   printf("\nTempo gasto: %.4f ms\n\n",1000*(double)(endTime-startTime)/(double)(CLOCKS_PER_SEC));
   
}
