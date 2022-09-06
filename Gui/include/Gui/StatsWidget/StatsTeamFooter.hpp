// Copyright 2020 <github.com/razaqq>
#pragma once

#include "Client/StatsParser.hpp"

#include <QLabel>
#include <QWidget>


namespace PotatoAlert::Gui {

using Client::StatsParser::MatchType;

class StatsTeamFooter : public QWidget
{
public:
	explicit StatsTeamFooter(QWidget* parent = nullptr);
	void Update(const MatchType& match) const;
private:
	void Init();
	void changeEvent(QEvent* event) override;

	QLabel* m_team1WrLabel = new QLabel();
	QLabel* m_team1DmgLabel = new QLabel();
	QLabel* m_team2WrLabel = new QLabel();
	QLabel* m_team2DmgLabel = new QLabel();
	QLabel* m_team1RegionLabel = new QLabel();
	QLabel* m_team2RegionLabel = new QLabel();

	QLabel* m_team1Wr = new QLabel("0.0%");
	QLabel* m_team1Dmg = new QLabel("0");
	QLabel* m_team1Tag = new QLabel();
	QLabel* m_team1Name = new QLabel();
	QLabel* m_team1Region = new QLabel();

	QLabel* m_team2Wr = new QLabel("0.0%");
	QLabel* m_team2Dmg = new QLabel("0");
	QLabel* m_team2Tag = new QLabel();
	QLabel* m_team2Name = new QLabel();
	QLabel* m_team2Region = new QLabel();
};

}  // namespace PotatoAlert::Gui