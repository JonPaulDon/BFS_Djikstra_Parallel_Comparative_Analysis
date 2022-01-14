#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <queue>
#include "omp.h"
#include <list>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int n = 1000;

int main() {
    
    int start=2, end = 497;
    int prev[n], j, path[n], bbb = 0, reversepath[n], a[n][n], randNum = 0;
    bool visited[n];
    std::list<int> queue;
    clock_t startTime, endTime;
    bool tempVisited[n][n]; 


    for(int i =0; i < n; i++){

     for(int j = 0; j < n; j++){

        if(i == j){
            continue;
        } 
      
       if(a[i][j] == 0 ){
        
            if(j%2 == 0 && !tempVisited[i][j] && !tempVisited[j][i]){ 
                randNum = 1;
                a[i][j] = randNum; a[j][i] = randNum;
                tempVisited[i][j] = true; tempVisited[j][i] = true;

            }
            else if (!tempVisited[i][j] && !tempVisited[j][i]){
                
                a[i][j] = 0; a[j][i] = 0;
                tempVisited[i][j] = true; tempVisited[j][i] = true;

            }
       }

     }

    }


    //bfs code

    startTime = clock();

    for (int i = 0;i < n;i++){
        visited[i] = false;
    }
    
    visited[start] = true;
    queue.push_back(start);
    
    //This array tracks who the parent of node i was, so we can reconstruct the path later
    for (int i = 0;i < n;i++){
        prev[i] = -127;
    }

    printf("\n\n");
    while (!queue.empty()) {
        
        j = queue.front();
        queue.pop_front();

        for (int i = 0;i < n;i++) {

            if (a[j][i] == 1) {
                if (!visited[i]) {
                    visited[i] = true;
                    prev[i] = j;
                    queue.push_back(i);

                }
            }

        }
    }

    //Construct path
    #pragma omp parallel num_threads(2)
    {
        for (int i = 0;i < n;i++){
            path[i] = -127;
        }
    }
    
    for (int curr = end; curr != -127; curr=prev[curr]) {
        path[bbb] = curr;
        bbb++;
    }

    #pragma omp parallel num_threads(2)
    {
        for (int i = 0;i < n;i++) {
            reversepath[i] = -127;
        }
    }
   
    for (int i = 0;i < bbb;i++) {
        if (path[bbb - i - 1] != -127) {
            reversepath[i] = path[bbb - i - 1];     
        }
    }

    endTime = clock();

    double time_taken = double(endTime - start) / double(CLOCKS_PER_SEC);

    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;

    printf("\nPath:\n\n");
    
    for (int i = 0;i < n;i++){
        
        if(reversepath[i] == -127){
            break;
        }
        else
        {
            if( i + 1 < n && reversepath[i + 1] == -127 ){
                printf("%d", reversepath[i]);
            }else{
                printf("%d->", reversepath[i]);
            }
        }
    } 

    printf("\n\n");
    return 0;
}
