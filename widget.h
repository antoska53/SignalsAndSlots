#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QSpinBox>
//#include <QSlider>

#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include<QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QSignalMapper>
#include <QComboBox>
#include <QStackedLayout>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QPushButton* buttonExit;// = new QPushButton("Exit", this);
    QPushButton* vertical;
    QPushButton* horizontal;
    QPushButton* grid;
    QPushButton* stack;
    QVBoxLayout* buttonLayout;
    QHBoxLayout* mainLayout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QVBoxLayout* vertikalStackLayout;
    QStackedLayout* stackLayout;
    QGridLayout* gLayout;
    QSignalMapper* mapper;
    QLineEdit* edit;
    QSpinBox* box;
    QSlider* slider;
    QLabel* label;
    QComboBox* combo;
    QSpacerItem* spacer;
    QIntValidator* qIntVal;
signals:
    void mySignalEdit(int);
public slots:
    void mySlotEdit(QString);
    void changeLayout(QObject* pNewLayout);

};

#endif // WIDGET_H
