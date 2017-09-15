/********************************************************************************
** Form generated from reading UI file 'SocialNetworks.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKS_H
#define UI_SOCIALNETWORKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworksClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SocialNetworksClass)
    {
        if (SocialNetworksClass->objectName().isEmpty())
            SocialNetworksClass->setObjectName(QStringLiteral("SocialNetworksClass"));
        SocialNetworksClass->resize(600, 400);
        menuBar = new QMenuBar(SocialNetworksClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SocialNetworksClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SocialNetworksClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SocialNetworksClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SocialNetworksClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SocialNetworksClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SocialNetworksClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SocialNetworksClass->setStatusBar(statusBar);

        retranslateUi(SocialNetworksClass);

        QMetaObject::connectSlotsByName(SocialNetworksClass);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworksClass)
    {
        SocialNetworksClass->setWindowTitle(QApplication::translate("SocialNetworksClass", "SocialNetworks", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworksClass: public Ui_SocialNetworksClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKS_H
