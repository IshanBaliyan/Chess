// boardview.cc
#include "boardview.h"
#include <string>
using namespace std;

BoardView::BoardView(BoardModel *subject) :  subject{subject} {
    subject->attach(this);
}
void BoardView::notify(){
    //TODO: [INSERT CODE THAT WILL COUT CURRENT BOARD AS TEXT]
    
    // TODO: [INSERT CODE THAT WILL DISPLAY CURRENT BOARD TO GRAPHIC DISPLAY]
}
BoardView::~BoardView(){
    subject->detach(this);
}


