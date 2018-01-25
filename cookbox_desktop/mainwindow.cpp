#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QTableView>
#include <QKeyEvent>
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

	_list_model->setEditStrategy(QSqlTableModel::OnFieldChange);
	_list_model->setTable("recipe");
	_list_model->setHeaderData(1, Qt::Horizontal, "Name");
	_list_model->setHeaderData(2, Qt::Horizontal, "Description");

	if (!_list_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _list_model->lastError().text());
		msg->exec();
		return;
	}

	ui.list_tableView->setModel(_list_model);
	ui.list_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.list_tableView->setColumnHidden(6, true);
	ui.list_tableView->setColumnHidden(5, true);
	ui.list_tableView->setColumnHidden(4, true);
	ui.list_tableView->setColumnHidden(3, true);
	ui.list_tableView->setColumnHidden(0, true);


	//Hide row number column
	ui.list_tableView->verticalHeader()->setVisible(false);
	ui.list_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	QItemSelectionModel* selection_model {ui.list_tableView->selectionModel()};

	//Hide row number column
	ui.recipe_tableView->verticalHeader()->setVisible(false);
	ui.recipe_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	ui.recipe_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//Hide row number column
	ui.ingredients_tableView->verticalHeader()->setVisible(false);
	ui.ingredients_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	ui.ingredients_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//Hide row number column
	ui.instructions_tableView->verticalHeader()->setVisible(false);
	ui.instructions_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	ui.instructions_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//Hide row number column
	ui.comments_tableView->verticalHeader()->setVisible(false);
	ui.comments_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	ui.comments_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	QObject::connect(selection_model,
				 SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
				 this,
				 SLOT(onRecipeSelected(const QModelIndex &, const QModelIndex &))
	);
	QObject::connect(ui.add_recipe_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onAddRecipe())
	);
	QObject::connect(ui.add_ingredient_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onAddIngredient())
	);
	QObject::connect(ui.add_instruction_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onAddInstruction())
	);
	QObject::connect(ui.add_comment_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onAddComment())
	);
	QObject::connect(ui.add_recipe_Button_bis,
					 SIGNAL(released()),
					 this,
					 SLOT(onDeleteKeyPressed())
	);
	QObject::connect(ui.delete_recipe_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onDeleteRecipe())
	);
	QObject::connect(ui.delete_ingredient_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onDeleteIngredient())
	);
	QObject::connect(ui.delete_instruction_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onDeleteInstruction())
	);
	QObject::connect(ui.delete_comment_Button,
					 SIGNAL(released()),
					 this,
					 SLOT(onDeleteComment())
	);
}

MainWindow::~MainWindow()
{
	//TODO!!!
	_db.close();
}

bool MainWindow::eventFilter(QObject * watched, QEvent * event)
{
	if (event->type() == QEvent::KeyRelease) {
		QKeyEvent* key {static_cast<QKeyEvent*>(event)};
		if (key->key() == Qt::Key_Delete) {
			onDeleteKeyPressed();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return QMainWindow::eventFilter(watched, event);
	}
}

void MainWindow::onAddRecipe()
{
	bool ok;
	QString name{QInputDialog::getText(this, "Add recipe",
										"Give a new recipe a name.",
										QLineEdit::Normal, "Recipe name",
										&ok)};
	if (!ok) {
		return;
	}
	int row{_list_model->rowCount()};

	_list_model->database().transaction();

	_list_model->insertRow(row);
	_list_model->setData(_list_model->index(row, 1), name);
	_list_model->setData(_list_model->index(row, 4), 1);

	if (_list_model->submitAll()) {
		_list_model->database().commit();
	}
	else {
		_list_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Could not add recipe."
			+ _list_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onAddIngredient()
{
	int row{_ingredients_model->rowCount()};

	_ingredients_model->database().transaction();

	_ingredients_model->insertRow(row);
	_ingredients_model->setData(_ingredients_model->index(row, 0), _selected_id);
	_ingredients_model->setData(_ingredients_model->index(row, 1), 1);
	_ingredients_model->setData(_ingredients_model->index(row, 2), "");

	if (_ingredients_model->submitAll()) {
		_ingredients_model->database().commit();
	}
	else {
		_ingredients_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Could not add ingredient."
			+ _ingredients_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onAddInstruction()
{
	bool ok;
	QString instruction {QInputDialog::getText(this, "Add an instruction",
										"Instruction:",
										QLineEdit::Normal, "",
										&ok)};
	if (!ok) {
		return;
	}
	int row{_instructions_model->rowCount()};

	_instructions_model->database().transaction();

	_instructions_model->insertRow(row);
	_instructions_model->setData(_instructions_model->index(row, 0), _selected_id);
	_instructions_model->setData(_instructions_model->index(row, 1), row-1);
	_instructions_model->setData(_instructions_model->index(row, 2), instruction);
	
	for (int i {0}; i <= row; ++i) {
		_instructions_model->setData(_instructions_model->index(i, 1), i);
	}

	if (_instructions_model->submitAll()) {
		_instructions_model->database().commit();
	}
	else {
		_instructions_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Couldn't add an instruciton"
			+ _instructions_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onAddComment()
{
	bool ok;
	QString comment {QInputDialog::getText(this, "Add a comment",
										"Comment",
										QLineEdit::Normal, "Comments",
										&ok)};
	if (!ok) {
		return;
	}
	int row{_comments_model->rowCount()};

	_comments_model->database().transaction();

	_comments_model->insertRow(row);
	_comments_model->setData(_comments_model->index(row, 0), _selected_id);
	_comments_model->setData(_comments_model->index(row, 1), comment);

	if (_comments_model->submitAll()) {
		_comments_model->database().commit();
	}
	else {
		_comments_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Couldn't add a comment: "
			+ _comments_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onDeleteRecipe()
{
	int row {ui.recipe_tableView->currentIndex().row()};
	
	QMessageBox* confirmation {new QMessageBox{}};
	confirmation->setText("Are you sure you want to delete a recipe?");
	confirmation->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	confirmation->setDefaultButton(QMessageBox::Cancel);
	int ret{confirmation->exec()};
	if (ret == QMessageBox::Cancel) {
		return;
	}

	/*
		TODO:	
	*/
}

void MainWindow::onDeleteIngredient()
{
	int row {ui.ingredients_tableView->currentIndex().row()};
	
	QMessageBox* confirmation {new QMessageBox{}};
	confirmation->setText("Are you sure you want to delete an ingredients?");
	confirmation->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	confirmation->setDefaultButton(QMessageBox::Cancel);
	int ret{confirmation->exec()};
	if (ret == QMessageBox::Cancel) {
		return;
	}

	_ingredients_model->database().transaction();
	
	_ingredients_model->removeRow(row);

	if (_ingredients_model->submitAll()) {
		_ingredients_model->database().commit();
	}
	else {
		_ingredients_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Couldn't delete an ingredients: "
			+ _ingredients_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onDeleteInstruction()
{
	 int row {ui.instructions_tableView->currentIndex().row()}; 
 
	QMessageBox* confirmation {new QMessageBox{}};
	confirmation->setText("Are you sure you want to delete a instruction?");
	confirmation->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	confirmation->setDefaultButton(QMessageBox::Cancel);
	int ret{confirmation->exec()};
	if (ret == QMessageBox::Cancel) {
		return;
	}

	_instructions_model->database().transaction();
	
	_instructions_model->removeRow(row);

	for (int i {row}; i < _instructions_model->rowCount(); ++i) {
		_instructions_model->setData(_instructions_model->index(i, 1), i);
	}

	if (_instructions_model->submitAll()) {
		_instructions_model->database().commit();
	}
	else {
		_instructions_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Couldn't delete an instruction: "
			+ _instructions_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onDeleteComment()
{
	int row {ui.comments_tableView->currentIndex().row()}; 
 
	QMessageBox* confirmation {new QMessageBox{}};
	confirmation->setText("Are you sure you want to delete a comment?");
	confirmation->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	confirmation->setDefaultButton(QMessageBox::Cancel);
	int ret{confirmation->exec()};
	if (ret == QMessageBox::Cancel) {
		return;
	}

	_comments_model->database().transaction();
	
	_comments_model->removeRow(row);

	if (_comments_model->submitAll()) {
		_comments_model->database().commit();
	}
	else {
		_comments_model->database().rollback();

		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Couldn't delete a comment: "
			+ _comments_model->lastError().text());
		msg->exec();
	}
}

void MainWindow::onDeleteKeyPressed()
{
	auto focused_w {QApplication::focusWidget()};
	QString message{"Nothing"};
	if (focused_w == ui.list_tableView) {
		message = "list";
	}
	else if (focused_w == ui.ingredients_tableView) {
		message = "ingredients";
	}
	else if (focused_w == ui.instructions_tableView) {
		message = "instrucions";
	}
	else if (focused_w == ui.comments_tableView) {
		message = "comments";
	}
	QMessageBox* msg {new QMessageBox {}};
	msg->setText(message);
	msg->exec();
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
	ui.recipe_tableView->setColumnHidden(0, true);

	_ingredients_model->setTable("ingredient_list");
	_ingredients_model->setFilter("recipe_id = " + QString::number(id));

	//_ingredients_model->setRelation(3, QSqlRelation {"recipe","id","name"});
	

	if (!_ingredients_model->select()) {
		QMessageBox* msg {new QMessageBox {}};
		msg->setText("Cannot prepare query: "
					 + _ingredients_model->lastError().text());
		msg->exec();
		return;
	}

	ui.ingredients_tableView->setModel(_ingredients_model);
	ui.ingredients_tableView->setColumnHidden(0, true);

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
	ui.instructions_tableView->setColumnHidden(0, true);
	ui.instructions_tableView->setColumnHidden(1, true);

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

	ui.comments_tableView->setColumnHidden(0, true);
}