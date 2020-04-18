#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H
#define DELTA_T 100.0f
class CellularAutomata{
public:
    CellularAutomata(int, int);
    ~CellularAutomata();
    void clear(void);
    void random(void);
    void update(void);
    void setProb(double);
    int getState(int, int);

protected:
    int mX,
        mY,
        *mS0,
        *mS1;

    double mProb;
    
};
#endif