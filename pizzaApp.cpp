#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "pizzaApp.h"

pizzaApp::pizzaApp(QWidget *parent) : QWidget(parent)
{

    submit = new QPushButton("Submit");
    cancel = new QPushButton("Cancel");
    reset = new QPushButton("Reset Toppings");
    order = new QPushButton("Order");

    orderLayout = new QMessageBox();
    orderLayout->setDefaultButton(order);
    orderLayout->addButton(order, QMessageBox::AcceptRole);
    orderLayout->addButton("Cancel", QMessageBox::RejectRole);

    QFrame* lineUserInfo = new QFrame;
    lineUserInfo->setFrameShape(QFrame::HLine);
    QFrame* lineToppings = new QFrame;
    lineToppings->setFrameShape(QFrame::HLine);

    QLabel* userLabel = new QLabel("<b>Fill the Delivery Information Bellow:</b>");
    QLabel* pizzaInfoLabel = new QLabel("<b>Choose Pizza Size and Toppings:</b>");
    toppingsLabel = new QLabel("<b>Choose Pizza Toppings (3 Maximum):</b>");
    userLabel->setStyleSheet("Font : 12pt");
    pizzaInfoLabel->setStyleSheet("Font : 12pt");
    toppingsLabel->setStyleSheet("Font : 10pt");

    QHBoxLayout * hlayout = new QHBoxLayout();
    QHBoxLayout * submitAndCancel = new QHBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();
    QVBoxLayout * pizzaSize = new QVBoxLayout();
    QVBoxLayout * ToppingsAndButtons = new QVBoxLayout();

    small = new QRadioButton("Small (4'')");
    medium = new QRadioButton("Medium (8'')");
    large = new QRadioButton("Large (16'')");
    small->setStyleSheet("Font : 10pt");
    medium->setStyleSheet("Font : 10pt");
    large->setStyleSheet("Font : 10pt");

    QFormLayout* userInfo = new QFormLayout();
    nameLabel = new QLabel("*Name:");
    cityLabel = new QLabel("*City:");
    pCodeLabel = new QLabel("*Postal Code");
    AddressLabel = new QLabel("*Street Address:");
    phoneLabel = new QLabel("*Phone:");
    customerName = new QLineEdit();
    customerPhone = new QLineEdit();
    customerAddress = new QLineEdit();
    customerCity = new QLineEdit();
    customerPCode = new QLineEdit();
    customerAp = new QLineEdit();
    QLabel * customerinfo = new QLabel("All options with <b>*</b> are required");
    userInfo->addRow(nameLabel, customerName);
    userInfo->addRow(phoneLabel, customerPhone);
    userInfo->addRow(AddressLabel, customerAddress);
    userInfo->addRow("Apartment/Suit (Optional):", customerAp);
    userInfo->addRow(cityLabel, customerCity);
    userInfo->addRow(pCodeLabel, customerPCode);
    userInfo->addRow(customerinfo);


    userInfo->setSpacing(9);

    toppingList = new QListWidget();
    toppingList->addItem("Ham");
    toppingList->addItem("Pepperoni");
    toppingList->addItem("Green Pepper");
    toppingList->addItem("Mushroom");
    toppingList->addItem("Pineapples");
    toppingList->addItem("Onions");
    toppingList->addItem("Artichokes");
    toppingList->addItem("Black Olives");
    toppingList->addItem("Extra Cheese");
    toppingList->setSelectionMode(QAbstractItemView::NoSelection);


    pizzaSizeLabel = new QLabel("<b>Pizza Size:<\b> ");
    pizzaSizeLabel->setStyleSheet("Font : 10pt");
    pizzaSize->insertWidget(0, pizzaSizeLabel, 0, Qt::AlignTop);
    pizzaSize->addWidget(small);
    pizzaSize->addWidget(medium);
    pizzaSize->addWidget(large);
    pizzaSize->addStretch(10);
    pizzaSize->setSpacing(30);


    ToppingsAndButtons->addWidget(toppingsLabel);
    ToppingsAndButtons->addWidget(toppingList);
    ToppingsAndButtons->addWidget(reset);


    hlayout->addLayout(pizzaSize);
    hlayout->addLayout(ToppingsAndButtons);

    submitAndCancel->addWidget(cancel);
    submitAndCancel->addWidget(submit);

    vLayout->addWidget(userLabel);
    vLayout->addWidget(lineUserInfo);
    vLayout->addLayout(userInfo);
    vLayout->addWidget(pizzaInfoLabel);
    vLayout->addWidget(lineToppings);
    vLayout->addLayout(hlayout);
    vLayout->addLayout(submitAndCancel);
    count = new QListWidget();

    connect(small, &QAbstractButton::toggled, this, &pizzaApp::pizzaSize);
    connect(medium, &QAbstractButton::toggled, this, &pizzaApp::pizzaSize);
    connect(large, &QAbstractButton::toggled, this, &pizzaApp::pizzaSize);

    connect(reset, &QPushButton::clicked, this, &pizzaApp::clearSelection);
    connect(submit, &QPushButton::clicked, this, &pizzaApp::orderPizza);
    connect(order, &QPushButton::clicked, this, &pizzaApp::closeApp);
    connect(cancel, &QPushButton::clicked, this, &pizzaApp::closeApp);

    setLayout(vLayout);
}

void pizzaApp::closeApp(){
    close();
}

void pizzaApp::pizzaSize(){

    QListWidgetItem * tmp = toppingList->item(8);
    if(large->isChecked())
    {
     pizzaChoice = "Large";
     toppingList->item(8)->setSelected(false);
     tmp->setHidden(true);
    }
    else if(small->isChecked())
    {
     tmp->setHidden(false);
     pizzaChoice = "Small";
    }
    else
    {
     tmp->setHidden(false);
     pizzaChoice = "Medium";
    }
    toppingList->setSelectionMode(QAbstractItemView::MultiSelection);
}

void pizzaApp::clearSelection(){
    toppingList->clearSelection();

}

void pizzaApp::orderPizza(){

    QList<QListWidgetItem*> tempList;
    tempList = toppingList->selectedItems();
    auto bold = QFont();
    bold.setBold(true);
    auto notBold = QFont();
    notBold.setBold(false);

    if(customerName->text().length() < 4)
    {
        nameLabel->setStyleSheet("QLabel { color : rgb(102, 102, 150) }");
        nameLabel->setFont(bold);
        customerName->setStyleSheet("QLineEdit {background-color:rgb(192, 192, 255) }");
    }
    else
    {

        nameLabel->setStyleSheet("QLabel { color : black }");
        nameLabel->setFont(notBold);
        customerName->setStyleSheet("QLineEdit {background-color : white }");
    }
    if(customerPhone->text().length() < 10)
    {
        phoneLabel->setStyleSheet("QLabel { color : rgb(102, 102, 150) }");
        phoneLabel->setFont(bold);
        customerPhone->setStyleSheet("QLineEdit {background-color:rgb(192, 192, 255) }");
    }
    else
    {
        phoneLabel->setStyleSheet("QLabel { color : black; }");
        phoneLabel->setFont(notBold);
        customerPhone->setStyleSheet("QLineEdit {background-color: white }");
    }
    if(customerAddress->text().length() < 6)
    {
        AddressLabel->setStyleSheet("QLabel { color : rgb(102, 102, 150) }");
        AddressLabel->setFont(bold);
        customerAddress->setStyleSheet("QLineEdit {background-color:rgb(192, 192, 255) }");
    }
    else
    {

        AddressLabel->setStyleSheet("QLabel { color : black; }");
        AddressLabel->setFont(notBold);
        customerAddress->setStyleSheet("QLineEdit {background-color:white) }");
    }
    if(customerCity->text().length() < 4)
    {
        cityLabel->setStyleSheet("QLabel { color : rgb(102, 102, 150) }");
        cityLabel->setFont(bold);
        customerCity->setStyleSheet("QLineEdit {background-color:rgb(192, 192, 255) }");
    }
    else
    {
        cityLabel->setStyleSheet("QLabel { color : black; }");
        cityLabel->setFont(notBold);
        customerCity->setStyleSheet("QLineEdit {background-color:white) }");
    }
    if(customerPCode->text().length() < 4)
    {
        pCodeLabel->setStyleSheet("QLabel { color : rgb(102, 102, 150) }");
        pCodeLabel->setFont(bold);
        customerPCode->setStyleSheet("QLineEdit {background-color:rgb(192, 192, 255) }");
    }
    else
    {
        pCodeLabel->setStyleSheet("QLabel { color : black; }");
        pCodeLabel->setFont(notBold);
        customerPCode->setStyleSheet("QLineEdit {background-color:white }");
    }
    if(tempList.length()>3)
    {
        toppingsLabel->setStyleSheet("QLabel { Font: 10pt; color : red }");
    }
    else
       toppingsLabel->setStyleSheet("QLabel { Font: 10pt; color : black }");

    if(small->isChecked() == false && medium->isChecked() == false && large->isChecked() == false)
    {
        pizzaSizeLabel->setStyleSheet("QLabel { Font: 10pt ; color : red }");
    }
    else
    {
        pizzaSizeLabel->setStyleSheet("QLabel { Font: 10pt ; color : black }");
    }

    if(customerName->text().length() >= 4 && customerPhone->text().length() >= 10
        && customerAddress->text().length() >= 6
        && customerCity->text().length() >= 4 && customerPCode->text().length() >= 4
        && tempList.length() <= 3 && pizzaChoice != nullptr)
    {

        QString result;
        result.append("Order Summary: \n");
        result.append("Customer Name          : " + customerName->text() + '\n');
        result.append("Customer Phone          : " + customerPhone->text() + '\n');
        result.append("Customer Address       : " + customerAddress->text() + '\n');
        if(customerAp)
             result.append("Customer Apartment  : " + customerAp->text() + '\n');
        result.append("Customer City              : " + customerCity->text() + '\n');
        result.append("Customer PostalCode : " + customerPCode->text() + '\n');
        result.append("Pizza Size                       : " + pizzaChoice + '\n');
        result.append("\nPizza Toppings : \n");
        for(QListWidgetItem* wi:tempList){
            result.append(" ->" + wi->text()+'\n');
        }
        orderLayout->setText(result);

        orderLayout->exec();

    }

}
