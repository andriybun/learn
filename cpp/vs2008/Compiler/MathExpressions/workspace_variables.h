#pragma once

#include <map>
#include <string>
#include <boost/optional.hpp>

class WorkspaceVariables : std::map<std::string, int>
{
public:
	WorkspaceVariables(void);
	~WorkspaceVariables(void);
	void DictInsert(const std::string &word, int val);
	void DictUpdate(const std::string &word, int val);
	boost::optional<int> DictFind(const std::string &word) const;

};
