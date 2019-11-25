#ifndef LINK_H
#define LINK_H
#include <string>

class Link{
    private:
        int row; 
        int col;
        char id;
        int type;
        int strength;
        bool isLinkBoosted;
        bool isVisible;
        bool isDownloaded;
    public:
        Link(char id, int type, int strength);
        ~Link();
        //getters
        int getRow(); 
        int getCol();
        char getId();
        int getType();
        int getStrength();
        bool getIsLinkBoosted();
        bool getIsVisible();
        bool getIsDownloaded();

        std::string linkDescription(); // ex returns "a: D1" or "D1"
        void toggleType();
        void polarize();
        void scan();
        void linkBoost();
        void setStrength(int strength);
};

#endif