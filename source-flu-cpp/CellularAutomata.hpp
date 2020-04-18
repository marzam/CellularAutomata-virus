#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H
#define DELTA_T 100.0f
class CellularAutomata{
public:
    const int EMPTY       = 0;
    const int SUSCEPTIBLE = 1;
    const int INFECT      = 2;
    const int RECOVER     = 3;
    const int DIE         = 4;

    const int P_INFECT     = 0;
    const int P_RECOVER    = 1;
    const int P_DIE        = 2;

public:
    CellularAutomata(int, int);
    ~CellularAutomata();
    void clear(void);
    void random(void);
    void update(void);
    void setProb(int, double);
    int getState(int, int);
    double getStatistic(int);
    void setDays2R(int);
private:
    double randU(void);
    void updateS(void);
protected:
    int mX,
        mY,
        *mS0,
        *mS1,
        *mI;

    double mProb[3];
    double mStatistic[4];
    int days;
};
#endif