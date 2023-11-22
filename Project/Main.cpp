//Problem: Place N queens in such a manner on an NxN chess board that no queens attack
//         each other by being in the same row, column and diagonal.
//
//Pseudo Code: 
//         board[N][N] = {0}
//
//         function isSafe(row,col):
//            check if there is no queen in the same column:
//                  for i = 0 to row - 1 do:
//                      if board[i][col] = 1 do:
//                          return false
//            check if there is no queen in the same upper - left diagonal:
//                  for i = row - 1, j = col - 1 to 0,0 do:
//                      if board[i][col] = 1 do :
//                          return false
//            check if there is no queen in the same upper - right diagonal:
//                  for i = row - 1, j = col + 1 to 0, N - 1 do:
//                      if board[i][col] = 1 do :
//                          return false
//            return true if the queen is safe
//
//        function Solve(row):
//                  if row = N do:
//                      return 
//                  for col = 0 to N - 1 do:
//                      if isSafe(row,col) = 1 do:
//                          place queen in the board[row][col] and move to the next row:
//                               board[row][col] = 1
//                               Solve(row+1)
//                          backtrack if no solution found:
//                               board[row][col] = 0

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

void DrawChessBoard(SDL_Renderer*& renderer, int N, int rateSize);
void AddQueen(SDL_Renderer*& renderer, int rateSize, int x, int y);
void RemoveQueen(SDL_Renderer*& renderer, int rateSize, int x, int y);
bool IsSafe(std::vector<std::vector<int>>& board, int N, int row, int col);
void printSolution(SDL_Renderer*& renderer, int rateSize, std::vector<std::vector<int>>& board, int N);
bool Solve(SDL_Renderer*& renderer, SDL_Event& e, int rateSize, int& speed, std::vector<std::vector<int>>& board, int N, int row);

void DrawChessBoard(SDL_Renderer*& renderer, int N, int rateSize)
{
    bool isWhite = false;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            SDL_Rect rect = { x * rateSize, y * rateSize, rateSize, rateSize };
            if (isWhite)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            isWhite = !isWhite;
        }
        if (N % 2 == 0)
            isWhite = !isWhite;
    }
    SDL_RenderPresent(renderer);
}

void AddQueen(SDL_Renderer*& renderer, int rateSize, int x, int y)
{
    SDL_Surface* queenSurface = IMG_Load("C:/Users/ADMIN/OneDrive/Desktop/Project/Queen.png");
    SDL_Texture* queenTexture = SDL_CreateTextureFromSurface(renderer, queenSurface);
    SDL_Rect queenRect = { x * rateSize, y * rateSize, rateSize, rateSize };
    SDL_RenderCopy(renderer, queenTexture, NULL, &queenRect);
    SDL_RenderPresent(renderer);
}

void RemoveQueen(SDL_Renderer*& renderer, int rateSize, int x, int y)
{
    SDL_Rect rect = { x * rateSize, y * rateSize, rateSize, rateSize };
    if ((x + y) % 2 == 0)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void printSolution(SDL_Renderer*& renderer, int rateSize, std::vector<std::vector<int>>& board, int N)
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            std::cout << board[row][col] << "  ";
            if (board[row][col])
                AddQueen(renderer, rateSize, col, row);
            else
                RemoveQueen(renderer, rateSize, col, row);
        }
        std::cout << "\n\n";
    }
}

bool IsSafe(std::vector<std::vector<int>>& board, int N, int row, int col)
{
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;
    return true;
}

bool Solve(SDL_Renderer*& renderer, SDL_Event& e, int rateSize, int& speed, std::vector<std::vector<int>>& board, int N, int row)
{
    if (row >= N)
        return true;
    for (int col = 0; col < N; col++) 
    {
        while(SDL_PollEvent(&e) != 0)
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                speed = 0;
        if (IsSafe(board, N, row, col)) 
        {
            if (speed > 0)
            {
                AddQueen(renderer, rateSize, col, row);
                SDL_Delay(speed);
            }
            board[row][col] = 1;
            if (Solve(renderer, e, rateSize, speed, board, N, row + 1))
                return true;
            if (speed > 0)
            {
                RemoveQueen(renderer, rateSize, col, row);
                SDL_Delay(speed);
            }
            board[row][col] = 0;
        }
    }
    return false;
}

int main(int argc, char* argv[]) 
{
    std::cout << "Pham Ngoc Do - 22022154\n\n";
    int rateSize = 80;
    bool quit = false;
    int speed;
    bool solutionExist;
    int N;
    std::cout << "Input size of board (NxN): ";
    std::cin >> N;
    while (N < 0) 
    {
        std::cout << "Try again with N > 0: ";
        std::cin >> N;
    }
    std::cout << "Input running speed (ms): ";
    std::cin >> speed;
    std::cout << "Double clicking the left mouse button to skip solving process\n";
    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Solving N-queens Simulator", 700, SDL_WINDOWPOS_CENTERED, rateSize * N, rateSize * N, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;
    DrawChessBoard(renderer, N, rateSize);

    while (!quit)
    {
        solutionExist = Solve(renderer, e, rateSize, speed, board, N, 0);
        if (!solutionExist)
        {
            quit = true;
            std::cout << "No solution exists";
            return 0;
        }
        else
        {
            std::cout << "Solution is:\n";
            printSolution(renderer, rateSize, board, N);
            SDL_Delay(10000);
            quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}