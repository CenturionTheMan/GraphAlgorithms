#include "Headers/console_menu.h"

bool MenuConsole::TryParseToInt(std::string str, int& val)
{
    try
    {
        val = stoi(str);
        return true;
    }
    catch(const std::exception& e){}
    return false;
}

MenuConsole::MainMenuOptions MenuConsole::DisplayMainMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= MENU =======\n");
    printf("[0] Exit\n");
    printf("[1] Read data from file to all structures\n");
    printf("[2] Show graph as Adjacency Matrix\n");
    printf("[3] Show graph as Adjacency List\n");
    printf("[4] Kruskal algorithm\n");
    printf("[5] Prima algorithm\n");
    printf("[6] Dijkstra algorithm\n");
    printf("[7] Bellman-Ford algorithm\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 7)
            break;
        else
            std::cout<<WRONG_INPUT;

    } while (true);

    std::cout<<MenuConsole::LINE_SEP;
    return static_cast<MainMenuOptions>(input);
}

void MenuConsole::HandleInput(MainMenuOptions input, AdjacencyMatrix& matrixNotDirect, AdjacencyMatrix& matrixDirect, AdjacencyList& listNotDirect, AdjacencyList& listDirect)
    {
        switch (input)
        {
            case MenuConsole::MainMenuOptions::LOAD_FROM_FILE:
            {
                std::string path = "";
                bool isDirected = false;

                std::cout << "Path for file: ";
                std::cin >> path;



                if(matrixNotDirect.LoadDataFromFile(path, true) && matrixDirect.LoadDataFromFile(path, false))
                {
                    std::cout << "Data from file successfully loaded into adjacency matrix\n";
                }
                else
                {
                    std::cout << "ERROR - Something went wrong when loading data from file to adjacency matrix!\n";
                }

                if(listNotDirect.LoadDataFromFile(path, true) && listDirect.LoadDataFromFile(path, false))
                {
                    std::cout << "Data from file successfully loaded into adjacency list\n";
                }
                else
                {
                    std::cout << "ERROR - Something went wrong when loading data from file to adjacency list!\n";
                }

                break;
            }
            case MenuConsole::MainMenuOptions::SHOW_MATRIX:
            {
                std::cout << "Adjacency matrix (direct):\n" << matrixDirect.ToString();
                std::cout <<std::endl;
                std::cout << "Adjacency matrix (not direct):\n" << matrixNotDirect.ToString();
                break;
            }
            case MenuConsole::MainMenuOptions::SHOW_LIST:
            {
                std::cout << "Adjacency list (direct):\n" << listDirect.ToString();
                std::cout <<std::endl;
                std::cout << "Adjacency list (not direct):\n" << listNotDirect.ToString();
                break;
            }
            case MenuConsole::MainMenuOptions::DO_KRUSKAL:
            {
                AdjacencyMatrix kruskalMatRes = MST::KruskalAlgorithm(matrixNotDirect);
                AdjacencyList kruskalListRes = MST::KruskalAlgorithm(listNotDirect);

                std::cout<< "Kruskal algorithm (matrix):\n" << MST::ToString(kruskalMatRes);
                std::cout <<std::endl;
                std::cout<< "Kruskal algorithm (list):\n" << MST::ToString(kruskalListRes);

                break;
            }
            case MenuConsole::MainMenuOptions::DO_PRIMA:
            {
                AdjacencyMatrix primaMatRes = MST::PrimaAlgorithm(matrixNotDirect);
                AdjacencyList primaListRes = MST::PrimaAlgorithm(listNotDirect);

                std::cout<< "Prima algorithm (matrix):\n" << MST::ToString(primaMatRes);
                std::cout <<std::endl;
                std::cout<< "Prima algorithm (list):\n" << MST::ToString(primaListRes);
                break;
            }
            case MenuConsole::MainMenuOptions::DO_DIJKSTRA:
            {
                int* resMatArr = GSP::Dijkstra(matrixDirect);
                int* resListArr = GSP::Dijkstra(listDirect);
                if(resMatArr != NULL)
                {
                    std::cout << "Dijkstra algorithm (matrix):\n" << GSP::ToString(matrixDirect, resMatArr);
                    delete[] resMatArr;
                }
                else
                {
                    std::cout << "Dijkstra algorithm (matrix):\nNegative edge weight was found in Dijkstra algorithm!\n";
                }
                std::cout <<std::endl;
                if(resListArr != NULL)
                {
                    std::cout << "Dijkstra algorithm (list):\n" << GSP::ToString(listDirect, resListArr);
                    delete[] resListArr;
                }
                else
                {
                    std::cout << "Dijkstra algorithm (list):\nNegative edge weight was found in Dijkstra algorithm!\n";
                }
                break;
            }
            case MenuConsole::MainMenuOptions::DO_BELLMAN_FORD:
            {
                int* resMatArr = GSP::BellmanFord(matrixDirect);
                int* resListArr = GSP::BellmanFord(listDirect);
                if(resMatArr != NULL)
                {
                    std::cout << "Bellman-Ford algorithm (matrix):\n" << GSP::ToString(matrixDirect, resMatArr);
                    delete[] resMatArr;
                }
                else if(matrixDirect.GetVertexAmount() == 0)
                {
                    std::cout << "Bellman-Ford algorithm (matrix):\n" << GSP::ToString(matrixDirect, resMatArr);
                }
                else
                {
                    std::cout << "Bellman-Ford algorithm (matrix):\n" << "ERROR - Graph contains a negative cycle\n";
                }
                std::cout <<std::endl;
                if(resListArr != NULL)
                {
                    std::cout << "Bellman-Ford algorithm (list):\n" << GSP::ToString(listDirect, resListArr);
                    delete[] resListArr;
                }
                else if(listDirect.GetVertexAmount() == 0)
                {
                    std::cout << "Bellman-Ford algorithm (list):\n" << GSP::ToString(listDirect, resListArr);
                }
                else
                {
                    std::cout << "Bellman-Ford algorithm (list):\n" << "ERROR - Graph contains a negative cycle\n";
                }
                
                break;
            }
        }
        std::cout <<MenuConsole::LINE_SEP;
    }

