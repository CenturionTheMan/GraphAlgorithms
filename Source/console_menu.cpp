#include "Headers/console_menu.h"



bool MenuConsole::TryParseToBool(std::string str, bool& val)
{
    if (str.find("Y") != std::string::npos) {
        val = true;
        return true;
    }
    if (str.find("N") != std::string::npos) {
        val = false;
        return true;
    }
    if (str.find("y") != std::string::npos) {
        val = true;
        return true;
    }
    if (str.find("n") != std::string::npos) {
        val = false;
        return true;
    }
    if (str.find("true") != std::string::npos) {
        val = true;
        return true;
    }
    if (str.find("false") != std::string::npos) {
        val = false;
        return true;
    }
    if (str.find("t") != std::string::npos) {
        val = true;
        return true;
    }
    if (str.find("f") != std::string::npos) {
        val = false;
        return true;
    }
    if (str.find("T") != std::string::npos) {
        val = true;
        return true;
    }
    if (str.find("F") != std::string::npos) {
        val = false;
        return true;
    }

    return false;
}

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

void MenuConsole::HandleInput(MenuConsole::MainMenuOptions input, AdjacencyMatrix& matrix, AdjacencyList& list)
    {
        switch (input)
        {
            case MenuConsole::MainMenuOptions::LOAD_FROM_FILE:
            {
                std::string path = "";
                std::string isDirectedStr = "";
                bool isDirected = false;

                std::cout << "Path for file: ";
                std::cin >> path;

                std::cout << "Is graph directed? [Y/N]: ";
                std::cin >> isDirectedStr;

                if(!TryParseToBool(isDirectedStr, isDirected))
                {
                    std::cout <<"Can not parse given input to bool, graph will be set as directed\n";
                }

                if(matrix.LoadDataFromFile(path, !isDirected))
                {
                    std::cout << "Data from file successfully loaded into adjacency matrix\n";
                }
                else
                {
                    std::cout << "ERROR - Something went wrong when loading data from file to adjacency matrix!\n";
                }

                if(list.LoadDataFromFile(path, !isDirected))
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
                std::cout << "Adjacency matrix:\n" << matrix.ToString();
                break;
            }
            case MenuConsole::MainMenuOptions::SHOW_LIST:
            {
                std::cout << "Adjacency list:\n" << list.ToString();
                break;
            }
            case MenuConsole::MainMenuOptions::DO_KRUSKAL:
            {
                AdjacencyMatrix kruskalMatRes = MST::KruskalAlgorithm(matrix);
                AdjacencyList kruskalListRes = MST::KruskalAlgorithm(list);

                std::cout<< "Kruskal algorithm (matrix):\n" << MST::ToString(kruskalMatRes);
                std::cout <<std::endl;
                std::cout<< "Kruskal algorithm (list):\n" << MST::ToString(kruskalListRes);

                break;
            }
            case MenuConsole::MainMenuOptions::DO_PRIMA:
            {
                AdjacencyMatrix primaMatRes = MST::PrimaAlgorithm(matrix);
                AdjacencyList primaListRes = MST::PrimaAlgorithm(list);

                std::cout<< "Prima algorithm (matrix):\n" << MST::ToString(primaMatRes);
                std::cout <<std::endl;
                std::cout<< "Prima algorithm (list):\n" << MST::ToString(primaListRes);
                break;
            }
            case MenuConsole::MainMenuOptions::DO_DIJKSTRA:
            {
                int* resMatArr = GSP::Dijkstra(matrix);
                int* resListArr = GSP::Dijkstra(list);
                std::cout << "Dijkstra algorithm (matrix):\n" << GSP::ToString(matrix, resMatArr);
                std::cout <<std::endl;
                std::cout << "Dijkstra algorithm (list):\n" << GSP::ToString(list, resListArr);
                delete[] resMatArr;
                delete[] resListArr;
                break;
            }
            case MenuConsole::MainMenuOptions::DO_BELLMAN_FORD:
            {
                int* resMatArr = GSP::BellmanFord(matrix);
                int* resListArr = GSP::BellmanFord(list);
                if(resMatArr != NULL)
                {
                    std::cout << "Bellman-Ford algorithm (matrix):\n" << GSP::ToString(matrix, resMatArr);
                    delete[] resMatArr;
                }
                else
                {
                    std::cout << "Bellman-Ford algorithm (matrix):\n" << "ERROR - Graph contains a negative cycle\n";
                }
                std::cout <<std::endl;
                if(resListArr != NULL)
                {
                    std::cout << "Bellman-Ford algorithm (list):\n" << GSP::ToString(list, resListArr);
                    delete[] resListArr;
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

