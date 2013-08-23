#include "about.h"

About::About(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    this->setWindowTitle(tr("About"));
    this->setMinimumWidth(450);
    this->setMaximumWidth(450);
    this->setMinimumHeight(250);
    this->setMaximumHeight(250);

    aboutQt = new QLabel(this);
    //aboutQt->setMinimumSize(200,200);
    aboutQt->setPixmap(QPixmap(":/images/qt/qt_logo.png").scaledToHeight(150));

    aboutDigia = new QLabel(this);
    //aboutDigia->setMinimumSize(200,200);
    aboutDigia->setPixmap(QPixmap(":/images/qt/digia_logo.png").scaledToHeight(65));

    aboutAuthorsTitle = new QLabel(tr("Authors"), this);
    aboutAuthorsTitle->setFont(QFont("Fantasy", 20, QFont::Bold));
    aboutAuthors[0] = new QLabel(tr("Alessio Balsini"), this);
    aboutAuthors[1] = new QLabel(tr("David Librera"), this);
    for (unsigned int i=0; i<ABOUT_AUTHORS_NUM; i++)
        aboutAuthors[i]->setFont(QFont("Monospace", 14));

    aboutLayout = new QHBoxLayout();
    aboutAuthorsLayout = new QVBoxLayout();
    aboutToolsLayout = new QVBoxLayout();

    aboutAuthorsLayout->addSpacing(50);
    aboutAuthorsLayout->addWidget(aboutAuthorsTitle);
    aboutAuthorsLayout->addSpacing(15);
    aboutAuthorsLayout->addWidget(aboutAuthors[0]);
    aboutAuthorsLayout->addWidget(aboutAuthors[1]);
    aboutAuthorsLayout->addSpacing(50);
    aboutToolsLayout->addWidget(aboutQt);
    aboutToolsLayout->addWidget(aboutDigia);
    aboutLayout->addLayout(aboutAuthorsLayout);
    aboutLayout->addSpacing(70);
    aboutLayout->addLayout(aboutToolsLayout);
    this->setLayout(aboutLayout);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}
