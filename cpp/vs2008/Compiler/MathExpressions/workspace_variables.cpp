#include "workspace_variables.h"

WorkspaceVariables::WorkspaceVariables(void)
{
}

WorkspaceVariables::~WorkspaceVariables(void)
{
}

void WorkspaceVariables::DictInsert(const std::string &word, int val)
{
	this->insert(std::pair<std::string, int>(word, val));
}

void WorkspaceVariables::DictUpdate(const std::string &word, int val)
{
	(*this)[word] = val;
}

boost::optional<int> WorkspaceVariables::DictFind(const std::string &word) const
{
	std::map<std::string, int>::const_iterator wordCard = this->find(word);
	if (wordCard == this->end())
	{
		return boost::none;
	}
	else
	{
		return wordCard->second;
	}
}
