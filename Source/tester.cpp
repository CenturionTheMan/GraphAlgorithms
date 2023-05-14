#include "Headers/tester.h"
#include "Headers/file_handler.h"

void Tester::WriteLineToFile(std::string pathSuffix, int vertexAmount, float density, double time)
{   
    std::stringstream stream;
    std::string* values = new std::string[3];
    values[0] = std::to_string(vertexAmount);

    stream << std::setw(0) << std::setfill('.') << density * 100;
    values[1] = stream.str();
    stream.clear();
    
    stream << std::setw(2) << std::setfill('.') << time;
    values[2] = stream.str();

    WriteDataToCsv(Tester::OutputDirectory + pathSuffix, values, 3);
    
    delete[] values;
}


void Tester::SetupGraph(AdjacencyMatrix& matrix, int vertexAmount, float density, bool isDirected, bool isNegative)
{
    RandomGenerator random;
    matrix.SetVertexAmount(vertexAmount);

    int edgesInGraph = (isDirected)? vertexAmount*vertexAmount : (int)( (vertexAmount+1)*vertexAmount/2 );
    edgesInGraph -= vertexAmount; 

    int edgesToSet = int(edgesInGraph*density);

    int edgeCounter = 0;
    int edgeStepAdd = 1;

    int lowerBound = (isNegative)? -Tester::MAX_WEIGHT : 0;

    int edgesPassed= 0;

    for (int i = 0; i < vertexAmount; i++)
    {
        int j = (isDirected)? 0 : i + 1;
        for (; j < vertexAmount; j++)
        {
            if(i == j)
                continue;

            if(edgeCounter >= edgesToSet)
                return;

            if(edgesInGraph - edgesPassed  > edgesToSet - edgeCounter )
            {
                int num = random.GetRandomNumber(1,10);
                if(num > 5)
                {
                    edgesPassed += edgeStepAdd;
                    continue;
                }
                matrix.SetConnection(i,j,random.GetRandomNumber(lowerBound,Tester::MAX_WEIGHT), !isDirected);
            }
            else
            {
                matrix.SetConnection(i,j,random.GetRandomNumber(lowerBound,Tester::MAX_WEIGHT), !isDirected);
            }
            
            edgeCounter += edgeStepAdd;
            edgesPassed += edgeStepAdd;
        }
    } 
}

void Tester::SetupGraph(AdjacencyList& list, int vertexAmount, float density, bool isDirected, bool isNegative)
{
    RandomGenerator random;
    list.SetVertexAmount(vertexAmount);

    int edgesInGraph = (isDirected)? vertexAmount*vertexAmount : (int)( (vertexAmount+1)*vertexAmount/2 );
    edgesInGraph -= vertexAmount; 

    int edgesToSet = int(edgesInGraph*density);

    int edgeCounter = 0;
    int edgeStepAdd = 1;

    int lowerBound = (isNegative)? -Tester::MAX_WEIGHT : 0;

    int edgesPassed= 0;

    for (int i = 0; i < vertexAmount; i++)
    {
        int j = (isDirected)? 0 : i + 1;
        for (; j < vertexAmount; j++)
        {
            if(i == j)
                continue;

            if(edgeCounter >= edgesToSet)
                return;

            if(edgesInGraph - edgesPassed  > edgesToSet - edgeCounter )
            {
                int num = random.GetRandomNumber(1,10);
                if(num > 5){
                    edgesPassed += edgeStepAdd;
                    continue;
                }
                list.SetConnection(i,j,random.GetRandomNumber(lowerBound,Tester::MAX_WEIGHT), !isDirected);
            }
            else
            {
                list.SetConnection(i,j,random.GetRandomNumber(lowerBound,Tester::MAX_WEIGHT), !isDirected);
            }
            
            edgeCounter += edgeStepAdd;
            edgesPassed += edgeStepAdd;
        }
    } 
}



void Tester::MatrixKruskalTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyMatrix matrix;

    std::string testSuffix = "Matrix_Kruskal.csv";

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Kruskal/Matrix | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(matrix, curentSize, densities[i], false, false);
                timer.StartTimer();
                MST::KruskalAlgorithm(matrix);
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::MatrixPrimaTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyMatrix matrix;

    std::string testSuffix = "Matrix_Prima.csv";

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Prima/Matrix | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(matrix, curentSize, densities[i], false, false);
                timer.StartTimer();
                MST::PrimaAlgorithm(matrix);
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::MatrixDijkstraTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyMatrix matrix;

    std::string testSuffix = "Matrix_Dijkstra.csv"; //! EDIT

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Dijkstra/Matrix | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(matrix, curentSize, densities[i], true, false); //!EDIT
                timer.StartTimer();
                GSP::Dijkstra(matrix); //!EDIT
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::MatrixBellmanFordTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyMatrix matrix;

    std::string testSuffix = "Matrix_BellmanFord.csv"; //! EDIT

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: BellmanFord/Matrix | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(matrix, curentSize, densities[i], true, true); //!EDIT
                timer.StartTimer();
                GSP::BellmanFord(matrix); //!EDIT
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::ListKruskalTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyList list;

    std::string testSuffix = "List_Kruskal.csv";

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Kruskal/List | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(list, curentSize, densities[i], false, false);
                timer.StartTimer();
                MST::KruskalAlgorithm(list);
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::ListPrimaTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyList list;

    std::string testSuffix = "List_Prima.csv";

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Prima/List | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(list, curentSize, densities[i], false, false);
                timer.StartTimer();
                MST::PrimaAlgorithm(list);
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::ListDijkstraTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyList list;

    std::string testSuffix = "List_Dijkstra.csv"; //! EDIT

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: Dijkstra/List | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(list, curentSize, densities[i], true, false); //!EDIT
                timer.StartTimer();
                GSP::Dijkstra(list); //!EDIT
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}

void Tester::ListBellmanFordTest(int maxVertexAmount, int samplesAmount, int repsForAvg)
{
    Timer timer;
    int step = maxVertexAmount/samplesAmount;
    AdjacencyList list;

    std::string testSuffix = "List_BellmanFord.csv"; //! EDIT

    RemoveFile(Tester::OutputDirectory + testSuffix);

    for (int curentSize = step; curentSize <= maxVertexAmount; curentSize += step)
    {
        float densities[] = {0.25, 0.5, 0.75, 0.99};
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Test: BellmanFord/List | " << "density=" << densities[i] << ", vertexAmount=" << curentSize << "\n";
            double time = 0;
            std::cout << "Rep number: ";
            for (int j = 1; j <= repsForAvg; j++)
            {
                Tester::SetupGraph(list, curentSize, densities[i], true, true); //!EDIT
                timer.StartTimer();
                GSP::BellmanFord(list); //!EDIT
                time += timer.TimerStop(MILI_SECONDS);
                if(j % 10 == 0)
                    std::cout << j <<", ";
            }
            std::cout << "\n\n";
            time /= repsForAvg;
            WriteLineToFile(testSuffix, curentSize, densities[i], time);
        }
    }
    std::cout << "\n\n";
}