// Copyright 2020 <github.com/razaqq>
#pragma once

#include "Client/Config.hpp"
#include "Client/Game.hpp"
#include "Client/ReplayAnalyzer.hpp"
#include "Client/ServiceProvider.hpp"
#include "Client/StatsParser.hpp"

#include "Core/DirectoryWatcher.hpp"

#include "ReplayParser/ReplayParser.hpp"

#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QNetworkReply>

#include <string>


using PotatoAlert::Client::Config;
using PotatoAlert::Client::Game::DirectoryStatus;
using PotatoAlert::Client::StatsParser::MatchContext;

namespace PotatoAlert::Client {

enum class Status
{
	Ready,
	Loading,
	Error
};

class PotatoClient : public QObject
{
	Q_OBJECT

private:
	const ServiceProvider& m_services;
	Core::DirectoryWatcher m_watcher;
	std::string m_lastArenaInfoHash;
	DirectoryStatus m_dirStatus;
	ReplayAnalyzer& m_replayAnalyzer;
	QNetworkAccessManager* m_networkAccessManager = new QNetworkAccessManager();

public:
	explicit PotatoClient(const ServiceProvider& serviceProvider)
		: m_services(serviceProvider), m_replayAnalyzer(serviceProvider.Get<ReplayAnalyzer>()) {}
	~PotatoClient() override = default;

	void Init();
	void TriggerRun();
	void ForceRun();
	DirectoryStatus CheckPath();

private:
	void OnFileChanged(const std::string& file);
	void SendRequest(std::string_view request, MatchContext&& matchContext);
	void HandleReply(QNetworkReply* reply, auto& successHandler);
	void LookupResult(const std::string& url, const std::string& authToken, const MatchContext& matchContext);

signals:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
	void MatchReady(const StatsParser::MatchType& match);
	void MatchHistoryChanged();
	void MatchSummaryChanged(uint32_t id, const ReplaySummary& summary);
	void StatusReady(Status status, std::string_view statusText);
#pragma clang diagnostic pop
};

}  // namespace PotatoAlert::Client
