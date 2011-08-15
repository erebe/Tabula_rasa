/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Aug 15 03:44:59 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Ouvrir;
    QAction *actionMode_Insertion;
    QAction *actionMode_Edition;
    QAction *actionEnregistrer;
    QAction *actionIteration;
    QAction *actionCondition;
    QAction *actionAction;
    QAction *actionProcedure;
    QAction *actionConditionMultiple;
    QAction *actionRoi;
    QAction *actionEnregistrer_vers_une_image;
    QAction *actionEnregistrer_vers_XML;
    QAction *actionA_propos_de_Tabula_Rasa;
    QAction *actionSortie;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu_Fichier;
    QMenu *menuEdition;
    QMenu *menuG_n_rer;
    QMenu *menuA_propos;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(938, 543);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action_Ouvrir = new QAction(MainWindow);
        action_Ouvrir->setObjectName(QString::fromUtf8("action_Ouvrir"));
        actionMode_Insertion = new QAction(MainWindow);
        actionMode_Insertion->setObjectName(QString::fromUtf8("actionMode_Insertion"));
        actionMode_Insertion->setCheckable(true);
        actionMode_Insertion->setChecked(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icones/pointer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMode_Insertion->setIcon(icon);
        actionMode_Edition = new QAction(MainWindow);
        actionMode_Edition->setObjectName(QString::fromUtf8("actionMode_Edition"));
        actionMode_Edition->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icones/linepointer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMode_Edition->setIcon(icon1);
        actionEnregistrer = new QAction(MainWindow);
        actionEnregistrer->setObjectName(QString::fromUtf8("actionEnregistrer"));
        actionIteration = new QAction(MainWindow);
        actionIteration->setObjectName(QString::fromUtf8("actionIteration"));
        actionIteration->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icones/vignette_boucle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIteration->setIcon(icon2);
        actionCondition = new QAction(MainWindow);
        actionCondition->setObjectName(QString::fromUtf8("actionCondition"));
        actionCondition->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icones/vignette_condition.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCondition->setIcon(icon3);
        actionAction = new QAction(MainWindow);
        actionAction->setObjectName(QString::fromUtf8("actionAction"));
        actionAction->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icones/vignette_action.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAction->setIcon(icon4);
        actionProcedure = new QAction(MainWindow);
        actionProcedure->setObjectName(QString::fromUtf8("actionProcedure"));
        actionProcedure->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icones/vignette_procedure.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProcedure->setIcon(icon5);
        actionConditionMultiple = new QAction(MainWindow);
        actionConditionMultiple->setObjectName(QString::fromUtf8("actionConditionMultiple"));
        actionConditionMultiple->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icones/vignette_conditionMultiple.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConditionMultiple->setIcon(icon6);
        actionRoi = new QAction(MainWindow);
        actionRoi->setObjectName(QString::fromUtf8("actionRoi"));
        actionRoi->setCheckable(true);
        actionRoi->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icones/vignette_roi.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRoi->setIcon(icon7);
        actionEnregistrer_vers_une_image = new QAction(MainWindow);
        actionEnregistrer_vers_une_image->setObjectName(QString::fromUtf8("actionEnregistrer_vers_une_image"));
        actionEnregistrer_vers_XML = new QAction(MainWindow);
        actionEnregistrer_vers_XML->setObjectName(QString::fromUtf8("actionEnregistrer_vers_XML"));
        actionA_propos_de_Tabula_Rasa = new QAction(MainWindow);
        actionA_propos_de_Tabula_Rasa->setObjectName(QString::fromUtf8("actionA_propos_de_Tabula_Rasa"));
        actionSortie = new QAction(MainWindow);
        actionSortie->setObjectName(QString::fromUtf8("actionSortie"));
        actionSortie->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icones/vignette_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSortie->setIcon(icon8);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);

        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 938, 26));
        menu_Fichier = new QMenu(menuBar);
        menu_Fichier->setObjectName(QString::fromUtf8("menu_Fichier"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuG_n_rer = new QMenu(menuBar);
        menuG_n_rer->setObjectName(QString::fromUtf8("menuG_n_rer"));
        menuA_propos = new QMenu(menuBar);
        menuA_propos->setObjectName(QString::fromUtf8("menuA_propos"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menuBar->addAction(menu_Fichier->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuG_n_rer->menuAction());
        menuBar->addAction(menuA_propos->menuAction());
        menu_Fichier->addAction(action_Ouvrir);
        menu_Fichier->addAction(actionEnregistrer_vers_une_image);
        menu_Fichier->addAction(actionEnregistrer_vers_XML);
        menuA_propos->addAction(actionA_propos_de_Tabula_Rasa);
        mainToolBar->addAction(action_Ouvrir);
        mainToolBar->addAction(actionEnregistrer);
        toolBar->addAction(actionMode_Insertion);
        toolBar->addAction(actionMode_Edition);
        toolBar->addAction(actionRoi);
        toolBar->addSeparator();
        toolBar->addAction(actionAction);
        toolBar->addAction(actionProcedure);
        toolBar->addAction(actionSortie);
        toolBar->addSeparator();
        toolBar->addAction(actionIteration);
        toolBar->addAction(actionCondition);
        toolBar->addAction(actionConditionMultiple);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Ouvrir->setText(QApplication::translate("MainWindow", "&Ouvrir un XML", 0, QApplication::UnicodeUTF8));
        actionMode_Insertion->setText(QApplication::translate("MainWindow", "Mode &Insertion", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMode_Insertion->setToolTip(QApplication::translate("MainWindow", "Permet de d\303\251placer les \303\251l\303\251ments", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMode_Edition->setText(QApplication::translate("MainWindow", "Mode &Edition", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMode_Edition->setToolTip(QApplication::translate("MainWindow", "Permet de cr\303\251er une hi\303\251rarchie entre les \303\251l\303\251ments", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionEnregistrer->setText(QApplication::translate("MainWindow", "Enregistrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEnregistrer->setToolTip(QApplication::translate("MainWindow", "Permet d'enregistrer vers une Image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionIteration->setText(QApplication::translate("MainWindow", "It\303\251ration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionIteration->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer une it\303\251ration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCondition->setText(QApplication::translate("MainWindow", "condition", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCondition->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer une condition", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAction->setText(QApplication::translate("MainWindow", "Action", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAction->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer une action", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionProcedure->setText(QApplication::translate("MainWindow", "procedure", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionProcedure->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer un appel de procedure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionConditionMultiple->setText(QApplication::translate("MainWindow", "ConditionMultiple", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionConditionMultiple->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer une condition multiple", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRoi->setText(QApplication::translate("MainWindow", "Roi", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRoi->setToolTip(QApplication::translate("MainWindow", "Un roi pour les gouverner tous", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionEnregistrer_vers_une_image->setText(QApplication::translate("MainWindow", "Enregistrer vers une image", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_vers_XML->setText(QApplication::translate("MainWindow", "Enregistrer vers XML", 0, QApplication::UnicodeUTF8));
        actionA_propos_de_Tabula_Rasa->setText(QApplication::translate("MainWindow", "A propos de Tabula Rasa", 0, QApplication::UnicodeUTF8));
        actionSortie->setText(QApplication::translate("MainWindow", "Sortie", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSortie->setToolTip(QApplication::translate("MainWindow", "Permet d'ins\303\251rer une action de sortie", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Algorithme", 0, QApplication::UnicodeUTF8));
        menu_Fichier->setTitle(QApplication::translate("MainWindow", "&Fichier", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edition", 0, QApplication::UnicodeUTF8));
        menuG_n_rer->setTitle(QApplication::translate("MainWindow", "G\303\251n\303\251rer", 0, QApplication::UnicodeUTF8));
        menuA_propos->setTitle(QApplication::translate("MainWindow", "Aide", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
