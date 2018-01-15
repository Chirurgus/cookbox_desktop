#include "mainwindow.h"
#include <QtWidgets>
#include <QtSql>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w {};
	w.show();
	/*
	QString db_path {"C:/Documents/Projects/cookbox_desktop/cookbox_desktop/recipe.db"};
	QSqlDatabase db {QSqlDatabase::addDatabase("QSQLITE")};
	db.setDatabaseName(db_path);
	db.open();


	if (db.open()) {
		QWidget* widget {new QWidget {}};
		QTableView t_widget {widget};

		QSqlQuery q {db};
		q.prepare("select * from recipe");

		QSqlQueryModel* model {new QSqlQueryModel {}};
		model->setQuery(q);
		t_widget.setModel(model);

		widget->show();
	}
	else {
		QLabel label {"Oh no, it didn't open! :("};
		label.show();
	}

	*/
	return a.exec();
}
