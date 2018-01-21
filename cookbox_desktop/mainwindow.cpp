#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, _db {QSqlDatabase::addDatabase("QSQLITE")}
	, _list_model {new QSqlRelationalTableModel{}} 
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

	_list_model->setTable("recipe");
	_list_model->setHeaderData(0, Qt::Horizontal, "ID");

	if (!_list_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _list_model->lastError().text());
		msg->exec();
		return;
	}

	ui.list_tableView->setModel(_list_model);

	ui.list_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	QItemSelectionModel* selection_model {ui.list_tableView->selectionModel()};

	auto connection = QObject::connect(selection_model,
					 SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
					 this,
					 SLOT(onRecipeSelected(const QModelIndex &, const QModelIndex &))
	);
	if (!connection) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Could not set on Row selection listener");
		msg->exec();
		return;
	}

	QObject::connect(ui.add_recipe_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onAddRecipe())
	);
}

MainWindow::~MainWindow()
{
	//TODO!!!
	_db.close();
}

void MainWindow::onAddRecipe()
{
	_db.transaction();
	QSqlQuery* q{new QSqlQuery{"insert into recipe default values",_db}};
	if (!q->exec()) {
		_db.rollback();
		return;
	}
	//int last_id {q->lastInsertId().toInt()};
	_db.commit();
}

void MainWindow::onRecipeSelected(const QModelIndex& current,const QModelIndex&)
{
	_selected_id = _list_model->record(current.row()).value("id").toInt();
	int id {_selected_id};

	_recipe_model->setTable("recipe");
	_recipe_model->setFilter("id = " + QString::number(id));

	if (!_recipe_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _recipe_model->lastError().text());
		msg->exec();
		return;
	}

	ui.recipe_tableView->setModel(_recipe_model);

	_ingredients_model->setTable("ingredient_list");
	_ingredients_model->setFilter("recipe_id = " + QString::number(id));

	_ingredients_model->setRelation(4, QSqlRelation {"recipe","id","name"});

	if (!_ingredients_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _ingredients_model->lastError().text());
		msg->exec();
		return;
	}

	ui.ingredients_tableView->setModel(_ingredients_model);

	_instructions_model->setTable("instruction_list");
	_instructions_model->setFilter("recipe_id = " + QString::number(id));

	if (!_instructions_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _ingredients_model->lastError().text());
		msg->exec();
		return;
	}
	
	ui.instructions_tableView->setModel(_instructions_model);

	_comments_model->setTable("comment_list");
	_comments_model->setFilter("recipe_id = " + QString::number(id));

	if (!_comments_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _comments_model->lastError().text());
		msg->exec();
		return;
	}

	ui.comments_tableView->setModel(_comments_model);
}