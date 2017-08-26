#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

/*
Reference: https://github.com/htailor/cpp_progress_bar
Accessed in 23/08/2017
Modificado
*/

class ProgressBar{

    int size;
    int dimension;
    int percent;

    public:
        ProgressBar(int size_){
            size = size_;
        }

        void setDimension(int dimension_){
            dimension = dimension_;
        }

        void increase(){
            size++;
            int _percent = (size*1.0/dimension*1.0)*100;
            if(_percent > percent){
                percent = _percent;
                print();
            }
        }

        void print() {
           
            string bar;

            for(int i = 0; i < 50; i++){
                if( i < (percent/2)){
                    bar.replace(i,1,"=");
                }else if( i == (percent/2)){
                    bar.replace(i,1,">");
                }else{
                    bar.replace(i,1," ");
                }
            }

            cout<< "\r" "[" << bar << "] ";
            cout.width( 3 );
            cout<< percent << "%     " << std::flush;
        }
} ;

static ProgressBar progressbar(40);

#endif