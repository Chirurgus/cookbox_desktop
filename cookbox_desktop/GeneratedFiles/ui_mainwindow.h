/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QTableView *list_tableView;
    QHBoxLayout *recipe_horizontalLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *add_recipe_Button;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QTableView *recipe_tableView;
    QHBoxLayout *recipe_horizontalLayout;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *recipe_Button;
    QTableView *ingredients_tableView;
    QHBoxLayout *ingredient_horizontalLayout;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_9;
    QTableView *instructions_tableView;
    QHBoxLayout *instruction_horizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_8;
    QTableView *comments_tableView;
    QHBoxLayout *comment_horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1052, 850);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 961, 781));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        list_tableView = new QTableView(horizontalLayoutWidget);
        list_tableView->setObjectName(QStringLiteral("list_tableView"));

        verticalLayout_3->addWidget(list_tableView);

        recipe_horizontalLayout_3 = new QHBoxLayout();
        recipe_horizontalLayout_3->setSpacing(6);
        recipe_horizontalLayout_3->setObjectName(QStringLiteral("recipe_horizontalLayout_3"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipe_horizontalLayout_3->addItem(horizontalSpacer_12);

        add_recipe_Button = new QPushButton(horizontalLayoutWidget);
        add_recipe_Button->setObjectName(QStringLiteral("add_recipe_Button"));

        recipe_horizontalLayout_3->addWidget(add_recipe_Button);


        verticalLayout_3->addLayout(recipe_horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_3);

        line = new QFrame(horizontalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        recipe_tableView = new QTableView(horizontalLayoutWidget);
        recipe_tableView->setObjectName(QStringLiteral("recipe_tableView"));

        verticalLayout->addWidget(recipe_tableView);

        recipe_horizontalLayout = new QHBoxLayout();
        recipe_horizontalLayout->setSpacing(6);
        recipe_horizontalLayout->setObjectName(QStringLiteral("recipe_horizontalLayout"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipe_horizontalLayout->addItem(horizontalSpacer_10);

        recipe_Button = new QPushButton(horizontalLayoutWidget);
        recipe_Button->setObjectName(QStringLiteral("recipe_Button"));

        recipe_horizontalLayout->addWidget(recipe_Button);


        verticalLayout->addLayout(recipe_horizontalLayout);

        ingredients_tableView = new QTableView(horizontalLayoutWidget);
        ingredients_tableView->setObjectName(QStringLiteral("ingredients_tableView"));

        verticalLayout->addWidget(ingredients_tableView);

        ingredient_horizontalLayout = new QHBoxLayout();
        ingredient_horizontalLayout->setSpacing(6);
        ingredient_horizontalLayout->setObjectName(QStringLiteral("ingredient_horizontalLayout"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        ingredient_horizontalLayout->addItem(horizontalSpacer_9);

        pushButton_9 = new QPushButton(horizontalLayoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        ingredient_horizontalLayout->addWidget(pushButton_9);


        verticalLayout->addLayout(ingredient_horizontalLayout);

        instructions_tableView = new QTableView(horizontalLayoutWidget);
        instructions_tableView->setObjectName(QStringLiteral("instructions_tableView"));

        verticalLayout->addWidget(instructions_tableView);

        instruction_horizontalLayout = new QHBoxLayout();
        instruction_horizontalLayout->setSpacing(6);
        instruction_horizontalLayout->setObjectName(QStringLiteral("instruction_horizontalLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        instruction_horizontalLayout->addItem(horizontalSpacer_8);

        pushButton_8 = new QPushButton(horizontalLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        instruction_horizontalLayout->addWidget(pushButton_8);


        verticalLayout->addLayout(instruction_horizontalLayout);

        comments_tableView = new QTableView(horizontalLayoutWidget);
        comments_tableView->setObjectName(QStringLiteral("comments_tableView"));

        verticalLayout->addWidget(comments_tableView);

        comment_horizontalLayout = new QHBoxLayout();
        comment_horizontalLayout->setSpacing(6);
        comment_horizontalLayout->setObjectName(QStringLiteral("comment_horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        comment_horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        comment_horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(comment_horizontalLayout);


        horizontalLayout->addLayout(verticalLayout);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1052, 21));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        add_recipe_Button->setText(QApplication::translate("MainWindowClass", "Add Recipe", nullptr));
        recipe_Button->setText(QApplication::translate("MainWindowClass", "Add Recipe", nullptr));
        pushButton_9->setText(QApplication::translate("MainWindowClass", "Add Ingredient", nullptr));
        pushButton_8->setText(QApplication::translate("MainWindowClass", "Add Instruction", nullptr));
        pushButton->setText(QApplication::translate("MainWindowClass", "Add Comment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
