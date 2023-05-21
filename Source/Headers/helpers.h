#pragma once
#include <iomanip>
#include <random>
#include <windows.h>

enum TimeScales
{
    SECONDS,
    MILI_SECONDS,
    MICRO_SECONDS,
};

class Timer
{
private:
    long long int timerStartTime;

    /// @brief Function reads counter (ticks)
    /// @return ticks amount in given moment
    long long int ReadQPC();
public:
    /// @brief CTOR
    Timer();

    /// @brief DTOR
    ~Timer();

    /// @brief Function starts timer
    void StartTimer();

    /// @brief Function stops timer
    /// @param timeScale scale in which time is returned
    /// @return time elapsed science timer started
    double TimerStop(TimeScales timeScale);
};

class RandomGenerator
{
    private:
        std::mt19937 generator;
    public:
        RandomGenerator();
        ~RandomGenerator();


    /// @brief Function return random number within min, max - inclusive.
    /// @param min Min possible value
    /// @param max Max possible value
    /// @return Random number within boundaries
    int GetRandomNumber(int min, int max);
    
    /// @brief Function will return given amount of random number within min, max - inclusive.
    /// @param min Min possible value
    /// @param max Max possible value
    /// @param numberAmount Amount of numbers to return
    /// @return Pointer to array of random numbers
    int* GetRandomNumbers(int min, int max, int numberAmount);
};