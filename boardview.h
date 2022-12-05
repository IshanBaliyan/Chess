
// boardview.h

#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_
#include "observer.h"
#include "boardmodel.h"
#include "window.h"

class BoardView : public Observer {
    BoardModel *subject;
    Xwindow *win;
    void textDisplay();
    void graphicDisplay();

  public:
    BoardView(BoardModel *subject);
    void notify() override;
    ~BoardView();
};

#endif




