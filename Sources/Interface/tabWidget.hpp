/*
 * =====================================================================================
 *
 *       Filename:  tabWidget.hpp
 *

 *        Version:  1.0
 *        Created:  16/08/2011 03:41:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef TABWIDGET_HPP
#define TABWIDGET_HPP
#include <QWidget>

class AlgorithmeScene;
class QGraphicsView;
class QHBoxLayout;
class QHBoxLayout;

class TabWidget : public QWidget {

     public:
          TabWidget();
          inline AlgorithmeScene* scene() const { return scene_; }
          inline QGraphicsView* view() const { return vue_; }

     private:
          AlgorithmeScene* scene_;
          QGraphicsView* vue_;
          QHBoxLayout* layout_;
};

#endif // TABWIDGET_HPP
