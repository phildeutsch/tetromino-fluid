int insert_tetro(int lattice[], string tetro[], int position, 
    int orientation, string type);

int delete_tetro(int lattice[], string tetro[], int position, 
    string type);

int translate_tetro(int lattice[], string tetro[], string type);

int rotate_tetro(int lattice[], string tetro[]);

int switch_tetro(int lattice[], string tetro[]);

int change_tetro(int lattice[], string tetro[]);

int performStep(int lattice[], string tetro[], double pot, 
    string type);
