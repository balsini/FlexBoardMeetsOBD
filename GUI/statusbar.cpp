#include "statusbar.h"

StatusBar::StatusBar(QWidget * parent)
    : QStatusBar(parent)
{
    serialStatusText.setText("Serial:");
    serialConnectionLost();
    flexStatusText.setText("Flex:");
    flexConnectionLost();

    addPermanentWidget(&serialStatusText);
    addPermanentWidget(&serialStatusImg);
    addPermanentWidget(&flexStatusText);
    addPermanentWidget(&flexStatusImg);
}

void StatusBar::serialConnectionEstabilished()
{
    showMessage(tr("Serial Connection: ESTABILISHED"));
    serialStatusImg.setPixmap(QPixmap(":/images/symbols/greendot.png").scaledToHeight(20));
}

void StatusBar::serialConnectionLost()
{
    showMessage(tr("Serial Connection: LOST. Try checking device permissions"));
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
