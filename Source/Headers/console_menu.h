#pragma once
#include <string>
#include <iostream>
#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "ms_tree.h"
#include "shortest_path.h"

namespace MenuConsole
{
    enum MainMenuOptions
    {
        EXIT = 0,
        LOAD_FROM_FILE = 1,
        SHOW_MATRIX = 2,
        SHOW_LIST = 3,
        DO_KRUSKAL = 4,
        DO_PRIMA = 5,
        DO_DIJKSTRA = 6,
        DO_BELLMAN_FORD = 7,
    };

    /// @brief Some const
    const std::string LINE_SEP = "========================================\n\n";
    const std::string WRONG_INPUT = "WRONG INPUT!\n";

    /// @brief Function will try to parse given string to int
    /// @param str string to parse
    /// @param val result
    /// @return true if success, false otherwise
    bool TryParseToInt(std::string str, int& val);

    /// @brief Function will try to parse given string to bool
    /// @param str string to parse
    /// @param val result
    /// @return true if success, false otherwise
    bool TryParseToBool(std::string str, bool& val);
    
    /// @brief Function will display menu
    /// @return user input
    MainMenuOptions DisplayMainMenu();

    /// @brief Function will perform action choosen by user
    /// @param input user input
    /// @param matrix graph as matrix to perform action on
    /// @param list graph as list to perform action on
    void HandleInput(MainMenuOptions input, AdjacencyMatrix& matrix, AdjacencyList& list);
}