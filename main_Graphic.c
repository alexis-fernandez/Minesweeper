#include <stdio.h>
#include <stdlib.h> //header needed for srand() and rand()
#include <time.h> //header needed for time()
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>  //For importing images

/*
Sources for learning SDL:

https://en.wikibooks.org/wiki/SDL_(Simple_DirectMedia_Layer)/Basics/Creating_a_window
https://dev.to/noah11012/using-sdl2-in-c-and-with-c-too-1l72
https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
https://dev.to/noah11012/using-sdl2-drawing-rectangles-3hc2
https://forums.libsdl.org/viewtopic.php?p=38556
https://gist.github.com/armornick/3434362
*/

#define WIDTH 900
#define HEIGHT 900
#define SIZE 10
#define BOMBS 15

SDL_Rect createRect(int x, int y, int w, int h)   //Function to create a rectangle at position (x,y) with dimensions w x h. This function returns a rectangle in the SDL_Rect structure
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

void printNumber(SDL_Renderer* renderer,SDL_Texture* zero, SDL_Texture* one,SDL_Texture* two,SDL_Texture* three,SDL_Texture* four,SDL_Texture* five,SDL_Texture* six,SDL_Texture* seven,SDL_Texture* eight , SDL_Rect board[SIZE][SIZE], int adjacent, int row, int column)
{
    //This function will take the adjacent number of bombs along with the textures needed, and it will then print the png of the corresponding
    //number of bombs onto the window
    if (adjacent == 0)  
    {
        SDL_RenderCopy(renderer, zero, NULL, &board[row][column]);
    }
    else if (adjacent == 1)
    {
        SDL_RenderCopy(renderer, one, NULL, &board[row][column]);
    }
    else if (adjacent == 2)
    {
        SDL_RenderCopy(renderer, two, NULL, &board[row][column]);
    }
    else if (adjacent == 3)
    {
        SDL_RenderCopy(renderer, three, NULL, &board[row][column]);
    }
    else if (adjacent == 4)
    {
        SDL_RenderCopy(renderer, four, NULL, &board[row][column]);
    }
    else if (adjacent == 5)
    {
        SDL_RenderCopy(renderer, five, NULL, &board[row][column]);
    }
    else if (adjacent == 6)
    {
        SDL_RenderCopy(renderer, six, NULL, &board[row][column]);
    }
    else if (adjacent == 7)
    {
        SDL_RenderCopy(renderer, seven, NULL, &board[row][column]);
    }
    else if (adjacent == 8)
    {
        SDL_RenderCopy(renderer, eight, NULL, &board[row][column]);
    }
}

void fillBoard(SDL_Rect board[SIZE][SIZE])  //This function will take in the 2D board array which is initialized as a SDL_Rect, and it will create a rectangle for each of the cells that is 82x82 pixels
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = createRect(40+(i*82),60+(j*82),82, 82);  //Each cell must be 82 by 82 pixels
        }
    }
}

void printBoard(SDL_Renderer* renderer,SDL_Texture* tile_texture, SDL_Rect board[SIZE][SIZE], int keep_number[SIZE][SIZE])
{
    //This function will take in the renderer, the tile textures, the board array, and the keep_number array that keeps track of the cells that have been clicked
    //And it will then print the texture of the tiles (the png) onto each of the cells of the board array in the window 
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (keep_number[i][j] == 0)   //Only place back the tile if the cell has not been revealed yet
            {
                SDL_RenderCopy(renderer, tile_texture, NULL, &board[i][j]);     //Copying the drawing of the tiles to each 82x82 cell
            }
        }
    }
}

void placeBombs(int bomb_condition[SIZE][SIZE])  //This function takes in the 2D array bomb_condition and it will place 15 bombs in random places within the 2D array
{
    srand(time(NULL)); //time(NULL) returns a time_t object that represents the current time. Initializes random number generator. srand(time(NULL)) uses current time as seed (will always change with time)
    int random_row;
    int random_col;

    for (int i = 0; i < BOMBS; i++)
    {
        while (1)  //While true
        {
            random_row = rand() % 10;
            random_col = rand() % 10;

            if (bomb_condition[random_row][random_col] == 0)
            { 
                bomb_condition[random_row][random_col] = 1;
                break;
            }

            else  //Generate a different random position because there's a bomb in that position already
            {
                continue;
            }
        }
        
    }
    
}

void printBombs(SDL_Renderer* renderer, SDL_Texture* bomb_texture, SDL_Rect board[SIZE][SIZE], int bomb_condition[SIZE][SIZE])  
{
    //This function will take in the png for the bombs, and the board and bomb_condition arrays and it will print the bomb texture onto the board array in the window if the corresponding index in the bomb_condition array has a bomb
    for(int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {          
            if(bomb_condition[i][j] == 1)   //If there's a bomb, print the drawing of the bomb
            {
                SDL_RenderCopy(renderer, bomb_texture, NULL, &board[i][j]);
            }
        }
    }
}

int countAdjacentBombs(int bomb_condition[SIZE][SIZE], int row, int column)  
{
    int bomb_counter = 0;

    //The following nested if statements and for loops count the adjacent bombs to a cell that was clicked,
    //however avoiding incorrect counting by setting the boundaries at the edge cases so the program does not count bombs that are
    //on the other side of the board
    //It determines the adjacent bombs by checking if all of the indices that are adjacent to the inputted row and column in the bomb_condition array have a bomb and if it does, it updates a counter 

    if (row == 0)
    {
        for (int i = 0; i<=1; i++)
        {
            if (column == 0)         //Top left case
            {
                for (int j = 0; j<=1; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else if (column == 9)    //Top right case
            {
                for (int j = -1; j<=0; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else     //Case of everything in between the first and last column of the first row
            {
                for (int j = -1; j<=1; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }
            
        }
    }

    else if (row == 9)
    {
        for (int i = -1; i<=0; i++)
        {
            if (column == 0)       //Bottom left case
            {
                for (int j = 0; j<=1; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else if (column == 9)    //Bottom right case
            {
                for (int j = -1; j<=0; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else
            {
                for (int j = -1; j<=1; j++)    //Everything in between the first and last column of the last row
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }
            
        }
    }

    else  //anything in between rows 0 and 9
    {
        for (int i = -1; i<=1; i++)
        {
            if (column == 0)          //left edge of the board
            {
                for (int j = 0; j<=1; j++)
                {
                    //board[x][y] will not have an X therefore it does not matter if its checked
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else if (column == 9)     //right edge of the board
            {
                for (int j = -1; j<=0; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }

            else                //middle of the board
            {
                for (int j = -1; j<=1; j++)
                {
                    if (bomb_condition[row+i][column+j] == 1)
                    {
                        bomb_counter ++;
                    }
                }
            }
            
        }
    }

    return bomb_counter;
}

int main(int argc, char* argv[])  //char* argv[] is a common parameter for the main function in C
{

    /////////CREATING WINDOW AND RENDERER///////
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow("Minesweeper", //Title of window
                              SDL_WINDOWPOS_UNDEFINED,   //undefined x position of the window
                              SDL_WINDOWPOS_UNDEFINED,   //undefined y position of the window
                              WIDTH,    //Set width of the window
                              HEIGHT,   //Set height of the window
                              0);

    ////////////HANDLING ERRORS/////////////////////////

    if (window == NULL)
    {
        printf("Window Creation Error: %s\n", SDL_GetError());  //Print the error in the case that the window fails to create
        SDL_Quit();  //In case the window fails to create, quit the program
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //-1 is the index to acces the rendering driver that meets the flag SDL_RENDERER_ACCELERATED.
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Initialization failed: %s\n", SDL_GetError());   //Catching the error in case SDL doesnt intialize
        return 1;
    }


    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Image Initialization failed: %s\n", SDL_GetError());   //Catching the error in case SDL doesnt intialize
        return 1;
    }


    //////////TITLE SCREEN///////////////////////

    //Loading the pngs for the title screen
    SDL_Rect title_rectangle = createRect(0,0,900,900);
    SDL_Texture* title_screen_surface = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/title_screen.png" );

    SDL_Texture* playButton_surface = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/playButton.png" );
    SDL_Texture* quitButton_surface = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/quitButton.png" );

    SDL_Rect playButton_rectangle = createRect(350,500,200,75);
    SDL_Rect quitButton_rectangle = createRect(350,600,200,75);

    ///////////////////GRAPHICS FOR SECOND SCREEN//////////////////
    //For reference:
    //SDL_Rect window_rectangle = createRect(0,0,900,900);  //Rectangle for entire window
    //SDL_Rect minefield_rectangle = createRect(40,60,820,820);   //Rectangle for game area
    
    //Creating rectangles for the area around the minefield
    SDL_Rect backgroundTop_rectangle = createRect(40,0,820,60);
    SDL_Rect backgroundLeft_rectangle = createRect(0,0,40,900);
    SDL_Rect backgroundRight_rectangle = createRect(860,0,40,900);
    SDL_Rect backgroundBottom_rectangle = createRect(40,880,820,20);

    
    SDL_Rect board[SIZE][SIZE] = {0};  //Creating the array of rectangles that will be the cells in the game
    int bomb_condition [SIZE][SIZE] = {0};
    int keep_number[SIZE][SIZE] = {0};    //Separate array to keep track of cells that have already been clicked
    
    SDL_Texture* bomb_texture = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/final_bomb_drawing.png" );    //Importing the bomb drawing I created
    SDL_Texture* tile_texture = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/final_tile.png" );      //Importing the tile drawing i created

    //Loading all of the numbers  *All pngs made using GIMP*
    SDL_Texture* zero = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/0.png" );
    SDL_Texture* one = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/1.png" );
    SDL_Texture* two = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/2.png" );
    SDL_Texture* three = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/3.png" );
    SDL_Texture* four = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/4.png" );
    SDL_Texture* five = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/5.png" );
    SDL_Texture* six = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/6.png" );
    SDL_Texture* seven = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/7.png" );
    SDL_Texture* eight = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/8.png" );

    SDL_Texture* gameOver_background = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/Top_GameOver.png" );
    SDL_Texture* win_background = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/winBanner.png" );
    SDL_Texture* winning_bomb_texture = IMG_LoadTexture(renderer,"/home/alexis/MECHTRON2MP3/Assignments/Minesweeper/winningBomb.png" );

    //Catching the error in case the images are failed to initialize
    if (bomb_texture == NULL||tile_texture == NULL ||one==NULL||two==NULL||three==NULL||four==NULL||five==NULL||six==NULL||seven==NULL||eight==NULL)
    {
        printf("Image Initialization failed: %s\n", SDL_GetError());   
        return 1;
    }
    
    ////////////MAIN LOOP//////////////////
    
    SDL_Event event;
    int quit = 0;
    int screen2 = 0;
    int game_over = 0;
    int row;
    int column;
    int adjacent = -1;  //Giving it an initial value because if not, it can contain any arbitrary value in memory. This prevents errors in the code
    int hold = 0;
    int counter = 0;
    placeBombs(bomb_condition);

    while(quit == 0 && screen2 == 0)   //Keeping the window open until the user exits the window. This loop will run until the user either closes the window or clicks play and moves onto the second screen
    {
        while(SDL_PollEvent(&event))    //this loop runs as long as there are events to be processed
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
            }

            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    if (mouseX >= quitButton_rectangle.x &&              //If the user LEFT clicks on quit button rectangle, quit the program
                        mouseX <= quitButton_rectangle.x + quitButton_rectangle.w &&
                        mouseY >= quitButton_rectangle.y &&
                        mouseY <= quitButton_rectangle.y + quitButton_rectangle.h)
                        {
                            quit = 1;
                        }

                    else if (mouseX >= playButton_rectangle.x &&              //If the user LEFT clicks on play button rectangle, go to screen 2
                        mouseX <= playButton_rectangle.x + playButton_rectangle.w &&
                        mouseY >= playButton_rectangle.y &&
                        mouseY <= playButton_rectangle.y + playButton_rectangle.h)
                        {
                            screen2 = 1;
                        }
                }
            }
        }

        SDL_RenderClear(renderer);

        //Displaying the title screen
        SDL_RenderCopy(renderer, title_screen_surface, NULL, &title_rectangle);
        SDL_RenderCopy(renderer, playButton_surface, NULL, &playButton_rectangle);
        SDL_RenderCopy(renderer, quitButton_surface, NULL, &quitButton_rectangle);

        //Displaying it to the window
        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
        
    }

    while (quit == 0 && screen2 == 1)     //Creating the graphics for the second screen. This loop will run until the user closes the window
    {
        while(hold == 0)     //This loop is used to hold the window at the end game screen without allowing input from the user until the close the window
        {
            while(SDL_PollEvent(&event))    //this loop runs as long as there are events to be processed
            {
                if(event.type == SDL_QUIT)
                {
                    quit = 1;
                }

                else if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)   //If the user left clicks whithin the area of the rectangle of any of the cells, the program will show the adjacent bombs or show if they hit a bomb
                    {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        

                        for (int i = 0; i < SIZE; i++)
                        {
                            for (int j = 0; j < SIZE; j++)
                            {
                                if (mouseX >= board[i][j].x &&               
                                mouseX <= board[i][j].x + board[i][j].w &&
                                mouseY >= board[i][j].y &&
                                mouseY <= board[i][j].y + board[i][j].h)
                                {
                                    if(bomb_condition[i][j] == 1)   //If the user hits a bomb, end the game
                                    {
                                        game_over = 1;
                                    }
                                    
                                    else                           //Else, show the number of adjacent bombs
                                    {
                                        row = i;
                                        column = j;
                                        keep_number[i][j] = 1;
                                        adjacent = countAdjacentBombs(bomb_condition, row, column);
                                        continue;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }

            //This nested for loop counts how many cells have been revealed so far. The value of counter resets for every iteration of the loop
            counter = 0;
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (keep_number[i][j] == 1)   //Checking how many cells have been revealed
                    {
                        counter ++;
                    }
                }
            }

            if(game_over == 1)
            {
                SDL_SetRenderDrawColor(renderer, 49,54,58,255);  //Filling the window with a color
                SDL_RenderFillRect(renderer, &backgroundLeft_rectangle);
                SDL_RenderFillRect(renderer, &backgroundRight_rectangle);
                SDL_RenderFillRect(renderer, &backgroundBottom_rectangle);

                SDL_RenderCopy(renderer, gameOver_background, NULL, &backgroundTop_rectangle); //Display the game over banner

                fillBoard(board);
                printBoard(renderer, tile_texture, board, keep_number);    //Print the tiles onto the window
                printNumber(renderer, zero, one, two, three, four, five, six, seven, eight, board, adjacent, row, column);  //Print the adjacent number of bombs
                printBombs(renderer, bomb_texture, board, bomb_condition);  //Print the bombs
                
                SDL_UpdateWindowSurface(window);
                SDL_RenderPresent(renderer);

                hold = 1;
            }

            else if(counter == 85)  //If all of the cells that are not bombs have been revealed, the user won
            {
                SDL_SetRenderDrawColor(renderer, 49,54,58,255);  //Filling the window with a color
                SDL_RenderFillRect(renderer, &backgroundLeft_rectangle);
                SDL_RenderFillRect(renderer, &backgroundRight_rectangle);
                SDL_RenderFillRect(renderer, &backgroundBottom_rectangle);

                SDL_RenderCopy(renderer, win_background, NULL, &backgroundTop_rectangle);  //Display the win banner
                
                fillBoard(board);
                printBoard(renderer, tile_texture, board, keep_number);
                printNumber(renderer, zero, one, two, three, four, five, six, seven, eight, board, adjacent, row, column);
                printBombs(renderer, winning_bomb_texture, board, bomb_condition);   //Print the bombs if the user wins

                SDL_UpdateWindowSurface(window);
                SDL_RenderPresent(renderer);

                hold = 1;
            }

            else
            {
                SDL_SetRenderDrawColor(renderer, 49,54,58,255);  //Filling the window with a color
                SDL_RenderFillRect(renderer, &backgroundTop_rectangle);
                SDL_RenderFillRect(renderer, &backgroundLeft_rectangle);
                SDL_RenderFillRect(renderer, &backgroundRight_rectangle);
                SDL_RenderFillRect(renderer, &backgroundBottom_rectangle);

                //Print the board with the tiles and the adjacent number of bombs
                fillBoard(board);
                printBoard(renderer, tile_texture, board, keep_number);
                printNumber(renderer, zero, one, two, three, four, five, six, seven, eight, board, adjacent, row, column);

                SDL_UpdateWindowSurface(window);
                SDL_RenderPresent(renderer);
            }
        }

        while(SDL_PollEvent(&event))  //Once the game is over, the game will hold at that screen without accepting any other input from the user other than exiting the window
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    }

    //Destroying all textures used (good practice). Along with the renderer and the window used.
    SDL_DestroyTexture(bomb_texture);
    SDL_DestroyTexture(win_background);
    SDL_DestroyTexture(winning_bomb_texture);
    SDL_DestroyTexture(tile_texture);
    SDL_DestroyTexture(zero);
    SDL_DestroyTexture(one);
    SDL_DestroyTexture(two);
    SDL_DestroyTexture(three);
    SDL_DestroyTexture(four);
    SDL_DestroyTexture(five);
    SDL_DestroyTexture(six);
    SDL_DestroyTexture(seven);
    SDL_DestroyTexture(eight);
    SDL_DestroyTexture(gameOver_background);
    SDL_DestroyTexture(title_screen_surface);
    SDL_DestroyTexture(playButton_surface);
    SDL_DestroyTexture(quitButton_surface);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;

}

