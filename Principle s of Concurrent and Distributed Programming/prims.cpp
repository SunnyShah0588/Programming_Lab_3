#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
using namespace std;

int N = 5;
//int totalWeight = 0;

void Prims(float W[][5], int **T, int N)
{
        int i, j, k;

        // array of nearest node
        int *nearNode = new int[N];

        // array of distance to nearest node
        float *minDist = new float[N];
        float min;

        // assume 0 as root node, set it as nearest node to all nodes   

        for (i = 1; i < N; i++)  
        {
              nearNode[i] = 0;
          
              // set distance of each node from [0]
              minDist[i] = W[i][0];
        
        }

        // loop for all (N-1) edges

        for (i = 0; i < N-1; i++) 
          {
         min = 999999;

     // find minimum distance
            for (j = 1; j < N; j++) 
                  {
                  if (0 <= minDist[j] && minDist[j] < min) 
                       {
                    min = minDist[j];
                    // k is closest node
                    k = j;
                        }
                  }   // update output array - link from nearNode to node

                  T[i][0] = nearNode[k];
                  T[i][1] = k;
                   //totalWeight = totalWeight + min;
                  // k is in the tree; set distance to - so that when ever that node comes to picture for comparasion we dont have to 
                    // to be confisued about that
                minDist[k] = -1;  
                  // updates all node distances wrt new tree
                
                #pragma omp parallel for
                  for (j = 1; j < N; j++)
                       {
                          if (W[j][k] < minDist[j]) 
                    {
                          minDist[j] = W[j][k];
                          nearNode[j] = k;
                              }
                       } // for i
                      }
              return;
              free(nearNode); 
              free(minDist);
}


int main()
{
    int totalWeight = 0;

  float W[N][5]; //= {{999, 1, 999, 999, 2}, {1, 999, 1, 2, 999}, {999, 1, 999, 2, 999}, {999, 2, 2, 999, 1}, {2, 999, 999, 1, 999}};

    for (int i = 0 ; i < N ; i++){
      for (int j = 0; j < N ; j++){

             if (i != j ){

        cout<<"ENTER THE "<<i+1<<" ROW ELEMENT OF "<<j+1<<" COLOUM "<<endl;
        cin>>W[i][j]; 

        }else {

          W[i][j] = 999;
        }
      }
    }

    
      int **t = new int*;
  
            for(int i = 0; i < N; i++) {

                                           t[i] = new int;
  
            }

 

        Prims(W, t, N);
  
            for(int i = 0; i < N-1; i++) {

                                          cout << t[i][0] <<"\t" <<t[i][1] <<"\t"<< W[t[i][0]][t[i][1]]<<endl<<endl;
                                          totalWeight = totalWeight + W[t[i][0]][t[i][1]];
            }
    cout << "THE TOTAL WEIGHT OF THE GRAPH TREE IS " <<totalWeight<<endl;
    return 0;

}       
