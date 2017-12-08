#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    mapper = new QSignalMapper(this);
    spacer = new QSpacerItem(30, 40);


    mainLayout = new QHBoxLayout(this);
    buttonLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();
    vLayout = new QVBoxLayout();
    vertikalStackLayout = new QVBoxLayout();
    stackLayout = new QStackedLayout();
    gLayout = new QGridLayout();
    //stackLayout = new QVBoxLayout();
    stack = new QPushButton("Stack");
    vertical = new QPushButton("Vertical");
    horizontal = new QPushButton("Horizontal");
    grid = new QPushButton("Grid");

    //qIntVal = new QIntValidator(0, 50, this);

    buttonLayout->addWidget(vertical);
    buttonLayout->addWidget(horizontal);
    buttonLayout->addWidget(grid);
    buttonLayout->addWidget(stack);
    buttonLayout->addItem(spacer);

    buttonExit = new QPushButton("Exit");
    connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));
    mainLayout->addWidget(buttonExit);

    edit = new QLineEdit();
    box = new QSpinBox();
    slider = new QSlider();
    label = new QLabel("Notset");
    combo = new QComboBox();

    combo->addItem("edit");
    combo->addItem("box");
    combo->addItem("slider");
    combo->hide();
    //connect(buttonExit, buttonExit->click(), this, this->close());
    //connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));

    hLayout->addWidget(edit,Qt::AlignCenter);
    hLayout->addWidget(box, Qt::AlignCenter);
    hLayout->addWidget(slider, Qt::AlignCenter);
    hLayout->addWidget(label, Qt::AlignCenter);
    vLayout->addWidget(edit, Qt::AlignCenter);
    vLayout->addWidget(box, Qt::AlignCenter);
    vLayout->addWidget(slider, Qt::AlignCenter);
    vLayout->addWidget(label, Qt::AlignCenter);
    gLayout->addWidget(edit, 0, 0);
    gLayout->addWidget(box, 0, 1);
    gLayout->addWidget(slider, 1, 0);
    gLayout->addWidget(label, 1, 1);
    vertikalStackLayout->addWidget(combo);
    vertikalStackLayout->addWidget(label);
    stackLayout->addWidget(edit);
    stackLayout->addWidget(box);
    stackLayout->addWidget(slider);
    stackLayout->setStackingMode(QStackedLayout::StackAll);

    vertikalStackLayout->addLayout(stackLayout);
    mainLayout->addLayout(hLayout, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout, Qt::AlignCenter);

    box->setRange(0, 50);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,50);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setTickInterval(3);
    slider->setSingleStep(1);
    qIntVal = new QIntValidator(0, 50, this);
    edit->setValidator(qIntVal);

    //edit->setValidator(new QIntValidator(0,50));
    label->setFrameStyle(1);
    label->setMaximumWidth(50);
    label->setAlignment(Qt::AlignHCenter);
    label->setAlignment(Qt::AlignVCenter);

   // connect(box, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    connect(box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), slider, static_cast<void(QSlider::*)(int)>(&QSlider::setValue));

    connect(slider, SIGNAL(valueChanged(int)), box, SLOT(setValue(int)));
    connect(box, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));

    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(mySlotEdit(QString)));
    connect(this, SIGNAL(mySignalEdit(int)), box, SLOT(setValue(int)));
    connect(box, SIGNAL(valueChanged(QString)), edit, SLOT(setText(QString)));

    connect(vertical, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(horizontal, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(grid, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(stack, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    mapper->setMapping(vertical, vLayout);
    mapper->setMapping(horizontal, hLayout);
    mapper->setMapping(grid, gLayout);
    mapper->setMapping(stack, vertikalStackLayout);
    connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(changeLayout(QObject*)));

    connect(combo, SIGNAL(activated(int)), stackLayout, SLOT(setCurrentIndex(int)));

    buttonExit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vertical->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    horizontal->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grid->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    stack->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
   //gLayout->setSpacing(100);
    //gLayout->setMargin(1);

    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   // box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
   // slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

}

Widget::~Widget()
{

}

void Widget::mySlotEdit(QString str){
    int n;
    n = str.toInt();
    emit mySignalEdit(n);
}

void Widget::changeLayout(QObject *pNewLayout){
    QLayoutItem* pLayout = mainLayout->itemAt(1);
    mainLayout->removeItem(pLayout);
    mainLayout->insertLayout(1, static_cast<QLayout*>(pNewLayout));

    if(pNewLayout==vertikalStackLayout)
      {
        combo->setVisible(true);
          //скрываем все элементы управления
            box->hide();
            edit->hide();
            slider->hide();
        //отображаем только текущий
            stackLayout->currentWidget()->show();
        stackLayout->setStackingMode(QStackedLayout::StackOne);
     }
     else
     {
        combo->setVisible(false);
        stackLayout->setStackingMode(QStackedLayout::StackAll);
      }

}
