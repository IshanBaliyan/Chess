
// boardview.h

#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_
#include "observer.h"
#include "boardmodel.h"

class BoardView : public Observer {
    BoardModel *subject;

  public:
    BoardView(BoardModel *subject);
    void notify() override;
    ~BoardView();
};

#endif




