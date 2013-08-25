#include "statusbar.h"

StatusBar::StatusBar(QWidget * parent)
    : QStatusBar(parent)
{
    serialStatusText.setText("Serial Connection:");
    serialConnectionLost();

    this->addPermanentWidget(&serialStatusText);
    this->addPermanentWidget(&serialStatusImg);
}

void StatusBar::serialConnectionEstabilished()
{
    this->showMessage(tr("Serial Connection: ESTABILISHED"));
    serialStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::serialConnectionLost()
{
    this->showMessage(tr("Serial Connection: LOST"));
    serialStatusImg.setPixmap(QPixmap(":/images/symbols/reddot.png").scaledToHeight(20));
}
