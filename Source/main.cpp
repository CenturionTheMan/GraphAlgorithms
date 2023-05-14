#include "Headers/adjacency_list.h"
#include "Headers/adjacency_matrix.h"
#include "Headers/ms_tree.h"
#include "Headers/shortest_path.h"
#include "Headers/console_menu.h"
#include "Headers/tester.h"

//? MENU
//? TESTY
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

//! DISJOINT SETS => Popraw na pseudo graph
int main()
{
    InitMenu();
    //PerformTests();
}