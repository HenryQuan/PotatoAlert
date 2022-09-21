// Copyright 2022 <github.com/razaqq>

#include "Client/StringTable.hpp"

#include "Gui/QuestionDialog.hpp"

#include <QApplication>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>


using namespace PotatoAlert::Client::StringTable;
using PotatoAlert::Gui::QuestionAnswer;
using PotatoAlert::Gui::QuestionDialog;

QuestionDialog::QuestionDialog(int language, QWidget* parent, const QString& questionText) : FramelessDialog(parent)
{
	auto buttonBox = new QDialogButtonBox();
	buttonBox->setAttribute(Qt::WA_TranslucentBackground);

	auto yesButton = new QPushButton(GetStringView(language, StringTableKey::YES).data(), buttonBox);
	yesButton->setObjectName("confirmButton");

	auto noButton = new QPushButton(GetStringView(language, StringTableKey::NO).data(), buttonBox);
	noButton->setObjectName("confirmButton");

	connect(yesButton, &QPushButton::clicked, [this]([[maybe_unused]] bool checked)
	{
		done(Accepted);
	});
	connect(noButton, &QPushButton::clicked, [this]([[maybe_unused]] bool checked)
	{
		done(Rejected);
	});

	buttonBox->addButton(yesButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(noButton, QDialogButtonBox::ActionRole);
	buttonBox->setCenterButtons(true);

	auto textField = new QLabel(questionText);
	textField->setWordWrap(true);

	auto icon = new QIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion));
	auto iconLabel = new QLabel();
	iconLabel->setPixmap(icon->pixmap(100, 100));

	auto layout = new QVBoxLayout();
	layout->setContentsMargins(15, 15, 15, 10);

	auto textLayout = new QHBoxLayout();
	textLayout->addWidget(iconLabel, 0, Qt::AlignRight);
	textLayout->addWidget(textField, 0, Qt::AlignLeft);

	layout->addLayout(textLayout);
	layout->addWidget(buttonBox, 0, Qt::AlignHCenter);

	setLayout(layout);
}

QuestionAnswer QuestionDialog::Run()
{
	// just cast return value to bool
	show();
	return exec() ? QuestionAnswer::Yes : QuestionAnswer::No;
}
