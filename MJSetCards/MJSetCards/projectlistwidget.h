#ifndef PROJECTLISTWIDGET_H  
#define PROJECTLISTWIDGET_H  

#include <QtWidgets/QMainWindow>
#include <QtGui>  
#include <QListWidget>
#include <QApplication>

class ProjectListWidget : public QListWidget
{
	Q_OBJECT

public:
	ProjectListWidget(QWidget *parent = 0);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	void performDrag();

	QPoint startPos;
};

#endif // PROJECTLISTWIDGET_H 