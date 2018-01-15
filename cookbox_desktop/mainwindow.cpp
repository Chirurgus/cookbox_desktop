#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, _db {QSqlDatabase::addDatabase("QSQLITE")}
	, _recipe_model {new QSqlRelationalTableModel{}} 
	, _ingredients_model {new QSqlRelationalTableModel{}} 
	, _instructions_model {new QSqlRelationalTableModel{}} 
	, _comments_model {new QSqlRelationalTableModel{}} 
{
	ui.setupUi(this);

	QString db_path {"C:/Documents/Projects/cookbox_desktop/cookbox_desktop/recipe.db"};
	_db.setDatabaseName(db_path);

	if (!_db.open()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot open db: " + _db.lastError().text());
		msg->exec();
		return;
	}

	_recipe_model->setTable("recipe");
	
	if (!_recipe_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _recipe_model->lastError().text());
		msg->exec();
		return;
	}

	ui.list_tableView->setModel(_recipe_model);
}

MainWindow::~MainWindow()
{
	//TODO!!!
	_db.close();
}
