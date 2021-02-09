#ifndef PIZZAAPP_H
#define PIZZAAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>

class pizzaApp : public QWidget
{
    Q_OBJECT

public:
    pizzaApp(QWidget *parent = nullptr);

private:
   void toppingChange(QListWidgetItem *item);
   void pizzaSize();
   void closeApp();
   void orderPizza();
   void clearSelection();
private:    
   QString pizzaChoice;
   QLabel* toppingsLabel;
   QLabel* nameLabel;
   QLabel* cityLabel;
   QLabel* pCodeLabel;
   QLabel* AddressLabel;
   QLabel* phoneLabel;
   QRadioButton* small;
   QRadioButton* medium;
   QRadioButton* large;
   QList<QString> listOfToppings;
   QLabel* test;
   QListWidget* count;
   QPushButton* submit;
   QPushButton* cancel;
   QPushButton* reset;
   QPushButton* order;
   QListWidget* toppingList;
   QLineEdit* customerName;
   QLineEdit* customerAddress;
   QLineEdit* customerPhone;
   QLineEdit* customerPCode;
   QLineEdit* customerCity;
   QLineEdit* customerAp;
   QMessageBox* orderLayout;
   QLabel* pizzaSizeLabel;
};
#endif
