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
days(28){
        srand (time(NULL));
        cout << "Domain (" << mX << ", " << mY << ")" << endl;
        clear();

        assert(posix_memalign((void**) &mS0, ALIGN,   mX * mY *  sizeof(int)) == 0);
        assert(posix_memalign((void**) &mS1, ALIGN,   mX * mY *  sizeof(int)) == 0);
        assert(posix_memalign((void**) &mI, ALIGN,   mX * mY *  sizeof(int)) == 0);

        memset(mS0, 0x00,   mX * mY *  sizeof(int));
        memset(mS1, 0x00,   mX * mY *  sizeof(int));
        memset(mI, 0x00,   mX * mY *  sizeof(int));

        mProb[CellularAutomata::P_INFECT]  = 0.01f;
        mProb[CellularAutomata::P_RECOVER] = 0.98f;
        mProb[CellularAutomata::P_DIE]     = 0.02f;
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
            mS0[k] = CellularAutomata::SUSCEPTIBLE;
            if ((i == (mY / 2)) && (j == (mX / 2)))
                mS0[k] = CellularAutomata::INFECT;
                mI[k] = days;
                mStatistic[INFECT] = 1;
        }
    }
    updateS();

};

/*
    Moore neighborhood with r = 1
 
            |nw|n|ne|
            |w | |e |
            |sw|s|se|
 
 */

void CellularAutomata::update(void){

    /*
        nw | n | ne
       ----|---|----
        w  | c |  e
       ----|---|----
        sw | s | se
    */

    for (int j = 0; j < mY ; j++){
        for (int i = 0; i < mX ; i++){

          double infec = 0.0f;
          if ((j > 0) && (i > 0))
            if (mS0[(j - 1) * mX  +  (i - 1)] == CellularAutomata::INFECT)
                infec++;

          if (j > 0)
            if (mS0[(j - 1) * mX  +  i] == CellularAutomata::INFECT)
                infec++;

          if ((j > 0 ) && (i < mX - 1))
            if (mS0[(j - 1) * mX  +  (i + 1)]== CellularAutomata::INFECT)
                infec++;

          if (i > 0)
            if (mS0[j * mX  +  (i - 1)]== CellularAutomata::INFECT)
                infec++;

          if (i < mX - 1)
            if (mS0[j * mX  +  (i + 1)]== CellularAutomata::INFECT)
                infec++;

          if ((j < mY - 1 ) && (i > 0))
            if (mS0[(j + 1) * mX  +  (i - 1)]== CellularAutomata::INFECT)
                 infec++;

          if (j < mY - 1)
            if (mS0[(j + 1) * mX  +  i]== CellularAutomata::INFECT)
             infec++;

          if ((j < mY - 1) && (i < mX - 1))
          if (mS0[(j + 1) * mX  +  i+1]== CellularAutomata::INFECT)
             infec++;



          int cell = mS0[j * mX  +  i];

          if (cell == CellularAutomata::SUSCEPTIBLE){
            if (randU() < (infec * mProb[CellularAutomata::P_INFECT])){
                mS1[j * mX  +  i] = CellularAutomata::INFECT;
                //cout << "(" << i << "," << j << ") = prob: " << prob << "\t" << infec * mProb[CellularAutomata::P_INFECT] << endl;
                mI[j * mX  +  i] = days;
                //mS1[j * mX  +  i] = cell;
             }else
                mS1[j * mX  +  i] = cell;
          }else if (cell == CellularAutomata::INFECT){
            mI[j * mX  +  i]--;
            if ( mI[j * mX  +  i] == 0){

               if (randU() < mProb[CellularAutomata::P_DIE])
                mS1[j * mX  +  i] = CellularAutomata::DIE;
               else
                mS1[j * mX  +  i] = CellularAutomata::RECOVER;

            }else if (randU() < mProb[CellularAutomata::P_RECOVER]){
               mI[j * mX  +  i] = 0;
               mS1[j * mX  +  i] = CellularAutomata::RECOVER;
               //mS1[j * mX  +  i] = cell;
            }else
                mS1[j * mX  +  i] = cell;
          }else
                mS1[j * mX  +  i] = cell;
          if (cell > 0)
            mStatistic[cell-1]++;
        }//end-  for (int i = 0; i < mLattice->width; i++){
    }//end-for (int j = 0; j < mLattice->height; j++){
    int *swap = mS0;
    mS0 = mS1;
    mS1 = swap;
    updateS();
};

void CellularAutomata::setProb(int index, double p){
    mProb[index] = p;
}

int CellularAutomata::getState(int x, int y)       { return mS0[y * mX + x]; }

double CellularAutomata::getStatistic(int index){
    //double N = mStatistic[0] + mStatistic[1] + mStatistic[2] + mStatistic[3];
    return mStatistic[index-1];// / N;
}

double CellularAutomata::randU(void)         {return static_cast<double> (rand() % 10000 + 1) / 10000.0f; }
void CellularAutomata::updateS(void){
    mStatistic[0] = mStatistic[1] = mStatistic[2] = mStatistic[3]  = 0.0f;
    for (int j = 0; j < mY ; j++){
        for (int i = 0; i < mX ; i++){
            if (mS0[j * mX + i] > 0)
                mStatistic[mS0[j * mX + i] - 1]++;

        }
    }
}

void CellularAutomata::setDays2R(int d)             { days = d; }
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
