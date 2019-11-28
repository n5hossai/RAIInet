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
        bool isLinkBoosted = 0;
        bool isVisible = 0;
        bool isDownloaded = 0;
    public:
        Link(char id, int type, int strength);
        ~Link();
        //getters:
        int getRow() const; 
        int getCol() const;
        char getId() const;
        int getType() const;
        int getStrength() const;
        bool getIsLinkBoosted() const;
        bool getIsVisible()const;
        bool getIsDownloaded()const;

        //setters:
        void setRow(int row_);
        void setCol(int col_);
        void setId(char id_);
        void setType(int type_);
        void setStrength(int strength_);
        void setIsLinkBoosted(bool boolean_);
        void setIsVisible(bool boolean_);
        void setIsDownloaded(bool boolean_);

        //functions:
        std::string linkDescription(); // ex returns "a: D1" or "D1"
        void toggleType();
        void polarize();
        void scan();
        void linkBoost();
        void strengthen();
};

#endif