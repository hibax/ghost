
#ifndef GHOSTINTHECELL_ENTITY_H
#define GHOSTINTHECELL_ENTITY_H


enum OWNER {ME, OPPONENT, NEUTRAL};

class Entity {
public:
    Entity(int id, OWNER owner);


private:
    int id;
    OWNER owner;
};


#endif //GHOSTINTHECELL_ENTITY_H
