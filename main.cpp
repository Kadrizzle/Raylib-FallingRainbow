#include <raylib.h>
#include <stdlib.h> //used for the rand() function
#include <vector>

//----------------------------Beginning of functions----------------------------

bool colorCompare(Color colorOne, Color colorTwo){
    bool same = true;
    if(colorOne.r == colorTwo.r &&
        colorOne.g == colorTwo.g &&
        colorOne.b == colorTwo.b &&
        colorOne.a == colorTwo.a){
        same = true;
    } 
    else{
        same = false;
    }  
    return same;
}

//------------------------------End of functions--------------------------------

int main() 
{
    //DrawRectangle(x,y,width,height,color)
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 1000;

    float timer = 0.0f;
    int fallingHeight = 0;
    int randomNum;
    int randomX = 0;
    int previousX = 0;
    bool drawnOnScreenOnce = false;
    bool rainbowAtBottomScreen = false;

    //randomColors will be the array used for the next colors that will pop up on the screen
    Color randomColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, DARKBLUE, DARKPURPLE, BLACK, DARKGREEN};

    //previousColors holds the colors that should stay on the screen after the falling animation is done
    Color previousColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, DARKBLUE, DARKPURPLE, BLACK, DARKGREEN};
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, DARKBLUE, DARKPURPLE, BLACK, DARKGREEN};
    int colorArraySize = sizeof(colors) / sizeof(colors[0]);
    
    InitWindow(screenWidth, screenHeight, "Falling Rainbow");
    SetTargetFPS(60);

//------------------------------------Beginning of logic------------------------------------

    while (!WindowShouldClose())
    {

        float deltaTime = GetFrameTime();
        timer += deltaTime;

        if(fallingHeight >= 1000){ //If the animated rainbow (randomColors list) hits the bottom of the screen
            rainbowAtBottomScreen = true;
            fallingHeight = 0;
            drawnOnScreenOnce = true;
            for(int i = 0; i < colorArraySize; i++){
                previousColors[i] = randomColors[i];
            }
        }
        if(rainbowAtBottomScreen == true){

            //Compare the first position of randomColors array to the previousColors array
            while(colorCompare(randomColors[0], previousColors[0]) == true){
                randomNum = GetRandomValue(0, 9);
                randomColors[0] = colors[randomNum];
            }

            //If randomColors at the ith position is equal to the previous color
            //OR randomColors at the ith position is equal to previousColors at the ith position
            //then keep looping and generating random numbers until this is false
            for(int i = 1; i < colorArraySize; i++){
                while(colorCompare(randomColors[i], randomColors[i - 1]) == true || colorCompare(randomColors[i], previousColors[i]) == true){
                    randomNum = GetRandomValue(0, 9);
                    randomColors[i] = colors[randomNum];
                }
            }
        }
            rainbowAtBottomScreen = false;

        if(timer >= 0.02f){
            fallingHeight += 5;
            timer -= 0.02f;
        }

//-----------------------------------End of logic-----------------------------------

//-----------------------------------Begin Drawing----------------------------------

        BeginDrawing();
            ClearBackground(WHITE);

            if(drawnOnScreenOnce){
                //display the previous falling rainbow fully on screen
                for(int i = 0; i < colorArraySize; i++){
                    DrawRectangle(previousX, 0, 100, 1000, previousColors[i]);
                    previousX += 100;
                }
                if(previousX >= 900){
                    previousX = 0;
                }
            }
            //Falling rainbow animation
            for(int i = 0; i < colorArraySize; i++){
                DrawRectangle(randomX, 0, 100, fallingHeight, randomColors[i]);
                randomX += 100;
            }
            if(randomX >= 900){
                randomX = 0;
            }

        EndDrawing();
    }
    
//----------------------------------End drawing-------------------------------------

    CloseWindow();
}
