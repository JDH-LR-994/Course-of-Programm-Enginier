//Класс отвечающий за каждую клетку на поле
class Cell{
    public:
    //Параметры отвечающие за состояние клетки
    bool is_opened, is_mine;
    int number_of_mines_arround;
    //Конструктор для создания клетки
    Cell(int arround_mines = 0, bool mine = false, bool opened = false) {
        number_of_mines_arround = arround_mines;   
        is_opened = opened;
        is_mine = mine;
    }
};
