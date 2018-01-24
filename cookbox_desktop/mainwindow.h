#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include <QSqlRelationalTableModel>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~MainWindow();

protected slots:
	void onRecipeSelected(const QModelIndex &current, const QModelIndex &previous);
	void onAddRecipe();
	void onAddIngredient();
	void onAddInstruction();
	void onAddComment();

private:
	Ui::MainWindowClass ui;
	
	int _selected_id {-1};
	QSqlDatabase _db;
	QSqlTableModel* _list_model {nullptr};
	QSqlTableModel* _recipe_model {nullptr};
	QSqlRelationalTableModel* _ingredients_model {nullptr};
	QSqlTableModel* _instructions_model {nullptr};
	QSqlTableModel* _comments_model {nullptr};
};
