#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <random>
#include <fstream>

using namespace std;
//structs
struct Point {
    double x;
    double y;
};
struct User {
    string name;
    int score;
    int bomb;
    int laser;
};
//global declaration
SDL_Renderer* rend;
SDL_Window* window;
SDL_Event e;
const int max_dim = 20 ;
const double PI = 3.14159265358979323846;
vector < vector <int> > balls(15, vector<int>(12));
vector < vector <int> > fallingBalls(15, vector<int>(12));
int amounts[6];
int removingBalls[max_dim][12];
int ballQueue[2] = {0};
int themes = 0;
int volumeLevel[5] = {0,25,50,75,100};
unsigned int v = 4;
int timeStart, timeEnd, totalTime;
Point movingBall;
Point dst;
int mouseX, mouseY;
int step =0;
vector<int> arr;
int t =0 ;
bool succ ;
int temp_i = 8 ,temp_j ;
int max_i = 8;
bool up=false;
bool strt = false ;
int m =0 ;
double beginY = 0;
double vx, vy;
int frame = 1;
int seconds = 50;
int score = 0;
int endPoint = 0;

//textures
SDL_Texture* ball_1_tex = NULL;
SDL_Texture* ball_2_tex = NULL;
SDL_Texture* ball_3_tex = NULL;
SDL_Texture* ball_4_tex = NULL;
SDL_Texture* ball_5_tex = NULL;
SDL_Texture* ball_6_tex = NULL;
SDL_Texture* cannon_tex = NULL;
SDL_Texture* cannon_laser_tex = NULL;
SDL_Texture* main_menu_tex = NULL;
SDL_Texture* settings_menu_tex = NULL;
SDL_Texture* themes_menu_tex = NULL;
SDL_Texture* modes_menu_tex = NULL;
SDL_Texture* enter_user_tex = NULL;
SDL_Texture* info_tex = NULL;
SDL_Texture* score_board_tex = NULL;
SDL_Texture* game_bg_tex = NULL;
SDL_Texture* pause_button_tex = NULL;
SDL_Texture* timer_tex = NULL;
SDL_Texture* pause_menu_tex = NULL;
SDL_Texture* user_info_tex = NULL;
SDL_Texture* win_tex = NULL;
SDL_Texture* lose_tex = NULL;
SDL_Texture* main_menu_d_tex = NULL;
SDL_Texture* settings_menu_d_tex = NULL;
SDL_Texture* themes_menu_d_tex = NULL;
SDL_Texture* modes_menu_d_tex = NULL;
SDL_Texture* enter_user_d_tex = NULL;
SDL_Texture* info_d_tex = NULL;
SDL_Texture* score_board_d_tex = NULL;
SDL_Texture* game_bg_d_tex = NULL;
SDL_Texture* pause_button_d_tex = NULL;
SDL_Texture* timer_d_tex = NULL;
SDL_Texture* pause_menu_d_tex = NULL;
SDL_Texture* user_info_d_tex = NULL;
SDL_Texture* win_d_tex = NULL;
SDL_Texture* lose_d_tex = NULL;
SDL_Texture* bomb_tex = NULL;
SDL_Texture* pop_f1_tex = NULL;
SDL_Texture* pop_f2_tex = NULL;
SDL_Texture* pop_f3_tex = NULL;
SDL_Texture* pop_f4_tex = NULL;
SDL_Texture* pop_f5_tex = NULL;
SDL_Texture* explosion_f1_tex =NULL;
SDL_Texture* explosion_f2_tex =NULL;
SDL_Texture* explosion_f3_tex =NULL;
SDL_Texture* explosion_f4_tex =NULL;
SDL_Texture* explosion_f5_tex =NULL;



//music and sfx
Mix_Chunk* button;
Mix_Chunk* pop;
Mix_Chunk* success;
Mix_Chunk* lose;
Mix_Chunk* laser;
Mix_Chunk* bomb;
Mix_Music* bg_music1;
Mix_Music* bg_music2;



//rects
SDL_Rect background_rect;
SDL_Rect ball_rect;
SDL_Rect cannon_rect;
SDL_Rect pause_rect;
SDL_Rect timer_rect;
SDL_Rect explosion_rect;


//functions declaration
void Cannon( double x, double y, SDL_Renderer* renderer );
void generateBalls();
void printBall(SDL_Renderer* rend, int type, int x, int y);
void printBalls(SDL_Renderer* rend, double beginY);
void shootBall(int type, SDL_Renderer* renderer);
void checkandRemove(int i, int j);
int x_linear(int i, double d);
bool putBall(int i , int j );
Point add_ball(double d);
double mouseAngle(double x, double y);
void fallingCheck();
bool rightCon(int i, int j);
bool upCon(int i , int j);
void bombEffect(int i, int j);
void ballChecker();
int nextBall();
void printVector();
void clearFallingVector();
vector<string> explodeStr(const string &s, const char &d);
vector<User> readFromFile(string fileName);
void writeToFile(vector<User> users, string filename);
int findUser(vector<User> users, string user);
bool compareByScore(User a, User b);
vector<User> sortUserVector(vector<User> users);
void textRGBA2(SDL_Renderer*m_renderer, int x, int y, const char* text,int f_size,int r, int g, int b, int a);
User addUser(string username);
void popAnimation(SDL_Renderer* renderer, int frame, int x, int y);
void explosionAnimation(SDL_Renderer* renderer, int frame, int x, int y);
void ballsPop(SDL_Renderer* renderer, int frame);
void fallingBallsAnim(SDL_Renderer* renderer, int frame);
void clearFallingArray();
void laserEffect(double d);
void laserAnimation(SDL_Renderer* renderer, int frame, double d);
void findEndPoint();

//boolians
bool running = true;
bool main_menu = true;
bool settings_menu = false;
bool gameMode1 = false;
bool gameModeTime = false;
bool selectMode_menu = false;
bool enterUser = false;
bool pause_menu = false;
bool score_board = false;
bool info = false;
bool selectTheme_menu = false;
bool volume = true;
bool shoot_ball = false;
bool bomb_power = false;
bool laser_power = false;
bool lose_menu = false;
bool win_menu = false;
bool character = false;
bool user_info = false;
bool timer = false;
bool animStart = false;
bool laserAnim = false;




int main(int argc, char* argv[]) {
    //window
    SDL_Init (SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow ("Bubble Master", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720,850 , 0);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer (win, -1, render_flags);
    //loading textures
    ball_1_tex = IMG_LoadTexture(rend, "Ball1.png");
    ball_2_tex = IMG_LoadTexture(rend, "Ball2.png");
    ball_3_tex = IMG_LoadTexture(rend, "Ball3.png");
    ball_4_tex = IMG_LoadTexture(rend, "Ball4.png");
    ball_5_tex = IMG_LoadTexture(rend, "Ball5.png");
    ball_6_tex = IMG_LoadTexture(rend, "Ball6.png");
    cannon_tex = IMG_LoadTexture(rend,"Cannon.png");
    cannon_laser_tex = IMG_LoadTexture(rend,"CannonLaser.png");
    main_menu_tex = IMG_LoadTexture(rend, "MainMenu.png");
    settings_menu_tex = IMG_LoadTexture(rend, "SettingsMenu.png");
    themes_menu_tex = IMG_LoadTexture(rend, "ThemesMenu.png");
    modes_menu_tex = IMG_LoadTexture(rend,"ModesMenu.png");
    pause_menu_tex = IMG_LoadTexture(rend, "PauseMenu.png");
    enter_user_tex = IMG_LoadTexture(rend,"EnterUser.png");
    info_tex = IMG_LoadTexture(rend,"Info.png");
    score_board_tex = IMG_LoadTexture(rend, "ScoreBoard.png");
    game_bg_tex = IMG_LoadTexture(rend, "GameBG.png");
    pause_button_tex = IMG_LoadTexture(rend, "PauseButton.png");
    timer_tex = IMG_LoadTexture(rend, "Timer.png");
    user_info_tex = IMG_LoadTexture(rend, "UserInfo.png");
    win_tex = IMG_LoadTexture(rend, "Win.png");
    lose_tex = IMG_LoadTexture(rend, "Lose.png");
    main_menu_d_tex = IMG_LoadTexture(rend, "MainMenuD.png");
    settings_menu_d_tex = IMG_LoadTexture(rend, "SettingsMenuD.png");
    themes_menu_d_tex = IMG_LoadTexture(rend, "ThemesMenuD.png");
    modes_menu_d_tex = IMG_LoadTexture(rend,"ModesMenuD.png");
    pause_menu_d_tex = IMG_LoadTexture(rend, "PauseMenuD.png");
    enter_user_d_tex = IMG_LoadTexture(rend,"EnterUserD.png");
    info_d_tex = IMG_LoadTexture(rend,"InfoD.png");
    score_board_d_tex = IMG_LoadTexture(rend, "ScoreBoardD.png");
    game_bg_d_tex = IMG_LoadTexture(rend, "GameBGD.png");
    pause_button_d_tex = IMG_LoadTexture(rend, "PauseButtonD.png");
    timer_d_tex = IMG_LoadTexture(rend, "TimerD.png");
    user_info_d_tex = IMG_LoadTexture(rend, "UserInfoD.png");
    win_d_tex = IMG_LoadTexture(rend, "WinD.png");
    lose_d_tex = IMG_LoadTexture(rend, "LoseD.png");
    bomb_tex = IMG_LoadTexture(rend, "Bomb.png");
    pop_f1_tex = IMG_LoadTexture(rend, "PopAniF1.png");
    pop_f2_tex = IMG_LoadTexture(rend, "PopAniF2.png");
    pop_f3_tex = IMG_LoadTexture(rend, "PopAniF3.png");
    pop_f4_tex = IMG_LoadTexture(rend, "PopAniF4.png");
    pop_f5_tex = IMG_LoadTexture(rend, "PopAniF5.png");
    explosion_f1_tex = IMG_LoadTexture(rend, "ExpAniF1.png");
    explosion_f2_tex = IMG_LoadTexture(rend, "ExpAniF2.png");
    explosion_f3_tex = IMG_LoadTexture(rend, "ExpAniF3.png");
    explosion_f4_tex = IMG_LoadTexture(rend, "ExpAniF4.png");
    explosion_f5_tex = IMG_LoadTexture(rend, "ExpAniF5.png");



    //loading sounds
    button = Mix_LoadWAV("Button.wav");
    pop = Mix_LoadWAV("Pop.wav");
    success = Mix_LoadWAV("Success.wav");
    lose = Mix_LoadWAV("Lose.wav");
    laser = Mix_LoadWAV("Laser.wav");
    bomb = Mix_LoadWAV("Bomb.wav");
    bg_music1 = Mix_LoadMUS("BGMusic1.mp3");
    bg_music2 = Mix_LoadMUS("BGMusic2.mp3");


    //init rects
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.h = 850;
    background_rect.w = 720;
    pause_rect.x = 26;
    pause_rect.y = 25;
    pause_rect.h = 100;
    pause_rect.w = 133;
    timer_rect.x = 587;
    timer_rect.y = 25;
    timer_rect.h = 100;
    timer_rect.w = 133;


    //balllls
    generateBalls();
    ballChecker();
    movingBall.x = 396;
    movingBall.y = 850;
    ballQueue[1] = nextBall();
    ballQueue[0] = nextBall();
    //file managements
    vector<User> players = readFromFile("UsersAndScores.txt");
    vector<User> sortedPlayers;
    string username;
    int userNum;



    Mix_PlayMusic(bg_music1,-1);
    //main loop
    while (running) {

        while (main_menu){
            SDL_RenderCopy(rend,(themes == 1) ? main_menu_d_tex : main_menu_tex,NULL,&background_rect);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    main_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 253 && e.button.x <= 467 ) {
                            if (e.button.y >= 456 && e.button.y <= 548 ) {
                                Mix_PlayChannel(-1,button,0);
                                enterUser = true;
                                main_menu = false;
                                break;
                            }
                            if (e.button.y >= 573 && e.button.y <= 662) {
                                Mix_PlayChannel(-1,button,0);
                                settings_menu = true;
                                main_menu = false;

                                break;
                            }
                            if (e.button.y >= 689 && e.button.y <= 779) {
                                Mix_PlayChannel(-1,button,0);
                                running = false;
                                main_menu = false;
                                break;
                            }
                        }
                        if (e.button.y >= 689 && e.button.y <= 779 ) {
                            if (e.button.x >= 80 && e.button.x <= 170 ) {
                                Mix_PlayChannel(-1,button,0);
                                sortedPlayers = sortUserVector(players);
                                score_board = true;
                                main_menu = false;
                                break;
                            }
                            if (e.button.x >= 553 && e.button.x <= 642) {
                                Mix_PlayChannel(-1,button,0);
                                info = true;
                                main_menu = false;
                                break;
                            }

                        }
                    }
                }

            }
        }
        while (settings_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? settings_menu_d_tex : settings_menu_tex,NULL,&background_rect);
            boxRGBA(rend,328,290,328+(v*43),313,222,241,213,255);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    settings_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 484 && e.button.y <= 577 ) {
                                Mix_PlayChannel(-1,button,0);
                                selectTheme_menu = true;
                                settings_menu = false;
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                settings_menu = false;
                                main_menu = true;

                                break;
                            }
                        }
                        if (e.button.y >= 370 && e.button.y <= 442 ) {
                            if (e.button.x >= 219 && e.button.x <= 285 ) {
                                if (volume) {
                                    Mix_VolumeMusic(0);
                                    volume = false;
                                    v = 0;
                                }
                                else if (!volume) {
                                    Mix_VolumeMusic(100);
                                    volume = true;
                                    v = 4;
                                }


                            }
                            if (e.button.x >= 327 && e.button.x <= 393) {
                                Mix_VolumeMusic(volumeLevel[v--]);

                                break;
                            }
                            if (e.button.x >= 431 && e.button.x <= 499) {
                                Mix_VolumeMusic(volumeLevel[v++]);

                                break;
                            }

                        }
                    }
                }

            }
        }
        while (selectTheme_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? themes_menu_d_tex : themes_menu_tex,NULL,&background_rect);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    selectTheme_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 351 && e.button.y <= 441 ) {
                                Mix_PlayChannel(-1,button,0);
                                themes = 0;
                                break;
                            }
                            if (e.button.y >= 484 && e.button.y <= 577 ) {
                                Mix_PlayChannel(-1,button,0);
                                themes = 1;
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                selectTheme_menu = false;
                                settings_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
        }
        while (selectMode_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? modes_menu_d_tex : modes_menu_tex,NULL,&background_rect);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    selectTheme_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 351 && e.button.y <= 441 ) {
                                Mix_PlayChannel(-1,button,0);
                                gameMode1 = true;
                                selectMode_menu = false;
                                timeStart = time(NULL);
                                break;
                            }
                            if (e.button.y >= 484 && e.button.y <= 577 ) {
                                Mix_PlayChannel(-1,button,0);
                                gameMode1 = true;
                                gameModeTime = true;
                                selectMode_menu = false;
                                timeStart = time(NULL);
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                selectMode_menu = false;
                                enterUser = true;

                                break;
                            }
                        }

                    }
                }

            }
        }
        while (enterUser) {
            SDL_RenderCopy(rend,(themes == 1) ? enter_user_d_tex : enter_user_tex,NULL,&background_rect);
            int ch;
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    enterUser = false;
                    break;
                }
                if (e.type == SDL_KEYDOWN) {
                    ch = e.key.keysym.sym;
                    character = true;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 484 && e.button.y <= 577 ) {
                                userNum = findUser(players, username);
                                Mix_PlayChannel(-1,button,0);
                                user_info = true;
                                enterUser = false;
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                enterUser = false;
                                main_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
            if(ch != 8 && username.length()<25 && character) {
                username += ch;
                character = false;
            }
            else if (ch == 8 && character) {
                username.pop_back();
                character = false;
            }
            if(username != "")
                textRGBA2(rend,148,366,username.c_str(),50,3,86,95,255);
            SDL_RenderPresent(rend);
        }
        while (user_info) {
            SDL_RenderCopy(rend, (themes == 1) ? user_info_d_tex : user_info_tex, NULL, &background_rect);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                    user_info = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if (e.button.x >= 252 && e.button.x <= 468) {
                            if (e.button.y >= 484 && e.button.y <= 577) {
                                Mix_PlayChannel(-1, button, 0);
                                selectMode_menu = true;
                                user_info = false;
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1, button, 0);
                                user_info = false;
                                enterUser = true;
                                if (userNum == -1) {
                                    players.pop_back();
                                }
                                username = "";
                                break;
                            }
                        }

                    }
                }

            }
            if ( userNum == -1 ) {
                players.push_back(addUser(username));
                userNum = players.size()-1;
            }
            textRGBA2(rend,300,133,players[userNum].name.c_str(), 30, 222, 241, 213, 255);
            textRGBA2(rend,300,276,to_string(players[userNum].score).c_str(), 30, 222, 241, 213, 255);
            textRGBA2(rend,300,430,to_string(players[userNum].bomb).c_str(), 20, 222, 241, 213, 255);
            textRGBA2(rend,400,430,to_string(players[userNum].laser).c_str(), 20, 222, 241, 213, 255);
            SDL_RenderPresent(rend);
        }

        while (score_board) {
            SDL_RenderCopy(rend,(themes == 1) ? score_board_d_tex : score_board_tex,NULL,&background_rect);

            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    score_board = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                score_board = false;
                                main_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
            for (int i = 0; i < sortedPlayers.size(); ++i) {
                textRGBA2(rend,182,183+(i*44),sortedPlayers[i].name.c_str(),20,222, 241, 213, 255);
                textRGBA2(rend,385,183+(i*44),to_string(sortedPlayers[i].score).c_str(),20,222, 241, 213, 255);
            }
            SDL_RenderPresent(rend);
        }
        while (info) {
            SDL_RenderCopy(rend,(themes == 1) ? info_d_tex : info_tex,NULL,&background_rect);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    info = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                info = false;
                                main_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
        }
        while (gameMode1) {
            //ballChecker();
            beginY+= 0.05;
            cout<<endPoint;
            findEndPoint();
            timeEnd = time(NULL);

            if ( (endPoint+1)*62 + beginY == 700 || seconds == 0) {
                gameMode1 = false;
                lose_menu = true;
                break;
            }
            if ( amounts[5] == 0 ) {
                gameMode1 = false;
                win_menu = true;
                break;
            }

            //cout<<nextBall(counter)<<" "<<ballQueue[0]<<endl;
            SDL_RenderCopy(rend, (themes == 1) ? game_bg_d_tex : game_bg_tex,NULL,&background_rect);
            textRGBA2(rend, 562, 800, to_string(players[userNum].bomb).c_str(), 15, 222, 241, 213, 255);
            textRGBA2(rend, 654, 800, to_string(players[userNum].laser).c_str(), 15, 3,86,95,255);
            while (SDL_PollEvent(&e) != 0 && !shoot_ball) {
                if (e.type == SDL_QUIT) {
                    running = false;
                    gameMode1 = false;
                    break;
                }
                if (e.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    break;
                }
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_r) {
                        int tmp = ballQueue[1];
                        ballQueue[1] = ballQueue[0];
                        ballQueue[0] = tmp;
                        break;

                    }
                    else if (e.key.keysym.sym == SDLK_b) {
                        if (players[userNum].bomb!=0) {
                            players[userNum].bomb--;
                            bomb_power = true;
                        }

                    }
                    else if (e.key.keysym.sym == SDLK_l) {
                        if (players[userNum].laser!=0) {
                            players[userNum].laser--;
                            laser_power = true;
                        }

                    }

                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if (e.button.x >= 26 && e.button.x <= 130 && e.button.y >= 26 && e.button.y <= 111) {
                            pause_menu = true;
                            gameMode1 = false;
                            break;
                        }
                        else {
                            if (laser_power){
                                Mix_PlayChannel(-1,laser,0);
                                laserEffect(mouseAngle(mouseX,mouseY));
                                fallingCheck();
                                step =0 ;
                                ballQueue[1] = ballQueue[0];
                                ballQueue[0] = nextBall();
                                ballChecker();
                                laser_power = false;
                                laserAnim = true;
                                break;
                            }
                                shoot_ball = true;
                                dst = add_ball(mouseAngle(mouseX, mouseY));
                                double d = mouseAngle(mouseX, mouseY);
                                vy = -abs(5 * sin(atan(abs(d))));
                                vx = (d / abs(d)) * 5 * cos(atan(abs(d)));
                                printVector();
                                break;

                        }
                    }
                }
            }
            if (shoot_ball && bomb_power) {
                shootBall(7, rend);
                if(movingBall.y > dst.y-10 &&movingBall.y < dst.y+10 ) {
                    Mix_PlayChannel(-1,bomb,0);
                    shoot_ball = false;
                    animStart = true;
                    movingBall.x = 396;
                    movingBall.y = 850;
                    bombEffect(temp_i,temp_j);
                    fallingCheck();
                    step =0 ;
                    ballQueue[1] = ballQueue[0];
                    ballQueue[0] = nextBall();
                    ballChecker();
                }
            }
            else if (shoot_ball) {
                shootBall(ballQueue[1], rend);
                if(movingBall.y > dst.y-10 &&movingBall.y < dst.y+10 ) {
                    Mix_PlayChannel(-1,pop,0);
                    shoot_ball = false;
                    balls[temp_i][temp_j] = ballQueue[1];
                    movingBall.x = 396;
                    movingBall.y = 850;
                    SDL_Delay(10);
                    checkandRemove(temp_i,temp_j);
                    animStart = true;
                    fallingCheck();
                    step =0 ;
                    ballQueue[1] = ballQueue[0];
                    ballQueue[0] = nextBall();
                    ballChecker();
                }
            }
            Cannon(mouseX, mouseY, rend);
            printBalls(rend,beginY);
            if (bomb_power) {
                printBall(rend, 7, 396, 844);
            }
            else if (laser_power) {

            }
            else {
                printBall(rend, ballQueue[1], 396, 844);
            }
            if (animStart && bomb_power) {
                explosionAnimation(rend,frame,dst.x,dst.y);
                fallingBallsAnim(rend, frame);
                frame++;
                if ( frame == 5 ) {
                    animStart = false;
                    bomb_power = false;
                    frame = 1;
                    clearFallingArray();
                    clearFallingVector();
                }
            }
            else if (laserAnim) {
                laserAnimation(rend, frame, mouseAngle(mouseX, mouseY));
                fallingBallsAnim(rend, frame);
                frame++;
                if ( frame == 5 ) {
                    laserAnim = false;
                    frame = 1;
                    clearFallingArray();
                    clearFallingVector();
                }
            }
            else if (animStart) {
                ballsPop(rend,frame);
                fallingBallsAnim(rend, frame);
                frame++;
                if ( frame == 5 ) {
                    animStart = false;
                    frame = 1;
                    clearFallingArray();
                    clearFallingVector();
                }
            }
            printBall(rend, ballQueue[0], 184, 844);
            SDL_RenderCopy(rend,(themes == 1) ? pause_button_d_tex : pause_button_tex,NULL,&pause_rect);
            if (gameModeTime) {
                seconds = 50 - (timeEnd-timeStart);
                SDL_RenderCopy(rend, (themes == 1) ? timer_d_tex : timer_tex, NULL, &timer_rect);
                textRGBA2(rend,607,35, to_string(seconds).c_str(), 50, 222, 241, 213, 255);

            }
            SDL_RenderPresent(rend);
            SDL_Delay(10);




        }
        while (win_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? win_d_tex : win_tex,NULL,&background_rect);
            Mix_PlayChannel(-1,success,0);
            players[userNum].bomb += 2;
            players[userNum].laser += 2;
            textRGBA2(rend, 286, 287, to_string(score).c_str(), 50, 222, 241, 213, 255);
            players[userNum].score = (players[userNum].score < score) ? score : players[userNum].score;
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                    win_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                win_menu = false;
                                main_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
        }
        while (lose_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? lose_d_tex : lose_tex,NULL,&background_rect);
            Mix_PlayChannel(-1,lose,0);
            textRGBA2(rend, 286, 287, to_string(score).c_str(), 50, 222, 241, 213, 255);
            SDL_RenderPresent(rend);
            seconds = 50;
            players[userNum].score = (players[userNum].score < score) ? score : players[userNum].score;
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    lose_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                lose_menu = false;
                                main_menu = true;

                                break;
                            }
                        }

                    }
                }

            }
        }
        while (pause_menu) {
            SDL_RenderCopy(rend,(themes == 1) ? pause_menu_d_tex : pause_menu_tex,NULL,&background_rect);
            boxRGBA(rend,328,290,328+(v*43),313,222,241,213,255);
            SDL_RenderPresent(rend);
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT) {
                    running = false;
                    pause_menu = false;
                    break;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if ( e.button.x >= 252 && e.button.x <= 468 ) {
                            if (e.button.y >= 484 && e.button.y <= 577 ) {
                                Mix_PlayChannel(-1,button,0);
                                gameMode1 = true;
                                pause_menu = false;
                                break;
                            }
                            if (e.button.y >= 617 && e.button.y <= 711) {
                                Mix_PlayChannel(-1,button,0);
                                pause_menu = false;
                                main_menu = true;
                                generateBalls();
                                clearFallingArray();
                                balls[9] = {0}; balls[10] = {0}; balls[11] = {0}; balls[12] = {0}; balls[13] = {0}; balls[14] = {0};
                                beginY = 0;
                                max_i = 8;
                                up=false;
                                strt = false ;
                                m = 0 ;

                                break;
                            }
                        }
                        if (e.button.y >= 370 && e.button.y <= 442 ) {
                            if (e.button.x >= 219 && e.button.x <= 285 ) {
                                if (volume) {
                                    Mix_VolumeMusic(0);
                                    volume = false;
                                    v = 0;
                                }
                                else if (!volume) {
                                    Mix_VolumeMusic(100);
                                    volume = true;
                                    v = 4;
                                }


                            }
                            if (e.button.x >= 327 && e.button.x <= 393) {
                                Mix_VolumeMusic(volumeLevel[v--]);

                                break;
                            }
                            if (e.button.x >= 431 && e.button.x <= 499) {
                                Mix_VolumeMusic(volumeLevel[v++]);

                                break;
                            }

                        }
                    }
                }

            }
        }

    }
    writeToFile(players, "UsersAndScores.txt");
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}

//functions
void Cannon( double x, double y, SDL_Renderer* renderer ) {
    int cannon_dim;
    SDL_Point center = {108,108};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    cannon_rect.h = 216;
    cannon_rect.w = 216;
    cannon_rect.y = 700;
    cannon_rect.x = 252;
    double d =-( 850.0 - y ) / ( 360.0 - x );
    double deg = atan2( 850.0 - y, 360.0 - x ) * 180 / PI;
    if ( d > 0 ) {
        thickLineRGBA(renderer, 360, 814, 720, 850 - (360*d),10, 255, 255, 255, 100);
        if ( 0 < 850 - (360*d) && 850 > 850 - (360*d)) {
            thickLineRGBA(renderer, 720, 850 - (360*d), 0, 850 - 2*(360*d),10, 255, 255, 255, 100);
        }
    }
    else if ( d < 0 ) {
        thickLineRGBA(renderer, 360, 814, 0, 850 - (360*(-d)),10, 255, 255, 255, 100);
        if ( 0 < 850 - abs(360*d) && 850 > 850 - abs(360*d)) {
            thickLineRGBA(renderer, 0, 850 - abs(360*d), 720, 850 - abs(2*(360*d)),10, 255, 255, 255, 100);
        }

    }
    SDL_RenderCopyEx(renderer, (laser_power) ? cannon_laser_tex:cannon_tex, NULL, &cannon_rect,deg-90 , &center, flip);

}
//******************************************************
void generateBalls() {
    srand(time(NULL));
    int randInput;
    for (int i = 1; i <= 8; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 1; j <= 10; ++j) {
                randInput = rand();
                if ( randInput%30 == 23 )
                    balls[i][j] = 6;
                else
                    balls[i][j] = (randInput%30+1)/6+1;
            }
        }
        else {
            for (int j = 1; j <= 9; ++j) {
                randInput = rand();
                if ( randInput%30 == 14 )
                    balls[i][j] = 6;
                else
                    balls[i][j] = (randInput%30+1)/6+1;
            }
        }

    }
}
//******************************************************
void printBall(SDL_Renderer* rend, int type, int x, int y) {


    int ball_dim;
    SDL_QueryTexture (ball_1_tex, NULL, NULL, &ball_dim, &ball_dim);


    ball_rect.h = ball_dim;
    ball_rect.w = ball_dim;
    ball_rect.x = x-ball_dim;
    ball_rect.y = y-ball_dim;
    if ( type == 1 ) {
        SDL_RenderCopy(rend, ball_1_tex, NULL, &ball_rect);
    }
    else if ( type == 2 ) {
        SDL_RenderCopy(rend, ball_2_tex, NULL, &ball_rect);
    }
    else if ( type == 3 ) {
        SDL_RenderCopy(rend, ball_3_tex, NULL, &ball_rect);
        //SDL_RenderPresent(rend);
    }
    else if ( type == 4 ) {
        SDL_RenderCopy (rend, ball_4_tex, NULL, &ball_rect);
        //SDL_RenderPresent(rend);
    }
    else if ( type == 5 ) {
        SDL_RenderCopy(rend, ball_5_tex, NULL, &ball_rect);
        //SDL_RenderPresent(rend);
    }
    else if ( type == 6 ) {
        SDL_RenderCopy(rend, ball_6_tex, NULL, &ball_rect);
        //SDL_RenderPresent(rend);
    }
    else if ( type == 7 ) {
        SDL_RenderCopy(rend, bomb_tex, NULL, &ball_rect);
        //SDL_RenderPresent(rend);
    }
    //SDL_RenderPresent(rend);


}
//******************************************************
void printBalls(SDL_Renderer* rend, double beginY) {
    for (int i = 1; i <= max_i; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 1; j <= 10; ++j) {
                printBall(rend, balls[i][j], 70+((j-1)*72), beginY+double((i-1)*62));
                //filledCircleRGBA(rend, 70+(j*72), beginY+(i*62), 36, 255,0,0,255);
            }
        }
        else {
            for (int j = 1; j <= 9; ++j) {
                printBall(rend, balls[i][j], 106+((j-1)*72), beginY+double((i-1)*62));
                //filledCircleRGBA(rend, 106+(j*72), beginY+(i*62), 36, 255,0,0,255);
            }
        }

    }
}
//******************************************************
void shootBall(int type, SDL_Renderer* renderer) {
    movingBall.x += vx;
    if( ( movingBall.x < 72 ) || ( movingBall.x > 720 ) )
    {
        vx *= -1;
        movingBall.x += vx;
    }
    movingBall.y += vy;
    printBall(renderer, type, movingBall.x, movingBall.y);
//cout<<d;
}
//******************************************************
double mouseAngle(double x, double y) {
    double d;
    return d =-( 850.0 - y ) / ( 361.0 - x );
}
//******************************************************
int x_linear(int i,double d)
{
    //cout<<d;
    double x ;
    double y = 62.0 *  (i-1) + 36.0 + beginY ;
    x =(850.0-y)/d + 360.0;
    //cout<<y<<" "<<x;
    int e = floor(x/720);
    //cout<<e;
    if(e%2==0)
        return int(x)%720;

    else
        return 720 -(int(x)%720+720)%720;
}
//******************************************************
Point add_ball(double d)
{
    for(int i = max_i   ; i > 0 ; i--) {
        int x = x_linear(i+1,d);
        int col ;
        if( i%2 == 0) {
            col = x/72 +1 ;
        }
        else {
            col = (x-36) /72  + 1;
        }
        if(putBall(i+1 , col)&&balls[i+1][col]<=0) {
            temp_j = col ;
            temp_i = i+1 ;
            Point dst;
            i % 2 == 1 ? dst.x = 72 * col : dst.x = 72*col - 36 ;
            dst.y = 36 + 62*i + beginY;
            if(i+1>max_i)
                max_i = i+1 ;
            return dst;
        }
    }
}
//******************************************************
bool putBall(int i , int j )
{

    if (i%2 == 1) {
        if (balls[i-1][j]>0||balls[i-1][j-1]>0||balls[i+1][j]>0||balls[i+1][j-1]>0)
            return true ;
    }
    else {
        if (balls[i-1][j]>0||balls[i-1][j+1]>0||balls[i+1][j]>0||balls[i+1][j+1]>0)
            return true ;
    }
    return false ;

}
//******************************************************
void checkandRemove(int i, int j)// Note :  after calling this function , reset the value of step to 0 .
{
    int score_now = int( 5 * 5/(((beginY)-0)/36 + 1));
    int  temp = balls[i][j];
    if(step>1) {
        balls[i][j] = 0;
        removingBalls[i][j] = 1;
    }
    if(balls[i][j+1]==temp) {
        step ++;
        balls[i][j] = 0;
        removingBalls[i][j] = 1;
        checkandRemove(i,j+1);
    }
    if(balls[i][j-1]==temp) {
        step ++;
        balls[i][j] = 0;
        removingBalls[i][j] = 1;
        checkandRemove(i,j-1);
    }
    if(i%2==1) {
        if(balls[i-1][j]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i-1,j);
        }
        if(balls[i-1][j-1]==temp) {
            step ++;
            balls[i][j]= 0;
            removingBalls[i][j] = 1;
            checkandRemove(i-1,j-1);
        }
        if(balls[i+1][j]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i+1,j);
        }
        if(balls[i+1][j-1]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i+1,j-1);
        }

    }
    else {
        if(balls[i-1][j]==temp) {
            step ++;
            balls[i][j]= 0;
            removingBalls[i][j] = 1;
            checkandRemove(i-1,j);
        }
        if(balls[i-1][j+1]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i-1,j+1);
        }
        if(balls[i+1][j]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i+1,j);
        }
        if(balls[i+1][j+1]==temp) {
            step ++;
            balls[i][j] = 0;
            removingBalls[i][j] = 1;
            checkandRemove(i+1,j+1);
        }

    }
    if(step==1) {
        removingBalls[i][j] = 0;
        balls[i][j]= temp;
        return;
    }
    //put your function here
}
//******************************************************
void fallingCheck()
{
    int score_now = int( 5 * 5/(((beginY)-72)/36 + 1));
    for(int  i= 2 ; i<=max_i ; i++) {
        for (int j = 1; j <= 10; j++) {
            if (balls[i][j] <= 0) {
                strt= false;
                up =false;
                m=0;
            }
            else {
                if(!strt) {
                    strt =true ;
                    m = j;
                }
                if(!up)
                    up = upCon(i, j);
                if(!rightCon(i,j)&&!up) {
                    for(int z = m ; z <= j ; z++) {
                        fallingBalls[i][z] = balls[i][z];
                        balls[i][z] =0 ;
                        score += score_now;
                    }
                    up = false;
                    m = 0;
                    strt = false ;
                }
            }
        }
        up = false;
        strt = false;
    }
}
bool rightCon(int i, int j) {
    if(balls[i][j+1] > 0)
        return true;
    return false;
}
bool upCon(int i , int j) {
    if(balls[i-1][j]>0)
        return true;
    if(i%2==0){
        if(balls[i-1][j+1]>0)
            return true ;
    }
    else
    {
        if(balls[i-1][j-1]>0)
            return true ;
    }
    return false ;
}
//******************************************************
void ballChecker() {
    amounts[0] = 0;
    amounts[1] = 0;
    amounts[2] = 0;
    amounts[3] = 0;
    amounts[4] = 0;
    amounts[5] = 0;
    for (int i = 1; i <= max_i; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 1; j <= 10; ++j) {
                if (balls[i][j] == 1)
                    amounts[0]++;
                else if (balls[i][j] == 2)
                    amounts[1]++;
                else if (balls[i][j] == 3)
                    amounts[2]++;
                else if (balls[i][j] == 4)
                    amounts[3]++;
                else if (balls[i][j] == 5)
                    amounts[4]++;
            }
        }
        else {
            for (int j = 1; j <= 9; ++j) {
                if (balls[i][j] == 1)
                    amounts[0]++;
                else if (balls[i][j] == 2)
                    amounts[1]++;
                else if (balls[i][j] == 3)
                    amounts[2]++;
                else if (balls[i][j] == 4)
                    amounts[3]++;
                else if (balls[i][j] == 5)
                    amounts[4]++;
            }
        }

    }
    int sum = amounts[0] + amounts[1] + amounts[2] + amounts[3] + amounts[4];
    amounts[5] = sum;
    cout<<sum;
}
//******************************************************
int nextBall(){
    int total = amounts[5];
    int range1 = (amounts[0]*1000)/total;
    int range2 = (amounts[1]*1000)/total;
    int range3 = (amounts[2]*1000)/total;
    int range4 = (amounts[3]*1000)/total;
    int range5 = (amounts[4]*1000)/total;
    random_device rd;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<> dis(0, 1);
    double r = dis(rng);
    int randInput = r*1000;
    if (randInput >= 0 && randInput <= range1)
        return 1;
    else if (randInput >= range1+1 && randInput <= range1+range2)
        return 2;
    else if (randInput >= range1+range2+1 && randInput <= range1+range2+range3)
        return 3;
    else if (randInput >= range1+range2+range3+1 && randInput <= range1+range2+range3+range4)
        return 4;
    else if (randInput >= range1+range2+range3+range4+1 && randInput <= range1+range2+range3+range4+range5+100)
        return 5;
}
//******************************************************
void printVector() {
    for (int i = 0; i < 15; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 0; j < 12; ++j) {
                cout<<balls[i][j]<<" ";
            }
        }
        else {
            for (int j = 0; j < 12; ++j) {
                cout<<balls[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

void clearFallingVector() {
    for (int i = 0; i < 15; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 0; j < 12; ++j) {
                fallingBalls[i][j] = 0;
            }
        }
        else {
            for (int j = 0; j < 12; ++j) {
                fallingBalls[i][j] = 0;
            }
        }
    }
}
//******************************************************
vector<string> explodeStr(const string &s, const char &d){
    vector<string> sv;
    string g = "";
    for(auto ch:s)
        if(ch!=d){
            g+=ch;
        }
        else{
            sv.push_back(g);
            g="";
        }
    if(g.length()!=0)
        sv.push_back(g);
    return sv;
}
//******************************************************
vector<User> readFromFile(string fileName){
    vector<User> vec;
    ifstream in(fileName);
    if(in.good())
    {
        //cout<<"open";
        while(!in.eof())
        {
            string s;
            getline(in,s);
            //cout<<s<<endl;
            if(in.good() && !s.empty())
            {
                vector<string> sv= explodeStr(s,',');
                User st;
                st.name=sv[0];
                st.score=stoi(sv[1]);
                st.bomb=stoi(sv[2]);
                st.laser=stoi(sv[3]);
                vec.push_back(st);
            }
        }
        in.close();
    }
    return vec;
}
//******************************************************
void writeToFile(vector<User> users, string fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (User user : users) {
            file << user.name << "," << user.score << "," << user.bomb << "," << user.laser << "\n";
        }
        file.close();
    }
}
//******************************************************
bool compareByScore(User a, User b) {
    return a.score > b.score;
}
//******************************************************
vector<User> sortUserVector(vector<User> users) {
    vector<User> sorted_users = users;
    sort(sorted_users.begin(), sorted_users.end(), compareByScore);
    return sorted_users;
}
//******************************************************
int findUser(vector<User> users, string user) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].name == user) {
            return i;
        }
    }
    return -1;
}
//******************************************************
void textRGBA2(SDL_Renderer*m_renderer, int x, int y, const char* text,int f_size,int r, int g, int b, int a)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("ARLRDBD.ttf", f_size);
    int textWidth, textHeight;
    TTF_SizeText(font, text, &textWidth, &textHeight);

    SDL_Rect rectText{x, y, 0, 0};
    Uint8 rr = r;    Uint8 gg = g;    Uint8 bb = b;    Uint8 aa = a;
    SDL_Color color{rr,gg,bb,aa};

    SDL_Surface *textSur = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textTex = SDL_CreateTextureFromSurface(m_renderer, textSur);
    SDL_FreeSurface(textSur);
    SDL_QueryTexture(textTex, nullptr, nullptr, &rectText.w, &rectText.h);
    SDL_RenderCopy(m_renderer, textTex, nullptr, &rectText);
    SDL_DestroyTexture(textTex);
    TTF_CloseFont(font);
}
//******************************************************
User addUser(string username) {
    User newUser;
    newUser.name = username;
    newUser.score = 0;
    newUser.bomb = 2;
    newUser.laser = 2;
    return newUser;
}
//******************************************************
void popAnimation(SDL_Renderer* renderer, int frame, int x, int y){
    ball_rect.h = 72;
    ball_rect.w = 72;
    ball_rect.x = x-72;
    ball_rect.y = y-72;
    if ( frame == 1 )
        SDL_RenderCopy(renderer,pop_f1_tex,NULL,&ball_rect);
    else if ( frame == 2 )
        SDL_RenderCopy(renderer,pop_f2_tex,NULL,&ball_rect);
    else if ( frame == 3 )
        SDL_RenderCopy(renderer,pop_f3_tex,NULL,&ball_rect);
    else if ( frame == 4 )
        SDL_RenderCopy(renderer,pop_f4_tex,NULL,&ball_rect);
    else if ( frame == 5 )
        SDL_RenderCopy(renderer,pop_f5_tex,NULL,&ball_rect);
    SDL_Delay(15);
}

void explosionAnimation(SDL_Renderer* renderer, int frame, int x, int y){
    explosion_rect.h = 216;
    explosion_rect.w = 216;
    explosion_rect.x = x-108;
    explosion_rect.y = y-108;
    if ( frame == 1 )
        SDL_RenderCopy(renderer,explosion_f1_tex,NULL,&explosion_rect);
    else if ( frame == 2 )
        SDL_RenderCopy(renderer,explosion_f2_tex,NULL,&explosion_rect);
    else if ( frame == 3 )
        SDL_RenderCopy(renderer,explosion_f3_tex,NULL,&explosion_rect);
    else if ( frame == 4 )
        SDL_RenderCopy(renderer,explosion_f4_tex,NULL,&explosion_rect);
    else if ( frame == 5 )
        SDL_RenderCopy(renderer,explosion_f5_tex,NULL,&explosion_rect);
    SDL_Delay(15);
}

void ballsPop(SDL_Renderer* renderer, int frame){

    int score_now = int( 5 * 5/(((beginY)-72)/36 + 1));
    for (int k = 0; k < max_i; ++k) {
        for (int l = 0; l < 12; ++l) {
            if ( removingBalls[k][l] == 1 ) {
                score += score_now;
                if ( k%2 != 0 ) {
                    popAnimation(renderer, frame, 70+((l-1)*72), beginY+double((k-1)*62));
                    }
                else {
                    popAnimation(renderer, frame, 106+((l-1)*72), beginY+double((k-1)*62));
                }

            }
        }
    }
}

void fallingBallsAnim(SDL_Renderer* renderer, int frame){
    for (int i = 1; i <= max_i; ++i) {
        if ( i%2 != 0 ) {
            for (int j = 1; j <= 10; ++j) {
                printBall(renderer, fallingBalls[i][j], 70+((j-1)*72), 50*frame + beginY+double((i-1)*62));
            }
        }
        else {
            for (int j = 1; j <= 9; ++j) {
                printBall(renderer, fallingBalls[i][j], 106+((j-1)*72), 50*frame + beginY+double((i-1)*62));
            }
        }

    }




}
void clearFallingArray(){
    for (int k = 0; k < max_i; ++k) {
        for (int l = 0; l < 12; ++l) {
            removingBalls[k][l]=0;
        }
    }
}

void bombEffect(int i, int j) {
    balls[i][j+1] =0;
    balls[i][j-1] =0;
    balls[i-1][j] =0;
    balls[i+1][j] =0;
    if(i%2==0) {
        balls[i+1][j+1] =0;
        balls[i-1][j+1] =0;
    }
    else {
        balls[i+1][j-1] =0;
        balls[i-1][j-1] =0;
    }
}

void laserEffect(double d) {
    for (int i = 9; i > 0; i--) {
        int x = x_linear(i , d);
        cout<<x<<endl;
        int col;
        if (i % 2 == 0) {
            col = (x - 36) / 72 + 1;
        }
        else {
            col = x / 72 + 1;
        }
        balls[i][col] = 0;
    }
}
void laserAnimation(SDL_Renderer* renderer, int frame, double d) {
    if ( d > 0 ) {
        thickLineRGBA(renderer, 360, 814, 720, 850 - (360*d),5*frame, 255, 0, 0, 100);
    }
    else if ( d < 0 ) {
        thickLineRGBA(renderer, 360, 814, 0, 850 - (360*(-d)),5*frame, 255, 0, 0, 100);
    }
    SDL_Delay(15);

}
void findEndPoint(){
    for (int i =14; i >=1 ; --i) {
        for (int j = 1; j <=10 ; ++j) {
            if(balls[i][j]>0){
                endPoint = i;
                return;
            }
        }
    }
}