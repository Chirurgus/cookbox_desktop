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

private:
	Ui::MainWindowClass ui;
	
	QSqlDatabase _db;
	QSqlRelationalTableModel* _list_model {nullptr};
	QSqlRelationalTableModel* _recipe_model {nullptr};
	QSqlRelationalTableModel* _ingredients_model {nullptr};
	QSqlRelationalTableModel* _instructions_model {nullptr};
	QSqlRelationalTableModel* _comments_model {nullptr};
};
