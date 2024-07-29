#include "runtime.hpp"

std::vector<Connection::pointer> Runtime::GetTopicSubscribers(const Topic& topic)
{
	auto it = subscribers_.find(topic);
	if (it == subscribers_.end()) {
		return {};
	}

	return it->second;
}

bool Runtime::AddSubscribeToTopic(const Topic& topic, const std::shared_ptr<Connection>& connection)
{
	auto it = subscribers_.find(topic);
	if (it != subscribers_.end()) {
		it->second.push_back(connection);
		return true;
	}

	auto res = subscribers_.emplace(topic,connection);
	return res.second;
}

bool Runtime::DeleteSubscriberFromTopic(const Topic& topic, const std::shared_ptr<Connection>& connection)
{
	auto it = subscribers_.find(topic);
	if (it != subscribers_.end()) {
		for (auto i = 0 ; i < it->second.size(); ++i)
		{
			auto conn = it->second[i];
			if (connection->GetClientId() == conn->GetClientId()) {
				it->second.erase(it->second.begin() + i);
				break;
			}
		}
	}
	return true;
}

bool Runtime::DeleteSubscriberFromAllTopic(const std::shared_ptr<Connection>& connection)
{
	for (auto& topicConVec : subscribers_)
	{
		// Must be while
		auto begin = topicConVec.second.begin();
		for (auto it = begin; it != topicConVec.second.end(); ++it)
		{
			if (connection->GetClientId() == topicConVec.second.at(std::distance(it, begin))->GetClientId())
			{
				topicConVec.second.erase(it);
				++it;
			}
		}
	}
}