// Copyright 2020 <github.com/razaqq>

#include "Client/StatsParser.hpp"
#include "Client/StringTable.hpp"

#include "Gui/StatsWidget/StatsTeamFooter.hpp"

#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include <vector>


using namespace PotatoAlert::Core;
using PotatoAlert::Gui::StatsTeamFooter;

StatsTeamFooter::StatsTeamFooter(QWidget* parent) : QWidget(parent)
{
	this->Init();
}

void StatsTeamFooter::Init()
{
	auto layout = new QHBoxLayout;
	layout->setContentsMargins(10, 0, 10, 0);
	layout->setSpacing(10);

	const QFont labelFont = QFont("Segoe UI", 10, QFont::Bold);

	// left side
	auto leftWidget = new QWidget;
	auto leftLayout = new QHBoxLayout;
	leftLayout->setContentsMargins(10, 0, 10, 0);
	leftLayout->setSpacing(20);

	// right side
	auto rightWidget = new QWidget;
	auto rightLayout = new QHBoxLayout;
	rightLayout->setContentsMargins(10, 0, 10, 0);
	rightLayout->setSpacing(20);

	// set font on all labels
	std::vector<std::vector<QLabel*>> labels{
		std::vector<QLabel*>{ this->m_team1WrLabel, this->m_team1Wr, this->m_team1DmgLabel, this->m_team1Dmg, this->m_team1Tag, this->m_team1Name, this->m_team1RegionLabel, this->m_team1Region },
		std::vector<QLabel*>{ this->m_team2WrLabel, this->m_team2Wr, this->m_team2DmgLabel, this->m_team2Dmg, this->m_team2Tag, this->m_team2Name, this->m_team2RegionLabel, this->m_team2Region }
	};
	for (auto& side : labels)
		for (auto& label : side)
			label->setFont(labelFont);

	// add labels
	for (size_t side = 0; side < 2; side++)
	{
		for (size_t element = 0; element < 4; element++)
		{
			auto w = new QWidget;
			auto l = new QHBoxLayout;
			l->setContentsMargins(0, 0, 0, 0);
			l->setSpacing(0);

			l->addWidget(labels[side][2*element], 0, Qt::AlignRight);
			l->addWidget(labels[side][2*element+1], 0, Qt::AlignRight);

			w->setLayout(l);

			if (side == 0)
			{
				leftLayout->addWidget(w);
				if (element == 1 || element == 2)
					leftLayout->addStretch();
			}
			else
			{
				rightLayout->addWidget(w);
				if (element == 1 || element == 2)
					rightLayout->addStretch();
			}
		}
	}

	this->m_team1RegionLabel->setVisible(false);
	this->m_team2RegionLabel->setVisible(false);

	leftWidget->setLayout(leftLayout);
	rightWidget->setLayout(rightLayout);
	layout->addWidget(leftWidget);
	layout->addWidget(rightWidget);
	this->setLayout(layout);
}

void StatsTeamFooter::Update(const MatchType& match) const
{
	// set average stats per team
	match.Team1.Winrate.UpdateLabel(this->m_team1Wr);
	match.Team1.AvgDmg.UpdateLabel(this->m_team1Dmg);
	match.Team2.Winrate.UpdateLabel(this->m_team2Wr);
	match.Team2.AvgDmg.UpdateLabel(this->m_team2Dmg);

	// set clan battle stuff
	bool show1 = match.Team1.Clan.Show;
	if (show1)
	{
		match.Team1.Clan.Tag.UpdateLabel(this->m_team1Tag);
		match.Team1.Clan.Name.UpdateLabel(this->m_team1Name);
		match.Team1.Clan.Region.UpdateLabel(this->m_team1Region);
	}
	this->m_team1Tag->setVisible(show1);
	this->m_team1Name->setVisible(show1);
	this->m_team1Region->setVisible(show1);
	this->m_team1RegionLabel->setVisible(show1);

	bool show2 = match.Team1.Clan.Show;
	if (show2)
	{
		match.Team2.Clan.Tag.UpdateLabel(this->m_team2Tag);
		match.Team2.Clan.Name.UpdateLabel(this->m_team2Name);
		match.Team2.Clan.Region.UpdateLabel(this->m_team2Region);
	}
	this->m_team2Tag->setVisible(show2);
	this->m_team2Name->setVisible(show2);
	this->m_team2Region->setVisible(show2);
	this->m_team2RegionLabel->setVisible(show2);
}

void StatsTeamFooter::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->m_team1WrLabel->setText(GetString(StringTable::Keys::LABEL_WINRATE));
		this->m_team1DmgLabel->setText(GetString(StringTable::Keys::LABEL_DAMAGE));
		this->m_team1RegionLabel->setText(GetString(StringTable::Keys::LABEL_REGION));
		this->m_team2WrLabel->setText(GetString(StringTable::Keys::LABEL_WINRATE));
		this->m_team2DmgLabel->setText(GetString(StringTable::Keys::LABEL_DAMAGE));
		this->m_team2RegionLabel->setText(GetString(StringTable::Keys::LABEL_REGION));
	}
	else
	{
		QWidget::changeEvent(event);
	}
}