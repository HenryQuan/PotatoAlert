// Copyright 2020 <github.com/razaqq>
#pragma once

#include <QDialog>
#include <QShowEvent>
#include <QWidget>


namespace PotatoAlert::Gui {

class FramelessDialog : public QDialog
{
public:
	explicit FramelessDialog(QWidget* parent = nullptr);
private:
	void showEvent(QShowEvent* event) override;
	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
};

}  // namespace PotatoAlert::Gui
