
#ifndef GHOSTINTHECELL_WRITER_H
#define GHOSTINTHECELL_WRITER_H


#include <vector>
#include "Action.h"

class Writer {
public:

    static void debug(std::string log);
    static std::string actionsOutput(const std::vector<Action> &actions);

private:
    Writer() = default;
};



#endif //GHOSTINTHECELL_WRITER_H
