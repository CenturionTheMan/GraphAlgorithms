#include "Headers/helpers.h"

#pragma region TIMER
Timer::Timer()
{

}

Timer::~Timer()
{

}


long long int Timer::ReadQPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}


void Timer::StartTimer()
{
    Timer::timerStartTime = Timer::ReadQPC();
}

double Timer::TimerStop(TimeScales timeScale)
{
    long long int elapsed = Timer::ReadQPC() - Timer::timerStartTime; 

    LARGE_INTEGER count;
    QueryPerformanceFrequency(&count);

    float scale = 1.0;

    switch (timeScale)
    {
    case SECONDS:
        scale = 1.0; break;
    case MILI_SECONDS:
        scale = 1000.0; break;
    case MICRO_SECONDS:
        scale = 1000000.0; break;
    }

    return  (scale * elapsed) / ((long long int)count.QuadPart);
}

#pragma endregion

#pragma region RANDOM_GENERATOR

RandomGenerator::RandomGenerator()
{
    LARGE_INTEGER seedByTicks;
    QueryPerformanceCounter(&seedByTicks);

    RandomGenerator::generator = std::mt19937(seedByTicks.QuadPart);
}


RandomGenerator::~RandomGenerator()
{

}

int RandomGenerator::GetRandomNumber(int min, int max)
{
    std::uniform_int_distribution<> dist(min, max);
    return dist(RandomGenerator::generator);
}

int* RandomGenerator::GetRandomNumbers(int min, int max, int numberAmount)
{
    std::uniform_int_distribution<> dist(min, max);
    int* arr = new int[numberAmount];
    for (int i = 0; i < numberAmount; i++)
    {
        arr[i] = dist(RandomGenerator::generator);
    }
    return arr;
}
#pragma endregion