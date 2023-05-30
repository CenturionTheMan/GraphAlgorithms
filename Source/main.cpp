#include "Headers/adjacency_list.h"
#include "Headers/adjacency_matrix.h"
#include "Headers/ms_tree.h"
#include "Headers/shortest_path.h"
#include "Headers/console_menu.h"
#include "Headers/tester.h"



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
    AdjacencyMatrix matrixDirect(0);
    AdjacencyList list(0);
    AdjacencyList listDirect(0);
    MenuConsole::MainMenuOptions input;
    do
    {
        input = MenuConsole::DisplayMainMenu();
        MenuConsole::HandleInput(input, matrix, matrixDirect, list, listDirect);
    } while (input != MenuConsole::MainMenuOptions::EXIT);   
}


void Test()
{
    std::string filePath = "TestGraphs/prim.txt";
    AdjacencyMatrix matrixDir(filePath, false);
    AdjacencyMatrix matrix(filePath, true);
    AdjacencyList listDir(filePath, false);
    AdjacencyList list(filePath, true);

    auto mBell = GSP::BellmanFord(matrixDir);
    auto lBell = GSP::BellmanFord(listDir);

    auto mDi = GSP::Dijkstra(matrixDir);
    auto lDI = GSP::Dijkstra(listDir);

    auto mPrima = MST::PrimaAlgorithm(matrix);
    auto lPrima = MST::PrimaAlgorithm(list);

    auto mKrus = MST::KruskalAlgorithm(matrix);
    auto lKrus = MST::KruskalAlgorithm(list);

    std::cout<<"MATRIX | Bellman\n" << GSP::ToString(matrix, mBell);
    std::cout<<std::endl;
    std::cout<<"LIST | Bellman\n" << GSP::ToString(list, lBell);
    std::cout<<std::endl <<std::endl;
    std::cout<<"MATRIX | Dijkstra\n" << GSP::ToString(matrix, mDi);
    std::cout<<std::endl;
    std::cout<<"LIST | Dijkstra\n" << GSP::ToString(list, lDI);
    std::cout<<std::endl <<std::endl;
    std::cout<<"MATRIX | Prima\n" << MST::ToString(mPrima);
    std::cout<<std::endl;
    std::cout<<"LIST | Prima\n" << MST::ToString(lPrima);
    std::cout<<std::endl <<std::endl;
    std::cout<<"MATRIX | Kruskal\n" << MST::ToString(mKrus);
    std::cout<<std::endl;
    std::cout<<"LIST | Kruskal\n" << MST::ToString(lKrus);
}

int main()
{
    //Test();
    InitMenu();
    //PerformTests();
}
