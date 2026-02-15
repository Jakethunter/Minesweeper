#include <iostream>
#include <random>
#include <vector>

class tile {
    public:
        char apperance = '#';
        bool hasbomb = 0;
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
        }
        void setBombs(){
            //grab random coordinates
            //check if coordinates are a bomb
            //if no set it to a bomb
            //if it is then dont increase i. 
            for (int i = 0; i < bombs;) {
                int x = xdist(gen);
                int y = ydist(gen);
               if (field[y][x].hasbomb == 0)
               {
                field[y][x].hasbomb = 1;
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
    mainGrid.printfield();
    return 0;
}