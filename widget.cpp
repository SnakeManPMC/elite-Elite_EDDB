#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	OpenCommoditiesFile();
	OpenSystemsFile();
	OpenStationsFile();
}

Widget::~Widget()
{
	delete ui;
}


void Widget::OpenCommoditiesFile()
{
	QString elite_path = "D://Warez//Elite.Dangerous//EDDB_JSON//";
	QStringList nameFilter("commodities.json");

	QFile file(elite_path + nameFilter[0]);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("Unable to open commodities.json file"),
		file.errorString());
		return;
	}

	QByteArray line = file.readAll();
	file.close();

	parseCommoditiesJSON(line);

//	Commodities.sort();

	ui->textEdit->append("Commodities: " + QString::number(Commodities.size()));
	//for (int cx = 0; cx < Commodities.size(); cx++) ui->textEdit->append(Commodities[cx]);
}


void Widget::OpenSystemsFile()
{
	QString elite_path = "D://Warez//Elite.Dangerous//EDDB_JSON//";
	QStringList nameFilter("systems.json");

	QFile file(elite_path + nameFilter[0]);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("Unable to open systems.json file"),
		file.errorString());
		return;
	}

	QByteArray line = file.readAll();
	file.close();

	parseSystemsJSON(line);

//	Systems.sort();

	ui->textEdit->append("Systems: " + QString::number(Systems.size()));
	// heh dont do this, over 21,000 systems! :)
	//for (int xx = 0; xx < Systems.size(); xx++) ui->textEdit->append(Systems[xx]);
}


void Widget::OpenStationsFile()
{
	QString elite_path = "D://Warez//Elite.Dangerous//EDDB_JSON//";
	QStringList nameFilter("temporary_example_stations.json");

	QFile file(elite_path + nameFilter[0]);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this, tr("Unable to open stations.json file"),
		file.errorString());
		return;
	}

	QByteArray line = file.readAll();
	file.close();

	parseStationsJSON(line);

//	Stations.sort();

	ui->textEdit->append("Stations: " + QString::number(Stations.size()));
	// dont do this, too much text ;)
	//for (int xc = 0; xc < Stations.size(); xc++) ui->textEdit->append(Stations[xc]);
}


void Widget::parseCommoditiesJSON(QByteArray line)
{
	QJsonDocument d = QJsonDocument::fromJson(line);
	//qDebug() << "isArray: " << d.isArray() << ", isEmpty: " << d.isEmpty() << ", isObject: " << d.isObject();

	QJsonArray jarr = d.array();
	//qDebug() << "jarr; " << jarr[0];
	//QJsonValue(object, QJsonObject({"average_price":255,"category":{"id":1,"name":"Chemicals"},"category_id":1,"id":1,"name":"Explosives"}) )
	//qDebug() << jarr.at(0);

	for (int i = 0; i < jarr.count(); i++)
	{
		QJsonObject obj = jarr[i].toObject();
		Commodities.push_back(obj.value(QString("name")).toString());
	}
}


void Widget::parseSystemsJSON(QByteArray line)
{
	QJsonDocument d = QJsonDocument::fromJson(line);
	//qDebug() << "isArray: " << d.isArray() << ", isEmpty: " << d.isEmpty() << ", isObject: " << d.isObject();

	QJsonArray jarr = d.array();
	//qDebug() << "jarr; " << jarr[0];
	//qDebug() << jarr.at(0);

	for (int i = 0; i < jarr.count(); i++)
	{
		QJsonObject obj = jarr[i].toObject();
		Systems.push_back(obj.value(QString("name")).toString());
	}
}


void Widget::parseStationsJSON(QByteArray line)
{
	QJsonDocument d = QJsonDocument::fromJson(line);
	//qDebug() << "isArray: " << d.isArray() << ", isEmpty: " << d.isEmpty() << ", isObject: " << d.isObject();

	QJsonArray jarr = d.array();
	//qDebug() << "jarr; " << jarr[0];
	//qDebug() << jarr.at(0);

	int cmdity_id,buyprice,sellprice;
	QString nameCommodity;

	for (int i = 0; i < jarr.count(); i++)
	{
		// object
		QJsonObject obj = jarr[i].toObject();
		Stations.push_back(obj.value(QString("name")).toString());

		// array of commodity market items
		QJsonArray cm = obj.value(QString("listings")).toArray();
		//qDebug() << cm;
		//QJsonArray([{"buy_price":0,"collected_at":1420167760,"commodity_id":5,"demand":1137,"id":1,"sell_price":378,"station_id":1,"supply":0},
		for (int ci = 0; ci < cm.count(); ci++)
		{
			QJsonObject cmdity = cm[ci].toObject();
			//qDebug() << cmdity;
			cmdity_id = cmdity.value(QString("commodity_id")).toInt();
			buyprice = cmdity.value(QString("buy_price")).toInt();
			sellprice = cmdity.value(QString("sell_price")).toInt();
			//qDebug() << cmdity.value(QString("commodity_id")).toString();
			nameCommodity = Commodities.at(cmdity_id);
			ui->textEdit->append("Commodity_id: " + QString::number(cmdity_id) + ", Commodity: " + nameCommodity + ", sell_price: " + QString::number(sellprice) + ", buy_price: " + QString::number(buyprice));
		}
	}
}
