#include "statusbar.h"

StatusBar::StatusBar(QWidget * parent)
    : QStatusBar(parent)
{
    serialStatusText.setText("Serial:");
    serialConnectionLost();
    flexStatusText.setText("Flex:");
    flexConnectionLost();
    vehicleStatusText.setText("Vehicle:");
    vehicleConnectionLost();

    addPermanentWidget(&serialStatusText);
    addPermanentWidget(&serialStatusImg);
    addPermanentWidget(&flexStatusText);
    addPermanentWidget(&flexStatusImg);
    addPermanentWidget(&vehicleStatusText);
    addPermanentWidget(&vehicleStatusImg);
}

void StatusBar::serialConnectionEstabilished()
{
    showMessage(tr("Serial Connection: ESTABILISHED"));
    serialStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::serialConnectionLost()
{
    showMessage(tr("Serial Connection: LOST."));
    serialStatusImg.setPixmap(QPixmap(":/images/symbols/reddot.png").scaledToHeight(20));
}

void StatusBar::flexConnectionEstabilished()
{
    showMessage(tr("Flex Connection: ESTABILISHED"));
    flexStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::flexConnectionLost()
{
    showMessage(tr("Flex Connection: LOST"));
    flexStatusImg.setPixmap(QPixmap(":/images/symbols/reddot.png").scaledToHeight(20));
}
void StatusBar::vehicleConnectionEstabilished()
{
    showMessage(tr("Vehicle Connection: ESTABILISHED"));
    vehicleStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::vehicleConnectionLost()
{
    showMessage(tr("Vehicle Connection: LOST"));
    vehicleStatusImg.setPixmap(QPixmap(":/images/symbols/reddot.png").scaledToHeight(20));
}
