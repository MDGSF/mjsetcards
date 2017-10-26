#include "projectlistwidget.h"  

ProjectListWidget::ProjectListWidget(QWidget *parent)
	: QListWidget(parent)
{
	setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		startPos = event->pos();
	QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - startPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void ProjectListWidget::performDrag()
{
	QListWidgetItem *item = currentItem();
	if (item == NULL) {
		return;
	}

	int iCurRow = currentRow();
	takeItem(iCurRow);

	QMimeData *mimeData = new QMimeData;
	mimeData->setText(QString::number((int)item));

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	if (drag->exec(Qt::MoveAction) != Qt::MoveAction)
	{
		insertItem(iCurRow, item);
	}
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
	ProjectListWidget *source =
		qobject_cast<ProjectListWidget *>(event->source());
	if (source == NULL)
	{
		return;
	}

	//if (source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	//}
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	ProjectListWidget *source =
		qobject_cast<ProjectListWidget *>(event->source());
	if (source == NULL)
	{
		return;
	}

	//if (source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	//}
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
	ProjectListWidget *source =
		qobject_cast<ProjectListWidget *>(event->source());
	if (source == NULL)
	{
		return;
	}

	//if (source != this) {

		QPoint oEndPos = event->pos();
		QListWidgetItem * pEndItem = itemAt(oEndPos);
		int iEndRow = row(pEndItem);
		if (iEndRow < 0)
		{
			iEndRow = count();
		}

		QListWidgetItem * pSourceItem = (QListWidgetItem *)event->mimeData()->text().toInt();
		insertItem(iEndRow, pSourceItem);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	//}
}

