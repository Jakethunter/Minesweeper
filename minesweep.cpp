#include <iostream>
#include <random>
#include <vector>

class tile {
    public:
        char apperance = '#';
        bool hasbomb = 0;
        int value = 0;
        int bombcount;
};


class grid {
    public:
        int width;
        int height;
        int bombs;
        std::random_device rs;    
        std::mt19937 gen{rs()}; 
        std::uniform_int_distribution<int> xdist;
        std::uniform_int_distribution<int> ydist;

        std::vector<std::vector<tile>> field;


        void printfield(){
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    std::cout << field[i][j].apperance << " ";
                }
                std::cout << '\n';
            }   
            std::cout << '\n';
        }
        int revealspot(){
            int x;
            int y;
            std::cout << "enter x";
            std::cin >> x;
            std::cout << "enter y";
            std::cin >> y;
            std::cout << '\n';
            x -= 1;
            y -= 1;
            if (field[y][x].value >= 9)
            {
                std::cout << "mine exploded!";
                return 1;
            } else {
                field[y][x].apperance =  field[y][x].value + '0';
                printfield();
                return 0;
            }       
        }
        void setBombs(){
            for (int i = 0; i < bombs;) {
                int x = xdist(gen);
                int y = ydist(gen);
               if (field[y][x].hasbomb == 0) {
                field[y][x].hasbomb = 1;
                field[y][x].value = 9;
                //chopped
                if(x != 0){
                    field[y][x - 1].value += 1;
                }
                if(x != width - 1){
                    field[y][x + 1].value += 1;
                }
                 if(y != 0){
                    field[y - 1][x].value += 1;
                }
                 if(y != height - 1){
                    field[y + 1][x].value += 1;
                }
                if(x != 0 && y != 0){
                    field[y - 1][x - 1].value += 1;
                }
                if(x != width - 1 && y != 0){
                    field[y - 1][x + 1].value += 1;
                }
                if(x != 0 && y != height - 1){
                    field[y + 1][x - 1].value += 1;
                }
                if(x != width - 1 && y != height - 1){
                    field[y + 1][x + 1].value += 1;
                }
                i++;
               }
            }
            
        }


    grid(int w, int h, int bombcount) : xdist(0, w - 1), ydist(0, h -1) {
        height = h;
        width = w;
        field = std::vector<std::vector<tile>>(h, std::vector<tile>(w));
        bombs = bombcount;
    }

};


int main() {
    int localwidth;
    int localheight;
    int bombcount;
    std::cout << "set field height: ";
    std::cin >> localheight;
    std::cout << "set field width: ";
    std::cin >> localwidth;
    std::cout << "set field bomb amount: ";
    std::cin >> bombcount;
    grid mainGrid(localwidth, localheight, bombcount);
    mainGrid.printfield();
    mainGrid.setBombs();

    while (mainGrid.revealspot() == 0){}
    
    return 0;
}