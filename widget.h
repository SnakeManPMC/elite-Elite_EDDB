#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private slots:
	void on_browseEDDBDir_clicked();

private:
	Ui::Widget *ui;
	void OpenCommoditiesFile();
	void OpenSystemsFile();
	void OpenStationsFile();
	void parseCommoditiesJSON(QByteArray line);
	void parseSystemsJSON(QByteArray line);
	void parseStationsJSON(QByteArray line);
	QStringList Systems;
	QStringList Stations;
	QStringList Commodities;
	QString eddbDir;
};

#endif // WIDGET_H
