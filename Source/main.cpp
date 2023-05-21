#include "Headers/adjacency_list.h"
#include "Headers/adjacency_matrix.h"
#include "Headers/ms_tree.h"
#include "Headers/shortest_path.h"
#include "Headers/console_menu.h"
#include "Headers/tester.h"


//TODO Sprawozdanie

void PerformTests()
{
    int max = 500;
    int samples = 10;
    int reps = 100;

    Tester::MatrixKruskalTest(max,samples,reps);
    Tester::MatrixPrimaTest(max,samples,reps);
    Tester::MatrixDijkstraTest(max,samples,reps);
    Tester::MatrixBellmanFordTest(max,samples,reps);

    Tester::ListKruskalTest(max,samples,reps);
    Tester::ListPrimaTest(max,samples,reps);
    Tester::ListDijkstraTest(max,samples,reps);
    Tester::ListBellmanFordTest(max,samples,reps);

    std::cout<<"END\n";
    std::cin.get();
    std::cin.get();
}

void InitMenu()
{
    AdjacencyMatrix matrix(0);
    AdjacencyList list(0);
    MenuConsole::MainMenuOptions input;
    do
    {
        input = MenuConsole::DisplayMainMenu();
        MenuConsole::HandleInput(input, matrix, list);
    } while (input != MenuConsole::MainMenuOptions::EXIT);   
}

void TestDijkstra()
{
    AdjacencyMatrix matrix("Test_Graphs/Dijkstra1.txt");
    AdjacencyList list("Test_Graphs/Dijkstra1.txt");
    auto mR = GSP::Dijkstra(matrix);
    auto lR = GSP::Dijkstra(list);
    std::cout<<"MATRIX\n" << GSP::ToString(matrix, mR);
    std::cout<<std::endl;
    std::cout<<"LIST\n" << GSP::ToString(list, lR);
    // Vertex          Distance from Source
    // 0                  0
    // 1                  4
    // 2                  12
    // 3                  19
    // 4                  21
    // 5                  11
    // 6                  9
    // 7                  8
    // 8                  14
}


int main()
{
    TestDijkstra();
    //InitMenu();
    //PerformTests();
}