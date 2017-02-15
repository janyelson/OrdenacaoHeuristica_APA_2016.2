#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>



using namespace std;

class Sorts {
   int isInt;
   int aux = 0;
   string *temp;
public:
   int *input;
   string *inputString;
   int siz;
   Sorts(int *in, int s);
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

Sorts::Sorts(int *in, int s) {

   input = new int[s];
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
   int x;

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
	int pivo, aux, indicePivo;
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

   int minimo = INT_MAX;
   int maximo = 0;
   int dif = INT_MAX;
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
	int *help = new int[dif];
	memset( help, 0, dif*sizeof(int));

	for( int i = 0; i < siz; i++ ){
      help[input[i] - minimo]++;
	}

	for(int i = minimo;i <= maximo;i++ )
	{
      while(help[i - minimo] )
      {
         input[aux++] = i;
         help[i - minimo]--;
	   }
	}
	free(help);
}

void Sorts::bucket() {
   int index = 0;
   int maximo = INT_MIN, minimo = INT_MAX, num;

   for(int i = 0; i < siz; i++ )
	{
	    if( input[i] > maximo ){
         maximo = input[i];
	    }
	    if( input[i] < minimo ){
         minimo = input[i];
	    }
	}
   int* help = new int[(maximo-minimo)+1];
   for(int i=0;i<((maximo-minimo)+1);i++){
      help[i] = 0;
   }

   for(int i = 0;i<siz;i++){
      (help[input[i]-minimo])++;
   }
   int aux = 0;
   for(int k = 0;k<((maximo-minimo)+1);k++) {
      for(int j = 0;j<help[k];j++) {
         input[aux++] = k + minimo;
      }
   }
}

void Sorts::radix() {

    int maximo = input[0];
    for (int i = 1; i < siz; i++){
        if (input[i] > maximo){
            maximo = input[i];
        }
    }

    for (int e = 1; maximo/e > 0; e *= 10) {
      int output[siz];
      int i, help[10] = {0};
      for (i = 0; i < siz; i++)
         help[(input[i]/e)%10 ]++;

      for (i = 1; i < 10; i++){
         help[i] += help[i - 1];
      }

      for (i = siz - 1; i >= 0; i--)
      {
         output[help[(input[i]/e)%10 ] - 1] = input[i];
         help[(input[i]/e)%10 ]--;
      }
      for (i = 0; i < siz; i++) {
         input[i] = output[i];
      }
   }
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
   int maximo = INT_MIN, minimo = INT_MAX;


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

      if((int)((maximo - minimo)/log10(siz)) >= (siz)){
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

   int siz, taxableIncome, aux = 0;
   int isInt = 0;
   cin >> siz;
   int *input = new int[siz];
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
         input[i] = atoi(inputString[i].c_str());
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
            cout << sorts->inputString[i] << endl;
         }
         else {
            cout << sorts->inputString[i];
         }
      }
	}

   printf("\nTempo gasto: %4.0f ms\n\n",1000*(double)(endTime-startTime)/(double)(CLOCKS_PER_SEC));
   
}
