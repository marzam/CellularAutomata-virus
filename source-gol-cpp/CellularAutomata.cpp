#include <CellularAutomata.hpp>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cassert>
using namespace std;
CellularAutomata::CellularAutomata(int x, int y):
mX(x),
mY(y),
mS0(NULL),
mS1(NULL),
mProb(0.0f){
        srand (time(NULL));
        cout << "Domain (" << mX << ", " << mY << ")" << endl;
        clear();

        assert(posix_memalign((void**) &mS0, ALIGN,   mX * mY *  sizeof(int)) == 0);
        assert(posix_memalign((void**) &mS1, ALIGN,   mX * mY *  sizeof(int)) == 0);
        assert(posix_memalign((void**) &mI, ALIGN,   mX * mY *  sizeof(int)) == 0);

        memset(mS0, 0x00,   mX * mY *  sizeof(int));
        memset(mS1, 0x00,   mX * mY *  sizeof(int));
        memset(mI, 0x00,   mX * mY *  sizeof(int));


};

CellularAutomata::~CellularAutomata(){
   clear();
};




void CellularAutomata::clear(void){
    if (mS0 != NULL)
        free(mS0);
    mS0 = NULL;

    if (mS1 != NULL)
        free(mS1);
    mS1 = NULL;
};

void CellularAutomata::random(void){
    for (int i = 0 ; i < mY; i++){
        for (int j = 0; j < mX; j++){
            double p = static_cast<double> (rand() % 10000 + 1) / 10000.0f;
            int k = (i * mX) + j;
            if (p < mProb)
                mS0[k] = 1;
            else
                mS0[k] = 0;
        }
    }


};

/*
    Moore neighborhood with r = 1
 
            |nw|n|ne|
            |w | |e |
            |sw|s|se|
 
 */

void CellularAutomata::update(void){

    int *swap = mS0;
    mS0 = mS1;
    mS1 = swap;

    
    int r = 1;
    int sum = 0;
    int x, y, p;

    for (int j = 0; j < mY; j++)
        for (int i = 0; i < mX; i++){
            sum = 0;
            p = (j * mX) + i;
            

            for (int rj = -r; rj <= r; rj++){
                
                int pj = j - rj;

                for (int ri = -r; ri <= r; ri++){
                    
                
                    int pi = i + ri;
                    
                    if ((pi >= 0) && (pi < mX) && (pj >= 0) && (pj < mY)){
                        p = (pj * mX) + pi;
                        if (!((rj == 0) && (ri == 0)))
                            sum += mS1[p];
                    }//else
                       // sum++;
                    
                }
                    
                
                
                
            }
            
            
            p = (j * mX) + i;
            if ((sum == 3) && (mS1[p] == 0))
                mS0[p] = 1;
            else if  ( ((sum >= 2) && (sum <= 3)) && (mS1[p] == 1))
                mS0[p] = 1;
            else
                mS0[p] = 0;
            
        }

    
    
};

void CellularAutomata::setProb(double p)            { mProb = p; }

int CellularAutomata::getState(int x, int y)       { return mS0[y * mX + x]; }

/*
void CellularAutomata::update(double time){
    mTimeInstant+=time;
    if (mTimeInstant < mDeltaT)
        return;
    
    mTimeInstant = 0.0f;
    
    int *swap = mCurrentState;
    mCurrentState = mOldState;
    mOldState = swap;
    
    
    int r = mDistance;
    int sum = 0;
    int x, y, p;
    for (int j = 0; j < mCellY; j++)
        for (int i = 0; i < mCellX; i++){
            sum = 0;
            p = (j * mCellX) + i;
            
            for (int rj = -r; rj <= r; rj++){
                
                int pj = j - rj;
                if (pj < 0)
                    pj = mCellY + pj;
                else if (pj >= mCellY)
                    pj %= mCellY;
                
                for (int ri = -r; ri <= r; ri++){
                    
                    
                    int pi = i + ri;
                    if (pi < 0)
                        pi = mCellX + ri;
                    else if (pi >= mCellX)
                        pi %= mCellX;
                    
                    
                    
                    p = (pj * mCellX) + pi;
                    if (!((rj == 0) && (ri == 0)))
                        sum += mOldState[p];
                }
                
                
                
            }
            
            
            p = (j * mCellX) + i;
            if ((sum == 3) && (mOldState[p] == 0))
                mCurrentState[p] = 1;
            else if  ( ((sum == 2) || (sum == 3)) && (mOldState[p] == 1))
                mCurrentState[p] = 1;
            else
                mCurrentState[p] = 0;
            
        }
    
    
    
};

*/
