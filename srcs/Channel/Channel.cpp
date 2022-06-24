/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:07:05 by jberredj          #+#    #+#             */
/*   Updated: 2022/06/24 17:04:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "typedefs.hpp"
#include <algorithm>
#include <ctime>

Channel::Channel(void):
_isAlive(true), _name("DEFAULT"), _userLimit(-1), _nbrMember(0), _modes(), _members(), _inviteOnly(false),
_inviteList(), _banList(), _userModes(), _topicSetAt(0), _topic()
{
}

Channel::Channel(const Channel &src):
_isAlive(src._isAlive), _name(src._name), _userLimit(src._userLimit), _nbrMember(src._nbrMember), _modes(src._modes),
_members(src._members), _inviteOnly(src._inviteOnly), _inviteList(src._inviteList), _banList(src._banList),
_userModes(src._userModes), _topicSetAt(src._topicSetAt), _topic(src._topic)
{
}

Channel::Channel(std::string name):
_isAlive(true), _name(name), _userLimit(-1), _nbrMember(0), _modes(), _members(), _inviteOnly(false), _inviteList(),
_banList(), _userModes(), _topicSetAt(0), _topic()
{
}

Channel::~Channel(void)
{
}

Channel	&Channel::operator=(const Channel &rhs)
{
	if (this != &rhs)
	{
		_isAlive = rhs._isAlive;
		_name = rhs._name;
		_userLimit = rhs._userLimit;
		_nbrMember = rhs._nbrMember;
		_modes = rhs._modes;
		_members = rhs._members;
		_inviteOnly = rhs._inviteOnly;
		_inviteList = rhs._inviteList;
		_banList = rhs._banList;
		_userModes = rhs._userModes;
		_topicSetAt = rhs._topicSetAt;
		_topic = rhs._topic;
	}
	return *this;
}

bool	Channel::setUserLimit(int limit)
{
	if (limit < 0)
		return false;
	_userLimit = limit;
	return true;
}
bool	Channel::setUserMode(std::string mode, User* user)
{
	if (!user)
		return false;
	std::map<User*, std::string>::iterator it;
	for (it = _userModes.begin(); it != _userModes.end(); it++)
		if ((*it).first == user)
			break;
	if (it == _userModes.end())
		return false;
	(*it).second = mode;
	//Need to check the mode that is added to ban/unban invite/uninvite user
	return true;

}

// void	Channel::setChannelModes(std::string modes) {
// 	_modes = modes;
// }

bool	Channel::setTopic(std::string topic) {
	if (topic.empty())
		_topicSetAt = 0;
	else
		_topicSetAt = std::time(ft::null_ptr);
	_topic = topic;
	return _topicSetAt;
}

bool	Channel::addUser(User *user)
{
	if (!user)
		return false;
	if (_nbrMember == _userLimit)
		return false;
	if (isBanned(user))
		return false;
	if (_inviteOnly && !isInvited(user))
		return false;
	_members.push_back(user);
	user->addChannelToUser(this);
	_userModes.insert(std::make_pair(user, ""));
	if (!_nbrMember)
		setUserMode("o", user);
	_nbrMember++;
	return true;
}

bool	Channel::removeUser(User *user)
{
	if (!user)
		return false;
	std::vector<User*>::iterator it = std::find(_members.begin(), _members.end(), user);
	if (it == _members.end())
		return false;
	_members.erase(it);
	_userModes.erase(user);
	user->removeChannelFromUser(this);
	_nbrMember--;
	if (!_nbrMember)
		_isAlive = false;
	return true;
}

void	Channel::broadcastMessage(std::string message, User *sender)
{
	for (std::vector<User*>::iterator it = _members.begin(); it != _members.end(); it++)
		if ((*it) != sender)
			(*it)->addReply(message);
}

bool	Channel::isAlive(void) const {return _isAlive;}

std::string	Channel::getName(void) const {return _name;}
int			Channel::getUserLimit(void) const {return _userLimit;}
std::string	Channel::getUserMode(User* user)
{
	std::map<User*, std::string>::iterator it;
	for (it = _userModes.begin(); it != _userModes.end(); it++)
		if ((*it).first == user)
			break;
	if (it == _userModes.end())
		return "";
	return _userModes[user];
}
ChannelMode	Channel::getChannelMode(void) const {return _modes;}

bool	Channel::isBanned(User *user)
{
	std::vector<User*>::iterator it = find(_banList.begin(), _banList.end(), user);
	if (it != _banList.end())
		return true;
	return false;
}

std::string	Channel::getTopic(void) const {return _topic;}

void	Channel::setInvite(bool invite) {_inviteOnly = invite;}
bool	Channel::getInvite(void) const {return _inviteOnly;}

bool	Channel::isInvited(User* user)
{
	std::vector<User*>::iterator it = find(_inviteList.begin(), _inviteList.end(), user);
	if (it != _inviteList.end())
		return true;
	return false;
}

bool	Channel::isOperator(User* user)
{
	if (!isMember(user))
		return false;
	std::string	userMode = getUserMode(user);
	if (userMode.find('o') != userMode.npos)
		return true;
	return false;
}

bool	Channel::isMember(User*	user) {return std::find(_members.begin(), _members.end(), user) != _members.end();}

bool	Channel::hasTopic(void) {return _topicSetAt;}


std::vector<User*>	Channel::getMembers(void) const {return _members;}

bool	Channel::_banUser(User* user)
{
	if (isBanned(user))
		return false;
	_banList.push_back(user);
	return true;
}

bool	Channel::_unbanUser(User* user)
{
	if (!isBanned(user))
		return false;
	_banList.erase(find(_banList.begin(), _banList.end(), user));
	return true;
}
bool	Channel::_inviteUser(User* user)
{
	if (isInvited(user))
		return false;
	_inviteList.push_back(user);
	return true;
}
bool	Channel::_revokeInviteUser(User* user)
{
	if (!isInvited(user))
		return false;
	_inviteList.erase(find(_inviteList.begin(), _inviteList.end(), user));
	return true;
}
