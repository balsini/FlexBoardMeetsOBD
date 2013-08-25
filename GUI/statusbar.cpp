#include "statusbar.h"

StatusBar::StatusBar(QWidget * parent)
    : QStatusBar(parent)
{
    serialStatusText.setText("Serial:");
    serialConnectionLost();
    flexStatusText.setText("Flex:");
    flexConnectionLost();

    this->addPermanentWidget(&serialStatusText);
    this->addPermanentWidget(&serialStatusImg);
    this->addPermanentWidget(&flexStatusText);
    this->addPermanentWidget(&flexStatusImg);
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

void StatusBar::flexConnectionEstabilished()
{
    this->showMessage(tr("Flex Connection: ESTABILISHED"));
    flexStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::flexConnectionLost()
{
    this->showMessage(tr("Flex Connection: LOST"));
    flexStatusImg.setPixmap(QPixmap(":/images/symbols/reddot.png").scaledToHeight(20));
}
